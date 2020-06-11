# Copyright (C) 2020  GreenWaves Technologies, SAS

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import logging
import re

import numpy as np
from generation.generators.globals.global_names import BIASES, WEIGHTS
from graph.types import InputParameters, OutputParameters

LOG = logging.getLogger("nntool." + __name__)


def find_next_dim(shape, next_idx):
    for i in range(len(shape) - 1, -1, -1):
        if shape[i] != next_idx[i]:
            return i
    return None


def at_tensor_loader(filename):
    re_head = re.compile(
        r'^Node: (?P<node_name>[a-zA-Z_][a-zA-Z0-9_]*)'
        r', Argument: (?P<arg_name>[a-zA-Z_][a-zA-Z0-9_]*)'
        r', Dim: (?P<dims>\d+)'
        r', \[(?P<d0>\d+)\]\[(?P<d1>\d+)\]\[(?P<d2>\d+)\]\[(?P<d3>\d+)\]\[(?P<d4>\d+)\]'
        r' ItemSize: (?P<item_size>\d+)$')
    re_cont = re.compile(
        r'^D(?P<dim>\d+): (?P<dim_idx>\d+)$')
    re_last2 = re.compile(
        r'^D(?P<dim_pen>\d+): (?P<dim_pen_start>\d+)'
        r' - D(?P<dim_last>\d+):(?P<dim_last_start>\d+)\.\.(?P<dim_last_end>\d+)$')
    re_last1 = re.compile(
        r'^D(?P<dim_last>\d+):(?P<dim_last_start>\d+)\.\.(?P<dim_last_end>\d+)$')
    state = 'start'
    tensors = {}
    line_num = -1
    with open(filename, "r") as pfile:
        for line in pfile:
            line_num += 1
            if state == 'start':
                match = re_head.search(line)
                if not match:
                    continue
                header = match.group('node_name', 'arg_name', 'dims', 'd0',
                                     'd1', 'd2', 'd3', 'd4', 'item_size')
                shape = [int(i) for i in [header[3], header[4], header[5],
                                          header[6], header[7]]]
                dims = int(header[2])
                shape = shape[(5-dims):]
                next_idx = [-1] * dims
                node_name = header[0]
                node_tensors = tensors.get(node_name)
                if not node_tensors:
                    node_tensors = {}
                    tensors[node_name] = node_tensors
                arg_name = header[1]
                item_size = int(header[8])
                dims_read = 0
                value = []
                state = 'read_dims'
            elif state == 'read_dims' and dims >= 2 and (dims - dims_read) == 2:
                match = re_last2.search(line)
                if not match:
                    state = 'start'
                    node_tensors[arg_name] = '[%s] bad_tensor - expecting last dim' % line_num
                    LOG.warning(node_tensors[arg_name])
                    continue
                header = [int(elem) for elem in match.group('dim_pen', 'dim_pen_start', 'dim_last',
                                                            'dim_last_start', 'dim_last_end')]
                if header[0] != dims_read or header[2] != dims_read + 1:
                    node_tensors[arg_name] = 'bad_tensor - wrong dim' % line_num
                    LOG.warning(node_tensors[arg_name])
                    state = 'start'
                    continue
                next_idx[header[0]] = header[1] + 1
                next_idx[header[2]] = header[4]
                cur_block_len = header[4] - header[3]
                cur_block_read = 0
                state = 'read_data'
            elif state == 'read_dims' and dims == 1 and dims_read == 0:
                match = re_last1.search(line)
                if not match:
                    state = 'start'
                    node_tensors[arg_name] = '[%s] bad_tensor - expecting last dim' % line_num
                    LOG.warning(node_tensors[arg_name])
                    continue
                header = [int(elem) for elem in match.group(
                    'dim_last', 'dim_last_start', 'dim_last_end')]
                if header[0] != dims_read:
                    node_tensors[arg_name] = '[%s] bad_tensor - wrong dim' % line_num
                    LOG.warning(node_tensors[arg_name])
                    state = 'start'
                    continue
                next_idx[header[0]] = header[2]
                cur_block_len = header[2] - header[1]
                cur_block_read = 0
                state = 'read_data'
            elif state == 'read_dims':
                match = re_cont.search(line)
                if not match:
                    node_tensors[arg_name] = '[%s] bad_tensor - expecting dim' % line_num
                    LOG.warning(node_tensors[arg_name])
                    state = 'start'
                    continue
                header = [int(elem) for elem in match.group('dim', 'dim_idx')]
                if header[0] != dims_read:
                    node_tensors[arg_name] = '[%s] bad_tensor - wrong dim' % line_num
                    LOG.warning(node_tensors[arg_name])
                    state = 'start'
                    continue
                next_idx[header[0]] = header[1] + 1
                dims_read += 1
            elif state == 'read_data':
                read = 0
                try:
                    for i in line.split():
                        value.append(i)
                        read += 1
                except ValueError:
                    node_tensors[arg_name] = '[%s] bad_tensor - read error' % line_num
                    LOG.warning(node_tensors[arg_name])
                    state = 'start'
                    continue

                cur_block_read += read

                if cur_block_read == cur_block_len:
                    state = 'read_dims'
                    dims_read = find_next_dim(shape, next_idx)
                    if dims_read is None:
                        state = 'start'
                        if arg_name in node_tensors.keys():
                            node_tensors[arg_name] = np.concatenate((node_tensors[arg_name],
                                np.array(value, dtype=np.dtype('i'+str(item_size))).reshape(shape)), axis=0)
                        else:
                            node_tensors[arg_name] = np.array(
                                value, dtype=np.dtype('i'+str(item_size))).reshape(shape)
                    else:
                        state = 'read_dims'
                elif cur_block_read > cur_block_len:
                    node_tensors[arg_name] = '[%s] bad_tensor - too long' % line_num
                    LOG.warning(node_tensors[arg_name])
                    state = 'start'
                    continue
    return tensors

def at_map_tensors(G, tensors):
    re_snum = re.compile(
        r'^S(?P<step>\d+)_')
    steps = G.graph_state.steps
    result = [[None, None, None] for _ in steps]
    for cname, tset in tensors.items():
        match = re_snum.search(cname)
        if not match:
            raise ValueError("tensor name in unexpected format")
        step_idx = int(match.group('step'))
        node = steps[step_idx]['node']
        for tname, tensor in tset.items():
            tname = tname.lower()
            if tname.startswith('input'):
                for edge in G.in_edges(node.name):
                    if isinstance(edge.from_node, InputParameters):
                        result[edge.from_node.step_idx][0] = tensor.reshape(node.in_dims[0].shape)
                        break
            elif tname.startswith('output'):
                for edge in G.out_edges(node.name):
                    if isinstance(edge.to_node, OutputParameters):
                        result[edge.to_node.step_idx][0] = tensor.reshape(node.out_dims[0].shape)
                        break
                result[step_idx][0] = tensor.reshape(node.out_dims[0].shape)
            elif tname == "s%s_output"%step_idx:
                result[step_idx][0] = tensor.reshape(node.out_dims[0].shape)
            elif tname.endswith(WEIGHTS):
                result[step_idx][1] = tensor
            elif tname.endswith(BIASES):
                result[step_idx][2] = tensor
    return result

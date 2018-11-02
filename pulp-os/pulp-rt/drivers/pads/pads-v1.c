/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Authors: Germain Haugou, ETH (germain.haugou@iis.ee.ethz.ch)
 */


#include "rt/rt_api.h"

static char __rt_padframe_is_init;

__attribute__((weak)) unsigned int __rt_padframe_default[] = { 0x00055500, 0x00000000, 0x00054000, 0x00000000,};

__attribute__((weak)) unsigned int __rt_padframe_hyper[] = { 0x00055500, 0x0f000000, 0x003fffff, 0x00000000,};

__attribute__((weak)) unsigned int __rt_padframe_hyper_gpio[] = { 0x00055500, 0x0f154000, 0x003fffff, 0x00000000,};

__attribute__((weak)) rt_padframe_profile_t __rt_padframe_profiles[] = {
  { .name="default", .config=__rt_padframe_default },
  { .name="hyper", .config=__rt_padframe_hyper },
  { .name="hyper_gpio", .config=__rt_padframe_hyper_gpio },
};

__attribute__((weak)) int __rt_nb_profile = 3;

void __rt_padframe_init()
{
  if (!__rt_padframe_is_init)
  {
    rt_padframe_profile_t *profile = &__rt_padframe_profiles[0];
    unsigned int *config = profile->config;

    for (int i=0; i<ARCHI_APB_SOC_PADFUN_NB; i++)
    {
      rt_trace(RT_TRACE_INIT, "Initializing pads function (id: %d, config: 0x%x)\n", i, config[i]);
      hal_apb_soc_padfun_set(i, config[i]);
    }

    __rt_padframe_is_init = 1;
  }
}

static inline int __rt_pad_nb_profiles()
{
  return __rt_nb_profile;
}

rt_padframe_profile_t *rt_pad_profile_get(char *profile_string) {

  for (int i=0; i<__rt_pad_nb_profiles(); i++) {
    rt_padframe_profile_t *prof = &__rt_padframe_profiles[i];
    if (strcmp(profile_string, prof->name) == 0) return prof;
  }
  return NULL;
}

void rt_padframe_set(rt_padframe_profile_t *profile) {

    unsigned int *config = profile->config;

    for (int i=0; i<ARCHI_APB_SOC_PADFUN_NB; i++)
    {
      rt_trace(RT_TRACE_INIT, "Initializing pads function (id: %d, config: 0x%x)\n", i, config[i]);
      hal_apb_soc_padfun_set(i, config[i]);
    }

    __rt_padframe_is_init = 1;

}

RT_FC_BOOT_CODE void __attribute__((constructor)) __rt_padframe_constructor()
{
  __rt_padframe_is_init = 0;
}

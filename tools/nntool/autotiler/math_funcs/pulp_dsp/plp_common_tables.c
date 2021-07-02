/** ==========================================================================
 * @file     plp_common_tables.c
 * @brief    File containing common tables
 * @version  V0
 * @date     28. June 2020
 * =========================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PLP_COMMON_TABLES_H__
#define __PLP_COMMON_TABLES_H__

#include "plp_math_extract.h"

/**
  @par
  Example code for the generation of the floating-point sine table:
  <pre>
  tableSize = 512;
  for (n = 0; n < (tableSize + 1); n++)
  {
  sinTable[n] = sin(2*PI*n/tableSize);
  }</pre>
 @par
  where PI value is  3.14159265358979
 */

const float32_t sinTable_f32[FAST_MATH_TABLE_SIZE + 1] = {
    0.00000000f,  0.01227154f,  0.02454123f,  0.03680722f,  0.04906767f,  0.06132074f,
    0.07356456f,  0.08579731f,  0.09801714f,  0.11022221f,  0.12241068f,  0.13458071f,
    0.14673047f,  0.15885814f,  0.17096189f,  0.18303989f,  0.19509032f,  0.20711138f,
    0.21910124f,  0.23105811f,  0.24298018f,  0.25486566f,  0.26671276f,  0.27851969f,
    0.29028468f,  0.30200595f,  0.31368174f,  0.32531029f,  0.33688985f,  0.34841868f,
    0.35989504f,  0.37131719f,  0.38268343f,  0.39399204f,  0.40524131f,  0.41642956f,
    0.42755509f,  0.43861624f,  0.44961133f,  0.46053871f,  0.47139674f,  0.48218377f,
    0.49289819f,  0.50353838f,  0.51410274f,  0.52458968f,  0.53499762f,  0.54532499f,
    0.55557023f,  0.56573181f,  0.57580819f,  0.58579786f,  0.59569930f,  0.60551104f,
    0.61523159f,  0.62485949f,  0.63439328f,  0.64383154f,  0.65317284f,  0.66241578f,
    0.67155895f,  0.68060100f,  0.68954054f,  0.69837625f,  0.70710678f,  0.71573083f,
    0.72424708f,  0.73265427f,  0.74095113f,  0.74913639f,  0.75720885f,  0.76516727f,
    0.77301045f,  0.78073723f,  0.78834643f,  0.79583690f,  0.80320753f,  0.81045720f,
    0.81758481f,  0.82458930f,  0.83146961f,  0.83822471f,  0.84485357f,  0.85135519f,
    0.85772861f,  0.86397286f,  0.87008699f,  0.87607009f,  0.88192126f,  0.88763962f,
    0.89322430f,  0.89867447f,  0.90398929f,  0.90916798f,  0.91420976f,  0.91911385f,
    0.92387953f,  0.92850608f,  0.93299280f,  0.93733901f,  0.94154407f,  0.94560733f,
    0.94952818f,  0.95330604f,  0.95694034f,  0.96043052f,  0.96377607f,  0.96697647f,
    0.97003125f,  0.97293995f,  0.97570213f,  0.97831737f,  0.98078528f,  0.98310549f,
    0.98527764f,  0.98730142f,  0.98917651f,  0.99090264f,  0.99247953f,  0.99390697f,
    0.99518473f,  0.99631261f,  0.99729046f,  0.99811811f,  0.99879546f,  0.99932238f,
    0.99969882f,  0.99992470f,  1.00000000f,  0.99992470f,  0.99969882f,  0.99932238f,
    0.99879546f,  0.99811811f,  0.99729046f,  0.99631261f,  0.99518473f,  0.99390697f,
    0.99247953f,  0.99090264f,  0.98917651f,  0.98730142f,  0.98527764f,  0.98310549f,
    0.98078528f,  0.97831737f,  0.97570213f,  0.97293995f,  0.97003125f,  0.96697647f,
    0.96377607f,  0.96043052f,  0.95694034f,  0.95330604f,  0.94952818f,  0.94560733f,
    0.94154407f,  0.93733901f,  0.93299280f,  0.92850608f,  0.92387953f,  0.91911385f,
    0.91420976f,  0.90916798f,  0.90398929f,  0.89867447f,  0.89322430f,  0.88763962f,
    0.88192126f,  0.87607009f,  0.87008699f,  0.86397286f,  0.85772861f,  0.85135519f,
    0.84485357f,  0.83822471f,  0.83146961f,  0.82458930f,  0.81758481f,  0.81045720f,
    0.80320753f,  0.79583690f,  0.78834643f,  0.78073723f,  0.77301045f,  0.76516727f,
    0.75720885f,  0.74913639f,  0.74095113f,  0.73265427f,  0.72424708f,  0.71573083f,
    0.70710678f,  0.69837625f,  0.68954054f,  0.68060100f,  0.67155895f,  0.66241578f,
    0.65317284f,  0.64383154f,  0.63439328f,  0.62485949f,  0.61523159f,  0.60551104f,
    0.59569930f,  0.58579786f,  0.57580819f,  0.56573181f,  0.55557023f,  0.54532499f,
    0.53499762f,  0.52458968f,  0.51410274f,  0.50353838f,  0.49289819f,  0.48218377f,
    0.47139674f,  0.46053871f,  0.44961133f,  0.43861624f,  0.42755509f,  0.41642956f,
    0.40524131f,  0.39399204f,  0.38268343f,  0.37131719f,  0.35989504f,  0.34841868f,
    0.33688985f,  0.32531029f,  0.31368174f,  0.30200595f,  0.29028468f,  0.27851969f,
    0.26671276f,  0.25486566f,  0.24298018f,  0.23105811f,  0.21910124f,  0.20711138f,
    0.19509032f,  0.18303989f,  0.17096189f,  0.15885814f,  0.14673047f,  0.13458071f,
    0.12241068f,  0.11022221f,  0.09801714f,  0.08579731f,  0.07356456f,  0.06132074f,
    0.04906767f,  0.03680722f,  0.02454123f,  0.01227154f,  0.00000000f,  -0.01227154f,
    -0.02454123f, -0.03680722f, -0.04906767f, -0.06132074f, -0.07356456f, -0.08579731f,
    -0.09801714f, -0.11022221f, -0.12241068f, -0.13458071f, -0.14673047f, -0.15885814f,
    -0.17096189f, -0.18303989f, -0.19509032f, -0.20711138f, -0.21910124f, -0.23105811f,
    -0.24298018f, -0.25486566f, -0.26671276f, -0.27851969f, -0.29028468f, -0.30200595f,
    -0.31368174f, -0.32531029f, -0.33688985f, -0.34841868f, -0.35989504f, -0.37131719f,
    -0.38268343f, -0.39399204f, -0.40524131f, -0.41642956f, -0.42755509f, -0.43861624f,
    -0.44961133f, -0.46053871f, -0.47139674f, -0.48218377f, -0.49289819f, -0.50353838f,
    -0.51410274f, -0.52458968f, -0.53499762f, -0.54532499f, -0.55557023f, -0.56573181f,
    -0.57580819f, -0.58579786f, -0.59569930f, -0.60551104f, -0.61523159f, -0.62485949f,
    -0.63439328f, -0.64383154f, -0.65317284f, -0.66241578f, -0.67155895f, -0.68060100f,
    -0.68954054f, -0.69837625f, -0.70710678f, -0.71573083f, -0.72424708f, -0.73265427f,
    -0.74095113f, -0.74913639f, -0.75720885f, -0.76516727f, -0.77301045f, -0.78073723f,
    -0.78834643f, -0.79583690f, -0.80320753f, -0.81045720f, -0.81758481f, -0.82458930f,
    -0.83146961f, -0.83822471f, -0.84485357f, -0.85135519f, -0.85772861f, -0.86397286f,
    -0.87008699f, -0.87607009f, -0.88192126f, -0.88763962f, -0.89322430f, -0.89867447f,
    -0.90398929f, -0.90916798f, -0.91420976f, -0.91911385f, -0.92387953f, -0.92850608f,
    -0.93299280f, -0.93733901f, -0.94154407f, -0.94560733f, -0.94952818f, -0.95330604f,
    -0.95694034f, -0.96043052f, -0.96377607f, -0.96697647f, -0.97003125f, -0.97293995f,
    -0.97570213f, -0.97831737f, -0.98078528f, -0.98310549f, -0.98527764f, -0.98730142f,
    -0.98917651f, -0.99090264f, -0.99247953f, -0.99390697f, -0.99518473f, -0.99631261f,
    -0.99729046f, -0.99811811f, -0.99879546f, -0.99932238f, -0.99969882f, -0.99992470f,
    -1.00000000f, -0.99992470f, -0.99969882f, -0.99932238f, -0.99879546f, -0.99811811f,
    -0.99729046f, -0.99631261f, -0.99518473f, -0.99390697f, -0.99247953f, -0.99090264f,
    -0.98917651f, -0.98730142f, -0.98527764f, -0.98310549f, -0.98078528f, -0.97831737f,
    -0.97570213f, -0.97293995f, -0.97003125f, -0.96697647f, -0.96377607f, -0.96043052f,
    -0.95694034f, -0.95330604f, -0.94952818f, -0.94560733f, -0.94154407f, -0.93733901f,
    -0.93299280f, -0.92850608f, -0.92387953f, -0.91911385f, -0.91420976f, -0.90916798f,
    -0.90398929f, -0.89867447f, -0.89322430f, -0.88763962f, -0.88192126f, -0.87607009f,
    -0.87008699f, -0.86397286f, -0.85772861f, -0.85135519f, -0.84485357f, -0.83822471f,
    -0.83146961f, -0.82458930f, -0.81758481f, -0.81045720f, -0.80320753f, -0.79583690f,
    -0.78834643f, -0.78073723f, -0.77301045f, -0.76516727f, -0.75720885f, -0.74913639f,
    -0.74095113f, -0.73265427f, -0.72424708f, -0.71573083f, -0.70710678f, -0.69837625f,
    -0.68954054f, -0.68060100f, -0.67155895f, -0.66241578f, -0.65317284f, -0.64383154f,
    -0.63439328f, -0.62485949f, -0.61523159f, -0.60551104f, -0.59569930f, -0.58579786f,
    -0.57580819f, -0.56573181f, -0.55557023f, -0.54532499f, -0.53499762f, -0.52458968f,
    -0.51410274f, -0.50353838f, -0.49289819f, -0.48218377f, -0.47139674f, -0.46053871f,
    -0.44961133f, -0.43861624f, -0.42755509f, -0.41642956f, -0.40524131f, -0.39399204f,
    -0.38268343f, -0.37131719f, -0.35989504f, -0.34841868f, -0.33688985f, -0.32531029f,
    -0.31368174f, -0.30200595f, -0.29028468f, -0.27851969f, -0.26671276f, -0.25486566f,
    -0.24298018f, -0.23105811f, -0.21910124f, -0.20711138f, -0.19509032f, -0.18303989f,
    -0.17096189f, -0.15885814f, -0.14673047f, -0.13458071f, -0.12241068f, -0.11022221f,
    -0.09801714f, -0.08579731f, -0.07356456f, -0.06132074f, -0.04906767f, -0.03680722f,
    -0.02454123f, -0.01227154f, -0.00000000f
};
#endif
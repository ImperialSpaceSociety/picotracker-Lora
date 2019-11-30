/*
 ******************************************************************************
 * @file    lsm6dsl_reg.c
 * @author  MEMS Software Solution Team
 * @brief   LSM6DSL driver file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "lsm6dsl_reg.h"

/**
  * @addtogroup  lsm6dsl
  * @brief  This file provides a set of functions needed to drive the
  *         lsm6dsl enanced inertial module.
  * @{
  */

/**
  * @addtogroup  interfaces_functions
  * @brief  This section provide a set of functions used to read and write
  *         a generic register of the device.
  * @{
  */

/**
  * @brief  Read generic device register
  *
  * @param  lsm6dsl_ctx_t* ctx: read / write interface definitions
  * @param  uint8_t reg: register to read
  * @param  uint8_t* data: pointer to buffer that store the data read
  * @param  uint16_t len: number of consecutive register to read
  *
  */
int32_t lsm6dsl_read_reg(lsm6dsl_ctx_t *ctx, uint8_t reg, uint8_t *data,
                         uint16_t len)
{
  int32_t ret;
  ret = ctx->read_reg(ctx->handle, reg, data, len);
  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t reg: register to write
  * @param  uint8_t* data: pointer to data to write in register reg
  * @param  uint16_t len: number of consecutive register to write
  *
*/
int32_t lsm6dsl_write_reg(lsm6dsl_ctx_t *ctx, uint8_t reg, uint8_t *data,
                          uint16_t len)
{
  int32_t ret;
  ret = ctx->write_reg(ctx->handle, reg, data, len);
  return ret;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @addtogroup  data_generation_c
  * @brief   This section groups all the functions concerning data generation
  * @{
  */

/**
  * @brief  xl_full_scale: [set]  Accelerometer full-scale selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_fs_xl_t: change the values of fs_xl in reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_full_scale_set(lsm6dsl_ctx_t *ctx, lsm6dsl_fs_xl_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl1_xl.fs_xl = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_full_scale: [get]  Accelerometer full-scale selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_fs_xl_t: Get the values of fs_xl in reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_full_scale_get(lsm6dsl_ctx_t *ctx, lsm6dsl_fs_xl_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  switch (reg.ctrl1_xl.fs_xl)
  {
    case LSM6DSL_2g:
      *val = LSM6DSL_2g;
      break;
    case LSM6DSL_16g:
      *val = LSM6DSL_16g;
      break;
    case LSM6DSL_4g:
      *val = LSM6DSL_4g;
      break;
    case LSM6DSL_8g:
      *val = LSM6DSL_8g;
      break;
    default:
      *val = LSM6DSL_XL_FS_ND;
      break;
  }

  return ret;
}

/**
  * @brief  xl_data_rate: [set]  Accelerometer data rate selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_odr_xl_t: change the values of odr_xl in reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_data_rate_set(lsm6dsl_ctx_t *ctx, lsm6dsl_odr_xl_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl1_xl.odr_xl = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_data_rate: [get]  Accelerometer data rate selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_odr_xl_t: Get the values of odr_xl in reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_data_rate_get(lsm6dsl_ctx_t *ctx, lsm6dsl_odr_xl_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  switch (reg.ctrl1_xl.odr_xl)
  {
    case LSM6DSL_XL_ODR_OFF:
      *val = LSM6DSL_XL_ODR_OFF;
      break;
    case LSM6DSL_XL_ODR_12Hz5:
      *val = LSM6DSL_XL_ODR_12Hz5;
      break;
    case LSM6DSL_XL_ODR_26Hz:
      *val = LSM6DSL_XL_ODR_26Hz;
      break;
    case LSM6DSL_XL_ODR_52Hz:
      *val = LSM6DSL_XL_ODR_52Hz;
      break;
    case LSM6DSL_XL_ODR_104Hz:
      *val = LSM6DSL_XL_ODR_104Hz;
      break;
    case LSM6DSL_XL_ODR_208Hz:
      *val = LSM6DSL_XL_ODR_208Hz;
      break;
    case LSM6DSL_XL_ODR_416Hz:
      *val = LSM6DSL_XL_ODR_416Hz;
      break;
    case LSM6DSL_XL_ODR_833Hz:
      *val = LSM6DSL_XL_ODR_833Hz;
      break;
    case LSM6DSL_XL_ODR_1k66Hz:
      *val = LSM6DSL_XL_ODR_1k66Hz;
      break;
    case LSM6DSL_XL_ODR_3k33Hz:
      *val = LSM6DSL_XL_ODR_3k33Hz;
      break;
    case LSM6DSL_XL_ODR_6k66Hz:
      *val = LSM6DSL_XL_ODR_6k66Hz;
      break;
    case LSM6DSL_XL_ODR_1Hz6:
      *val = LSM6DSL_XL_ODR_1Hz6;
      break;
    default:
      *val = LSM6DSL_XL_ODR_ND;
      break;
  }

  return ret;
}

/**
  * @brief  gy_full_scale: [set]  Gyroscope chain full-scale selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_fs_g_t: change the values of fs_g in reg CTRL2_G
  *
  */
int32_t lsm6dsl_gy_full_scale_set(lsm6dsl_ctx_t *ctx, lsm6dsl_fs_g_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL2_G, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl2_g.fs_g = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL2_G, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  gy_full_scale: [get]  Gyroscope chain full-scale selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_fs_g_t: Get the values of fs_g in reg CTRL2_G
  *
  */
int32_t lsm6dsl_gy_full_scale_get(lsm6dsl_ctx_t *ctx, lsm6dsl_fs_g_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL2_G, &reg.byte, 1);
  switch (reg.ctrl2_g.fs_g)
  {
    case LSM6DSL_250dps:
      *val = LSM6DSL_250dps;
      break;
    case LSM6DSL_125dps:
      *val = LSM6DSL_125dps;
      break;
    case LSM6DSL_500dps:
      *val = LSM6DSL_500dps;
      break;
    case LSM6DSL_1000dps:
      *val = LSM6DSL_1000dps;
      break;
    case LSM6DSL_2000dps:
      *val = LSM6DSL_2000dps;
      break;
    default:
      *val = LSM6DSL_GY_FS_ND;
      break;
  }

  return ret;
}

/**
  * @brief  gy_data_rate: [set]  Gyroscope data rate selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_odr_g_t: change the values of odr_g in reg CTRL2_G
  *
  */
int32_t lsm6dsl_gy_data_rate_set(lsm6dsl_ctx_t *ctx, lsm6dsl_odr_g_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL2_G, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl2_g.odr_g = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL2_G, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  gy_data_rate: [get]  Gyroscope data rate selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_odr_g_t: Get the values of odr_g in reg CTRL2_G
  *
  */
int32_t lsm6dsl_gy_data_rate_get(lsm6dsl_ctx_t *ctx, lsm6dsl_odr_g_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL2_G, &reg.byte, 1);
  switch (reg.ctrl2_g.odr_g)
  {
    case LSM6DSL_GY_ODR_OFF:
      *val = LSM6DSL_GY_ODR_OFF;
      break;
    case LSM6DSL_GY_ODR_12Hz5:
      *val = LSM6DSL_GY_ODR_12Hz5;
      break;
    case LSM6DSL_GY_ODR_26Hz:
      *val = LSM6DSL_GY_ODR_26Hz;
      break;
    case LSM6DSL_GY_ODR_52Hz:
      *val = LSM6DSL_GY_ODR_52Hz;
      break;
    case LSM6DSL_GY_ODR_104Hz:
      *val = LSM6DSL_GY_ODR_104Hz;
      break;
    case LSM6DSL_GY_ODR_208Hz:
      *val = LSM6DSL_GY_ODR_208Hz;
      break;
    case LSM6DSL_GY_ODR_416Hz:
      *val = LSM6DSL_GY_ODR_416Hz;
      break;
    case LSM6DSL_GY_ODR_833Hz:
      *val = LSM6DSL_GY_ODR_833Hz;
      break;
    case LSM6DSL_GY_ODR_1k66Hz:
      *val = LSM6DSL_GY_ODR_1k66Hz;
      break;
    case LSM6DSL_GY_ODR_3k33Hz:
      *val = LSM6DSL_GY_ODR_3k33Hz;
      break;
    case LSM6DSL_GY_ODR_6k66Hz:
      *val = LSM6DSL_GY_ODR_6k66Hz;
      break;
    default:
      *val = LSM6DSL_GY_ODR_ND;
      break;
  }

  return ret;
}

/**
  * @brief  block_data_update: [set] Blockdataupdate.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of bdu in reg CTRL3_C
  *
  */
int32_t lsm6dsl_block_data_update_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.bdu = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  block_data_update: [get] Blockdataupdate.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of bdu in reg CTRL3_C
  *
  */
int32_t lsm6dsl_block_data_update_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  *val = reg.ctrl3_c.bdu;

  return ret;
}

/**
  * @brief  xl_offset_weight: [set] Weight of XL user offset bits of
  *                                 registers X_OFS_USR(73h), Y_OFS_USR(74h),
  *                                 Z_OFS_USR (75h)
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_usr_off_w_t: change the values of usr_off_w in reg CTRL6_C
  *
  */
int32_t lsm6dsl_xl_offset_weight_set(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_usr_off_w_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl6_c.usr_off_w = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_offset_weight: [get] Weight of XL user offset bits of
  *                                 registers X_OFS_USR(73h), Y_OFS_USR(74h),
  *                                 Z_OFS_USR(75h)
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_usr_off_w_t: Get the values of usr_off_w in reg CTRL6_C
  *
  */
int32_t lsm6dsl_xl_offset_weight_get(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_usr_off_w_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  switch (reg.ctrl6_c.usr_off_w)
  {
    case LSM6DSL_LSb_1mg:
      *val = LSM6DSL_LSb_1mg;
      break;
    case LSM6DSL_LSb_16mg:
      *val = LSM6DSL_LSb_16mg;
      break;
    default:
      *val = LSM6DSL_WEIGHT_ND;
      break;
  }

  return ret;
}

/**
  * @brief  xl_power_mode: [set] High-performance operating mode
  *                              for accelerometer
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_xl_hm_mode_t: change the values of xl_hm_mode
  *                               in reg CTRL6_C
  *
  */
int32_t lsm6dsl_xl_power_mode_set(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_xl_hm_mode_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl6_c.xl_hm_mode = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_power_mode: [get] High-performance operating mode
  *                              for accelerometer
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_xl_hm_mode_t: Get the values of xl_hm_mode in reg CTRL6_C
  *
  */
int32_t lsm6dsl_xl_power_mode_get(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_xl_hm_mode_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  switch (reg.ctrl6_c.xl_hm_mode)
  {
    case LSM6DSL_XL_HIGH_PERFORMANCE:
      *val = LSM6DSL_XL_HIGH_PERFORMANCE;
      break;
    case LSM6DSL_XL_NORMAL:
      *val = LSM6DSL_XL_NORMAL;
      break;
    default:
      *val = LSM6DSL_XL_PW_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  rounding_on_status: [set] Source register rounding function
  *                                   on WAKE_UP_SRC (1Bh), TAP_SRC (1Ch),
  *                                   D6D_SRC (1Dh), STATUS_REG (1Eh) and
  *                                   FUNC_SRC1 (53h) registers in the
  *                                   primary interface
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_rounding_status_t: change the values of rounding_status
  *                                    in reg CTRL7_G
  *
  */
int32_t lsm6dsl_rounding_on_status_set(lsm6dsl_ctx_t *ctx,
                                       lsm6dsl_rounding_status_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl7_g.rounding_status = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  rounding_on_status: [get] Source register rounding function
  *                                   on WAKE_UP_SRC (1Bh), TAP_SRC (1Ch),
  *                                   D6D_SRC (1Dh), STATUS_REG (1Eh) and
  *                                   FUNC_SRC1 (53h) registers in the
  *                                   primary interface
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_rounding_status_t: Get the values of rounding_status
  *                                    in reg CTRL7_G
  *
  */
int32_t lsm6dsl_rounding_on_status_get(lsm6dsl_ctx_t *ctx,
                                       lsm6dsl_rounding_status_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  switch (reg.ctrl7_g.rounding_status)
  {
    case LSM6DSL_STAT_RND_DISABLE:
      *val = LSM6DSL_STAT_RND_DISABLE;
      break;
    case LSM6DSL_STAT_RND_ENABLE:
      *val = LSM6DSL_STAT_RND_ENABLE;
      break;
    default:
      *val = LSM6DSL_STAT_RND_ND;
      break;
  }

  return ret;
}

/**
  * @brief  gy_power_mode: [set] High-performance operating mode
  *                              disable for gyroscope.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_g_hm_mode_t: change the values of g_hm_mode in reg CTRL7_G
  *
  */
int32_t lsm6dsl_gy_power_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_g_hm_mode_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl7_g.g_hm_mode = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  gy_power_mode: [get] High-performance operating mode
  *                              disable for gyroscope.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_g_hm_mode_t: Get the values of g_hm_mode in reg CTRL7_G
  *
  */
int32_t lsm6dsl_gy_power_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_g_hm_mode_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  switch (reg.ctrl7_g.g_hm_mode)
  {
    case LSM6DSL_GY_HIGH_PERFORMANCE:
      *val = LSM6DSL_GY_HIGH_PERFORMANCE;
      break;
    case LSM6DSL_GY_NORMAL:
      *val = LSM6DSL_GY_NORMAL;
      break;
    default:
      *val = LSM6DSL_GY_PW_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  all_sources: [get] Read all the interrupt/status flag of
  *                            the device.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_all_sources: WAKE_UP_SRC, TAP_SRC, D6D_SRC, STATUS_REG,
  *                              FUNC_SRC1, FUNC_SRC2, WRIST_TILT_IA,
  *                              A_WRIST_TILT_Mask
  *
  */
int32_t lsm6dsl_all_sources_get(lsm6dsl_ctx_t *ctx, lsm6dsl_all_sources_t *val)
{
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_SRC, &(val->byte[0]), 4);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_FUNC_SRC1, &(val->byte[4]), 3);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
      if (ret == 0)
      {
        ret = lsm6dsl_read_reg(ctx, LSM6DSL_A_WRIST_TILT_MASK,
                               &(val->byte[7]), 1);
        if (ret == 0)
        {
          ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  status_reg: [get] The STATUS_REG register is read by the
  *                           primary interface
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  status_reg_t: registers STATUS_REG
  *
  */
int32_t lsm6dsl_status_reg_get(lsm6dsl_ctx_t *ctx, lsm6dsl_status_reg_t *val)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_STATUS_REG, (uint8_t *) val, 1);
}

/**
  * @brief  xl_flag_data_ready: [get]  Accelerometer new data available.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of xlda in reg STATUS_REG
  *
  */
int32_t lsm6dsl_xl_flag_data_ready_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_STATUS_REG, &reg.byte, 1);
  *val = reg.status_reg.xlda;

  return ret;
}

/**
  * @brief  gy_flag_data_ready: [get]  Gyroscope new data available.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of gda in reg STATUS_REG
  *
  */
int32_t lsm6dsl_gy_flag_data_ready_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_STATUS_REG, &reg.byte, 1);
  *val = reg.status_reg.gda;

  return ret;
}

/**
  * @brief   temp_flag_data_ready: [get]  Temperature new data available.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tda in reg STATUS_REG
  *
  */
int32_t lsm6dsl_temp_flag_data_ready_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_STATUS_REG, &reg.byte, 1);
  *val = reg.status_reg.tda;

  return ret;
}

/**
  * @brief  xl_usr_offset: [set] Accelerometer axis user offset correction
  *                              expressed in two’s complement, weight
  *                              depends on USR_OFF_W in CTRL6_C.
  *                              The value must be in the range [-127 127].
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lsm6dsl_xl_usr_offset_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_write_reg(ctx, LSM6DSL_X_OFS_USR, buff, 3);
}

/**
  * @brief  xl_usr_offset: [get] Accelerometer axis user offset correction
  *                              expressed in two’s complement, weight
  *                              depends on USR_OFF_W in CTRL6_C.
  *                              The value must be in the range [-127 127].
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_xl_usr_offset_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_X_OFS_USR, buff, 3);
}

/**
  * @}
  */

/**
  * @addtogroup  Timestamp
  * @brief   This section groups all the functions that manage the
  *          timestamp generation.
  * @{
  */

/**
  * @brief  timestamp: [set] Enable timestamp count. The count is saved in
  *                          TIMESTAMP0_REG (40h), TIMESTAMP1_REG (41h)
  *                          and TIMESTAMP2_REG (42h).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of timer_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_timestamp_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.timer_en = val;
    if (val != 0x00U)
    {
      reg.ctrl10_c.func_en = val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
    }
  }
  return ret;
}

/**
  * @brief  timestamp: [get] Enable timestamp count. The count is saved
  *                          in TIMESTAMP0_REG (40h), TIMESTAMP1_REG (41h)
  *                          and TIMESTAMP2_REG (42h).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of timer_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_timestamp_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  *val = reg.ctrl10_c.timer_en;

  return ret;
}

/**
  * @brief  timestamp_res: [set] Timestamp register resolution setting.
  *                              Configuration of this bit affects
  *                              TIMESTAMP0_REG(40h), TIMESTAMP1_REG(41h),
  *                              TIMESTAMP2_REG(42h), STEP_TIMESTAMP_L(49h),
  *                              STEP_TIMESTAMP_H(4Ah) and
  *                              STEP_COUNT_DELTA(15h) registers.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_timer_hr_t: change the values of timer_hr in
  *                             reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_timestamp_res_set(lsm6dsl_ctx_t *ctx, lsm6dsl_timer_hr_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  if (ret == 0)
  {
    reg.wake_up_dur.timer_hr = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  timestamp_res: [get] Timestamp register resolution setting.
  *                              Configuration of this bit affects
  *                              TIMESTAMP0_REG(40h), TIMESTAMP1_REG(41h),
  *                              TIMESTAMP2_REG(42h), STEP_TIMESTAMP_L(49h),
  *                              STEP_TIMESTAMP_H(4Ah) and
  *                              STEP_COUNT_DELTA(15h) registers.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_timer_hr_t: Get the values of timer_hr in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_timestamp_res_get(lsm6dsl_ctx_t *ctx, lsm6dsl_timer_hr_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  switch (reg.wake_up_dur.timer_hr)
  {
    case LSM6DSL_LSB_6ms4:
      *val = LSM6DSL_LSB_6ms4;
      break;
    case LSM6DSL_LSB_25us:
      *val = LSM6DSL_LSB_25us;
      break;
    default:
      *val = LSM6DSL_TS_RES_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  Dataoutput
  * @brief   This section groups all the data output functions.
  * @{
  */

/**
  * @brief  rounding_mode: [set] Circular burst-mode (rounding) read from
  *                              output registers through the primary interface.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_rounding_t: change the values of rounding in reg CTRL5_C
  *
  */
int32_t lsm6dsl_rounding_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_rounding_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl5_c.rounding = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  rounding_mode: [get] Circular burst-mode (rounding) read from
  *                              output registers through the primary
  *                              interface.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_rounding_t: Get the values of rounding in reg CTRL5_C
  *
  */
int32_t lsm6dsl_rounding_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_rounding_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  switch (reg.ctrl5_c.rounding)
  {
    case LSM6DSL_ROUND_DISABLE:
      *val = LSM6DSL_ROUND_DISABLE;
      break;
    case LSM6DSL_ROUND_XL:
      *val = LSM6DSL_ROUND_XL;
      break;
    case LSM6DSL_ROUND_GY:
      *val = LSM6DSL_ROUND_GY;
      break;
    case LSM6DSL_ROUND_GY_XL:
      *val = LSM6DSL_ROUND_GY_XL;
      break;
    case LSM6DSL_ROUND_SH1_TO_SH6:
      *val = LSM6DSL_ROUND_SH1_TO_SH6;
      break;
    case LSM6DSL_ROUND_XL_SH1_TO_SH6:
      *val = LSM6DSL_ROUND_XL_SH1_TO_SH6;
      break;
    case LSM6DSL_ROUND_GY_XL_SH1_TO_SH12:
      *val = LSM6DSL_ROUND_GY_XL_SH1_TO_SH12;
      break;
    case LSM6DSL_ROUND_GY_XL_SH1_TO_SH6:
      *val = LSM6DSL_ROUND_GY_XL_SH1_TO_SH6;
      break;
    default:
      *val = LSM6DSL_ROUND_OUT_ND;
      break;
  }

  return ret;
}

/**
  * @brief  temperature_raw: [get] Temperature data output register (r).
  *                                L and H registers together express a 16-bit
  *                                word in two’s complement.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_temperature_raw_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_OUT_TEMP_L, buff, 2);
}

/**
  * @brief  angular_rate_raw: [get] Angular rate sensor. The value is
  *                                 expressed as a 16-bit word in
  *                                 two’s complement.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_angular_rate_raw_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_OUTX_L_G, buff, 6);
}

/**
  * @brief  acceleration_raw: [get] Linear acceleration output register.
  *                                 The value is expressed as a 16-bit word
  *                                 in two’s complement.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_acceleration_raw_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_OUTX_L_XL, buff, 6);
}

/**
  * @brief  mag_calibrated_raw: [get]  External magnetometer raw data
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_mag_calibrated_raw_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_OUT_MAG_RAW_X_L, buff, 6);
}

/**
  * @brief   fifo_raw_data: [get]  read data in FIFO.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t *: data buffer to store FIFO data.
  * @param  uint8_t : number of data to read from FIFO.
  *
  */
int32_t lsm6dsl_fifo_raw_data_get(lsm6dsl_ctx_t *ctx, uint8_t *buffer,
                                  uint8_t len)
{
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_DATA_OUT_L, buffer, len);

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  common
  * @brief   This section groups common usefull functions.
  * @{
  */

/**
  * @brief  mem_bank: [set] Enable access to the embedded
  *                         functions/sensor hub configuration registers
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_func_cfg_en_t: change the values of func_cfg_en in
  *                                reg FUNC_CFG_ACCESS
  *
  */
int32_t lsm6dsl_mem_bank_set(lsm6dsl_ctx_t *ctx, lsm6dsl_func_cfg_en_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FUNC_CFG_ACCESS, &reg.byte, 1);
  if (ret == 0)
  {
    reg.func_cfg_access.func_cfg_en = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FUNC_CFG_ACCESS, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  mem_bank: [get] Enable access to the embedded functions/sensor
  *                         hub configuration registers
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_func_cfg_en_t: Get the values of func_cfg_en in
  *                                reg FUNC_CFG_ACCESS
  *
  */
int32_t lsm6dsl_mem_bank_get(lsm6dsl_ctx_t *ctx, lsm6dsl_func_cfg_en_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FUNC_CFG_ACCESS, &reg.byte, 1);
  switch (reg.func_cfg_access.func_cfg_en)
  {
    case LSM6DSL_USER_BANK:
      *val = LSM6DSL_USER_BANK;
      break;
    case LSM6DSL_BANK_B:
      *val = LSM6DSL_BANK_B;
      break;
    default:
      *val = LSM6DSL_BANK_ND;
      break;
  }

  return ret;
}

/**
  * @brief  data_ready_mode: [set]  data-ready pulsed / letched mode
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_drdy_pulsed_t: change the values of drdy_pulsed in
  *                                reg DRDY_PULSE_CFG
  *
  */
int32_t lsm6dsl_data_ready_mode_set(lsm6dsl_ctx_t *ctx,
                                    lsm6dsl_drdy_pulsed_g_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_DRDY_PULSE_CFG_G, &reg.byte, 1);
  if (ret == 0)
  {
    reg.drdy_pulse_cfg_g.drdy_pulsed = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_DRDY_PULSE_CFG_G, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  data_ready_mode: [get]  data-ready pulsed / letched mode
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_drdy_pulsed_t: Get the values of drdy_pulsed
  *                                in reg DRDY_PULSE_CFG
  *
  */
int32_t lsm6dsl_data_ready_mode_get(lsm6dsl_ctx_t *ctx,
                                    lsm6dsl_drdy_pulsed_g_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_DRDY_PULSE_CFG_G, &reg.byte, 1);
  switch (reg.drdy_pulse_cfg_g.drdy_pulsed)
  {
    case LSM6DSL_DRDY_LATCHED:
      *val = LSM6DSL_DRDY_LATCHED;
      break;
    case LSM6DSL_DRDY_PULSED:
      *val = LSM6DSL_DRDY_PULSED;
      break;
    default:
      *val = LSM6DSL_DRDY_ND;
      break;
  }

  return ret;
}

/**
  * @brief  device_id: [get] DeviceWhoamI.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_device_id_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_WHO_AM_I, buff, 1);
}

/**
  * @brief  reset: [set] Software reset. Restore the default
  *                      values in user registers
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of sw_reset in reg CTRL3_C
  *
  */
int32_t lsm6dsl_reset_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.sw_reset = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  reset: [get] Software reset. Restore the default
  *                      values in user registers
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of sw_reset in reg CTRL3_C
  *
  */
int32_t lsm6dsl_reset_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  *val = reg.ctrl3_c.sw_reset;

  return ret;
}

/**
  * @brief  data_format: [set]  Big/Little Endian Data selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_ble_t: change the values of ble in reg CTRL3_C
  *
  */
int32_t lsm6dsl_data_format_set(lsm6dsl_ctx_t *ctx, lsm6dsl_ble_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.ble = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  data_format: [get]  Big/Little Endian Data selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_ble_t: Get the values of ble in reg CTRL3_C
  *
  */
int32_t lsm6dsl_data_format_get(lsm6dsl_ctx_t *ctx, lsm6dsl_ble_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  switch (reg.ctrl3_c.ble)
  {
    case LSM6DSL_LSB_AT_LOW_ADD:
      *val = LSM6DSL_LSB_AT_LOW_ADD;
      break;
    case LSM6DSL_MSB_AT_LOW_ADD:
      *val = LSM6DSL_MSB_AT_LOW_ADD;
      break;
    default:
      *val = LSM6DSL_DATA_FMT_ND;
      break;
  }

  return ret;
}

/**
  * @brief  auto_increment: [set] Register address automatically incremented
  *                               during a multiple byte access with a
  *                               serial interface.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of if_inc in reg CTRL3_C
  *
  */
int32_t lsm6dsl_auto_increment_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.if_inc = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  auto_increment: [get] Register address automatically incremented
  *                               during a multiple byte access with a
  *                               serial interface.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of if_inc in reg CTRL3_C
  *
  */
int32_t lsm6dsl_auto_increment_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  *val = reg.ctrl3_c.if_inc;

  return ret;
}

/**
  * @brief  boot: [set] Reboot memory content. Reload the calibration
  *                     parameters.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of boot in reg CTRL3_C
  *
  */
int32_t lsm6dsl_boot_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.boot = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  boot: [get] Reboot memory content. Reload the calibration
  *                     parameters.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of boot in reg CTRL3_C
  *
  */
int32_t lsm6dsl_boot_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  *val = reg.ctrl3_c.boot;

  return ret;
}

/**
  * @brief  xl_self_test: [set]  Linear acceleration sensor self-test enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_st_xl_t: change the values of st_xl in reg CTRL5_C
  *
  */
int32_t lsm6dsl_xl_self_test_set(lsm6dsl_ctx_t *ctx, lsm6dsl_st_xl_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl5_c.st_xl = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_self_test: [get]  Linear acceleration sensor self-test enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_st_xl_t: Get the values of st_xl in reg CTRL5_C
  *
  */
int32_t lsm6dsl_xl_self_test_get(lsm6dsl_ctx_t *ctx, lsm6dsl_st_xl_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  switch (reg.ctrl5_c.st_xl)
  {
    case LSM6DSL_XL_ST_DISABLE:
      *val = LSM6DSL_XL_ST_DISABLE;
      break;
    case LSM6DSL_XL_ST_POSITIVE:
      *val = LSM6DSL_XL_ST_POSITIVE;
      break;
    case LSM6DSL_XL_ST_NEGATIVE:
      *val = LSM6DSL_XL_ST_NEGATIVE;
      break;
    default:
      *val = LSM6DSL_XL_ST_ND;
      break;
  }
  return ret;
}

/**
  * @brief  gy_self_test: [set]  Angular rate sensor self-test enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_st_g_t: change the values of st_g in reg CTRL5_C
  *
  */
int32_t lsm6dsl_gy_self_test_set(lsm6dsl_ctx_t *ctx, lsm6dsl_st_g_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl5_c.st_g = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  gy_self_test: [get]  Angular rate sensor self-test enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_st_g_t: Get the values of st_g in reg CTRL5_C
  *
  */
int32_t lsm6dsl_gy_self_test_get(lsm6dsl_ctx_t *ctx, lsm6dsl_st_g_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  switch (reg.ctrl5_c.st_g)
  {
    case LSM6DSL_GY_ST_DISABLE:
      *val = LSM6DSL_GY_ST_DISABLE;
      break;
    case LSM6DSL_GY_ST_POSITIVE:
      *val = LSM6DSL_GY_ST_POSITIVE;
      break;
    case LSM6DSL_GY_ST_NEGATIVE:
      *val = LSM6DSL_GY_ST_NEGATIVE;
      break;
    default:
      *val = LSM6DSL_GY_ST_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  filters
  * @brief   This section group all the functions concerning the filters
  *          configuration that impact both accelerometer and gyro.
  * @{
  */

/**
  * @brief   filter_settling_mask: [set] Mask DRDY on pin (both XL & Gyro)
  *                                      until filter settling ends
  *                                      (XL and Gyro independently masked).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of drdy_mask in reg CTRL4_C
  *
  */
int32_t lsm6dsl_filter_settling_mask_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl4_c.drdy_mask = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief   filter_settling_mask: [get] Mask DRDY on pin (both XL & Gyro)
  *                                      until filter settling ends
  *                                      (XL and Gyro independently masked).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of drdy_mask in reg CTRL4_C
  *
  */
int32_t lsm6dsl_filter_settling_mask_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  *val = reg.ctrl4_c.drdy_mask;

  return ret;
}

/**
  * @brief   xl_hp_path_internal: [set] HPF or SLOPE filter selection on
  *                                     wake-up and Activity/Inactivity
  *                                     functions.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slope_fds_t: change the values of slope_fds in reg TAP_CFG
  *
  */
int32_t lsm6dsl_xl_hp_path_internal_set(lsm6dsl_ctx_t *ctx,
                                        lsm6dsl_slope_fds_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_cfg.slope_fds = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief   xl_hp_path_internal: [get] HPF or SLOPE filter selection on
  *                                     wake-up and Activity/Inactivity
  *                                     functions.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slope_fds_t: Get the values of slope_fds in reg TAP_CFG
  *
  */
int32_t lsm6dsl_xl_hp_path_internal_get(lsm6dsl_ctx_t *ctx,
                                        lsm6dsl_slope_fds_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  switch (reg.tap_cfg.slope_fds)
  {
    case LSM6DSL_USE_SLOPE:
      *val = LSM6DSL_USE_SLOPE;
      break;
    case LSM6DSL_USE_HPF:
      *val = LSM6DSL_USE_HPF;
      break;
    default:
      *val = LSM6DSL_HP_PATH_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup   accelerometer_filters
  * @brief   This section group all the functions concerning the filters
  *          configuration that impact accelerometer in every mode.
  * @{
  */

/**
  * @brief  xl_filter_analog: [set] Accelerometer analog chain bandwidth
  *                                 selection (only for accelerometer
  *                                 ODR ≥ 1.67 kHz).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_bw0_xl_t: change the values of bw0_xl in reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_filter_analog_set(lsm6dsl_ctx_t *ctx, lsm6dsl_bw0_xl_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl1_xl.bw0_xl = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_filter_analog: [get] Accelerometer analog chain bandwidth
  *                                 selection (only for accelerometer
  *                                 ODR ≥ 1.67 kHz).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_bw0_xl_t: Get the values of bw0_xl in reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_filter_analog_get(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_bw0_xl_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  switch (reg.ctrl1_xl.bw0_xl)
  {
    case LSM6DSL_XL_ANA_BW_1k5Hz:
      *val = LSM6DSL_XL_ANA_BW_1k5Hz;
      break;
    case LSM6DSL_XL_ANA_BW_400Hz:
      *val = LSM6DSL_XL_ANA_BW_400Hz;
      break;
    default:
      *val = LSM6DSL_XL_ANA_BW_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup   accelerometer_filters
  * @brief   This section group all the functions concerning the filters
  *          configuration that impact accelerometer.
  * @{
  */

/**
  * @brief  xl_lp1_bandwidth: [set] Accelerometer digital LPF (LPF1)
  *                                 bandwidth selection LPF2 is not used.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_lpf1_bw_sel_t: change the values of lpf1_bw_sel in
  *                                reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_lp1_bandwidth_set(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_lpf1_bw_sel_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl1_xl.lpf1_bw_sel = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
      if (ret == 0)
      {
        reg.ctrl8_xl.lpf2_xl_en = 0;
        reg.ctrl8_xl.hp_slope_xl_en = 0;
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
      }
    }
  }
  return ret;
}

/**
  * @brief  xl_lp1_bandwidth: [get] Accelerometer digital LPF (LPF1)
  *                                 bandwidth selection LPF2 is not used.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_lpf1_bw_sel_t: Get the values of lpf1_bw_sel in
  *                                reg CTRL1_XL
  *
  */
int32_t lsm6dsl_xl_lp1_bandwidth_get(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_lpf1_bw_sel_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (ret == 0)
  {
    if ((reg.ctrl8_xl.lpf2_xl_en != 0x00U) ||
        (reg.ctrl8_xl.hp_slope_xl_en != 0x00U))
    {
      *val = LSM6DSL_XL_LP1_NA;
    }
    else
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, &reg.byte, 1);
      switch (reg.ctrl1_xl.lpf1_bw_sel)
      {
        case LSM6DSL_XL_LP1_ODR_DIV_2:
          *val = LSM6DSL_XL_LP1_ODR_DIV_2;
          break;
        case LSM6DSL_XL_LP1_ODR_DIV_4:
          *val = LSM6DSL_XL_LP1_ODR_DIV_4;
          break;
        default:
          *val = LSM6DSL_XL_LP1_NA;
          break;
      }
    }
  }
  return ret;
}

/**
  * @brief  xl_lp2_bandwidth: [set] LPF2onoutputs
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_input_composite_t: change the values of
  *                                    input_composite in reg CTRL8_XL
  *
  */
int32_t lsm6dsl_xl_lp2_bandwidth_set(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_input_composite_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl8_xl.input_composite = ((uint8_t) val & 0x10U) >> 4;
    reg.ctrl8_xl.hpcf_xl = (uint8_t) val & 0x03U;
    reg.ctrl8_xl.lpf2_xl_en = 1;
    reg.ctrl8_xl.hp_slope_xl_en = 0;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_lp2_bandwidth: [get] LPF2onoutputs
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_input_composite_t: Get the values of
  *                                    input_composite in reg CTRL8_XL
  *
  */
int32_t lsm6dsl_xl_lp2_bandwidth_get(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_input_composite_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (ret == 0)
  {
    if ((reg.ctrl8_xl.lpf2_xl_en == 0x00U) ||
        (reg.ctrl8_xl.hp_slope_xl_en != 0x00U))
    {
      *val = LSM6DSL_XL_LP_NA;
    }
    else
    {
      switch ((reg.ctrl8_xl.input_composite << 4) + reg.ctrl8_xl.hpcf_xl)
      {
        case LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_50:
          *val = LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_50;
          break;
        case LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_100:
          *val = LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_100;
          break;
        case LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_9:
          *val = LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_9;
          break;
        case LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_400:
          *val = LSM6DSL_XL_LOW_LAT_LP_ODR_DIV_400;
          break;
        case LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_50:
          *val = LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_50;
          break;
        case LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_100:
          *val = LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_100;
          break;
        case LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_9:
          *val = LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_9;
          break;
        case LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_400:
          *val = LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_400;
          break;
        default:
          *val = LSM6DSL_XL_LP_NA;
          break;
      }
    }
  }

  return ret;
}

/**
  * @brief  xl_reference_mode: [set]  Enable HP filter reference mode.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of hp_ref_mode in reg CTRL8_XL
  *
  */
int32_t lsm6dsl_xl_reference_mode_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl8_xl.hp_ref_mode = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_reference_mode: [get]  Enable HP filter reference mode.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of hp_ref_mode in reg CTRL8_XL
  *
  */
int32_t lsm6dsl_xl_reference_mode_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  *val = reg.ctrl8_xl.hp_ref_mode;

  return ret;
}

/**
  * @brief  xl_hp_bandwidth: [set]  High pass/Slope on outputs.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_hpcf_xl_t: change the values of hpcf_xl in reg CTRL8_XL
  *
  */
int32_t lsm6dsl_xl_hp_bandwidth_set(lsm6dsl_ctx_t *ctx, lsm6dsl_hpcf_xl_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl8_xl.input_composite = 0;
    reg.ctrl8_xl.hpcf_xl = (uint8_t)val & 0x03U;
    reg.ctrl8_xl.hp_slope_xl_en = 1;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  xl_hp_bandwidth: [get]  High pass/Slope on outputs.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_hpcf_xl_t: Get the values of hpcf_xl in reg CTRL8_XL
  *
  */
int32_t lsm6dsl_xl_hp_bandwidth_get(lsm6dsl_ctx_t *ctx, lsm6dsl_hpcf_xl_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (reg.ctrl8_xl.hp_slope_xl_en == 0x00U)
  {
    *val = LSM6DSL_XL_HP_NA;
  }
  switch (reg.ctrl8_xl.hpcf_xl)
  {
    case LSM6DSL_XL_HP_ODR_DIV_4:
      *val = LSM6DSL_XL_HP_ODR_DIV_4;
      break;
    case LSM6DSL_XL_HP_ODR_DIV_100:
      *val = LSM6DSL_XL_HP_ODR_DIV_100;
      break;
    case LSM6DSL_XL_HP_ODR_DIV_9:
      *val = LSM6DSL_XL_HP_ODR_DIV_9;
      break;
    case LSM6DSL_XL_HP_ODR_DIV_400:
      *val = LSM6DSL_XL_HP_ODR_DIV_400;
      break;
    default:
      *val = LSM6DSL_XL_HP_NA;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup   gyroscope_filters
  * @brief   This section group all the functions concerning the filters
  *          configuration that impact gyroscope.
  * @{
  */

/**
  * @brief  gy_band_pass: [set] Gyroscope low pass path bandwidth.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_lpf1_sel_g_t: gyroscope filtering chain configuration.
  *
  */
int32_t lsm6dsl_gy_band_pass_set(lsm6dsl_ctx_t *ctx, lsm6dsl_lpf1_sel_g_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl7_g.hpm_g  = ((uint8_t)val & 0x30U) >> 4;
    reg.ctrl7_g.hp_en_g = ((uint8_t)val & 0x80U) >> 7;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL7_G, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
      if (ret == 0)
      {
        reg.ctrl6_c.ftype = (uint8_t)val & 0x03U;
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
        if (ret == 0)
        {
          ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
          if (ret == 0)
          {
            reg.ctrl4_c.lpf1_sel_g = ((uint8_t)val & 0x08U) >> 3;
            ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
          }
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  gy_band_pass: [get] Gyroscope low pass path bandwidth.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_lpf1_sel_g_t: gyroscope filtering chain
  *
  */
int32_t lsm6dsl_gy_band_pass_get(lsm6dsl_ctx_t *ctx, lsm6dsl_lpf1_sel_g_t *val)
{
  lsm6dsl_reg_t reg[3];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg[0].byte, 1);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg[1].byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL7_G, &reg[2].byte, 1);

      switch ((reg[2].ctrl7_g.hp_en_g << 7) + (reg[2].ctrl7_g.hpm_g << 4) +
              (reg[1].ctrl4_c.lpf1_sel_g << 3) + reg[0].ctrl6_c.ftype)
      {
        case LSM6DSL_HP_16mHz_LP2:
          *val = LSM6DSL_HP_16mHz_LP2;
          break;
        case LSM6DSL_HP_65mHz_LP2:
          *val = LSM6DSL_HP_65mHz_LP2;
          break;
        case LSM6DSL_HP_260mHz_LP2:
          *val = LSM6DSL_HP_260mHz_LP2;
          break;
        case LSM6DSL_HP_1Hz04_LP2:
          *val = LSM6DSL_HP_1Hz04_LP2;
          break;
        case LSM6DSL_HP_DISABLE_LP1_LIGHT:
          *val = LSM6DSL_HP_DISABLE_LP1_LIGHT;
          break;
        case LSM6DSL_HP_DISABLE_LP1_NORMAL:
          *val = LSM6DSL_HP_DISABLE_LP1_NORMAL;
          break;
        case LSM6DSL_HP_DISABLE_LP_STRONG:
          *val = LSM6DSL_HP_DISABLE_LP_STRONG;
          break;
        case LSM6DSL_HP_DISABLE_LP1_AGGRESSIVE:
          *val = LSM6DSL_HP_DISABLE_LP1_AGGRESSIVE;
          break;
        case LSM6DSL_HP_16mHz_LP1_LIGHT:
          *val = LSM6DSL_HP_16mHz_LP1_LIGHT;
          break;
        case LSM6DSL_HP_65mHz_LP1_NORMAL:
          *val = LSM6DSL_HP_65mHz_LP1_NORMAL;
          break;
        case LSM6DSL_HP_260mHz_LP1_STRONG:
          *val = LSM6DSL_HP_260mHz_LP1_STRONG;
          break;
        case LSM6DSL_HP_1Hz04_LP1_AGGRESSIVE:
          *val = LSM6DSL_HP_1Hz04_LP1_AGGRESSIVE;
          break;
        default:
          *val = LSM6DSL_HP_GY_BAND_NA;
          break;
      }
    }
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup   serial_interface
  * @brief   This section groups all the functions concerning serial
  *          interface management
  * @{
  */

/**
  * @brief  spi_mode: [set]  SPI Serial Interface Mode selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sim_t: change the values of sim in reg CTRL3_C
  *
  */
int32_t lsm6dsl_spi_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_sim_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.sim = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  spi_mode: [get]  SPI Serial Interface Mode selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sim_t: Get the values of sim in reg CTRL3_C
  *
  */
int32_t lsm6dsl_spi_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_sim_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  switch (reg.ctrl3_c.sim)
  {
    case LSM6DSL_SPI_4_WIRE:
      *val = LSM6DSL_SPI_4_WIRE;
      break;
    case LSM6DSL_SPI_3_WIRE:
      *val = LSM6DSL_SPI_3_WIRE;
      break;
    default:
      *val = LSM6DSL_SPI_MODE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  i2c_interface: [set]  Disable / Enable I2C interface.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_i2c_disable_t: change the values of i2c_disable in
  *                                reg CTRL4_C
  *
  */
int32_t lsm6dsl_i2c_interface_set(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_i2c_disable_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl4_c.i2c_disable = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  i2c_interface: [get]  Disable / Enable I2C interface.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_i2c_disable_t: Get the values of i2c_disable in
  *                                reg CTRL4_C
  *
  */
int32_t lsm6dsl_i2c_interface_get(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_i2c_disable_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  switch (reg.ctrl4_c.i2c_disable)
  {
    case LSM6DSL_I2C_ENABLE:
      *val = LSM6DSL_I2C_ENABLE;
      break;
    case LSM6DSL_I2C_DISABLE:
      *val = LSM6DSL_I2C_DISABLE;
      break;
    default:
      *val = LSM6DSL_I2C_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  interrupt_pins
  * @brief   This section groups all the functions that manage interrup pins
  * @{
  */

/**
  * @brief  pin_int1_route: [set] Select the signal that need to route on
  *                               int1 pad
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_int1_ctrl: configure INT1_CTRL, MD1_CFG,
  *                            CTRL4_C(den_drdy_int1),
  *                            MASTER_CONFIG(drdy_on_int1)
  *
  */
int32_t lsm6dsl_pin_int1_route_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_int1_route_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT1_CTRL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.int1_ctrl.int1_drdy_xl        = val.int1_drdy_xl;
    reg.int1_ctrl.int1_drdy_g         = val.int1_drdy_g;
    reg.int1_ctrl.int1_boot           = val.int1_boot;
    reg.int1_ctrl.int1_fth            = val.int1_fth;
    reg.int1_ctrl.int1_fifo_ovr       = val.int1_fifo_ovr;
    reg.int1_ctrl.int1_full_flag      = val.int1_full_flag;
    reg.int1_ctrl.int1_sign_mot       = val.int1_sign_mot;
    reg.int1_ctrl.int1_step_detector  = val.int1_step_detector;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_INT1_CTRL, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_MD1_CFG, &reg.byte, 1);
      if (ret == 0)
      {
        reg.md1_cfg.int1_timer           = val.int1_timer;
        reg.md1_cfg.int1_tilt            = val.int1_tilt;
        reg.md1_cfg.int1_6d              = val.int1_6d;
        reg.md1_cfg.int1_double_tap      = val.int1_double_tap;
        reg.md1_cfg.int1_ff              = val.int1_ff;
        reg.md1_cfg.int1_wu              = val.int1_wu;
        reg.md1_cfg.int1_single_tap      = val.int1_single_tap;
        reg.md1_cfg.int1_inact_state     = val.int1_inact_state;
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_MD1_CFG, &reg.byte, 1);
        if (ret == 0)
        {
          ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
          if (ret == 0)
          {
            reg.ctrl4_c.den_drdy_int1 = val.den_drdy_int1;
            ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
            if (ret == 0)
            {
              ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG,
                                     &reg.byte, 1);
              if (ret == 0)
              {
                reg.master_config.drdy_on_int1   = val.den_drdy_int1;
                ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG,
                                        &reg.byte, 1);
                if (ret == 0)
                {
                  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
                  if ((val.int1_6d != 0x00U) ||
                      (val.int1_ff != 0x00U) ||
                      (val.int1_wu != 0x00U) ||
                      (val.int1_single_tap != 0x00U) ||
                      (val.int1_double_tap != 0x00U) ||
                      (val.int1_inact_state != 0x00U))
                  {
                    reg.tap_cfg.interrupts_enable = PROPERTY_ENABLE;
                  }
                  else
                  {
                    reg.tap_cfg.interrupts_enable = PROPERTY_DISABLE;
                  }
                  ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
                }
              }
            }
          }
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  pin_int1_route: [get] Select the signal that need to route on
  *                               int1 pad
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_int1_route_t: read INT1_CTRL, MD1_CFG,
  *                               CTRL4_C(den_drdy_int1),
  *                               MASTER_CONFIG(drdy_on_int1)
  *
  */
int32_t lsm6dsl_pin_int1_route_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_int1_route_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT1_CTRL, &reg.byte, 1);
  if (ret == 0)
  {
    val->int1_drdy_xl       = reg.int1_ctrl.int1_drdy_xl;
    val->int1_drdy_g        = reg.int1_ctrl.int1_drdy_g;
    val->int1_boot          = reg.int1_ctrl.int1_boot;
    val->int1_fth           = reg.int1_ctrl.int1_fth;
    val->int1_fifo_ovr      = reg.int1_ctrl.int1_fifo_ovr;
    val->int1_full_flag     = reg.int1_ctrl.int1_full_flag;
    val->int1_sign_mot      = reg.int1_ctrl.int1_sign_mot;
    val->int1_step_detector = reg.int1_ctrl.int1_step_detector ;

    ret = lsm6dsl_read_reg(ctx, LSM6DSL_MD1_CFG, &reg.byte, 1);
    if (ret == 0)
    {
      val->int1_timer       = reg.md1_cfg.int1_timer;
      val->int1_tilt        = reg.md1_cfg.int1_tilt;
      val->int1_6d          = reg.md1_cfg.int1_6d;
      val->int1_double_tap  = reg.md1_cfg.int1_double_tap;
      val->int1_ff          = reg.md1_cfg.int1_ff;
      val->int1_wu          = reg.md1_cfg.int1_wu;
      val->int1_single_tap  = reg.md1_cfg.int1_single_tap;
      val->int1_inact_state = reg.md1_cfg.int1_inact_state;

      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
      if (ret == 0)
      {
        val->den_drdy_int1 = reg.ctrl4_c.den_drdy_int1;
        ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
        val->den_drdy_int1 = reg.master_config.drdy_on_int1;
      }
    }
  }
  return ret;
}

/**
  * @brief  pin_int2_route: [set] Select the signal that need to route on
  *                               int2 pad
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_int2_route_t: INT2_CTRL, DRDY_PULSE_CFG(int2_wrist_tilt),
  *                               MD2_CFG
  *
  */
int32_t lsm6dsl_pin_int2_route_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_int2_route_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT2_CTRL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.int2_ctrl.int2_drdy_xl        = val.int2_drdy_xl;
    reg.int2_ctrl.int2_drdy_g         = val.int2_drdy_g;
    reg.int2_ctrl.int2_drdy_temp      = val.int2_drdy_temp;
    reg.int2_ctrl.int2_fth            = val.int2_fth;
    reg.int2_ctrl.int2_fifo_ovr       = val.int2_fifo_ovr;
    reg.int2_ctrl.int2_full_flag      = val.int2_full_flag;
    reg.int2_ctrl.int2_step_count_ov  = val.int2_step_count_ov;
    reg.int2_ctrl.int2_step_delta     = val.int2_step_delta;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_INT2_CTRL, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_MD2_CFG, &reg.byte, 1);
      if (ret == 0)
      {
        reg.md2_cfg.int2_iron              = val.int2_iron;
        reg.md2_cfg.int2_tilt              = val.int2_tilt;
        reg.md2_cfg.int2_6d                = val.int2_6d;
        reg.md2_cfg.int2_double_tap        = val.int2_double_tap;
        reg.md2_cfg.int2_ff                = val.int2_ff;
        reg.md2_cfg.int2_wu                = val.int2_wu;
        reg.md2_cfg.int2_single_tap        = val.int2_single_tap;
        reg.md2_cfg.int2_inact_state       = val.int2_inact_state;
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_MD2_CFG, &reg.byte, 1);
        if (ret == 0)
        {
          ret = lsm6dsl_read_reg(ctx, LSM6DSL_DRDY_PULSE_CFG_G,
                                 &reg.byte, 1);
          if (ret == 0)
          {
            reg.drdy_pulse_cfg_g.int2_wrist_tilt = val.int2_wrist_tilt;
            ret = lsm6dsl_write_reg(ctx, LSM6DSL_DRDY_PULSE_CFG_G,
                                    &reg.byte, 1);
            if (ret == 0)
            {
              ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
              if (ret == 0)
              {
                if ((val.int2_6d != 0x00U) ||
                    (val.int2_ff != 0x00U) ||
                    (val.int2_wu != 0x00U) ||
                    (val.int2_single_tap != 0x00U) ||
                    (val.int2_double_tap != 0x00U) ||
                    (val.int2_inact_state != 0x00U))
                {
                  reg.tap_cfg.interrupts_enable = PROPERTY_ENABLE;
                }
                else
                {
                  reg.tap_cfg.interrupts_enable = PROPERTY_DISABLE;
                }
                ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
              }
            }
          }
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  pin_int2_route: [get] Select the signal that need to route on
  *                               int2 pad
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_int2_route_t: INT2_CTRL, DRDY_PULSE_CFG(int2_wrist_tilt),
  *                               MD2_CFG
  *
  */
int32_t lsm6dsl_pin_int2_route_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_int2_route_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT2_CTRL, &reg.byte, 1);
  if (ret == 0)
  {
    val->int2_drdy_xl         = reg.int2_ctrl.int2_drdy_xl;
    val->int2_drdy_g          = reg.int2_ctrl.int2_drdy_g;
    val->int2_drdy_temp       = reg.int2_ctrl.int2_drdy_temp;
    val->int2_fth             = reg.int2_ctrl.int2_fth;
    val->int2_fifo_ovr        = reg.int2_ctrl.int2_fifo_ovr;
    val->int2_full_flag       = reg.int2_ctrl.int2_full_flag;
    val->int2_step_count_ov   = reg.int2_ctrl.int2_step_count_ov;
    val->int2_step_delta      = reg.int2_ctrl.int2_step_delta;

    ret = lsm6dsl_read_reg(ctx, LSM6DSL_MD2_CFG, &reg.byte, 1);
    if (ret == 0)
    {
      val->int2_iron           = reg.md2_cfg.int2_iron;
      val->int2_tilt           = reg.md2_cfg.int2_tilt;
      val->int2_6d             = reg.md2_cfg.int2_6d;
      val->int2_double_tap     = reg.md2_cfg.int2_double_tap;
      val->int2_ff             = reg.md2_cfg.int2_ff;
      val->int2_wu             = reg.md2_cfg.int2_wu;
      val->int2_single_tap     = reg.md2_cfg.int2_single_tap;
      val->int2_inact_state    = reg.md2_cfg.int2_inact_state;

      ret = lsm6dsl_read_reg(ctx, LSM6DSL_DRDY_PULSE_CFG_G, &reg.byte, 1);
      val->int2_wrist_tilt = reg.drdy_pulse_cfg_g.int2_wrist_tilt;
    }
  }
  return ret;
}

/**
  * @brief  pin_mode: [set]  Push-pull/open drain selection on interrupt pads.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_pp_od_t: change the values of pp_od in reg CTRL3_C
  *
  */
int32_t lsm6dsl_pin_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_pp_od_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.pp_od = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  pin_mode: [get]  Push-pull/open drain selection on interrupt pads.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_pp_od_t: Get the values of pp_od in reg CTRL3_C
  *
  */
int32_t lsm6dsl_pin_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_pp_od_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  switch (reg.ctrl3_c.pp_od)
  {
    case LSM6DSL_PUSH_PULL:
      *val = LSM6DSL_PUSH_PULL;
      break;
    case LSM6DSL_OPEN_DRAIN:
      *val = LSM6DSL_OPEN_DRAIN;
      break;
    default:
      *val = LSM6DSL_PIN_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  pin_polarity: [set]  Interrupt active-high/low.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_h_lactive_t: change the values of h_lactive in reg CTRL3_C
  *
  */
int32_t lsm6dsl_pin_polarity_set(lsm6dsl_ctx_t *ctx, lsm6dsl_h_lactive_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl3_c.h_lactive = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  pin_polarity: [get]  Interrupt active-high/low.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_h_lactive_t: Get the values of h_lactive in reg CTRL3_C
  *
  */
int32_t lsm6dsl_pin_polarity_get(lsm6dsl_ctx_t *ctx, lsm6dsl_h_lactive_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL3_C, &reg.byte, 1);
  switch (reg.ctrl3_c.h_lactive)
  {
    case LSM6DSL_ACTIVE_HIGH:
      *val = LSM6DSL_ACTIVE_HIGH;
      break;
    case LSM6DSL_ACTIVE_LOW:
      *val = LSM6DSL_ACTIVE_LOW;
      break;
    default:
      *val = LSM6DSL_POLARITY_ND;
      break;
  }

  return ret;
}

/**
  * @brief  all_on_int1: [set] All interrupt signals become available on
  *                            INT1 pin.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of int2_on_int1 in reg CTRL4_C
  *
  */
int32_t lsm6dsl_all_on_int1_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl4_c.int2_on_int1 = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  all_on_int1: [get] All interrupt signals become available on
  *                            INT1 pin.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of int2_on_int1 in reg CTRL4_C
  *
  */
int32_t lsm6dsl_all_on_int1_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  *val = reg.ctrl4_c.int2_on_int1;

  return ret;
}

/**
  * @brief  int_notification: [set]  Latched/pulsed interrupt.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_lir_t: change the values of lir in reg TAP_CFG
  *
  */
int32_t lsm6dsl_int_notification_set(lsm6dsl_ctx_t *ctx, lsm6dsl_lir_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_cfg.lir = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  int_notification: [get]  Latched/pulsed interrupt.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_lir_t: Get the values of lir in reg TAP_CFG
  *
  */
int32_t lsm6dsl_int_notification_get(lsm6dsl_ctx_t *ctx, lsm6dsl_lir_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  switch (reg.tap_cfg.lir)
  {
    case LSM6DSL_INT_PULSED:
      *val = LSM6DSL_INT_PULSED;
      break;
    case LSM6DSL_INT_LATCHED:
      *val = LSM6DSL_INT_LATCHED;
      break;
    default:
      *val = LSM6DSL_INT_MODE;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  Wake_Up_event
  * @brief   This section groups all the functions that manage the Wake Up
  *          event generation.
  * @{
  */

/**
  * @brief  wkup_threshold: [set]  Threshold for wakeup.1 LSB = FS_XL / 64.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of wk_ths in reg WAKE_UP_THS
  *
  */
int32_t lsm6dsl_wkup_threshold_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_THS, &reg.byte, 1);
  if (ret == 0)
  {
    reg.wake_up_ths.wk_ths = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_WAKE_UP_THS, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  wkup_threshold: [get]  Threshold for wakeup.1 LSB = FS_XL / 64.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of wk_ths in reg WAKE_UP_THS
  *
  */
int32_t lsm6dsl_wkup_threshold_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_THS, &reg.byte, 1);
  *val = reg.wake_up_ths.wk_ths;

  return ret;
}

/**
  * @brief  wkup_dur: [set]  Wake up duration event.1LSb = 1 / ODR
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of wake_dur in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_wkup_dur_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  if (ret == 0)
  {
    reg.wake_up_dur.wake_dur = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  wkup_dur: [get]  Wake up duration event.1LSb = 1 / ODR
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of wake_dur in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_wkup_dur_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  *val = reg.wake_up_dur.wake_dur;

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup   Activity/Inactivity_detection
  * @brief   This section groups all the functions concerning
  *          activity/inactivity detection.
  * @{
  */

/**
  * @brief  gy_sleep_mode: [set]  Enables gyroscope Sleep mode.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of sleep in reg CTRL4_C
  *
  */
int32_t lsm6dsl_gy_sleep_mode_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl4_c.sleep = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  gy_sleep_mode: [get]  Enables gyroscope Sleep mode.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of sleep in reg CTRL4_C
  *
  */
int32_t lsm6dsl_gy_sleep_mode_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
  *val = reg.ctrl4_c.sleep;

  return ret;
}

/**
  * @brief  act_mode: [set]  Enable inactivity function.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_inact_en_t: change the values of inact_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_act_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_inact_en_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_cfg.inact_en = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  act_mode: [get]  Enable inactivity function.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_inact_en_t: Get the values of inact_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_act_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_inact_en_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  switch (reg.tap_cfg.inact_en)
  {
    case LSM6DSL_PROPERTY_DISABLE:
      *val = LSM6DSL_PROPERTY_DISABLE;
      break;
    case LSM6DSL_XL_12Hz5_GY_NOT_AFFECTED:
      *val = LSM6DSL_XL_12Hz5_GY_NOT_AFFECTED;
      break;
    case LSM6DSL_XL_12Hz5_GY_SLEEP:
      *val = LSM6DSL_XL_12Hz5_GY_SLEEP;
      break;
    case LSM6DSL_XL_12Hz5_GY_PD:
      *val = LSM6DSL_XL_12Hz5_GY_PD;
      break;
    default:
      *val = LSM6DSL_ACT_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  act_sleep_dur: [set] Duration to go in sleep mode.
  *                              1 LSb = 512 / ODR
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of sleep_dur in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_act_sleep_dur_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  if (ret == 0)
  {
    reg.wake_up_dur.sleep_dur = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  act_sleep_dur: [get] Duration to go in sleep mode.
  *                              1 LSb = 512 / ODR
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of sleep_dur in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_act_sleep_dur_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
  *val = reg.wake_up_dur.sleep_dur;

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  tap_generator
  * @brief   This section groups all the functions that manage the tap and
  *          double tap event generation.
  * @{
  */

/**
  * @brief  tap_src: [get]  Read the tap / double tap source register.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_: union of registers from TAP_SRC to
  *
  */
int32_t lsm6dsl_tap_src_get(lsm6dsl_ctx_t *ctx, lsm6dsl_tap_src_t *val)
{
  return lsm6dsl_read_reg(ctx, LSM6DSL_TAP_SRC, (uint8_t *) val, 1);
}

/**
  * @brief  tap_detection_on_z: [set]  Enable Z direction in tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tap_z_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_tap_detection_on_z_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_cfg.tap_z_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_detection_on_z: [get]  Enable Z direction in tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tap_z_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_tap_detection_on_z_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  *val = reg.tap_cfg.tap_z_en;

  return ret;
}

/**
  * @brief  tap_detection_on_y: [set]  Enable Y direction in tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tap_y_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_tap_detection_on_y_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_cfg.tap_y_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_detection_on_y: [get]  Enable Y direction in tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tap_y_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_tap_detection_on_y_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  *val = reg.tap_cfg.tap_y_en;

  return ret;
}

/**
  * @brief  tap_detection_on_x: [set]  Enable X direction in tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tap_x_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_tap_detection_on_x_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_cfg.tap_x_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_detection_on_x: [get]  Enable X direction in tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tap_x_en in reg TAP_CFG
  *
  */
int32_t lsm6dsl_tap_detection_on_x_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_CFG, &reg.byte, 1);
  *val = reg.tap_cfg.tap_x_en;

  return ret;
}

/**
  * @brief  tap_threshold_x: [set]  Threshold for tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tap_ths in reg TAP_THS_6D
  *
  */
int32_t lsm6dsl_tap_threshold_x_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_ths_6d.tap_ths = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_threshold_x: [get]  Threshold for tap recognition.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tap_ths in reg TAP_THS_6D
  *
  */
int32_t lsm6dsl_tap_threshold_x_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  *val = reg.tap_ths_6d.tap_ths;

  return ret;
}

/**
  * @brief  tap_shock: [set] Maximum duration is the maximum time of an
  *                          overthreshold signal detection to be recognized
  *                          as a tap event.
  *                          The default value of these bits is 00b which
  *                          corresponds to 4*ODR_XL time.
  *                          If the SHOCK[1:0] bits are set to a different
  *                          value, 1LSB corresponds to 8*ODR_XL time.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of shock in reg INT_DUR2
  *
  */
int32_t lsm6dsl_tap_shock_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  if (ret == 0)
  {
    reg.int_dur2.shock = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_shock: [get] Maximum duration is the maximum time of an
  *                          overthreshold signal detection to be recognized
  *                          as a tap event.
  *                          The default value of these bits is 00b which
  *                          corresponds to 4*ODR_XL time.
  *                          If the SHOCK[1:0] bits are set to a different
  *                          value, 1LSB corresponds to 8*ODR_XL time.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of shock in reg INT_DUR2
  *
  */
int32_t lsm6dsl_tap_shock_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  *val = reg.int_dur2.shock;

  return ret;
}

/**
  * @brief  tap_quiet: [set] Quiet time is the time after the first
  *                          detected tap in which there must not be
  *                          any overthreshold event.
  *                          The default value of these bits is 00b
  *                          which corresponds to 2*ODR_XL time.
  *                          If the QUIET[1:0] bits are set to a
  *                          different value, 1LSB corresponds to
  *                          4*ODR_XL time.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of quiet in reg INT_DUR2
  *
  */
int32_t lsm6dsl_tap_quiet_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  if (ret == 0)
  {
    reg.int_dur2.quiet = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_quiet: [get] Quiet time is the time after the first
  *                          detected tap in which there must not be any
  *                          overthreshold event.
  *                          The default value of these bits is 00b which
  *                          corresponds to 2*ODR_XL time.
  *                          If the QUIET[1:0] bits are set to a different
  *                          value, 1LSB corresponds to 4*ODR_XL time.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of quiet in reg INT_DUR2
  *
  */
int32_t lsm6dsl_tap_quiet_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  *val = reg.int_dur2.quiet;

  return ret;
}

/**
  * @brief  tap_dur: [set] When double tap recognition is enabled,
  *                        this register expresses the maximum time between
  *                        two consecutive detected taps to determine a double
  *                        tap event.
  *                        The default value of these bits is 0000b which
  *                        corresponds to 16*ODR_XL time.
  *                        If the DUR[3:0] bits are set to a different value,
  *                        1LSB corresponds to 32*ODR_XL time.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of dur in reg INT_DUR2
  *
  */
int32_t lsm6dsl_tap_dur_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  if (ret == 0)
  {
    reg.int_dur2.dur = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_dur: [get] When double tap recognition is enabled,
  *                        this register expresses the maximum time between
  *                        two consecutive detected taps to determine a
  *                        double tap event.
  *                        The default value of these bits is 0000b which
  *                        corresponds to 16*ODR_XL time.
  *                        If the DUR[3:0] bits are set to a different value,
  *                        1LSB corresponds to 32*ODR_XL time.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of dur in reg INT_DUR2
  *
  */
int32_t lsm6dsl_tap_dur_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_INT_DUR2, &reg.byte, 1);
  *val = reg.int_dur2.dur;

  return ret;
}

/**
  * @brief  tap_mode: [set]  Single/double-tap event enable/disable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_single_double_tap_t: change the values of
  *                                      single_double_tap in reg WAKE_UP_THS
  *
  */
int32_t lsm6dsl_tap_mode_set(lsm6dsl_ctx_t *ctx,
                             lsm6dsl_single_double_tap_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_THS, &reg.byte, 1);
  if (ret == 0)
  {
    reg.wake_up_ths.single_double_tap = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_WAKE_UP_THS, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tap_mode: [get]  Single/double-tap event enable/disable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_single_double_tap_t: Get the values of single_double_tap
  *                                      in reg WAKE_UP_THS
  *
  */
int32_t lsm6dsl_tap_mode_get(lsm6dsl_ctx_t *ctx,
                             lsm6dsl_single_double_tap_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_THS, &reg.byte, 1);
  switch (reg.wake_up_ths.single_double_tap)
  {
    case LSM6DSL_ONLY_SINGLE:
      *val = LSM6DSL_ONLY_SINGLE;
      break;
    case LSM6DSL_BOTH_SINGLE_DOUBLE:
      *val = LSM6DSL_BOTH_SINGLE_DOUBLE;
      break;
    default:
      *val = LSM6DSL_TAP_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup   Six_position_detection(6D/4D)
  * @brief   This section groups all the functions concerning six
  *          position detection (6D).
  * @{
  */

/**
  * @brief  6d_feed_data: [set]  LPF2 feed 6D function selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_low_pass_on_6d_t: change the values of low_pass_on_6d in
  *                                   reg CTRL8_XL
  *
  */
int32_t lsm6dsl_6d_feed_data_set(lsm6dsl_ctx_t *ctx,
                                 lsm6dsl_low_pass_on_6d_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl8_xl.low_pass_on_6d = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  6d_feed_data: [get]  LPF2 feed 6D function selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_low_pass_on_6d_t: Get the values of low_pass_on_6d in
  *                                   reg CTRL8_XL
  *
  */
int32_t lsm6dsl_6d_feed_data_get(lsm6dsl_ctx_t *ctx,
                                 lsm6dsl_low_pass_on_6d_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL8_XL, &reg.byte, 1);
  switch (reg.ctrl8_xl.low_pass_on_6d)
  {
    case LSM6DSL_ODR_DIV_2_FEED:
      *val = LSM6DSL_ODR_DIV_2_FEED;
      break;
    case LSM6DSL_LPF2_FEED:
      *val = LSM6DSL_LPF2_FEED;
      break;
    default:
      *val = LSM6DSL_6D_FEED_ND;
      break;
  }

  return ret;
}

/**
  * @brief  6d_threshold: [set]  Threshold for 4D/6D function.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sixd_ths_t: change the values of sixd_ths in reg TAP_THS_6D
  *
  */
int32_t lsm6dsl_6d_threshold_set(lsm6dsl_ctx_t *ctx, lsm6dsl_sixd_ths_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_ths_6d.sixd_ths = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  6d_threshold: [get]  Threshold for 4D/6D function.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sixd_ths_t: Get the values of sixd_ths in reg TAP_THS_6D
  *
  */
int32_t lsm6dsl_6d_threshold_get(lsm6dsl_ctx_t *ctx, lsm6dsl_sixd_ths_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  switch (reg.tap_ths_6d.sixd_ths)
  {
    case LSM6DSL_DEG_80:
      *val = LSM6DSL_DEG_80;
      break;
    case LSM6DSL_DEG_70:
      *val = LSM6DSL_DEG_70;
      break;
    case LSM6DSL_DEG_60:
      *val = LSM6DSL_DEG_60;
      break;
    case LSM6DSL_DEG_50:
      *val = LSM6DSL_DEG_50;
      break;
    default:
      *val = LSM6DSL_6D_TH_ND;
      break;
  }

  return ret;
}

/**
  * @brief  4d_mode: [set]  4D orientation detection enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of d4d_en in reg TAP_THS_6D
  *
  */
int32_t lsm6dsl_4d_mode_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  if (ret == 0)
  {
    reg.tap_ths_6d.d4d_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  4d_mode: [get]  4D orientation detection enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of d4d_en in reg TAP_THS_6D
  *
  */
int32_t lsm6dsl_4d_mode_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_TAP_THS_6D, &reg.byte, 1);
  *val = reg.tap_ths_6d.d4d_en;

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  free_fall
  * @brief   This section group all the functions concerning the free
  *          fall detection.
  * @{
  */

/**
  * @brief  ff_dur: [set]  Free-fall duration event. 1LSb = 1 / ODR
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of ff_dur in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_ff_dur_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FREE_FALL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.free_fall.ff_dur = (val & 0x1FU);
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FREE_FALL, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
      if (ret == 0)
      {
        reg.wake_up_dur.ff_dur = (val & 0x20U) >> 5;
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg.byte, 1);
      }
    }
  }
  return ret;
}

/**
  * @brief  ff_dur: [get]  Free-fall duration event. 1LSb = 1 / ODR
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of ff_dur in reg WAKE_UP_DUR
  *
  */
int32_t lsm6dsl_ff_dur_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_WAKE_UP_DUR, &reg[0].byte, 2);
  *val = (reg[0].wake_up_dur.ff_dur << 5) + reg[1].free_fall.ff_dur;

  return ret;
}

/**
  * @brief  ff_threshold: [set]  Free fall threshold setting.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_ff_ths_t: change the values of ff_ths in reg FREE_FALL
  *
  */
int32_t lsm6dsl_ff_threshold_set(lsm6dsl_ctx_t *ctx, lsm6dsl_ff_ths_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FREE_FALL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.free_fall.ff_ths = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FREE_FALL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  ff_threshold: [get]  Free fall threshold setting.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_ff_ths_t: Get the values of ff_ths in reg FREE_FALL
  *
  */
int32_t lsm6dsl_ff_threshold_get(lsm6dsl_ctx_t *ctx, lsm6dsl_ff_ths_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FREE_FALL, &reg.byte, 1);
  switch (reg.free_fall.ff_ths)
  {
    case LSM6DSL_FF_TSH_156mg:
      *val = LSM6DSL_FF_TSH_156mg;
      break;
    case LSM6DSL_FF_TSH_219mg:
      *val = LSM6DSL_FF_TSH_219mg;
      break;
    case LSM6DSL_FF_TSH_250mg:
      *val = LSM6DSL_FF_TSH_250mg;
      break;
    case LSM6DSL_FF_TSH_312mg:
      *val = LSM6DSL_FF_TSH_312mg;
      break;
    case LSM6DSL_FF_TSH_344mg:
      *val = LSM6DSL_FF_TSH_344mg;
      break;
    case LSM6DSL_FF_TSH_406mg:
      *val = LSM6DSL_FF_TSH_406mg;
      break;
    case LSM6DSL_FF_TSH_469mg:
      *val = LSM6DSL_FF_TSH_469mg;
      break;
    case LSM6DSL_FF_TSH_500mg:
      *val = LSM6DSL_FF_TSH_500mg;
      break;
    default:
      *val = LSM6DSL_FF_TSH_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  fifo
  * @brief   This section group all the functions concerning the fifo usage
  * @{
  */

/**
  * @brief  fifo_watermark: [set]  FIFO watermark level selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of fth in reg FIFO_CTRL1
  *
  */
int32_t lsm6dsl_fifo_watermark_set(lsm6dsl_ctx_t *ctx, uint16_t val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg[1].byte, 1);
  if (ret == 0)
  {
    reg[0].fifo_ctrl1.fth = (uint8_t)(0x00FFU & val);
    reg[1].fifo_ctrl2.fth = (uint8_t)((0x0700U & val) >> 8);
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL1, &reg[0].byte, 2);
  }
  return ret;
}

/**
  * @brief  fifo_watermark: [get]  FIFO watermark level selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of fth in reg FIFO_CTRL1
  *
  */
int32_t lsm6dsl_fifo_watermark_get(lsm6dsl_ctx_t *ctx, uint16_t *val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL1, &reg[0].byte, 2);
  *val = ((uint16_t)reg[1].fifo_ctrl2.fth << 8) +
         (uint16_t)reg[0].fifo_ctrl1.fth;

  return ret;
}

/**
  * @brief  lsm6dsl_fifo_data_level_get: [get]  FIFO data level.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: get the values of diff_fifo in reg  FIFO_STATUS1 and
  *                  FIFO_STATUS2(diff_fifo), it is recommended to set the
  *                  BDU bit
  *
  */
int32_t lsm6dsl_fifo_data_level_get(lsm6dsl_ctx_t *ctx, uint16_t *val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_STATUS1, &reg[0].byte, 2);
  *val = ((uint16_t) reg[1].fifo_status2.diff_fifo << 8) +
         (uint16_t) reg[0].fifo_status1.diff_fifo;

  return ret;
}

/**
  * @brief  lsm6dsl_fifo_wtm_flag: [get]  FIFO watermark.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: get the values of watermark in reg  FIFO_STATUS2 and
  *
  */
int32_t lsm6dsl_fifo_wtm_flag_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_STATUS2, &reg.byte, 1);
  *val = reg.fifo_status2.waterm;

  return ret;
}

/**
  * @brief  lsm6dsl_fifo_pattern_get: [get]  FIFO pattern.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: get the values of fifo_pattern in reg  FIFO_STATUS3 and
  *                  FIFO_STATUS4, it is recommended to set the BDU bit
  *
  */
int32_t lsm6dsl_fifo_pattern_get(lsm6dsl_ctx_t *ctx, uint16_t *val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_STATUS3, &reg[0].byte, 2);
  *val = ((uint16_t)reg[1].fifo_status4.fifo_pattern << 8) +
         reg[0].fifo_status3.fifo_pattern;

  return ret;
}

/**
  * @brief  fifo_temp_batch: [set]  batching of temperature data
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of fifo_temp_en in reg FIFO_CTRL2
  *
  */
int32_t lsm6dsl_fifo_temp_batch_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl2.fifo_temp_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  fifo_temp_batch: [get]  batching of temperature data
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of fifo_temp_en in reg FIFO_CTRL2
  *
  */
int32_t lsm6dsl_fifo_temp_batch_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  *val = reg.fifo_ctrl2.fifo_temp_en;

  return ret;
}

/**
  * @brief  fifo_write_trigger: [set]  trigger signal for FIFO write operation
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_trigger_fifo_t: act on FIFO_CTRL2(timer_pedo_fifo_drdy)
  *                                 and MASTER_CONFIG(data_valid_sel_fifo)
  *
  */
int32_t lsm6dsl_fifo_write_trigger_set(lsm6dsl_ctx_t *ctx,
                                       lsm6dsl_trigger_fifo_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl2.timer_pedo_fifo_drdy = (uint8_t)val & 0x01U;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        reg.master_config.data_valid_sel_fifo = (((uint8_t)val & 0x02U) >> 1);
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
      }
    }
  }

  return ret;
}

/**
  * @brief  fifo_write_trigger: [get]  trigger signal for FIFO write operation
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_trigger_fifo_t: act on FIFO_CTRL2(timer_pedo_fifo_drdy)
  *                                 and MASTER_CONFIG(data_valid_sel_fifo)
  *
  */
int32_t lsm6dsl_fifo_write_trigger_get(lsm6dsl_ctx_t *ctx,
                                       lsm6dsl_trigger_fifo_t *val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg[0].byte, 1);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg[1].byte, 1);

    switch ((reg[1].fifo_ctrl2.timer_pedo_fifo_drdy << 1) +
            reg[0].fifo_ctrl2. timer_pedo_fifo_drdy)
    {
      case LSM6DSL_TRG_XL_GY_DRDY:
        *val = LSM6DSL_TRG_XL_GY_DRDY;
        break;
      case LSM6DSL_TRG_STEP_DETECT:
        *val = LSM6DSL_TRG_STEP_DETECT;
        break;
      case LSM6DSL_TRG_SH_DRDY:
        *val = LSM6DSL_TRG_SH_DRDY;
        break;
      default:
        *val = LSM6DSL_TRG_SH_ND;
        break;
    }
  }

  return ret;
}

/**
  * @brief   fifo_pedo_and_timestamp_batch: [set] Enable pedometer step
  *                                               counter and timestamp as 4th
  *                                               FIFO data set.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of timer_pedo_fifo_en in
  *                      reg FIFO_CTRL2
  *
  */
int32_t lsm6dsl_fifo_pedo_and_timestamp_batch_set(lsm6dsl_ctx_t *ctx,
                                                  uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl2.timer_pedo_fifo_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief   fifo_pedo_and_timestamp_batch: [get] Enable pedometer step
  *                                               counter and timestamp as 4th
  *                                               FIFO data set.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of timer_pedo_fifo_en in reg FIFO_CTRL2
  *
  */
int32_t lsm6dsl_fifo_pedo_and_timestamp_batch_get(lsm6dsl_ctx_t *ctx,
                                                  uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL2, &reg.byte, 1);
  *val = reg.fifo_ctrl2.timer_pedo_fifo_en;

  return ret;
}

/**
  * @brief  fifo_xl_batch: [set] Selects Batching Data Rate (writing
  *                              frequency in FIFO) for accelerometer data.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_fifo_xl_t: change the values of dec_fifo_xl in
  *                                reg FIFO_CTRL3
  *
  */
int32_t lsm6dsl_fifo_xl_batch_set(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_dec_fifo_xl_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL3, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl3.dec_fifo_xl = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL3, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  fifo_xl_batch: [get] Selects Batching Data Rate (writing
  *                              frequency in FIFO) for accelerometer data.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_fifo_xl_t: Get the values of dec_fifo_xl in
  *                                reg FIFO_CTRL3
  *
  */
int32_t lsm6dsl_fifo_xl_batch_get(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_dec_fifo_xl_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL3, &reg.byte, 1);
  switch (reg.fifo_ctrl3.dec_fifo_xl)
  {
    case LSM6DSL_FIFO_XL_DISABLE:
      *val = LSM6DSL_FIFO_XL_DISABLE;
      break;
    case LSM6DSL_FIFO_XL_NO_DEC:
      *val = LSM6DSL_FIFO_XL_NO_DEC;
      break;
    case LSM6DSL_FIFO_XL_DEC_2:
      *val = LSM6DSL_FIFO_XL_DEC_2;
      break;
    case LSM6DSL_FIFO_XL_DEC_3:
      *val = LSM6DSL_FIFO_XL_DEC_3;
      break;
    case LSM6DSL_FIFO_XL_DEC_4:
      *val = LSM6DSL_FIFO_XL_DEC_4;
      break;
    case LSM6DSL_FIFO_XL_DEC_8:
      *val = LSM6DSL_FIFO_XL_DEC_8;
      break;
    case LSM6DSL_FIFO_XL_DEC_16:
      *val = LSM6DSL_FIFO_XL_DEC_16;
      break;
    case LSM6DSL_FIFO_XL_DEC_32:
      *val = LSM6DSL_FIFO_XL_DEC_32;
      break;
    default:
      *val = LSM6DSL_FIFO_XL_DEC_ND;
      break;
  }

  return ret;
}

/**
  * @brief  fifo_gy_batch: [set] Selects Batching Data Rate (writing
  *                              frequency in FIFO) for gyroscope data.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_fifo_gyro_t: change the values of dec_fifo_gyro
  *                                  in reg FIFO_CTRL3
  *
  */
int32_t lsm6dsl_fifo_gy_batch_set(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_dec_fifo_gyro_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL3, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl3.dec_fifo_gyro = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL3, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  fifo_gy_batch: [get] Selects Batching Data Rate (writing
  *                              frequency in FIFO) for gyroscope data.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_fifo_gyro_t: Get the values of dec_fifo_gyro in
  *                                  reg FIFO_CTRL3
  *
  */
int32_t lsm6dsl_fifo_gy_batch_get(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_dec_fifo_gyro_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL3, &reg.byte, 1);
  switch (reg.fifo_ctrl3.dec_fifo_gyro)
  {
    case LSM6DSL_FIFO_GY_DISABLE:
      *val = LSM6DSL_FIFO_GY_DISABLE;
      break;
    case LSM6DSL_FIFO_GY_NO_DEC:
      *val = LSM6DSL_FIFO_GY_NO_DEC;
      break;
    case LSM6DSL_FIFO_GY_DEC_2:
      *val = LSM6DSL_FIFO_GY_DEC_2;
      break;
    case LSM6DSL_FIFO_GY_DEC_3:
      *val = LSM6DSL_FIFO_GY_DEC_3;
      break;
    case LSM6DSL_FIFO_GY_DEC_4:
      *val = LSM6DSL_FIFO_GY_DEC_4;
      break;
    case LSM6DSL_FIFO_GY_DEC_8:
      *val = LSM6DSL_FIFO_GY_DEC_8;
      break;
    case LSM6DSL_FIFO_GY_DEC_16:
      *val = LSM6DSL_FIFO_GY_DEC_16;
      break;
    case LSM6DSL_FIFO_GY_DEC_32:
      *val = LSM6DSL_FIFO_GY_DEC_32;
      break;
    default:
      *val = LSM6DSL_FIFO_GY_DEC_ND;
      break;
  }

  return ret;
}

/**
  * @brief   fifo_dataset_3_batch: [set] Selects Batching Data Rate (writing
  *                                      frequency in FIFO) for third data set.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_ds3_fifo_t: change the values of dec_ds3_fifo in
  *                                 reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_dataset_3_batch_set(lsm6dsl_ctx_t *ctx,
                                         lsm6dsl_dec_ds3_fifo_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl4.dec_ds3_fifo = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief   fifo_dataset_3_batch: [get] Selects Batching Data Rate
  *                                      (writing frequency in FIFO) for
  *                                      third data set.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_ds3_fifo_t: Get the values of dec_ds3_fifo in
  *                                 reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_dataset_3_batch_get(lsm6dsl_ctx_t *ctx,
                                         lsm6dsl_dec_ds3_fifo_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  switch (reg.fifo_ctrl4.dec_ds3_fifo)
  {
    case LSM6DSL_FIFO_DS3_DISABLE:
      *val = LSM6DSL_FIFO_DS3_DISABLE;
      break;
    case LSM6DSL_FIFO_DS3_NO_DEC:
      *val = LSM6DSL_FIFO_DS3_NO_DEC;
      break;
    case LSM6DSL_FIFO_DS3_DEC_2:
      *val = LSM6DSL_FIFO_DS3_DEC_2;
      break;
    case LSM6DSL_FIFO_DS3_DEC_3:
      *val = LSM6DSL_FIFO_DS3_DEC_3;
      break;
    case LSM6DSL_FIFO_DS3_DEC_4:
      *val = LSM6DSL_FIFO_DS3_DEC_4;
      break;
    case LSM6DSL_FIFO_DS3_DEC_8:
      *val = LSM6DSL_FIFO_DS3_DEC_8;
      break;
    case LSM6DSL_FIFO_DS3_DEC_16:
      *val = LSM6DSL_FIFO_DS3_DEC_16;
      break;
    case LSM6DSL_FIFO_DS3_DEC_32:
      *val = LSM6DSL_FIFO_DS3_DEC_32;
      break;
    default:
      *val = LSM6DSL_FIFO_DS3_DEC_ND;
      break;
  }

  return ret;
}

/**
  * @brief   fifo_dataset_4_batch: [set] Selects Batching Data Rate
  *                                      (writing frequency in FIFO)
  *                                      for fourth data set.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_ds4_fifo_t: change the values of dec_ds4_fifo in
  *                                 reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_dataset_4_batch_set(lsm6dsl_ctx_t *ctx,
                                         lsm6dsl_dec_ds4_fifo_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl4.dec_ds4_fifo = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief   fifo_dataset_4_batch: [get] Selects Batching Data Rate
  *                                      (writing frequency in FIFO) for
  *                                      fourth data set.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_dec_ds4_fifo_t: Get the values of dec_ds4_fifo in
  *                                 reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_dataset_4_batch_get(lsm6dsl_ctx_t *ctx,
                                         lsm6dsl_dec_ds4_fifo_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  switch (reg.fifo_ctrl4.dec_ds4_fifo)
  {
    case LSM6DSL_FIFO_DS4_DISABLE:
      *val = LSM6DSL_FIFO_DS4_DISABLE;
      break;
    case LSM6DSL_FIFO_DS4_NO_DEC:
      *val = LSM6DSL_FIFO_DS4_NO_DEC;
      break;
    case LSM6DSL_FIFO_DS4_DEC_2:
      *val = LSM6DSL_FIFO_DS4_DEC_2;
      break;
    case LSM6DSL_FIFO_DS4_DEC_3:
      *val = LSM6DSL_FIFO_DS4_DEC_3;
      break;
    case LSM6DSL_FIFO_DS4_DEC_4:
      *val = LSM6DSL_FIFO_DS4_DEC_4;
      break;
    case LSM6DSL_FIFO_DS4_DEC_8:
      *val = LSM6DSL_FIFO_DS4_DEC_8;
      break;
    case LSM6DSL_FIFO_DS4_DEC_16:
      *val = LSM6DSL_FIFO_DS4_DEC_16;
      break;
    case LSM6DSL_FIFO_DS4_DEC_32:
      *val = LSM6DSL_FIFO_DS4_DEC_32;
      break;
    default:
      *val = LSM6DSL_FIFO_DS4_DEC_ND;
      break;
  }

  return ret;
}

/**
  * @brief   fifo_xl_gy_8bit_format: [set]  8-bit data storage in FIFO.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of only_high_data in reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_xl_gy_8bit_format_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl4.only_high_data = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief   fifo_xl_gy_8bit_format: [get]  8-bit data storage in FIFO.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of only_high_data in reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_xl_gy_8bit_format_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  *val = reg.fifo_ctrl4.only_high_data;

  return ret;
}

/**
  * @brief  fifo_stop_on_wtm: [set] Sensing chain FIFO stop values
  *                                 memorization at threshold level.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of stop_on_fth in reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_stop_on_wtm_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl4.stop_on_fth = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  fifo_stop_on_wtm: [get] Sensing chain FIFO stop values
  *                                 memorization at threshold level.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of stop_on_fth in reg FIFO_CTRL4
  *
  */
int32_t lsm6dsl_fifo_stop_on_wtm_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL4, &reg.byte, 1);
  *val = reg.fifo_ctrl4.stop_on_fth;

  return ret;
}

/**
  * @brief  fifo_mode: [set]  FIFO mode selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_fifo_mode_t: change the values of fifo_mode in
  *                              reg FIFO_CTRL5
  *
  */
int32_t lsm6dsl_fifo_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_fifo_mode_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL5, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl5.fifo_mode = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL5, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  fifo_mode: [get]  FIFO mode selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_fifo_mode_t: Get the values of fifo_mode in reg FIFO_CTRL5
  *
  */
int32_t lsm6dsl_fifo_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_fifo_mode_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL5, &reg.byte, 1);
  switch (reg.fifo_ctrl5.fifo_mode)
  {
    case LSM6DSL_BYPASS_MODE:
      *val = LSM6DSL_BYPASS_MODE;
      break;
    case LSM6DSL_FIFO_MODE:
      *val = LSM6DSL_FIFO_MODE;
      break;
    case LSM6DSL_STREAM_TO_FIFO_MODE:
      *val = LSM6DSL_STREAM_TO_FIFO_MODE;
      break;
    case LSM6DSL_BYPASS_TO_STREAM_MODE:
      *val = LSM6DSL_BYPASS_TO_STREAM_MODE;
      break;
    case LSM6DSL_STREAM_MODE:
      *val = LSM6DSL_STREAM_MODE;
      break;
    default:
      *val = LSM6DSL_FIFO_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  fifo_data_rate: [set]  FIFO ODR selection, setting FIFO_MODE also.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_odr_fifo_t: change the values of odr_fifo in reg FIFO_CTRL5
  *
  */
int32_t lsm6dsl_fifo_data_rate_set(lsm6dsl_ctx_t *ctx, lsm6dsl_odr_fifo_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL5, &reg.byte, 1);
  if (ret == 0)
  {
    reg.fifo_ctrl5.odr_fifo = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_FIFO_CTRL5, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  fifo_data_rate: [get]  FIFO ODR selection, setting FIFO_MODE also.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_odr_fifo_t: Get the values of odr_fifo in reg FIFO_CTRL5
  *
  */
int32_t lsm6dsl_fifo_data_rate_get(lsm6dsl_ctx_t *ctx, lsm6dsl_odr_fifo_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_FIFO_CTRL5, &reg.byte, 1);
  switch (reg.fifo_ctrl5.odr_fifo)
  {
    case LSM6DSL_FIFO_DISABLE:
      *val = LSM6DSL_FIFO_DISABLE;
      break;
    case LSM6DSL_FIFO_12Hz5:
      *val = LSM6DSL_FIFO_12Hz5;
      break;
    case LSM6DSL_FIFO_26Hz:
      *val = LSM6DSL_FIFO_26Hz;
      break;
    case LSM6DSL_FIFO_52Hz:
      *val = LSM6DSL_FIFO_52Hz;
      break;
    case LSM6DSL_FIFO_104Hz:
      *val = LSM6DSL_FIFO_104Hz;
      break;
    case LSM6DSL_FIFO_208Hz:
      *val = LSM6DSL_FIFO_208Hz;
      break;
    case LSM6DSL_FIFO_416Hz:
      *val = LSM6DSL_FIFO_416Hz;
      break;
    case LSM6DSL_FIFO_833Hz:
      *val = LSM6DSL_FIFO_833Hz;
      break;
    case LSM6DSL_FIFO_1k66Hz:
      *val = LSM6DSL_FIFO_1k66Hz;
      break;
    case LSM6DSL_FIFO_3k33Hz:
      *val = LSM6DSL_FIFO_3k33Hz;
      break;
    case LSM6DSL_FIFO_6k66Hz:
      *val = LSM6DSL_FIFO_6k66Hz;
      break;
    default:
      *val = LSM6DSL_FIFO_RATE_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  DEN_functionality
  * @brief   This section groups all the functions concerning DEN
  *          functionality.
  * @{
  */

/**
  * @brief  den_polarity: [set]  DEN active level configuration.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_den_lh_t: change the values of den_lh in reg CTRL5_C
  *
  */
int32_t lsm6dsl_den_polarity_set(lsm6dsl_ctx_t *ctx, lsm6dsl_den_lh_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl5_c.den_lh = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  den_polarity: [get]  DEN active level configuration.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_den_lh_t: Get the values of den_lh in reg CTRL5_C
  *
  */
int32_t lsm6dsl_den_polarity_get(lsm6dsl_ctx_t *ctx, lsm6dsl_den_lh_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL5_C, &reg.byte, 1);
  switch (reg.ctrl5_c.den_lh)
  {
    case LSM6DSL_DEN_ACT_LOW:
      *val = LSM6DSL_DEN_ACT_LOW;
      break;
    case LSM6DSL_DEN_ACT_HIGH:
      *val = LSM6DSL_DEN_ACT_HIGH;
      break;
    default:
      *val = LSM6DSL_DEN_POL_ND;
      break;
  }

  return ret;
}

/**
  * @brief  den_mode: [set]  DEN functionality marking mode
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_den_mode_t: change the values of den_mode in reg CTRL6_C
  *
  */
int32_t lsm6dsl_den_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_den_mode_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl6_c.den_mode = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  den_mode: [get]  DEN functionality marking mode
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_den_mode_t*: change the values of den_mode in reg CTRL6_C
  *
  */
int32_t lsm6dsl_den_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_den_mode_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL6_C, &reg.byte, 1);
  switch (reg.ctrl6_c.den_mode)
  {
    case LSM6DSL_DEN_DISABLE:
      *val = LSM6DSL_DEN_DISABLE;
      break;
    case LSM6DSL_LEVEL_LETCHED:
      *val = LSM6DSL_LEVEL_LETCHED;
      break;
    case LSM6DSL_LEVEL_TRIGGER:
      *val = LSM6DSL_LEVEL_TRIGGER;
      break;
    case LSM6DSL_EDGE_TRIGGER:
      *val = LSM6DSL_EDGE_TRIGGER;
      break;
    default:
      *val = LSM6DSL_DEN_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  den_enable: [set] Extend DEN functionality to accelerometer
  *                           sensor.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_den_xl_g_t: change the values of den_xl_g in reg CTRL9_XL
  *                             and den_xl_en in CTRL4_C.
  *
  */
int32_t lsm6dsl_den_enable_set(lsm6dsl_ctx_t *ctx, lsm6dsl_den_xl_en_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl9_xl.den_xl_g = (uint8_t)val & 0x01U;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
      if (ret == 0)
      {
        reg.ctrl4_c.den_xl_en = (uint8_t)val & 0x02U;
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL4_C, &reg.byte, 1);
      }
    }
  }
  return ret;
}

/**
  * @brief  den_enable: [get] Extend DEN functionality to accelerometer
  *                           sensor.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_den_xl_g_t: Get the values of den_xl_g in reg CTRL9_XL
  *                             and den_xl_en in CTRL4_C.
  *
  */
int32_t lsm6dsl_den_enable_get(lsm6dsl_ctx_t *ctx, lsm6dsl_den_xl_en_t *val)
{
  lsm6dsl_reg_t reg[2];
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL4_C, &reg[0].byte, 1);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg[1].byte, 1);
    switch ((reg[0].ctrl4_c.den_xl_en << 1) + reg[1].ctrl9_xl.den_xl_g)
    {
      case LSM6DSO_STAMP_IN_GY_DATA:
        *val = LSM6DSO_STAMP_IN_GY_DATA;
        break;
      case LSM6DSO_STAMP_IN_XL_DATA:
        *val = LSM6DSO_STAMP_IN_XL_DATA;
        break;
      case LSM6DSO_STAMP_IN_GY_XL_DATA:
        *val = LSM6DSO_STAMP_IN_GY_XL_DATA;
        break;
      default:
        *val = LSM6DSO_DEN_STAMP_ND;
        break;
    }
  }

  return ret;
}

/**
  * @brief  den_mark_axis_z: [set]  DEN value stored in LSB of Z-axis.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of den_z in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_den_mark_axis_z_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl9_xl.den_z = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  den_mark_axis_z: [get]  DEN value stored in LSB of Z-axis.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of den_z in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_den_mark_axis_z_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  *val = reg.ctrl9_xl.den_z;

  return ret;
}

/**
  * @brief  den_mark_axis_y: [set]  DEN value stored in LSB of Y-axis.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of den_y in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_den_mark_axis_y_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl9_xl.den_y = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  den_mark_axis_y: [get]  DEN value stored in LSB of Y-axis.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of den_y in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_den_mark_axis_y_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  *val = reg.ctrl9_xl.den_y;

  return ret;
}

/**
  * @brief  den_mark_axis_x: [set]  DEN value stored in LSB of X-axis.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of den_x in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_den_mark_axis_x_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl9_xl.den_x = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  den_mark_axis_x: [get]  DEN value stored in LSB of X-axis.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of den_x in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_den_mark_axis_x_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  *val = reg.ctrl9_xl.den_x;

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  Pedometer
  * @brief   This section groups all the functions that manage pedometer.
  * @{
  */

/**
  * @brief  pedo_step_reset: [set]  Reset pedometer step counter.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of pedo_rst_step in reg CTRL10_C
  *
  */
int32_t lsm6dsl_pedo_step_reset_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.pedo_rst_step = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  pedo_step_reset: [get]  Reset pedometer step counter.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of pedo_rst_step in reg CTRL10_C
  *
  */
int32_t lsm6dsl_pedo_step_reset_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  *val = reg.ctrl10_c.pedo_rst_step;

  return ret;
}

/**
  * @brief  pedo_sens: [set]  Enable pedometer algorithm.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of pedo_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_pedo_sens_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.pedo_en = val;
    if (val != 0x00U)
    {
      reg.ctrl10_c.func_en = val;
    }
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  pedo_sens: [get]  Enable pedometer algorithm.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of pedo_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_pedo_sens_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  *val = reg.ctrl10_c.pedo_en;

  return ret;
}

/**
  * @brief  pedo_threshold: [set] Minimum threshold to detect a peak.
  *                               Default is 10h.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of ths_min in reg
  *                      CONFIG_PEDO_THS_MIN
  *
  */
int32_t lsm6dsl_pedo_threshold_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_CONFIG_PEDO_THS_MIN, &reg.byte, 1);
    if (ret == 0)
    {
      reg. config_pedo_ths_min.ths_min = val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_CONFIG_PEDO_THS_MIN, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  pedo_threshold: [get] Minimum threshold to detect a peak.
  *                               Default is 10h.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of ths_min in reg  CONFIG_PEDO_THS_MIN
  *
  */
int32_t lsm6dsl_pedo_threshold_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_CONFIG_PEDO_THS_MIN, &reg.byte, 1);
    if (ret == 0)
    {
      *val = reg. config_pedo_ths_min.ths_min;
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  pedo_full_scale: [set]  Pedometer data range.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_pedo_fs_t: change the values of pedo_fs in
  *                            reg CONFIG_PEDO_THS_MIN
  *
  */
int32_t lsm6dsl_pedo_full_scale_set(lsm6dsl_ctx_t *ctx, lsm6dsl_pedo_fs_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_CONFIG_PEDO_THS_MIN, &reg.byte, 1);
    if (ret == 0)
    {
      reg. config_pedo_ths_min.pedo_fs = (uint8_t) val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_CONFIG_PEDO_THS_MIN, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  pedo_full_scale: [get]  Pedometer data range.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_pedo_fs_t: Get the values of pedo_fs in
  *                            reg CONFIG_PEDO_THS_MIN
  *
  */
int32_t lsm6dsl_pedo_full_scale_get(lsm6dsl_ctx_t *ctx, lsm6dsl_pedo_fs_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_CONFIG_PEDO_THS_MIN, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.config_pedo_ths_min.pedo_fs)
      {
        case LSM6DSL_PEDO_AT_2g:
          *val = LSM6DSL_PEDO_AT_2g;
          break;
        case LSM6DSL_PEDO_AT_4g:
          *val = LSM6DSL_PEDO_AT_4g;
          break;
        default:
          *val = LSM6DSL_PEDO_FS_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief   pedo_debounce_steps: [set] Pedometer debounce
  *                                     configuration register (r/w).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of deb_step in reg PEDO_DEB_REG
  *
  */
int32_t lsm6dsl_pedo_debounce_steps_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_PEDO_DEB_REG, &reg.byte, 1);
    if (ret == 0)
    {
      reg.pedo_deb_reg.deb_step = val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_PEDO_DEB_REG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief   pedo_debounce_steps: [get] Pedometer debounce configuration
  *                                     register (r/w).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of deb_step in reg PEDO_DEB_REG
  *
  */
int32_t lsm6dsl_pedo_debounce_steps_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_PEDO_DEB_REG, &reg.byte, 1);
    if (ret == 0)
    {
      *val = reg.pedo_deb_reg.deb_step;
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/**
  * @brief  pedo_timeout: [set] Debounce time. If the time between two
  *                             consecutive steps is greater than
  *                             DEB_TIME*80ms, the debouncer is reactivated.
  *                             Default value: 01101
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of deb_time in reg PEDO_DEB_REG
  *
  */
int32_t lsm6dsl_pedo_timeout_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_PEDO_DEB_REG, &reg.byte, 1);
    if (ret == 0)
    {
      reg.pedo_deb_reg.deb_time = val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_PEDO_DEB_REG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  pedo_timeout: [get] Debounce time. If the time between two
  *                             consecutive steps is greater than
  *                             DEB_TIME*80ms, the debouncer is reactivated.
  *                             Default value: 01101
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of deb_time in reg PEDO_DEB_REG
  *
  */
int32_t lsm6dsl_pedo_timeout_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_PEDO_DEB_REG, &reg.byte, 1);
    if (ret == 0)
    {
      *val = reg.pedo_deb_reg.deb_time;
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  pedo_steps_period: [set] Time period register for step
  *                                  detection on delta time (r/w).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lsm6dsl_pedo_steps_period_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_STEP_COUNT_DELTA, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  pedo_steps_period: [get] Time period register for step
  *                                  detection on delta time (r/w).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_pedo_steps_period_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_STEP_COUNT_DELTA, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  significant_motion
  * @brief   This section groups all the functions that manage the
  *          significant motion detection.
  * @{
  */

/**
  * @brief  motion_sens: [set]  Enable significant motion detection function.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of sign_motion_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_motion_sens_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.sign_motion_en = val;
    if (val != 0x00U)
    {
      reg.ctrl10_c.func_en = val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
    }
  }
  return ret;
}

/**
  * @brief  motion_sens: [get]  Enable significant motion detection function.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of sign_motion_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_motion_sens_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  *val = reg.ctrl10_c.sign_motion_en;

  return ret;
}

/**
  * @brief  motion_threshold: [set]  Significant motion threshold.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that store significant motion threshold.
  *
  */
int32_t lsm6dsl_motion_threshold_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SM_THS, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  motion_threshold: [get]  Significant motion threshold.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that store significant motion threshold.
  *
  */
int32_t lsm6dsl_motion_threshold_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SM_THS, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  tilt_detection
  * @brief   This section groups all the functions that manage the tilt
  *          event detection.
  * @{
  */

/**
  * @brief  tilt_sens: [set]  Enable tilt calculation.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tilt_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_tilt_sens_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.tilt_en = val;
    if (val != 0x00U)
    {
      reg.ctrl10_c.func_en = val;
    }
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  tilt_sens: [get]  Enable tilt calculation.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tilt_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_tilt_sens_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  *val = reg.ctrl10_c.tilt_en;

  return ret;
}

/**
  * @brief  wrist_tilt: [set]  Enable tilt calculation.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tilt_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_wrist_tilt_sens_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.wrist_tilt_en = val;
    if (val != 0x00U)
    {
      reg.ctrl10_c.func_en = val;
    }
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  wrist_tilt: [get]  Enable tilt calculation.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tilt_en in reg CTRL10_C
  *
  */
int32_t lsm6dsl_wrist_tilt_sens_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  *val = reg.ctrl10_c.wrist_tilt_en;

  return ret;
}

/**
  * @brief  tilt_latency: [set] Absolute Wrist Tilt latency register (r/w).
  *                             Absolute wrist tilt latency parameters.
  *                             1 LSB = 40 ms. Default value: 0Fh (600 ms).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lsm6dsl_tilt_latency_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
  if (ret == 0)
  {
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_A_WRIST_TILT_LAT, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  tilt_latency: [get] Absolute Wrist Tilt latency register (r/w).
  *                             Absolute wrist tilt latency parameters.
  *                             1 LSB = 40 ms. Default value: 0Fh (600 ms).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_tilt_latency_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_A_WRIST_TILT_LAT, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  tilt_threshold: [set] Absolute Wrist Tilt threshold register(r/w).
  *                               Absolute wrist tilt threshold parameters.
  *                               1 LSB = 15.625 mg.
  *                               Default value: 20h (500 mg).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lsm6dsl_tilt_threshold_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
  if (ret == 0)
  {
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_A_WRIST_TILT_THS, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  tilt_threshold: [get] Absolute Wrist Tilt threshold register(r/w).
  *                               Absolute wrist tilt threshold parameters.
  *                               1 LSB = 15.625 mg.
  *                               Default value: 20h (500 mg).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_tilt_threshold_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_A_WRIST_TILT_THS, buff, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  tilt_src: [set]  Absolute Wrist Tilt mask register (r/w).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_a_wrist_tilt_mask: registers A_WRIST_TILT_MASK
  *
  */
int32_t lsm6dsl_tilt_src_set(lsm6dsl_ctx_t *ctx,
                             lsm6dsl_a_wrist_tilt_mask_t *val)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_A_WRIST_TILT_MASK,
                           (uint8_t *) val, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  tilt_src: [get]  Absolute Wrist Tilt mask register (r/w).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_a_wrist_tilt_mask: registers A_WRIST_TILT_MASK
  *
  */
int32_t lsm6dsl_tilt_src_get(lsm6dsl_ctx_t *ctx,
                             lsm6dsl_a_wrist_tilt_mask_t *val)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_B);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_A_WRIST_TILT_MASK,
                           (uint8_t *) val, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;

}

/**
  * @}
  */

/**
  * @addtogroup   magnetometer_sensor
  * @brief   This section groups all the functions that manage additional
  *          magnetometer sensor.
  * @{
  */

/**
  * @brief  mag_soft_iron: [set] Enable soft-iron correction algorithm for
  *                              magnetometer.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of soft_en in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_mag_soft_iron_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl9_xl.soft_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  mag_soft_iron: [get] Enable soft-iron correction algorithm
  *                              for magnetometer.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of soft_en in reg CTRL9_XL
  *
  */
int32_t lsm6dsl_mag_soft_iron_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL9_XL, &reg.byte, 1);
  *val = reg.ctrl9_xl.soft_en;

  return ret;
}

/**
  * @brief  mag_hard_iron: [set] Enable hard-iron correction algorithm
  *                              for magnetometer.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of iron_en in reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_mag_hard_iron_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_config.iron_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
      if (ret == 0)
      {
        if (val != 0x00U)
        {
          reg.ctrl10_c.func_en = val;
        }
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
      }
    }
  }
  return ret;
}

/**
  * @brief  mag_hard_iron: [get] Enable hard-iron correction algorithm
  *                              for magnetometer.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of iron_en in reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_mag_hard_iron_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  *val = reg.master_config.iron_en;

  return ret;
}

/**
  * @brief  mag_soft_iron_mat: [set] 3x3 soft iron matrix. Value are
  *                                  expressed in sign-module format.
  *                                  (Es. SVVVVVVVb where S is the sign 0/+
  *                                  1/- and V is the value).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lsm6dsl_mag_soft_iron_mat_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MAG_SI_XX, buff, 9);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  mag_soft_iron_mat: [get] 3x3 soft iron matrix. Value are
  *                                  expressed in sign-module format.
  *                                  (Es. SVVVVVVVb where S is the sign 0/+
  *                                  1/- and V is the value).
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_mag_soft_iron_mat_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_MAG_SI_XX, buff, 9);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  mag_offset: [set] Offset for hard-iron compensation
  *                           register (r/w). The value is expressed as
  *                           a 16-bit word in two’s complement.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lsm6dsl_mag_offset_set(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MAG_OFFX_L, buff, 6);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @brief  mag_offset: [get] Offset for hard-iron compensation register(r/w).
  *                           The value is expressed as a 16-bit word in
  *                           two’s complement.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsl_mag_offset_get(lsm6dsl_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_MAG_OFFX_L, buff, 6);
    if (ret == 0)
    {
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }
  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  Sensor_hub
  * @brief   This section groups all the functions that manage the sensor
  *          hub functionality.
  * @{
  */

/**
* @brief  func_en: [set] Enable function.
*
* @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
* @param  uint8_t val: change the values func_en
*
*/
int32_t lsm6dsl_func_en_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  if (ret == 0)
  {
    reg.ctrl10_c.func_en = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL10_C, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  sh_sync_sens_frame: [set] Sensor synchronization time frame
  *                                   with the step of 500 ms and full range
  *                                   of 5 s. Unsigned 8-bit.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of tph in reg SENSOR_SYNC_TIME_FRAME
  *
  */
int32_t lsm6dsl_sh_sync_sens_frame_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENSOR_SYNC_TIME_FRAME,
                         &reg.byte, 1);
  if (ret == 0)
  {
    reg. sensor_sync_time_frame.tph = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SENSOR_SYNC_TIME_FRAME,
                            &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_sync_sens_frame: [get] Sensor synchronization time frame with
  *                                   the step of 500 ms and full range of 5s.
  *                                   Unsigned 8-bit.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of tph in reg  SENSOR_SYNC_TIME_FRAME
  *
  */
int32_t lsm6dsl_sh_sync_sens_frame_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENSOR_SYNC_TIME_FRAME,
                         &reg.byte, 1);
  *val = reg. sensor_sync_time_frame.tph;

  return ret;
}

/**
  * @brief  sh_sync_sens_ratio: [set] Resolution ratio of error code for
  *                                   sensor synchronization
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_rr_t: change the values of rr in reg  SENSOR_SYNC_RES_RATIO
  *
  */
int32_t lsm6dsl_sh_sync_sens_ratio_set(lsm6dsl_ctx_t *ctx, lsm6dsl_rr_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENSOR_SYNC_RES_RATIO,
                         &reg.byte, 1);
  if (ret == 0)
  {
    reg.sensor_sync_res_ratio.rr = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SENSOR_SYNC_RES_RATIO,
                            &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_sync_sens_ratio: [get] Resolution ratio of error code
  *                                   for sensor synchronization
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_rr_t: Get the values of rr in reg  SENSOR_SYNC_RES_RATIO
  *
  */
int32_t lsm6dsl_sh_sync_sens_ratio_get(lsm6dsl_ctx_t *ctx, lsm6dsl_rr_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENSOR_SYNC_RES_RATIO,
                         &reg.byte, 1);

  switch (reg. sensor_sync_res_ratio.rr)
  {
    case LSM6DSL_RES_RATIO_2_11:
      *val = LSM6DSL_RES_RATIO_2_11;
      break;
    case LSM6DSL_RES_RATIO_2_12:
      *val = LSM6DSL_RES_RATIO_2_12;
      break;
    case LSM6DSL_RES_RATIO_2_13:
      *val = LSM6DSL_RES_RATIO_2_13;
      break;
    case LSM6DSL_RES_RATIO_2_14:
      *val = LSM6DSL_RES_RATIO_2_14;
      break;
    default:
      *val = LSM6DSL_RES_RATIO_ND;
      break;
  }

  return ret;
}

/**
  * @brief  sh_master: [set]  Sensor hub I2C master enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of master_on in reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_master_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_config.master_on = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_master: [get]  Sensor hub I2C master enable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of master_on in reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_master_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  *val = reg.master_config.master_on;

  return ret;
}

/**
  * @brief  sh_pass_through: [set]  I2C interface pass-through.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of pass_through_mode in
  *                      reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_pass_through_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_config.pass_through_mode = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_pass_through: [get]  I2C interface pass-through.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of pass_through_mode in
  *                  reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_pass_through_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  *val = reg.master_config.pass_through_mode;

  return ret;
}

/**
  * @brief  sh_pin_mode: [set]  Master I2C pull-up enable/disable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_pull_up_en_t: change the values of pull_up_en in
  *                               reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_pin_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_pull_up_en_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_config.pull_up_en = (uint8_t) val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  sh_pin_mode: [get]  Master I2C pull-up enable/disable.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_pull_up_en_t: Get the values of pull_up_en in
  *                               reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_pin_mode_get(lsm6dsl_ctx_t *ctx, lsm6dsl_pull_up_en_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  switch (reg.master_config.pull_up_en)
  {
    case LSM6DSL_EXT_PULL_UP:
      *val = LSM6DSL_EXT_PULL_UP;
      break;
    case LSM6DSL_INTERNAL_PULL_UP:
      *val = LSM6DSL_INTERNAL_PULL_UP;
      break;
    default:
      *val = LSM6DSL_SH_PIN_MODE;
      break;
  }
  return ret;
}

/**
  * @brief  sh_syncro_mode: [set]  Sensor hub trigger signal selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_start_config_t: change the values of start_config in
  *                                 reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_syncro_mode_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_start_config_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_config.start_config = (uint8_t)val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_syncro_mode: [get] Sensor hub trigger signal selection.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_start_config_t: Get the values of start_config in
  *                                 reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_syncro_mode_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_start_config_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  switch (reg.master_config.start_config)
  {
    case LSM6DSL_XL_GY_DRDY:
      *val = LSM6DSL_XL_GY_DRDY;
      break;
    case LSM6DSL_EXT_ON_INT2_PIN:
      *val = LSM6DSL_EXT_ON_INT2_PIN;
      break;
    default:
      *val = LSM6DSL_SH_SYNCRO_ND;
      break;
  }

  return ret;
}

/**
  * @brief  sh_drdy_on_int1: [set] Manage the Master DRDY signal on INT1 pad.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of drdy_on_int1 in
  *                      reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_drdy_on_int1_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_config.drdy_on_int1 = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_drdy_on_int1: [get]  Manage the Master DRDY signal on INT1 pad.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of drdy_on_int1 in reg MASTER_CONFIG
  *
  */
int32_t lsm6dsl_sh_drdy_on_int1_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CONFIG, &reg.byte, 1);
  *val = reg.master_config.drdy_on_int1;

  return ret;
}

/**
  * @brief  sh_read_data_raw: [get]  Sensor hub output registers.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_: union of registers from SENSORHUB1_REG to
  *
  */
int32_t lsm6dsl_sh_read_data_raw_get(lsm6dsl_ctx_t *ctx,
                                     lsm6dsl_emb_sh_read_t *val)
{
  int32_t ret;
  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENSORHUB1_REG,
                         &(val->byte[0]), 12);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENSORHUB13_REG,
                           &(val->byte[12]), 6);
  }
  return ret;
}

/**
  * @brief  sh_cmd_sens_sync: [set] Master command code used for stamping
  *                                 for sensor sync.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of master_cmd_code in
  *                      reg MASTER_CMD_CODE
  *
  */
int32_t lsm6dsl_sh_cmd_sens_sync_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CMD_CODE, &reg.byte, 1);
  if (ret == 0)
  {
    reg.master_cmd_code.master_cmd_code = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_MASTER_CMD_CODE, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_cmd_sens_sync: [get] Master command code used for stamping
  *                                 for sensor sync.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of master_cmd_code in
  *                  reg MASTER_CMD_CODE
  *
  */
int32_t lsm6dsl_sh_cmd_sens_sync_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_MASTER_CMD_CODE, &reg.byte, 1);
  *val = reg.master_cmd_code.master_cmd_code;

  return ret;
}

/**
  * @brief  sh_spi_sync_error: [set] Error code used for sensor
  *                                  synchronization.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of error_code in
  *                      reg SENS_SYNC_SPI_ERROR_CODE
  *
  */
int32_t lsm6dsl_sh_spi_sync_error_set(lsm6dsl_ctx_t *ctx, uint8_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENS_SYNC_SPI_ERROR_CODE,
                         &reg.byte, 1);
  if (ret == 0)
  {
    reg. sens_sync_spi_error_code.error_code = val;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SENS_SYNC_SPI_ERROR_CODE,
                            &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  sh_spi_sync_error: [get] Error code used for sensor
  *                                  synchronization.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of error_code in
  *                  reg SENS_SYNC_SPI_ERROR_CODE
  *
  */
int32_t lsm6dsl_sh_spi_sync_error_get(lsm6dsl_ctx_t *ctx, uint8_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_read_reg(ctx, LSM6DSL_SENS_SYNC_SPI_ERROR_CODE,
                         &reg.byte, 1);
  *val = reg. sens_sync_spi_error_code.error_code;

  return ret;
}

/**
  * @brief   sh_num_of_dev_connected: [set] Number of external sensors to
  *                                         be read by the sensor hub.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_aux_sens_on_t: change the values of aux_sens_on in
  *                                reg SLAVE0_CONFIG
  *
  */
int32_t lsm6dsl_sh_num_of_dev_connected_set(lsm6dsl_ctx_t *ctx,
                                            lsm6dsl_aux_sens_on_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      reg.slave0_config.aux_sens_on = (uint8_t) val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief   sh_num_of_dev_connected: [get] Number of external sensors to
  *                                         be read by the sensor hub.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_aux_sens_on_t: Get the values of aux_sens_on in
  *                                reg SLAVE0_CONFIG
  *
  */
int32_t lsm6dsl_sh_num_of_dev_connected_get(lsm6dsl_ctx_t *ctx,
                                            lsm6dsl_aux_sens_on_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.slave0_config.aux_sens_on)
      {
        case LSM6DSL_SLV_0:
          *val = LSM6DSL_SLV_0;
          break;
        case LSM6DSL_SLV_0_1:
          *val = LSM6DSL_SLV_0_1;
          break;
        case LSM6DSL_SLV_0_1_2:
          *val = LSM6DSL_SLV_0_1_2;
          break;
        case LSM6DSL_SLV_0_1_2_3:
          *val = LSM6DSL_SLV_0_1_2_3;
          break;
        default:
          *val = LSM6DSL_SLV_EN_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/**
  * @brief  sh_cfg_write: Configure slave 0 for perform a write.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sh_cfg_write_t: a structure that contain
  *                      - uint8_t slv_add;    8 bit i2c device address
  *                      - uint8_t slv_subadd; 8 bit register device address
  *                      - uint8_t slv_data;   8 bit data to write
  *
  */
int32_t lsm6dsl_sh_cfg_write(lsm6dsl_ctx_t *ctx, lsm6dsl_sh_cfg_write_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    reg.byte = val->slv0_add;
    reg.slv0_add.rw_0 = 0;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV0_ADD, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV0_SUBADD,
                              &(val->slv0_subadd), 1);
      if (ret == 0)
      {
        ret = lsm6dsl_write_reg(ctx, LSM6DSL_DATAWRITE_SRC_MODE_SUB_SLV0,
                                &(val->slv0_data), 1);
        if (ret == 0)
        {
          ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slv0_cfg_read: [get] Configure slave 0 for perform a write/read.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sh_cfg_read_t: a structure that contain
  *                      - uint8_t slv_add;    8 bit i2c device address
  *                      - uint8_t slv_subadd; 8 bit register device address
  *                      - uint8_t slv_len;    num of bit to read
  *
  */
int32_t lsm6dsl_sh_slv0_cfg_read(lsm6dsl_ctx_t *ctx,
                                 lsm6dsl_sh_cfg_read_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    reg.byte = val->slv_add;
    reg.slv0_add.rw_0 = 1;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV0_ADD, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV0_SUBADD,
                              &(val->slv_subadd), 1);
      if (ret == 0)
      {
        ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
        reg.slave0_config.slave0_numop = val->slv_len;
        if (ret == 0)
        {
          ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
          if (ret == 0)
          {
            ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
          }
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slv1_cfg_read: [get] Configure slave 0 for perform a write/read.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sh_cfg_read_t: a structure that contain
  *                      - uint8_t slv_add;    8 bit i2c device address
  *                      - uint8_t slv_subadd; 8 bit register device address
  *                      - uint8_t slv_len;    num of bit to read
  *
  */
int32_t lsm6dsl_sh_slv1_cfg_read(lsm6dsl_ctx_t *ctx,
                                 lsm6dsl_sh_cfg_read_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    reg.byte = val->slv_add;
    reg.slv1_add.r_1 = 1;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV1_ADD, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV1_SUBADD,
                              &(val->slv_subadd), 1);
      if (ret == 0)
      {
        ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
        reg.slave1_config.slave1_numop = val->slv_len;
        if (ret == 0)
        {
          ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
          if (ret == 0)
          {
            ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
          }
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slv2_cfg_read: [get] Configure slave 0 for perform a write/read.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sh_cfg_read_t: a structure that contain
  *                      - uint8_t slv_add;    8 bit i2c device address
  *                      - uint8_t slv_subadd; 8 bit register device address
  *                      - uint8_t slv_len;    num of bit to read
  *
  */
int32_t lsm6dsl_sh_slv2_cfg_read(lsm6dsl_ctx_t *ctx,
                                 lsm6dsl_sh_cfg_read_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    reg.byte = val->slv_add;
    reg.slv2_add.r_2 = 1;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV2_ADD, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV2_SUBADD,
                              &(val->slv_subadd), 1);
      if (ret == 0)
      {
        ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE2_CONFIG, &reg.byte, 1);
        if (ret == 0)
        {
          reg.slave2_config.slave2_numop = val->slv_len;
          ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE2_CONFIG, &reg.byte, 1);
          if (ret == 0)
          {
            ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
          }
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  sh_slv3_cfg_read: [get] Configure slave 0 for perform a write/read.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_sh_cfg_read_t: a structure that contain
  *                      - uint8_t slv_add;    8 bit i2c device address
  *                      - uint8_t slv_subadd; 8 bit register device address
  *                      - uint8_t slv_len;    num of bit to read
  *
  */
int32_t lsm6dsl_sh_slv3_cfg_read(lsm6dsl_ctx_t *ctx,
                                 lsm6dsl_sh_cfg_read_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    reg.byte = val->slv_add;
    reg.slv3_add.r_3 = 1;
    ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV3_ADD, &reg.byte, 1);
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLV3_SUBADD,
                              &(val->slv_subadd), 1);
      if (ret == 0)
      {
        ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE3_CONFIG, &reg.byte, 1);
        if (ret == 0)
        {
          reg.slave3_config.slave3_numop = val->slv_len;
          ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE3_CONFIG, &reg.byte, 1);
          if (ret == 0)
          {
            ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
          }
        }
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slave_0_dec: [set] Decimation of read operation on Slave 0
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave0_rate_t: change the values of slave0_rate in
  *                                reg SLAVE0_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_0_dec_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave0_rate_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      reg.slave0_config.slave0_rate = (uint8_t) val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slave_0_dec: [get] Decimation of read operation on Slave 0
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave0_rate_t: Get the values of slave0_rate in
  *                                reg SLAVE0_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_0_dec_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave0_rate_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE0_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.slave0_config.slave0_rate)
      {
        case LSM6DSL_SL0_NO_DEC:
          *val = LSM6DSL_SL0_NO_DEC;
          break;
        case LSM6DSL_SL0_DEC_2:
          *val = LSM6DSL_SL0_DEC_2;
          break;
        case LSM6DSL_SL0_DEC_4:
          *val = LSM6DSL_SL0_DEC_4;
          break;
        case LSM6DSL_SL0_DEC_8:
          *val = LSM6DSL_SL0_DEC_8;
          break;
        default:
          *val = LSM6DSL_SL0_DEC_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/**
  * @brief  sh_write_mode: [set] Slave 0 write operation is performed only
  *                              at the first sensor hub cycle.
  *                              This is effective if the Aux_sens_on[1:0]
  *                              field in SLAVE0_CONFIG (04h) is set to a
  *                              value other than 00.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_write_once_t: change the values of write_once in
  *                               reg SLAVE1_CONFIG
  *
  */
int32_t lsm6dsl_sh_write_mode_set(lsm6dsl_ctx_t *ctx, lsm6dsl_write_once_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
    reg.slave1_config.write_once = (uint8_t) val;
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_write_mode: [get] Slave 0 write operation is performed only
  *                              at the first sensor hub cycle.
  *                              This is effective if the Aux_sens_on[1:0]
  *                              field in SLAVE0_CONFIG (04h) is set to a
  *                              value other than 00
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_write_once_t: Get the values of write_once in
  *                               reg SLAVE1_CONFIG
  *
  */
int32_t lsm6dsl_sh_write_mode_get(lsm6dsl_ctx_t *ctx,
                                  lsm6dsl_write_once_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.slave1_config.write_once)
      {
        case LSM6DSL_EACH_SH_CYCLE:
          *val = LSM6DSL_EACH_SH_CYCLE;
          break;
        case LSM6DSL_ONLY_FIRST_CYCLE:
          *val = LSM6DSL_ONLY_FIRST_CYCLE;
          break;
        default:
          *val = LSM6DSL_SH_WR_MODE_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/**
  * @brief  sh_slave_1_dec: [set] Decimation of read operation on Slave 1
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave1_rate_t: change the values of slave1_rate in
  *                                reg SLAVE1_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_1_dec_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave1_rate_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      reg.slave1_config.slave1_rate = (uint8_t) val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slave_1_dec: [get] Decimation of read operation on Slave 1
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave1_rate_t: Get the values of slave1_rate in
  *                                reg SLAVE1_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_1_dec_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave1_rate_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE1_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.slave1_config.slave1_rate)
      {
        case LSM6DSL_SL1_NO_DEC:
          *val = LSM6DSL_SL1_NO_DEC;
          break;
        case LSM6DSL_SL1_DEC_2:
          *val = LSM6DSL_SL1_DEC_2;
          break;
        case LSM6DSL_SL1_DEC_4:
          *val = LSM6DSL_SL1_DEC_4;
          break;
        case LSM6DSL_SL1_DEC_8:
          *val = LSM6DSL_SL1_DEC_8;
          break;
        default:
          *val = LSM6DSL_SL1_DEC_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/**
  * @brief  sh_slave_2_dec: [set] Decimation of read operation on Slave 2
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave2_rate_t: change the values of slave2_rate in
  *                                reg SLAVE2_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_2_dec_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave2_rate_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE2_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      reg.slave2_config.slave2_rate = (uint8_t) val;
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE2_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slave_2_dec: [get] Decimation of read operation on Slave 2
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave2_rate_t: Get the values of slave2_rate in
  *                                reg SLAVE2_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_2_dec_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave2_rate_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE2_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.slave2_config.slave2_rate)
      {
        case LSM6DSL_SL2_NO_DEC:
          *val = LSM6DSL_SL2_NO_DEC;
          break;
        case LSM6DSL_SL2_DEC_2:
          *val = LSM6DSL_SL2_DEC_2;
          break;
        case LSM6DSL_SL2_DEC_4:
          *val = LSM6DSL_SL2_DEC_4;
          break;
        case LSM6DSL_SL2_DEC_8:
          *val = LSM6DSL_SL2_DEC_8;
          break;
        default:
          *val = LSM6DSL_SL2_DEC_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/**
  * @brief  sh_slave_3_dec: [set] Decimation of read operation on
  *                               Slave 3 starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave3_rate_t: change the values of slave3_rate in
  *                                reg SLAVE3_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_3_dec_set(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave3_rate_t val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE3_CONFIG, &reg.byte, 1);
    reg.slave3_config.slave3_rate = (uint8_t)val;
    if (ret == 0)
    {
      ret = lsm6dsl_write_reg(ctx, LSM6DSL_SLAVE3_CONFIG, &reg.byte, 1);
      if (ret == 0)
      {
        ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
      }
    }
  }
  return ret;
}

/**
  * @brief  sh_slave_3_dec: [get] Decimation of read operation on Slave 3
  *                               starting from the sensor hub trigger.
  *
  * @param  lsm6dsl_ctx_t *ctx: read / write interface definitions
  * @param  lsm6dsl_slave3_rate_t: Get the values of slave3_rate in
  *                                reg SLAVE3_CONFIG
  *
  */
int32_t lsm6dsl_sh_slave_3_dec_get(lsm6dsl_ctx_t *ctx,
                                   lsm6dsl_slave3_rate_t *val)
{
  lsm6dsl_reg_t reg;
  int32_t ret;

  ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_BANK_A);
  if (ret == 0)
  {
    ret = lsm6dsl_read_reg(ctx, LSM6DSL_SLAVE3_CONFIG, &reg.byte, 1);
    if (ret == 0)
    {
      switch (reg.slave3_config.slave3_rate)
      {
        case LSM6DSL_SL3_NO_DEC:
          *val = LSM6DSL_SL3_NO_DEC;
          break;
        case LSM6DSL_SL3_DEC_2:
          *val = LSM6DSL_SL3_DEC_2;
          break;
        case LSM6DSL_SL3_DEC_4:
          *val = LSM6DSL_SL3_DEC_4;
          break;
        case LSM6DSL_SL3_DEC_8:
          *val = LSM6DSL_SL3_DEC_8;
          break;
        default:
          *val = LSM6DSL_SL3_DEC_ND;
          break;
      }
      ret = lsm6dsl_mem_bank_set(ctx, LSM6DSL_USER_BANK);
    }
  }

  return ret;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

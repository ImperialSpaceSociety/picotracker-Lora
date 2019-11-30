/*
 ******************************************************************************
 * @file    lps22hb_reg.c
 * @author  MEMS Software Solution Team
 * @brief   LPS22HB driver file
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

#include "lps22hb_reg.h"

/**
  * @addtogroup  lps22hb
  * @brief  This file provides a set of functions needed to drive the
  *         lps22hb enanced inertial module.
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
  * @param  lps22hb_ctx_t* ctx: read / write interface definitions
  * @param  uint8_t reg: register to read
  * @param  uint8_t* data: pointer to buffer that store the data read
  * @param  uint16_t len: number of consecutive register to read
  *
  */
int32_t lps22hb_read_reg(lps22hb_ctx_t *ctx, uint8_t reg, uint8_t *data,
                         uint16_t len)
{
  int32_t ret;
  ret = ctx->read_reg(ctx->handle, reg, data, len);
  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t reg: register to write
  * @param  uint8_t* data: pointer to data to write in register reg
  * @param  uint16_t len: number of consecutive register to write
  *
*/
int32_t lps22hb_write_reg(lps22hb_ctx_t *ctx, uint8_t reg, uint8_t *data,
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
  * @addtogroup  data_generation_c
  * @brief   This section group all the functions concerning data generation
  * @{
  */

/**
  * @brief  autozero_rst: [set]  Reset Autozero function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of reset_az in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_autozero_rst_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.reset_az = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  autozero_rst: [get]  Reset Autozero function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of reset_az in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_autozero_rst_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  *val = reg.interrupt_cfg.reset_az;

  return ret;
}

/**
  * @brief  autozero: [set]  Enable Autozero function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of autozero in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_autozero_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.autozero = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  autozero: [get]  Enable Autozero function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of autozero in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_autozero_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  *val = reg.interrupt_cfg.autozero;

  return ret;
}

/**
  * @brief  pressure_snap_rst: [set]  Reset AutoRifP function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of reset_arp in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_pressure_snap_rst_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.reset_arp = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  pressure_snap_rst: [get]  Reset AutoRifP function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of reset_arp in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_pressure_snap_rst_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  *val = reg.interrupt_cfg.reset_arp;

  return ret;
}

/**
  * @brief  pressure_snap: [set]  Enable AutoRifP function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of autorifp in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_pressure_snap_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.autorifp = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  pressure_snap: [get]  Enable AutoRifP function.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of autorifp in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_pressure_snap_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  *val = reg.interrupt_cfg.autorifp;

  return ret;
}

/**
  * @brief  block_data_update: [set] Blockdataupdate.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of bdu in reg CTRL_REG1
  *
  */
int32_t lps22hb_block_data_update_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg1.bdu = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  block_data_update: [get] Blockdataupdate.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of bdu in reg CTRL_REG1
  *
  */
int32_t lps22hb_block_data_update_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  *val = reg.ctrl_reg1.bdu;

  return ret;
}

/**
  * @brief   low_pass_filter_mode: [set]  Low-pass bandwidth selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_lpfp_t: change the values of lpfp in reg CTRL_REG1
  *
  */
int32_t lps22hb_low_pass_filter_mode_set(lps22hb_ctx_t *ctx,
                                         lps22hb_lpfp_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg1.lpfp = (uint8_t) val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief   low_pass_filter_mode: [get]  Low-pass bandwidth selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_lpfp_t: Get the values of lpfp in reg CTRL_REG1
  *
  */
int32_t lps22hb_low_pass_filter_mode_get(lps22hb_ctx_t *ctx,
                                         lps22hb_lpfp_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);

  switch (reg.ctrl_reg1.lpfp)
  {
    case LPS22HB_LPF_ODR_DIV_2:
      *val = LPS22HB_LPF_ODR_DIV_2;
      break;
    case LPS22HB_LPF_ODR_DIV_9:
      *val = LPS22HB_LPF_ODR_DIV_9;
      break;
    case LPS22HB_LPF_ODR_DIV_20:
      *val = LPS22HB_LPF_ODR_DIV_20;
      break;
    default:
      *val = LPS22HB_LPF_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  data_rate: [set]  Output data rate selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_odr_t: change the values of odr in reg CTRL_REG1
  *
  */
int32_t lps22hb_data_rate_set(lps22hb_ctx_t *ctx, lps22hb_odr_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg1.odr = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  data_rate: [get]  Output data rate selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_odr_t: Get the values of odr in reg CTRL_REG1
  *
  */
int32_t lps22hb_data_rate_get(lps22hb_ctx_t *ctx, lps22hb_odr_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);

  switch (reg.ctrl_reg1.odr)
  {
    case LPS22HB_POWER_DOWN:
      *val = LPS22HB_POWER_DOWN;
      break;
    case LPS22HB_ODR_1_Hz:
      *val = LPS22HB_ODR_1_Hz;
      break;
    case LPS22HB_ODR_10_Hz:
      *val = LPS22HB_ODR_10_Hz;
      break;
    case LPS22HB_ODR_25_Hz:
      *val = LPS22HB_ODR_25_Hz;
      break;
    case LPS22HB_ODR_50_Hz:
      *val = LPS22HB_ODR_50_Hz;
      break;
    case LPS22HB_ODR_75_Hz:
      *val = LPS22HB_ODR_75_Hz;
      break;
    default:
      *val = LPS22HB_ODR_ND;
      break;
  }
  return ret;
}

/**
  * @brief  one_shoot_trigger: [set]  One-shot mode. Device perform
  *                                   a single measure.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of one_shot in reg CTRL_REG2
  *
  */
int32_t lps22hb_one_shoot_trigger_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.one_shot = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  one_shoot_trigger: [get]  One-shot mode. Device perform
  *                                   a single measure.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of one_shot in reg CTRL_REG2
  *
  */
int32_t lps22hb_one_shoot_trigger_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.one_shot;

  return ret;
}

/**
  * @brief  pressure_ref: [set]  The Reference pressure value is a 24-bit
  *                              data expressed as 2’s complement. The value
  *                              is used when AUTOZERO or AUTORIFP function
  *                              is enabled.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lps22hb_pressure_ref_set(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_write_reg(ctx, LPS22HB_REF_P_XL, buff, 3);
}

/**
  * @brief  pressure_ref: [get]  The Reference pressure value is a
  *                              24-bit data expressed as 2’s complement.
  *                              The value is used when AUTOZERO or AUTORIFP
  *                              function is enabled.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_pressure_ref_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_REF_P_XL, buff, 3);
}

/**
  * @brief  pressure_offset: [set]  The pressure offset value is 16-bit
  *                                 data that can be used to implement
  *                                 one-point calibration (OPC) after
  *                                 soldering.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lps22hb_pressure_offset_set(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_write_reg(ctx, LPS22HB_RPDS_L, buff, 2);
}

/**
  * @brief  pressure_offset: [get]  The pressure offset value is 16-bit
  *                                 data that can be used to implement
  *                                 one-point calibration (OPC) after
  *                                 soldering.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_pressure_offset_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_RPDS_L, buff, 2);
}

/**
  * @brief  press_data_ready: [get]  Pressure data available.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of p_da in reg STATUS
  *
  */
int32_t lps22hb_press_data_ready_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_STATUS, &(reg.byte), 1);
  *val = reg.status.p_da;

  return ret;
}

/**
  * @brief  temp_data_ready: [get]  Temperature data available.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of t_da in reg STATUS
  *
  */
int32_t lps22hb_temp_data_ready_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_STATUS, &(reg.byte), 1);
  *val = reg.status.t_da;

  return ret;
}

/**
  * @brief  press_data_ovr: [get]  Pressure data overrun.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of p_or in reg STATUS
  *
  */
int32_t lps22hb_press_data_ovr_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_STATUS, &(reg.byte), 1);
  *val = reg.status.p_or;

  return ret;
}

/**
  * @brief  temp_data_ovr: [get]  Temperature data overrun.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of t_or in reg STATUS
  *
  */
int32_t lps22hb_temp_data_ovr_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_STATUS, &(reg.byte), 1);
  *val = reg.status.t_or;

  return ret;
}

/**
  * @brief  pressure_raw: [get]  Pressure output value
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_pressure_raw_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_PRESS_OUT_XL, buff, 3);
}

/**
  * @brief  temperature_raw: [get]  Temperature output value
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_temperature_raw_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_TEMP_OUT_L, (uint8_t *) buff, 2);
}

/**
  * @brief  low_pass_rst: [get]  Low-pass filter reset register. If the
  *                              LPFP is active, in order to avoid the
  *                              transitory phase, the filter can be reset
  *                              by reading this register before generating
  *                              pressure measurements.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_low_pass_rst_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_LPFP_RES, (uint8_t *) buff, 1);
}

/**
  * @}
  */

/**
  * @addtogroup  common
  * @brief   This section group common usefull functions
  * @{
  */

/**
  * @brief  device_id: [get] DeviceWhoamI
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_device_id_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_WHO_AM_I, (uint8_t *) buff, 1);
}

/**
  * @brief  reset: [set]  Software reset. Restore the default values
  *                       in user registers
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of swreset in reg CTRL_REG2
  *
  */
int32_t lps22hb_reset_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.swreset = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  reset: [get]  Software reset. Restore the default values
  *                       in user registers
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of swreset in reg CTRL_REG2
  *
  */
int32_t lps22hb_reset_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.swreset;

  return ret;
}

/**
  * @brief  boot: [set]  Reboot memory content. Reload the calibration
  *                      parameters
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of boot in reg CTRL_REG2
  *
  */
int32_t lps22hb_boot_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.boot = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  boot: [get]  Reboot memory content. Reload the calibration
  *                      parameters
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of boot in reg CTRL_REG2
  *
  */
int32_t lps22hb_boot_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.boot;

  return ret;
}

/**
  * @brief  low_power: [set] Lowcurrentmode.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of lc_en in reg RES_CONF
  *
  */
int32_t lps22hb_low_power_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_RES_CONF, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.res_conf.lc_en = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_RES_CONF, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  low_power: [get] Lowcurrentmode.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of lc_en in reg RES_CONF
  *
  */
int32_t lps22hb_low_power_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_RES_CONF, &(reg.byte), 1);
  *val = reg.res_conf.lc_en;

  return ret;
}

/**
  * @brief  boot_status: [get]  If ‘1’ indicates that the Boot (Reboot)
  *                             phase is running.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of boot_status in reg INT_SOURCE
  *
  */
int32_t lps22hb_boot_status_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INT_SOURCE, &(reg.byte), 1);
  *val = reg.int_source.boot_status;

  return ret;
}

/**
  * @brief  dev_status: [get]  All the status bit, FIFO and data generation
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_dev_stat: union of registers from FIFO_STATUS to STATUS
  *
  */
int32_t lps22hb_dev_status_get(lps22hb_ctx_t *ctx, lps22hb_dev_stat_t *val)
{
  return lps22hb_read_reg(ctx, LPS22HB_FIFO_STATUS, (uint8_t *) val, 2);
}

/**
  * @}
  */

/**
  * @addtogroup  interrupts
  * @brief   This section group all the functions that manage interrupts
  * @{
  */

/**
  * @brief   sign_of_int_threshold: [set]  Enable interrupt generation on
  *                                        pressure low/high event.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_pe_t: change the values of pe in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_sign_of_int_threshold_set(lps22hb_ctx_t *ctx,
                                          lps22hb_pe_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.pe = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief   sign_of_int_threshold: [get]  Enable interrupt generation on
  *                                        pressure low/high event.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_pe_t: Get the values of pe in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_sign_of_int_threshold_get(lps22hb_ctx_t *ctx,
                                          lps22hb_pe_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);

  switch (reg.interrupt_cfg.pe)
  {
    case LPS22HB_NO_THRESHOLD:
      *val = LPS22HB_NO_THRESHOLD;
      break;
    case LPS22HB_POSITIVE:
      *val = LPS22HB_POSITIVE;
      break;
    case LPS22HB_NEGATIVE:
      *val = LPS22HB_NEGATIVE;
      break;
    case LPS22HB_BOTH:
      *val = LPS22HB_BOTH;
      break;
    default:
      *val = LPS22HB_SIGN_ND;
      break;
  }
  return ret;
}

/**
  * @brief   int_notification_mode: [set]  Interrupt request to the
  *                                        INT_SOURCE (25h) register
  *                                        mode (pulsed / latched)
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_lir_t: change the values of lir in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_int_notification_mode_set(lps22hb_ctx_t *ctx,
                                          lps22hb_lir_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.lir = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief   int_notification_mode: [get]  Interrupt request to the
  *                                        INT_SOURCE (25h) register
  *                                        mode (pulsed / latched)
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_lir_t: Get the values of lir in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_int_notification_mode_get(lps22hb_ctx_t *ctx,
                                          lps22hb_lir_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);

  switch (reg.interrupt_cfg.lir)
  {
    case LPS22HB_INT_PULSED:
      *val = LPS22HB_INT_PULSED;
      break;
    case LPS22HB_INT_LATCHED:
      *val = LPS22HB_INT_LATCHED;
      break;
    default:
      *val = LPS22HB_INT_MODE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  int_generation: [set]  Enable interrupt generation.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of diff_en in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_int_generation_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.interrupt_cfg.diff_en = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  int_generation: [get]  Enable interrupt generation.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of diff_en in reg INTERRUPT_CFG
  *
  */
int32_t lps22hb_int_generation_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INTERRUPT_CFG, &(reg.byte), 1);
  *val = reg.interrupt_cfg.diff_en;

  return ret;
}

/**
  * @brief  int_threshold: [set]  User-defined threshold value for
  *                              pressure interrupt event
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that contains data to write
  *
  */
int32_t lps22hb_int_threshold_set(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_write_reg(ctx, LPS22HB_THS_P_L, (uint8_t *) buff, 2);
}

/**
  * @brief  int_threshold: [get]  User-defined threshold value for
  *                              pressure interrupt event
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lps22hb_int_threshold_get(lps22hb_ctx_t *ctx, uint8_t *buff)
{
  return lps22hb_read_reg(ctx, LPS22HB_THS_P_L, (uint8_t *) buff, 2);
}

/**
  * @brief  int_pin_mode: [set]  Data signal on INT_DRDY pin control bits.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_int_s_t: change the values of int_s in reg CTRL_REG3
  *
  */
int32_t lps22hb_int_pin_mode_set(lps22hb_ctx_t *ctx, lps22hb_int_s_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.int_s = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  int_pin_mode: [get]  Data signal on INT_DRDY pin control bits.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_int_s_t: Get the values of int_s in reg CTRL_REG3
  *
  */
int32_t lps22hb_int_pin_mode_get(lps22hb_ctx_t *ctx, lps22hb_int_s_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);

  switch (reg.ctrl_reg3.int_s)
  {
    case LPS22HB_DRDY_OR_FIFO_FLAGS:
      *val = LPS22HB_DRDY_OR_FIFO_FLAGS;
      break;
    case LPS22HB_HIGH_PRES_INT:
      *val = LPS22HB_HIGH_PRES_INT;
      break;
    case LPS22HB_LOW_PRES_INT:
      *val = LPS22HB_LOW_PRES_INT;
      break;
    case LPS22HB_EVERY_PRES_INT:
      *val = LPS22HB_EVERY_PRES_INT;
      break;
    default:
      *val = LPS22HB_PIN_ROUTE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  drdy_on_int: [set]  Data-ready signal on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of drdy in reg CTRL_REG3
  *
  */
int32_t lps22hb_drdy_on_int_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.drdy = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  drdy_on_int: [get]  Data-ready signal on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of drdy in reg CTRL_REG3
  *
  */
int32_t lps22hb_drdy_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.drdy;

  return ret;
}

/**
  * @brief  fifo_ovr_on_int: [set]  FIFO overrun interrupt on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of f_ovr in reg CTRL_REG3
  *
  */
int32_t lps22hb_fifo_ovr_on_int_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.f_ovr = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  fifo_ovr_on_int: [get]  FIFO overrun interrupt on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of f_ovr in reg CTRL_REG3
  *
  */
int32_t lps22hb_fifo_ovr_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.f_ovr;

  return ret;
}

/**
  * @brief   fifo_threshold_on_int: [set]  FIFO watermark status
  *                                        on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of f_fth in reg CTRL_REG3
  *
  */
int32_t lps22hb_fifo_threshold_on_int_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.f_fth = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief   fifo_threshold_on_int: [get]  FIFO watermark status
  *                                        on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of f_fth in reg CTRL_REG3
  *
  */
int32_t lps22hb_fifo_threshold_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.f_fth;

  return ret;
}

/**
  * @brief  fifo_full_on_int: [set]  FIFO full flag on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of f_fss5 in reg CTRL_REG3
  *
  */
int32_t lps22hb_fifo_full_on_int_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.f_fss5 = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  fifo_full_on_int: [get]  FIFO full flag on INT_DRDY pin.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of f_fss5 in reg CTRL_REG3
  *
  */
int32_t lps22hb_fifo_full_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  *val = reg.ctrl_reg3.f_fss5;

  return ret;
}

/**
  * @brief  pin_mode: [set]  Push-pull/open drain selection on interrupt pads.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_pp_od_t: change the values of pp_od in reg CTRL_REG3
  *
  */
int32_t lps22hb_pin_mode_set(lps22hb_ctx_t *ctx, lps22hb_pp_od_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.pp_od = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  pin_mode: [get]  Push-pull/open drain selection on interrupt pads.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_pp_od_t: Get the values of pp_od in reg CTRL_REG3
  *
  */
int32_t lps22hb_pin_mode_get(lps22hb_ctx_t *ctx, lps22hb_pp_od_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);

  switch (reg.ctrl_reg3.pp_od)
  {
    case LPS22HB_PUSH_PULL:
      *val = LPS22HB_PUSH_PULL;
      break;
    case LPS22HB_OPEN_DRAIN:
      *val = LPS22HB_OPEN_DRAIN;
      break;
    default:
      *val = LPS22HB_PIN_MODE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  int_polarity: [set]  Interrupt active-high/low.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_int_h_l_t: change the values of int_h_l in reg CTRL_REG3
  *
  */
int32_t lps22hb_int_polarity_set(lps22hb_ctx_t *ctx, lps22hb_int_h_l_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg3.int_h_l = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  int_polarity: [get]  Interrupt active-high/low.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_int_h_l_t: Get the values of int_h_l in reg CTRL_REG3
  *
  */
int32_t lps22hb_int_polarity_get(lps22hb_ctx_t *ctx, lps22hb_int_h_l_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG3, &(reg.byte), 1);

  switch (reg.ctrl_reg3.int_h_l)
  {
    case LPS22HB_ACTIVE_HIGH:
      *val = LPS22HB_ACTIVE_HIGH;
      break;
    case LPS22HB_ACTIVE_LOW:
      *val = LPS22HB_ACTIVE_LOW;
      break;
    default:
      *val = LPS22HB_POLARITY_ND;
      break;
  }
  return ret;
}

/**
  * @brief  int_source: [get]  Interrupt source register
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_int_source_t: register INT_SOURCE
  *
  */
int32_t lps22hb_int_source_get(lps22hb_ctx_t *ctx, lps22hb_int_source_t *val)
{
  return lps22hb_read_reg(ctx, LPS22HB_INT_SOURCE, (uint8_t *) val, 1);
}

/**
  * @brief  int_on_press_high: [get]  Differential pressure high
  *                                   interrupt flag.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of ph in reg INT_SOURCE
  *
  */
int32_t lps22hb_int_on_press_high_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INT_SOURCE, &(reg.byte), 1);
  *val = reg.int_source.ph;

  return ret;
}

/**
  * @brief  int_on_press_low: [get]  Differential pressure low interrupt flag.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of pl in reg INT_SOURCE
  *
  */
int32_t lps22hb_int_on_press_low_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INT_SOURCE, &(reg.byte), 1);
  *val = reg.int_source.pl;

  return ret;
}

/**
  * @brief  interrupt_event: [get]  Interrupt active flag.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of ia in reg INT_SOURCE
  *
  */
int32_t lps22hb_interrupt_event_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_INT_SOURCE, &(reg.byte), 1);
  *val = reg.int_source.ia;

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
  * @brief   stop_on_fifo_threshold: [set]  Stop on FIFO watermark.
  *                                         Enable FIFO watermark level use.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of stop_on_fth in reg CTRL_REG2
  *
  */
int32_t lps22hb_stop_on_fifo_threshold_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.stop_on_fth = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief   stop_on_fifo_threshold: [get]  Stop on FIFO watermark.
  *                                         Enable FIFO watermark level use.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of stop_on_fth in reg CTRL_REG2
  *
  */
int32_t lps22hb_stop_on_fifo_threshold_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.stop_on_fth;

  return ret;
}

/**
  * @brief  fifo: [set] FIFOenable.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of fifo_en in reg CTRL_REG2
  *
  */
int32_t lps22hb_fifo_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.fifo_en = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  fifo: [get] FIFOenable.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of fifo_en in reg CTRL_REG2
  *
  */
int32_t lps22hb_fifo_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.fifo_en;

  return ret;
}

/**
  * @brief  fifo_watermark: [set]  FIFO watermark level selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of wtm in reg FIFO_CTRL
  *
  */
int32_t lps22hb_fifo_watermark_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_CTRL, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.fifo_ctrl.wtm = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_FIFO_CTRL, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  fifo_watermark: [get]  FIFO watermark level selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of wtm in reg FIFO_CTRL
  *
  */
int32_t lps22hb_fifo_watermark_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_CTRL, &(reg.byte), 1);
  *val = reg.fifo_ctrl.wtm;

  return ret;
}

/**
  * @brief  fifo_mode: [set]  FIFO mode selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_f_mode_t: change the values of f_mode in reg FIFO_CTRL
  *
  */
int32_t lps22hb_fifo_mode_set(lps22hb_ctx_t *ctx, lps22hb_f_mode_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_CTRL, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.fifo_ctrl.f_mode = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_FIFO_CTRL, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  fifo_mode: [get]  FIFO mode selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_f_mode_t: Get the values of f_mode in reg FIFO_CTRL
  *
  */
int32_t lps22hb_fifo_mode_get(lps22hb_ctx_t *ctx, lps22hb_f_mode_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_CTRL, &(reg.byte), 1);

  switch (reg.fifo_ctrl.f_mode)
  {
    case LPS22HB_BYPASS_MODE:
      *val = LPS22HB_BYPASS_MODE;
      break;
    case LPS22HB_FIFO_MODE:
      *val = LPS22HB_FIFO_MODE;
      break;
    case LPS22HB_STREAM_MODE:
      *val = LPS22HB_STREAM_MODE;
      break;
    case LPS22HB_STREAM_TO_FIFO_MODE:
      *val = LPS22HB_STREAM_TO_FIFO_MODE;
      break;
    case LPS22HB_BYPASS_TO_STREAM_MODE:
      *val = LPS22HB_BYPASS_TO_STREAM_MODE;
      break;
    case LPS22HB_DYNAMIC_STREAM_MODE:
      *val = LPS22HB_DYNAMIC_STREAM_MODE;
      break;
    case LPS22HB_BYPASS_TO_FIFO_MODE:
      *val = LPS22HB_BYPASS_TO_FIFO_MODE;
      break;
    default:
      *val = LPS22HB_FIFO_MODE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  fifo_data_level: [get]  FIFO stored data level.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of fss in reg FIFO_STATUS
  *
  */
int32_t lps22hb_fifo_data_level_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_STATUS, &(reg.byte), 1);
  *val = reg.fifo_status.fss;

  return ret;
}

/**
  * @brief  fifo_ovr_flag: [get]  FIFO overrun status.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of ovr in reg FIFO_STATUS
  *
  */
int32_t lps22hb_fifo_ovr_flag_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_STATUS, &(reg.byte), 1);
  *val = reg.fifo_status.ovr;

  return ret;
}

/**
  * @brief  fifo_fth_flag: [get]  FIFO watermark status.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of fth_fifo in reg FIFO_STATUS
  *
  */
int32_t lps22hb_fifo_fth_flag_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_FIFO_STATUS, &(reg.byte), 1);
  *val = reg.fifo_status.fth_fifo;

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  serial_interface
  * @brief   This section group all the functions concerning serial
  *          interface management
  * @{
  */

/**
  * @brief  spi_mode: [set]  SPI Serial Interface Mode selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_sim_t: change the values of sim in reg CTRL_REG1
  *
  */
int32_t lps22hb_spi_mode_set(lps22hb_ctx_t *ctx, lps22hb_sim_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg1.sim = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  spi_mode: [get]  SPI Serial Interface Mode selection.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_sim_t: Get the values of sim in reg CTRL_REG1
  *
  */
int32_t lps22hb_spi_mode_get(lps22hb_ctx_t *ctx, lps22hb_sim_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG1, &(reg.byte), 1);

  switch (reg.ctrl_reg1.sim)
  {
    case LPS22HB_SPI_4_WIRE:
      *val = LPS22HB_SPI_4_WIRE;
      break;
    case LPS22HB_SPI_3_WIRE:
      *val = LPS22HB_SPI_3_WIRE;
      break;
    default:
      *val = LPS22HB_SPI_MODE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  i2c_interface: [set]  Disable I2C interface.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_i2c_dis_t: change the values of i2c_dis in reg CTRL_REG2
  *
  */
int32_t lps22hb_i2c_interface_set(lps22hb_ctx_t *ctx, lps22hb_i2c_dis_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.i2c_dis = (uint8_t)val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  i2c_interface: [get]  Disable I2C interface.
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  lps22hb_i2c_dis_t: Get the values of i2c_dis in reg CTRL_REG2
  *
  */
int32_t lps22hb_i2c_interface_get(lps22hb_ctx_t *ctx, lps22hb_i2c_dis_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);

  switch (reg.ctrl_reg2.i2c_dis)
  {
    case LPS22HB_I2C_ENABLE:
      *val = LPS22HB_I2C_ENABLE;
      break;
    case LPS22HB_I2C_DISABLE:
      *val = LPS22HB_I2C_DISABLE;
      break;
    default:
      *val = LPS22HB_I2C_MODE_ND;
      break;
  }
  return ret;
}

/**
  * @brief  auto_add_inc: [set]  Register address automatically incremented
  *                              during a multiple byte access with a serial
  *                              interface (I2C or SPI).
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of if_add_inc in reg CTRL_REG2
  *
  */
int32_t lps22hb_auto_add_inc_set(lps22hb_ctx_t *ctx, uint8_t val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  if (ret == 0)
  {
    reg.ctrl_reg2.if_add_inc = val;
    ret = lps22hb_write_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  }
  return ret;
}

/**
  * @brief  auto_add_inc: [get]  Register address automatically
  *                              incremented during a multiple byte access
  *                              with a serial interface (I2C or SPI).
  *
  * @param  lps22hb_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of if_add_inc in reg CTRL_REG2
  *
  */
int32_t lps22hb_auto_add_inc_get(lps22hb_ctx_t *ctx, uint8_t *val)
{
  lps22hb_reg_t reg;
  int32_t ret;

  ret = lps22hb_read_reg(ctx, LPS22HB_CTRL_REG2, &(reg.byte), 1);
  *val = reg.ctrl_reg2.if_add_inc;

  return ret;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

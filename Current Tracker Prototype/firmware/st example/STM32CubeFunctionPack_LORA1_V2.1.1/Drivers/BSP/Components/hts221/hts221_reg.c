/*
 ******************************************************************************
 * @file    hts221_reg.c
 * @author  MEMS Software Solution Team
 * @brief   HTS221 driver file
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

#include "hts221_reg.h"

/**
  * @addtogroup  hts221
  * @brief  This file provides a set of functions needed to drive the
  *         hts221 enanced inertial module.
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
  * @param  hts221_ctx_t* ctx: read / write interface definitions
  * @param  uint8_t reg: register to read
  * @param  uint8_t* data: pointer to buffer that store the data read
  * @param  uint16_t len: number of consecutive register to read
  *
  */
int32_t hts221_read_reg(hts221_ctx_t *ctx, uint8_t reg, uint8_t *data,
                        uint16_t len)
{
  int32_t ret;
  ret = ctx->read_reg(ctx->handle, reg, data, len);
  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t reg: register to write
  * @param  uint8_t* data: pointer to data to write in register reg
  * @param  uint16_t len: number of consecutive register to write
  *
*/
int32_t hts221_write_reg(hts221_ctx_t *ctx, uint8_t reg, uint8_t *data,
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
  * @brief  humidity_avg: [set]  The numbers of averaged humidity samples.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_avgh_t: change the values of avgh in reg AV_CONF
  *
  */
int32_t hts221_humidity_avg_set(hts221_ctx_t *ctx, hts221_avgh_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_AV_CONF, &reg.byte, 1);

  if (ret == 0)
  {
    reg.av_conf.avgh = (uint8_t)val;
    ret = hts221_write_reg(ctx, HTS221_AV_CONF, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  humidity_avg: [get]  The numbers of averaged humidity samples.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_avgh_t: Get the values of avgh in reg AV_CONF
  *
  */
int32_t hts221_humidity_avg_get(hts221_ctx_t *ctx, hts221_avgh_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_AV_CONF, &reg.byte, 1);

  switch (reg.av_conf.avgh)
  {
    case HTS221_H_AVG_4:
      *val = HTS221_H_AVG_4;
      break;
    case HTS221_H_AVG_8:
      *val = HTS221_H_AVG_8;
      break;
    case HTS221_H_AVG_16:
      *val = HTS221_H_AVG_16;
      break;
    case HTS221_H_AVG_32:
      *val = HTS221_H_AVG_32;
      break;
    case HTS221_H_AVG_64:
      *val = HTS221_H_AVG_64;
      break;
    case HTS221_H_AVG_128:
      *val = HTS221_H_AVG_128;
      break;
    case HTS221_H_AVG_256:
      *val = HTS221_H_AVG_256;
      break;
    case HTS221_H_AVG_512:
      *val = HTS221_H_AVG_512;
      break;
    default:
      *val = HTS221_H_AVG_ND;
      break;
  }

  return ret;
}

/**
  * @brief  temperature_avg: [set]  The numbers of averaged temperature samples.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_avgt_t: change the values of avgt in reg AV_CONF
  *
  */
int32_t hts221_temperature_avg_set(hts221_ctx_t *ctx, hts221_avgt_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_AV_CONF, &reg.byte, 1);

  if (ret == 0)
  {
    reg.av_conf.avgt = (uint8_t)val;
    ret = hts221_write_reg(ctx, HTS221_AV_CONF, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  temperature_avg: [get]  The numbers of averaged temperature
  *                                 samples.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_avgt_t: Get the values of avgt in reg AV_CONF
  *
  */
int32_t hts221_temperature_avg_get(hts221_ctx_t *ctx, hts221_avgt_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_AV_CONF, &reg.byte, 1);

  switch (reg.av_conf.avgh)
  {
    case HTS221_T_AVG_2:
      *val = HTS221_T_AVG_2;
      break;
    case HTS221_T_AVG_4:
      *val = HTS221_T_AVG_4;
      break;
    case HTS221_T_AVG_8:
      *val = HTS221_T_AVG_8;
      break;
    case HTS221_T_AVG_16:
      *val = HTS221_T_AVG_16;
      break;
    case HTS221_T_AVG_32:
      *val = HTS221_T_AVG_32;
      break;
    case HTS221_T_AVG_64:
      *val = HTS221_T_AVG_64;
      break;
    case HTS221_T_AVG_128:
      *val = HTS221_T_AVG_128;
      break;
    case HTS221_T_AVG_256:
      *val = HTS221_T_AVG_256;
      break;
    default:
      *val = HTS221_T_AVG_ND;
      break;
  }

  return ret;
}

/**
  * @brief  data_rate: [set]  Output data rate selection.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_odr_t: change the values of odr in reg CTRL_REG1
  *
  */
int32_t hts221_data_rate_set(hts221_ctx_t *ctx, hts221_odr_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg1.odr = (uint8_t)val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  data_rate: [get]  Output data rate selection.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_odr_t: Get the values of odr in reg CTRL_REG1
  *
  */
int32_t hts221_data_rate_get(hts221_ctx_t *ctx, hts221_odr_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);

  switch (reg.ctrl_reg1.odr)
  {
    case HTS221_ONE_SHOT:
      *val = HTS221_ONE_SHOT;
      break;
    case HTS221_ODR_1Hz:
      *val = HTS221_ODR_1Hz;
      break;
    case HTS221_ODR_7Hz:
      *val = HTS221_ODR_7Hz;
      break;
    case HTS221_ODR_12Hz5:
      *val = HTS221_ODR_12Hz5;
      break;
    default:
      *val = HTS221_ODR_ND;
      break;
  }

  return ret;
}

/**
  * @brief  block_data_update: [set] Blockdataupdate.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of bdu in reg CTRL_REG1
  *
  */
int32_t hts221_block_data_update_set(hts221_ctx_t *ctx, uint8_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg1.bdu = val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  block_data_update: [get] Blockdataupdate.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of bdu in reg CTRL_REG1
  *
  */
int32_t hts221_block_data_update_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);
  *val = reg.ctrl_reg1.bdu;

  return ret;
}

/**
  * @brief  one_shoot_trigger: [set]  One-shot mode. Device perform a
  *                                   single measure.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of one_shot in reg CTRL_REG2
  *
  */
int32_t hts221_one_shoot_trigger_set(hts221_ctx_t *ctx, uint8_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg2.one_shot = val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  one_shoot_trigger: [get]  One-shot mode. Device perform a
  *                                   single measure.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of one_shot in reg CTRL_REG2
  *
  */
int32_t hts221_one_shoot_trigger_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);
  *val = reg.ctrl_reg2.one_shot;

  return ret;
}

/**
  * @brief  temp_data_ready: [get]  Temperature data available.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of t_da in reg STATUS_REG
  *
  */
int32_t hts221_temp_data_ready_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_STATUS_REG, &reg.byte, 1);
  *val = reg.status_reg.t_da;

  return ret;
}

/**
  * @brief  hum_data_ready: [get]  Humidity data available.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of h_da in reg STATUS_REG
  *
  */
int32_t hts221_hum_data_ready_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_STATUS_REG, &reg.byte, 1);
  *val = reg.status_reg.h_da;

  return ret;
}

/**
  * @brief  humidity_raw: [get]  Humidity output value
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_humidity_raw_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_HUMIDITY_OUT_L, buff, 2);
}

/**
  * @brief  temperature_raw: [get]  Temperature output value
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_temperature_raw_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_TEMP_OUT_L, buff, 2);
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
  * @brief  device_id: [get] DeviceWhoamI.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_device_id_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_WHO_AM_I, buff, 1);
}

/**
  * @brief  power_on: [set]  Switch device on/off
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of pd in reg CTRL_REG1
  *
  */
int32_t hts221_power_on_set(hts221_ctx_t *ctx, uint8_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg1.pd = val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);
  }
  return ret;
}

/**
  * @brief  power_on: [get]  Switch device on/off
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of pd in reg CTRL_REG1
  *
  */
int32_t hts221_power_on_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t mm_error;

  mm_error = hts221_read_reg(ctx, HTS221_CTRL_REG1, &reg.byte, 1);
  *val = reg.ctrl_reg1.pd;

  return mm_error;
}

/**
  * @brief  heater: [set]  Heater enable / disable.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of heater in reg CTRL_REG2
  *
  */
int32_t hts221_heater_set(hts221_ctx_t *ctx, uint8_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg2.heater = val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  heater: [get]  Heater enable / disable.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of heater in reg CTRL_REG2
  *
  */
int32_t hts221_heater_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);
  *val = reg.ctrl_reg2.heater;

  return ret;
}

/**
  * @brief  boot: [set]  Reboot memory content. Reload the calibration
  *                      parameters.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of boot in reg CTRL_REG2
  *
  */
int32_t hts221_boot_set(hts221_ctx_t *ctx, uint8_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg2.boot = val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  boot: [get]  Reboot memory content. Reload the calibration
  *                      parameters.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of boot in reg CTRL_REG2
  *
  */
int32_t hts221_boot_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG2, &reg.byte, 1);
  *val = reg.ctrl_reg2.boot;

  return ret;
}

/**
  * @brief  status: [get]  Info about device status
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_status_t: Registers STATUS_REG
  *
  */
int32_t hts221_status_get(hts221_ctx_t *ctx, hts221_status_reg_t *val)
{
  return hts221_read_reg(ctx, HTS221_STATUS_REG, (uint8_t *) val, 1);
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
  * @brief  drdy_on_int: [set]  Data-ready signal on INT_DRDY pin.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t val: change the values of drdy in reg CTRL_REG3
  *
  */
int32_t hts221_drdy_on_int_set(hts221_ctx_t *ctx, uint8_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg3.drdy = val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  drdy_on_int: [get]  Data-ready signal on INT_DRDY pin.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t: change the values of drdy in reg CTRL_REG3
  *
  */
int32_t hts221_drdy_on_int_get(hts221_ctx_t *ctx, uint8_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);
  *val = reg.ctrl_reg3.drdy;

  return ret;
}

/**
  * @brief  pin_mode: [set]  Push-pull/open drain selection on interrupt pads.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_pp_od_t: change the values of pp_od in reg CTRL_REG3
  *
  */
int32_t hts221_pin_mode_set(hts221_ctx_t *ctx, hts221_pp_od_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg3.pp_od = (uint8_t)val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  pin_mode: [get]  Push-pull/open drain selection on interrupt pads.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_pp_od_t: Get the values of pp_od in reg CTRL_REG3
  *
  */
int32_t hts221_pin_mode_get(hts221_ctx_t *ctx, hts221_pp_od_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);

  switch (reg.ctrl_reg3.pp_od)
  {
    case HTS221_PUSH_PULL:
      *val = HTS221_PUSH_PULL;
      break;
    case HTS221_OPEN_DRAIN:
      *val = HTS221_OPEN_DRAIN;
      break;
    default:
      *val = HTS221_PIN_MODE_ND;
      break;
  }

  return ret;
}

/**
  * @brief  int_polarity: [set]  Interrupt active-high/low.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_drdy_h_l_t: change the values of drdy_h_l in reg CTRL_REG3
  *
  */
int32_t hts221_int_polarity_set(hts221_ctx_t *ctx, hts221_drdy_h_l_t val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);

  if (ret == 0)
  {
    reg.ctrl_reg3.drdy_h_l = (uint8_t)val;
    ret = hts221_write_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);
  }

  return ret;
}

/**
  * @brief  int_polarity: [get]  Interrupt active-high/low.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  hts221_drdy_h_l_t: Get the values of drdy_h_l in reg CTRL_REG3
  *
  */
int32_t hts221_int_polarity_get(hts221_ctx_t *ctx, hts221_drdy_h_l_t *val)
{
  hts221_reg_t reg;
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_CTRL_REG3, &reg.byte, 1);

  switch (reg.ctrl_reg3.drdy_h_l)
  {
    case HTS221_ACTIVE_HIGH:
      *val = HTS221_ACTIVE_HIGH;
      break;
    case HTS221_ACTIVE_LOW:
      *val = HTS221_ACTIVE_LOW;
      break;
    default:
      *val = HTS221_ACTIVE_ND;
      break;
  }

  return ret;
}

/**
  * @}
  */

/**
  * @addtogroup  calibration
  * @brief   This section group all the calibration coefficients need
  *          for reading data
  * @{
  */

/**
  * @brief  hum_rh_point_0: [get]  First calibration point for Rh Humidity.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_hum_rh_point_0_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_H0_RH_X2, buff, 1);
  *buff = (uint8_t)(((uint16_t)(*buff) >> 1) & 0x7FFFu);

  return ret;
}

/**
  * @brief  hum_rh_point_1: [get]  Second calibration point for Rh Humidity.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_hum_rh_point_1_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = hts221_read_reg(ctx, HTS221_H1_RH_X2, buff, 1);
  *buff = (uint8_t)(((uint16_t)(*buff) >> 1) & 0x7FFFu);

  return ret;
}

/**
  * @brief  temp_deg_point_0: [get]  First calibration point for
  *                                  degC temperature.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_temp_deg_point_0_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  hts221_reg_t reg;
  int32_t ret;
  axis1bit16_t coeff;

  ret = hts221_read_reg(ctx, HTS221_T0_DEGC_X8, coeff.u8bit, 1);

  if (ret == 0)
  {
    ret = hts221_read_reg(ctx, HTS221_T1_T0_MSB, &reg.byte, 1);
    coeff.u8bit[1] = reg.t1_t0_msb.t0_msb;
    coeff.i16bit = coeff.i16bit / 8;
    *(buff) = (uint8_t)coeff.i16bit;
  }

  return ret;
}

/**
  * @brief  temp_deg_point_1: [get]  Second calibration point for
  *                                  degC temperature.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_temp_deg_point_1_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  hts221_reg_t reg;
  int32_t ret;
  axis1bit16_t coeff;

  ret = hts221_read_reg(ctx, HTS221_T1_DEGC_X8, coeff.u8bit, 1);

  if (ret == 0)
  {
    ret = hts221_read_reg(ctx, HTS221_T1_T0_MSB, &reg.byte, 1);
    coeff.u8bit[1] = reg.t1_t0_msb.t1_msb;
    coeff.i16bit = coeff.i16bit / 8;
    *(buff) = (uint8_t)coeff.i16bit;
  }

  return ret;
}

/**
  * @brief  hum_adc_point_0: [get]  First calibration point for
  *                                 humidity in LSB.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_hum_adc_point_0_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_H0_T0_OUT_L, buff, 2);
}

/**
  * @brief  hum_adc_point_1: [get]  Second calibration point for
  *                                 humidity in LSB.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_hum_adc_point_1_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_H1_T0_OUT_L, buff, 2);
}

/**
  * @brief  temp_adc_point_0: [get]  First calibration point for
  *                                  temperature in LSB.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_temp_adc_point_0_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_T0_OUT_L, buff, 2);
}

/**
  * @brief  temp_adc_point_1: [get]  Second calibration point for
  *                                  temperature in LSB.
  *
  * @param  hts221_ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t hts221_temp_adc_point_1_get(hts221_ctx_t *ctx, uint8_t *buff)
{
  return hts221_read_reg(ctx, HTS221_T1_OUT_L, buff, 2);
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

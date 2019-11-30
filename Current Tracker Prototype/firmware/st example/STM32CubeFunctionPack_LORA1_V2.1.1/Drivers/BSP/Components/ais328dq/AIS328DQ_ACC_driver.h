/*
 ******************************************************************************
 * @file    AIS328DQ_ACC_driver.h
 * @author  MEMS Software Solution Team
 * @date    20-December-2017
 * @brief   This file contains all the functions prototypes for the
 *          AIS328DQ_reg.c driver.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AIS328DQ_DRIVER__H
#define __AIS328DQ_DRIVER__H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup ais328dq
 * @{
 */

#ifndef __MEMS_SHARED__TYPES
#define __MEMS_SHARED__TYPES

/** @defgroup ST_MEMS_common_types
  * @{
  */

typedef union{
	int16_t i16bit[3];
	uint8_t u8bit[6];
} axis3bit16_t;

typedef union{
	int16_t i16bit;
	uint8_t u8bit[2];
} axis1bit16_t;

typedef union{
	int32_t i32bit[3];
	uint8_t u8bit[12];
} axis3bit32_t;

typedef union{
	int32_t i32bit;
	uint8_t u8bit[4];
} axis1bit32_t;

typedef struct {
   uint8_t bit0       : 1;
   uint8_t bit1       : 1;
   uint8_t bit2       : 1;
   uint8_t bit3       : 1;
   uint8_t bit4       : 1;
   uint8_t bit5       : 1;
   uint8_t bit6       : 1;
   uint8_t bit7       : 1;
} bitwise_t;

#define PROPERTY_DISABLE                (0)
#define PROPERTY_ENABLE                 (1)

#endif /*__MEMS_SHARED__TYPES*/

/**
  * @}
  */

/** @defgroup ais328dq_interface
  * @{
  */

typedef uint8_t (*ais328dq_write_ptr)(void *, uint8_t, uint8_t*, uint16_t);
typedef uint8_t (*ais328dq_read_ptr) (void *, uint8_t, uint8_t*, uint16_t);

typedef struct {
  /** Component mandatory fields **/
  ais328dq_write_ptr  write_reg;
  ais328dq_read_ptr   read_reg;
  /** Customizable optional pointer **/
  void *handle;
} ais328dq_ctx_t;

/**
  * @}
  */


/** @defgroup ais328dq_Infos
  * @{
  */
  /** I2C Device Address 8 bit format  if SA0=0 -> 0x31 if SA0=1 -> 0x33 **/
#define AIS328DQ_I2C_ADD_L   0x31
#define AIS328DQ_I2C_ADD_H   0x33

/** Device Identification (Who am I) **/
#define AIS328DQ_ID            0x32

/**
  * @}
  */

/**
  * @defgroup ais328dq_Sensitivity
  * @{
  */

#define AIS328DQ_FROM_FS_2g_TO_mg(lsb)    (float)( (lsb >> 4 ) * 0.98f )
#define AIS328DQ_FROM_FS_4g_TO_mg(lsb)    (float)( (lsb >> 4 ) * 1.95f )
#define AIS328DQ_FROM_FS_8g_TO_mg(lsb)    (float)( (lsb >> 4 ) * 3.91f )

/**
  * @}
  */

#define AIS328DQ_WHO_AM_I                  0x0F
#define AIS328DQ_CTRL_REG1                 0x20
typedef struct {
  uint8_t xen                      : 1;
  uint8_t yen                      : 1;
  uint8_t zen                      : 1;
  uint8_t dr                       : 2;
  uint8_t pm                       : 3;
} ais328dq_ctrl_reg1_t;

#define AIS328DQ_CTRL_REG2                 0x21
typedef struct {
  uint8_t hpcf                     : 2;
  uint8_t hpen                     : 2;
  uint8_t fds                      : 1;
  uint8_t hpm                      : 2;
  uint8_t boot                     : 1;
} ais328dq_ctrl_reg2_t;

#define AIS328DQ_CTRL_REG3                 0x22
typedef struct {
  uint8_t i1_cfg                   : 2;
  uint8_t lir1                     : 1;
  uint8_t i2_cfg                   : 2;
  uint8_t lir2                     : 1;
  uint8_t pp_od                    : 1;
  uint8_t ihl                      : 1;
} ais328dq_ctrl_reg3_t;

#define AIS328DQ_CTRL_REG4                 0x23
typedef struct {
  uint8_t sim                      : 1;
  uint8_t st                       : 3; /* STsign + ST */
  uint8_t fs                       : 2;
  uint8_t ble                      : 1;
  uint8_t bdu                      : 1;
} ais328dq_ctrl_reg4_t;

#define AIS328DQ_CTRL_REG5                 0x24
typedef struct {
  uint8_t turnon                   : 2;
  uint8_t not_used_01              : 6;
} ais328dq_ctrl_reg5_t;

#define AIS328DQ_HP_FILTER_RESET           0x25
#define AIS328DQ_REFERENCE                 0x26
#define AIS328DQ_STATUS_REG                0x27
typedef struct {
  uint8_t xda                      : 1;
  uint8_t yda                      : 1;
  uint8_t zda                      : 1;
  uint8_t zyxda                    : 1;
  uint8_t xor                      : 1;
  uint8_t yor                      : 1;
  uint8_t zor                      : 1;
  uint8_t zyxor                    : 1;
} ais328dq_status_reg_t;

#define AIS328DQ_OUT_X_L                   0x28
#define AIS328DQ_OUT_X_H                   0x29
#define AIS328DQ_OUT_Y_L                   0x2A
#define AIS328DQ_OUT_Y_H                   0x2B
#define AIS328DQ_OUT_Z_L                   0x2C
#define AIS328DQ_OUT_Z_H                   0x2D
#define AIS328DQ_INT1_CFG                  0x30
typedef struct {
  uint8_t xlie                     : 1;
  uint8_t xhie                     : 1;
  uint8_t ylie                     : 1;
  uint8_t yhie                     : 1;
  uint8_t zlie                     : 1;
  uint8_t zhie                     : 1;
  uint8_t _6d                      : 1;
  uint8_t aoi                      : 1;
} ais328dq_int1_cfg_t;

#define AIS328DQ_INT1_SRC                  0x31
typedef struct {
  uint8_t xl                       : 1;
  uint8_t xh                       : 1;
  uint8_t yl                       : 1;
  uint8_t yh                       : 1;
  uint8_t zl                       : 1;
  uint8_t zh                       : 1;
  uint8_t ia                       : 1;
  uint8_t not_used_01              : 1;
} ais328dq_int1_src_t;

#define AIS328DQ_INT1_THS                  0x32
typedef struct {
  uint8_t ths                      : 7;
  uint8_t not_used_01              : 1;
} ais328dq_int1_ths_t;

#define AIS328DQ_INT1_DURATION             0x33
typedef struct {
  uint8_t d                        : 7;
  uint8_t not_used_01              : 1;
} ais328dq_int1_duration_t;

#define AIS328DQ_INT2_CFG                  0x34
typedef struct {
  uint8_t xlie                     : 1;
  uint8_t xhie                     : 1;
  uint8_t ylie                     : 1;
  uint8_t yhie                     : 1;
  uint8_t zlie                     : 1;
  uint8_t zhie                     : 1;
  uint8_t _6d                      : 1;
  uint8_t aoi                      : 1;
} ais328dq_int2_cfg_t;

#define AIS328DQ_INT2_SRC                  0x35
typedef struct {
  uint8_t xl                       : 1;
  uint8_t xh                       : 1;
  uint8_t yl                       : 1;
  uint8_t yh                       : 1;
  uint8_t zl                       : 1;
  uint8_t zh                       : 1;
  uint8_t ia                       : 1;
  uint8_t not_used_01              : 1;
} ais328dq_int2_src_t;

#define AIS328DQ_INT2_THS                  0x36
typedef struct {
  uint8_t ths                      : 7;
  uint8_t not_used_01              : 1;
} ais328dq_int2_ths_t;

#define AIS328DQ_INT2_DURATION             0x37
typedef struct {
  uint8_t d                        : 7;
  uint8_t not_used_01              : 1;
} ais328dq_int2_duration_t;

typedef union{
  ais328dq_ctrl_reg1_t                     ctrl_reg1;
  ais328dq_ctrl_reg2_t                     ctrl_reg2;
  ais328dq_ctrl_reg3_t                     ctrl_reg3;
  ais328dq_ctrl_reg4_t                     ctrl_reg4;
  ais328dq_ctrl_reg5_t                     ctrl_reg5;
  ais328dq_status_reg_t                    status_reg;
  ais328dq_int1_cfg_t                      int1_cfg;
  ais328dq_int1_src_t                      int1_src;
  ais328dq_int1_ths_t                      int1_ths;
  ais328dq_int1_duration_t                 int1_duration;
  ais328dq_int2_cfg_t                      int2_cfg;
  ais328dq_int2_src_t                      int2_src;
  ais328dq_int2_ths_t                      int2_ths;
  ais328dq_int2_duration_t                 int2_duration;
  bitwise_t                                 bitwise;
  uint8_t                                   byte;
} ais328dq_reg_t;

int32_t ais328dq_read_reg(ais328dq_ctx_t *ctx, uint8_t reg, uint8_t* data,
                           uint16_t len);
int32_t ais328dq_write_reg(ais328dq_ctx_t *ctx, uint8_t reg, uint8_t* data,
                            uint16_t len);

int32_t ais328dq_axis_x_data_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_axis_x_data_get(ais328dq_ctx_t *ctx, uint8_t *val);

int32_t ais328dq_axis_y_data_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_axis_y_data_get(ais328dq_ctx_t *ctx, uint8_t *val);

int32_t ais328dq_axis_z_data_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_axis_z_data_get(ais328dq_ctx_t *ctx, uint8_t *val);

typedef enum {
  AIS328DQ_ODR_OFF   = 0x00,
  AIS328DQ_ODR_Hz5   = 0x02,
  AIS328DQ_ODR_1Hz   = 0x03,
  AIS328DQ_ODR_2Hz   = 0x04,
  AIS328DQ_ODR_5Hz   = 0x05,
  AIS328DQ_ODR_10Hz  = 0x06,
  AIS328DQ_ODR_50Hz  = 0x01,
  AIS328DQ_ODR_100Hz = 0x11,
  AIS328DQ_ODR_400Hz = 0x21,
  AIS328DQ_ODR_1kHz  = 0x31,
} ais328dq_dr_t;
int32_t ais328dq_data_rate_set(ais328dq_ctx_t *ctx, ais328dq_dr_t val);
int32_t ais328dq_data_rate_get(ais328dq_ctx_t *ctx, ais328dq_dr_t *val);

typedef enum {
  AIS328DQ_NORMAL_MODE      = 0,
  AIS328DQ_REF_MODE_ENABLE  = 1,
} ais328dq_hpm_t;
int32_t ais328dq_reference_mode_set(ais328dq_ctx_t *ctx,
                                     ais328dq_hpm_t val);
int32_t ais328dq_reference_mode_get(ais328dq_ctx_t *ctx,
                                     ais328dq_hpm_t *val);

typedef enum {
  AIS328DQ_2g  = 0,
  AIS328DQ_4g  = 1,
  AIS328DQ_8g  = 3,
} ais328dq_fs_t;
int32_t ais328dq_full_scale_set(ais328dq_ctx_t *ctx, ais328dq_fs_t val);
int32_t ais328dq_full_scale_get(ais328dq_ctx_t *ctx, ais328dq_fs_t *val);

int32_t ais328dq_block_data_update_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_block_data_update_get(ais328dq_ctx_t *ctx, uint8_t *val);

int32_t ais328dq_status_reg_get(ais328dq_ctx_t *ctx,
                                 ais328dq_status_reg_t *val);

int32_t ais328dq_flag_data_ready_get(ais328dq_ctx_t *ctx,
                                      uint8_t *val);

int32_t ais328dq_acceleration_raw_get(ais328dq_ctx_t *ctx, uint8_t *buff);

int32_t ais328dq_device_id_get(ais328dq_ctx_t *ctx, uint8_t *buff);

int32_t ais328dq_boot_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_boot_get(ais328dq_ctx_t *ctx, uint8_t *val);

typedef enum {
  AIS328DQ_ST_DISABLE   = 0,
  AIS328DQ_ST_POSITIVE  = 1,
  AIS328DQ_ST_NEGATIVE  = 5,
} ais328dq_st_t;
int32_t ais328dq_self_test_set(ais328dq_ctx_t *ctx, ais328dq_st_t val);
int32_t ais328dq_self_test_get(ais328dq_ctx_t *ctx, ais328dq_st_t *val);

typedef enum {
  AIS328DQ_LSB_AT_LOW_ADD  = 0,
  AIS328DQ_MSB_AT_LOW_ADD  = 1,
} ais328dq_ble_t;
int32_t ais328dq_data_format_set(ais328dq_ctx_t *ctx, ais328dq_ble_t val);
int32_t ais328dq_data_format_get(ais328dq_ctx_t *ctx, ais328dq_ble_t *val);

typedef enum {
  AIS328DQ_CUT_OFF_8Hz   = 0,
  AIS328DQ_CUT_OFF_16Hz  = 1,
  AIS328DQ_CUT_OFF_32Hz  = 2,
  AIS328DQ_CUT_OFF_64Hz  = 3,
} ais328dq_hpcf_t;
int32_t ais328dq_hp_bandwidth_set(ais328dq_ctx_t *ctx,
                                   ais328dq_hpcf_t val);
int32_t ais328dq_hp_bandwidth_get(ais328dq_ctx_t *ctx,
                                   ais328dq_hpcf_t *val);

typedef enum {
  AIS328DQ_HP_DISABLE            = 0,
  AIS328DQ_HP_ON_OUT             = 4,
  AIS328DQ_HP_ON_INT1            = 1,
  AIS328DQ_HP_ON_INT2            = 2,
  AIS328DQ_HP_ON_INT1_INT2       = 3,
  AIS328DQ_HP_ON_INT1_INT2_OUT   = 7,
  AIS328DQ_HP_ON_INT2_OUT        = 6,
  AIS328DQ_HP_ON_INT1_OUT        = 5,
} ais328dq_hpen_t;
int32_t ais328dq_hp_path_set(ais328dq_ctx_t *ctx, ais328dq_hpen_t val);
int32_t ais328dq_hp_path_get(ais328dq_ctx_t *ctx, ais328dq_hpen_t *val);

int32_t ais328dq_hp_reset_get(ais328dq_ctx_t *ctx);

int32_t ais328dq_hp_reference_value_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_hp_reference_value_get(ais328dq_ctx_t *ctx, uint8_t *val);

typedef enum {
  AIS328DQ_SPI_4_WIRE  = 0,
  AIS328DQ_SPI_3_WIRE  = 1,
} ais328dq_sim_t;
int32_t ais328dq_spi_mode_set(ais328dq_ctx_t *ctx, ais328dq_sim_t val);
int32_t ais328dq_spi_mode_get(ais328dq_ctx_t *ctx, ais328dq_sim_t *val);

typedef enum {
  AIS328DQ_PAD1_INT1_SRC           = 0,
  AIS328DQ_PAD1_INT1_OR_INT2_SRC   = 1,
  AIS328DQ_PAD1_DRDY               = 2,
  AIS328DQ_PAD1_BOOT               = 3,
} ais328dq_i1_cfg_t;
int32_t ais328dq_pin_int1_route_set(ais328dq_ctx_t *ctx,
                                     ais328dq_i1_cfg_t val);
int32_t ais328dq_pin_int1_route_get(ais328dq_ctx_t *ctx,
                                     ais328dq_i1_cfg_t *val);

typedef enum {
  AIS328DQ_INT1_PULSED   = 0,
  AIS328DQ_INT1_LATCHED  = 1,
} ais328dq_lir1_t;
int32_t ais328dq_int1_notification_set(ais328dq_ctx_t *ctx,
                                        ais328dq_lir1_t val);
int32_t ais328dq_int1_notification_get(ais328dq_ctx_t *ctx,
                                        ais328dq_lir1_t *val);

typedef enum {
  AIS328DQ_PAD2_INT2_SRC           = 0,
  AIS328DQ_PAD2_INT1_OR_INT2_SRC   = 1,
  AIS328DQ_PAD2_DRDY               = 2,
  AIS328DQ_PAD2_BOOT               = 3,
} ais328dq_i2_cfg_t;
int32_t ais328dq_pin_int2_route_set(ais328dq_ctx_t *ctx,
                                     ais328dq_i2_cfg_t val);
int32_t ais328dq_pin_int2_route_get(ais328dq_ctx_t *ctx,
                                     ais328dq_i2_cfg_t *val);

typedef enum {
  AIS328DQ_INT2_PULSED   = 0,
  AIS328DQ_INT2_LATCHED  = 1,
} ais328dq_lir2_t;
int32_t ais328dq_int2_notification_set(ais328dq_ctx_t *ctx,
                                        ais328dq_lir2_t val);
int32_t ais328dq_int2_notification_get(ais328dq_ctx_t *ctx,
                                        ais328dq_lir2_t *val);

typedef enum {
  AIS328DQ_PUSH_PULL   = 0,
  AIS328DQ_OPEN_DRAIN  = 1,
} ais328dq_pp_od_t;
int32_t ais328dq_pin_mode_set(ais328dq_ctx_t *ctx, ais328dq_pp_od_t val);
int32_t ais328dq_pin_mode_get(ais328dq_ctx_t *ctx, ais328dq_pp_od_t *val);

typedef enum {
  AIS328DQ_ACTIVE_HIGH  = 0,
  AIS328DQ_ACTIVE_LOW   = 1,
} ais328dq_ihl_t;
int32_t ais328dq_pin_polarity_set(ais328dq_ctx_t *ctx,
                                   ais328dq_ihl_t val);
int32_t ais328dq_pin_polarity_get(ais328dq_ctx_t *ctx,
                                   ais328dq_ihl_t *val);

typedef struct {
  uint8_t int1_xlie             : 1;
  uint8_t int1_xhie             : 1;
  uint8_t int1_ylie             : 1;
  uint8_t int1_yhie             : 1;
  uint8_t int1_zlie             : 1;
  uint8_t int1_zhie             : 1;
} ais328dq_int1_on_th_conf_t;
int32_t ais328dq_int1_on_threshold_conf_set(ais328dq_ctx_t *ctx,
                                             ais328dq_int1_on_th_conf_t val);
int32_t ais328dq_int1_on_threshold_conf_get(ais328dq_ctx_t *ctx,
                                             ais328dq_int1_on_th_conf_t *val);

typedef enum {
  AIS328DQ_INT1_ON_THRESHOLD_OR   = 0,
  AIS328DQ_INT1_ON_THRESHOLD_AND  = 1,
} ais328dq_int1_aoi_t;
int32_t ais328dq_int1_on_threshold_mode_set(ais328dq_ctx_t *ctx,
                                             ais328dq_int1_aoi_t val);
int32_t ais328dq_int1_on_threshold_mode_get(ais328dq_ctx_t *ctx,
                                             ais328dq_int1_aoi_t *val);

int32_t ais328dq_int1_src_get(ais328dq_ctx_t *ctx,
                               ais328dq_int1_src_t *val);

int32_t ais328dq_int1_treshold_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_int1_treshold_get(ais328dq_ctx_t *ctx, uint8_t *val);

int32_t ais328dq_int1_dur_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_int1_dur_get(ais328dq_ctx_t *ctx, uint8_t *val);

typedef struct {
  uint8_t int2_xlie             : 1;
  uint8_t int2_xhie             : 1;
  uint8_t int2_ylie             : 1;
  uint8_t int2_yhie             : 1;
  uint8_t int2_zlie             : 1;
  uint8_t int2_zhie             : 1;
} ais328dq_int2_on_th_conf_t;
int32_t ais328dq_int2_on_threshold_conf_set(ais328dq_ctx_t *ctx,
                                             ais328dq_int2_on_th_conf_t val);
int32_t ais328dq_int2_on_threshold_conf_get(ais328dq_ctx_t *ctx,
                                             ais328dq_int2_on_th_conf_t *val);

typedef enum {
  AIS328DQ_INT2_ON_THRESHOLD_OR   = 0,
  AIS328DQ_INT2_ON_THRESHOLD_AND  = 1,
} ais328dq_int2_aoi_t;
int32_t ais328dq_int2_on_threshold_mode_set(ais328dq_ctx_t *ctx,
                                             ais328dq_int2_aoi_t val);
int32_t ais328dq_int2_on_threshold_mode_get(ais328dq_ctx_t *ctx,
                                             ais328dq_int2_aoi_t *val);

int32_t ais328dq_int2_src_get(ais328dq_ctx_t *ctx,
                               ais328dq_int2_src_t *val);

int32_t ais328dq_int2_treshold_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_int2_treshold_get(ais328dq_ctx_t *ctx, uint8_t *val);

int32_t ais328dq_int2_dur_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_int2_dur_get(ais328dq_ctx_t *ctx, uint8_t *val);

int32_t ais328dq_wkup_to_sleep_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_wkup_to_sleep_get(ais328dq_ctx_t *ctx, uint8_t *val);

typedef enum {
  AIS328DQ_6D_INT1_DISABLE   = 0,
  AIS328DQ_6D_INT1_MOVEMENT  = 1,
  AIS328DQ_6D_INT1_POSITION  = 3,
} ais328dq_int1_6d_t;
int32_t ais328dq_int1_6d_mode_set(ais328dq_ctx_t *ctx,
                                   ais328dq_int1_6d_t val);
int32_t ais328dq_int1_6d_mode_get(ais328dq_ctx_t *ctx,
                                   ais328dq_int1_6d_t *val);

int32_t ais328dq_int1_6d_src_get(ais328dq_ctx_t *ctx,
                                  ais328dq_int1_src_t *val);

int32_t ais328dq_int1_6d_treshold_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_int1_6d_treshold_get(ais328dq_ctx_t *ctx, uint8_t *val);

typedef enum {
  AIS328DQ_6D_INT2_DISABLE   = 0,
  AIS328DQ_6D_INT2_MOVEMENT  = 1,
  AIS328DQ_6D_INT2_POSITION  = 3,
} ais328dq_int2_6d_t;
int32_t ais328dq_int2_6d_mode_set(ais328dq_ctx_t *ctx, 
                                   ais328dq_int2_6d_t val);
int32_t ais328dq_int2_6d_mode_get(ais328dq_ctx_t *ctx, 
                                   ais328dq_int2_6d_t *val);

int32_t ais328dq_int2_6d_src_get(ais328dq_ctx_t *ctx,
                                  ais328dq_int2_src_t *val);

int32_t ais328dq_int2_6d_treshold_set(ais328dq_ctx_t *ctx, uint8_t val);
int32_t ais328dq_int2_6d_treshold_get(ais328dq_ctx_t *ctx, uint8_t *val);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__AIS328DQ_DRIVER__H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

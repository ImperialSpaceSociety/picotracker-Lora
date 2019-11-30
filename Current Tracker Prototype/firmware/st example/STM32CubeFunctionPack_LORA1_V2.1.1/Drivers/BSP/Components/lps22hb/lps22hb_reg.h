/*
 ******************************************************************************
 * @file    lps22hb_reg.h
 * @author  MEMS Software Solution Team
 * @brief   This file contains all the functions prototypes for the
 *          lps22hb_reg.c driver.
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
#ifndef LPS22HB_DRIVER_H
#define LPS22HB_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup lps22hb
 * @{
 */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

/** @defgroup ST_MEMS_common_types
  * @{
  */

typedef union
{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

typedef union
{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;

typedef union
{
  int32_t i32bit[3];
  uint8_t u8bit[12];
} axis3bit32_t;

typedef union
{
  int32_t i32bit;
  uint8_t u8bit[4];
} axis1bit32_t;

typedef struct
{
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

#endif /* MEMS_SHARED_TYPES*/

/**
  * @}
  */

/** @defgroup lps22hb_interface
  * @{
  */

typedef int32_t (*lps22hb_write_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef int32_t (*lps22hb_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct
{
  /** Component mandatory fields **/
  lps22hb_write_ptr  write_reg;
  lps22hb_read_ptr   read_reg;
  /** Customizable optional pointer **/
  void *handle;
} lps22hb_ctx_t;

/**
  * @}
  */


/** @defgroup lps22hb_Infos
  * @{
  */
/** I2C Device Address 8 bit format: if SA0=0 -> 0xB9 if SA0=1 -> 0xBB **/
#define LPS22HB_I2C_ADD_H   0xBB
#define LPS22HB_I2C_ADD_L   0xB9

/** Device Identification (Who am I) **/
#define LPS22HB_ID          0xB1

/**
  * @}
  */

/**
  * @defgroup lps22hb_Sensitivity
  * @{
  */

#define LPS22HB_FROM_LSB_TO_hPa(lsb)     (float)( lsb / 4096.0f )
#define LPS22HB_FROM_LSB_TO_degC(lsb)    (float)( lsb / 100.0f )

/**
  * @}
  */

#define LPS22HB_INTERRUPT_CFG  0x0B
typedef struct
{
  uint8_t pe               : 2; /* ple + phe -> pe */
  uint8_t lir              : 1;
  uint8_t diff_en          : 1;
  uint8_t reset_az         : 1;
  uint8_t autozero         : 1;
  uint8_t reset_arp        : 1;
  uint8_t autorifp         : 1;
} lps22hb_interrupt_cfg_t;

#define LPS22HB_THS_P_L        0x0C
#define LPS22HB_THS_P_H        0x0D
#define LPS22HB_WHO_AM_I       0x0F
#define LPS22HB_CTRL_REG1      0x10
typedef struct
{
  uint8_t sim              : 1;
  uint8_t bdu              : 1;
  uint8_t lpfp             : 2; /* en_lpfp + lpfp_cfg -> lpfp */
  uint8_t odr              : 3;
  uint8_t not_used_01      : 1;
} lps22hb_ctrl_reg1_t;

#define LPS22HB_CTRL_REG2      0x11
typedef struct
{
  uint8_t one_shot         : 1;
  uint8_t not_used_01      : 1;
  uint8_t swreset          : 1;
  uint8_t i2c_dis          : 1;
  uint8_t if_add_inc       : 1;
  uint8_t stop_on_fth      : 1;
  uint8_t fifo_en          : 1;
  uint8_t boot             : 1;
} lps22hb_ctrl_reg2_t;

#define LPS22HB_CTRL_REG3      0x12
typedef struct
{
  uint8_t int_s            : 2;
  uint8_t drdy             : 1;
  uint8_t f_ovr            : 1;
  uint8_t f_fth            : 1;
  uint8_t f_fss5           : 1;
  uint8_t pp_od            : 1;
  uint8_t int_h_l          : 1;
} lps22hb_ctrl_reg3_t;


#define LPS22HB_FIFO_CTRL      0x14
typedef struct
{
  uint8_t wtm              : 5;
  uint8_t f_mode           : 3;
} lps22hb_fifo_ctrl_t;

#define LPS22HB_REF_P_XL       0x15
#define LPS22HB_REF_P_L        0x16
#define LPS22HB_REF_P_H        0x17
#define LPS22HB_RPDS_L         0x18
#define LPS22HB_RPDS_H         0x19

#define LPS22HB_RES_CONF       0x1A
typedef struct
{
  uint8_t lc_en            : 1;
  uint8_t not_used_01      : 7;
} lps22hb_res_conf_t;

#define LPS22HB_INT_SOURCE     0x25
typedef struct
{
  uint8_t ph               : 1;
  uint8_t pl               : 1;
  uint8_t ia               : 1;
  uint8_t not_used_01      : 4;
  uint8_t boot_status      : 1;
} lps22hb_int_source_t;

#define LPS22HB_FIFO_STATUS    0x26
typedef struct
{
  uint8_t fss              : 6;
  uint8_t ovr              : 1;
  uint8_t fth_fifo         : 1;
} lps22hb_fifo_status_t;

#define LPS22HB_STATUS         0x27
typedef struct
{
  uint8_t p_da             : 1;
  uint8_t t_da             : 1;
  uint8_t not_used_02      : 2;
  uint8_t p_or             : 1;
  uint8_t t_or             : 1;
  uint8_t not_used_01      : 2;
} lps22hb_status_t;

#define LPS22HB_PRESS_OUT_XL   0x28
#define LPS22HB_PRESS_OUT_L    0x29
#define LPS22HB_PRESS_OUT_H    0x2A
#define LPS22HB_TEMP_OUT_L     0x2B
#define LPS22HB_TEMP_OUT_H     0x2C
#define LPS22HB_LPFP_RES       0x33

typedef union
{
  lps22hb_interrupt_cfg_t      interrupt_cfg;
  lps22hb_ctrl_reg1_t          ctrl_reg1;
  lps22hb_ctrl_reg2_t          ctrl_reg2;
  lps22hb_ctrl_reg3_t          ctrl_reg3;
  lps22hb_fifo_ctrl_t          fifo_ctrl;
  lps22hb_res_conf_t           res_conf;
  lps22hb_int_source_t         int_source;
  lps22hb_fifo_status_t        fifo_status;
  lps22hb_status_t             status;
  bitwise_t                    bitwise;
  uint8_t                      byte;
} lps22hb_reg_t;

int32_t lps22hb_read_reg(lps22hb_ctx_t *ctx, uint8_t reg, uint8_t *data,
                         uint16_t len);
int32_t lps22hb_write_reg(lps22hb_ctx_t *ctx, uint8_t reg, uint8_t *data,
                          uint16_t len);

int32_t lps22hb_autozero_rst_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_autozero_rst_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_autozero_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_autozero_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_pressure_snap_rst_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_pressure_snap_rst_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_pressure_snap_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_pressure_snap_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_block_data_update_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_block_data_update_get(lps22hb_ctx_t *ctx, uint8_t *val);

typedef enum
{
  LPS22HB_LPF_ODR_DIV_2  = 0,
  LPS22HB_LPF_ODR_DIV_9  = 2,
  LPS22HB_LPF_ODR_DIV_20 = 3,
  LPS22HB_LPF_MODE_ND    = 4,
} lps22hb_lpfp_t;
int32_t lps22hb_low_pass_filter_mode_set(lps22hb_ctx_t *ctx,
                                         lps22hb_lpfp_t val);
int32_t lps22hb_low_pass_filter_mode_get(lps22hb_ctx_t *ctx,
                                         lps22hb_lpfp_t *val);

typedef enum
{
  LPS22HB_POWER_DOWN  = 0,
  LPS22HB_ODR_1_Hz    = 1,
  LPS22HB_ODR_10_Hz   = 2,
  LPS22HB_ODR_25_Hz   = 3,
  LPS22HB_ODR_50_Hz   = 4,
  LPS22HB_ODR_75_Hz   = 5,
  LPS22HB_ODR_ND      = 6,
} lps22hb_odr_t;
int32_t lps22hb_data_rate_set(lps22hb_ctx_t *ctx, lps22hb_odr_t val);
int32_t lps22hb_data_rate_get(lps22hb_ctx_t *ctx, lps22hb_odr_t *val);

int32_t lps22hb_one_shoot_trigger_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_one_shoot_trigger_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_pressure_ref_set(lps22hb_ctx_t *ctx, uint8_t *buff);
int32_t lps22hb_pressure_ref_get(lps22hb_ctx_t *ctx, uint8_t *buff);

int32_t lps22hb_pressure_offset_set(lps22hb_ctx_t *ctx, uint8_t *buff);
int32_t lps22hb_pressure_offset_get(lps22hb_ctx_t *ctx, uint8_t *buff);

int32_t lps22hb_press_data_ready_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_temp_data_ready_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_press_data_ovr_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_temp_data_ovr_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_pressure_raw_get(lps22hb_ctx_t *ctx, uint8_t *buff);

int32_t lps22hb_temperature_raw_get(lps22hb_ctx_t *ctx, uint8_t *buff);

int32_t lps22hb_low_pass_rst_get(lps22hb_ctx_t *ctx, uint8_t *buff);

int32_t lps22hb_device_id_get(lps22hb_ctx_t *ctx, uint8_t *buff);

int32_t lps22hb_reset_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_reset_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_boot_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_boot_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_low_power_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_low_power_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_boot_status_get(lps22hb_ctx_t *ctx, uint8_t *val);

typedef struct
{
  lps22hb_fifo_status_t  fifo_status;
  lps22hb_status_t       status;
} lps22hb_dev_stat_t;
int32_t lps22hb_dev_status_get(lps22hb_ctx_t *ctx, lps22hb_dev_stat_t *val);

typedef enum
{
  LPS22HB_NO_THRESHOLD = 0,
  LPS22HB_POSITIVE     = 1,
  LPS22HB_NEGATIVE     = 2,
  LPS22HB_BOTH         = 3,
  LPS22HB_SIGN_ND      = 4,
} lps22hb_pe_t;
int32_t lps22hb_sign_of_int_threshold_set(lps22hb_ctx_t *ctx,
                                          lps22hb_pe_t val);
int32_t lps22hb_sign_of_int_threshold_get(lps22hb_ctx_t *ctx,
                                          lps22hb_pe_t *val);

typedef enum
{
  LPS22HB_INT_PULSED  = 0,
  LPS22HB_INT_LATCHED = 1,
  LPS22HB_INT_MODE_ND = 2,
} lps22hb_lir_t;
int32_t lps22hb_int_notification_mode_set(lps22hb_ctx_t *ctx,
                                          lps22hb_lir_t val);
int32_t lps22hb_int_notification_mode_get(lps22hb_ctx_t *ctx,
                                          lps22hb_lir_t *val);

int32_t lps22hb_int_generation_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_int_generation_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_int_threshold_set(lps22hb_ctx_t *ctx, uint8_t *buff);
int32_t lps22hb_int_threshold_get(lps22hb_ctx_t *ctx, uint8_t *buff);

typedef enum
{
  LPS22HB_DRDY_OR_FIFO_FLAGS = 0,
  LPS22HB_HIGH_PRES_INT      = 1,
  LPS22HB_LOW_PRES_INT       = 2,
  LPS22HB_EVERY_PRES_INT     = 3,
  LPS22HB_PIN_ROUTE_ND       = 4,
} lps22hb_int_s_t;
int32_t lps22hb_int_pin_mode_set(lps22hb_ctx_t *ctx, lps22hb_int_s_t val);
int32_t lps22hb_int_pin_mode_get(lps22hb_ctx_t *ctx, lps22hb_int_s_t *val);

int32_t lps22hb_drdy_on_int_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_drdy_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_ovr_on_int_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_fifo_ovr_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_threshold_on_int_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_fifo_threshold_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_full_on_int_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_fifo_full_on_int_get(lps22hb_ctx_t *ctx, uint8_t *val);

typedef enum
{
  LPS22HB_PUSH_PULL   = 0,
  LPS22HB_OPEN_DRAIN  = 1,
  LPS22HB_PIN_MODE_ND = 2,
} lps22hb_pp_od_t;
int32_t lps22hb_pin_mode_set(lps22hb_ctx_t *ctx, lps22hb_pp_od_t val);
int32_t lps22hb_pin_mode_get(lps22hb_ctx_t *ctx, lps22hb_pp_od_t *val);

typedef enum
{
  LPS22HB_ACTIVE_HIGH = 0,
  LPS22HB_ACTIVE_LOW  = 1,
  LPS22HB_POLARITY_ND = 2,
} lps22hb_int_h_l_t;
int32_t lps22hb_int_polarity_set(lps22hb_ctx_t *ctx, lps22hb_int_h_l_t val);
int32_t lps22hb_int_polarity_get(lps22hb_ctx_t *ctx, lps22hb_int_h_l_t *val);

int32_t lps22hb_int_source_get(lps22hb_ctx_t *ctx, lps22hb_int_source_t *val);

int32_t lps22hb_int_on_press_high_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_int_on_press_low_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_interrupt_event_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_stop_on_fifo_threshold_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_stop_on_fifo_threshold_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_fifo_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_watermark_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_fifo_watermark_get(lps22hb_ctx_t *ctx, uint8_t *val);

typedef enum
{
  LPS22HB_BYPASS_MODE           = 0,
  LPS22HB_FIFO_MODE             = 1,
  LPS22HB_STREAM_MODE           = 2,
  LPS22HB_STREAM_TO_FIFO_MODE   = 3,
  LPS22HB_BYPASS_TO_STREAM_MODE = 4,
  LPS22HB_DYNAMIC_STREAM_MODE   = 6,
  LPS22HB_BYPASS_TO_FIFO_MODE   = 7,
  LPS22HB_FIFO_MODE_ND          = 8,
} lps22hb_f_mode_t;
int32_t lps22hb_fifo_mode_set(lps22hb_ctx_t *ctx, lps22hb_f_mode_t val);
int32_t lps22hb_fifo_mode_get(lps22hb_ctx_t *ctx, lps22hb_f_mode_t *val);

int32_t lps22hb_fifo_data_level_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_ovr_flag_get(lps22hb_ctx_t *ctx, uint8_t *val);

int32_t lps22hb_fifo_fth_flag_get(lps22hb_ctx_t *ctx, uint8_t *val);

typedef enum
{
  LPS22HB_SPI_4_WIRE  = 0,
  LPS22HB_SPI_3_WIRE  = 1,
  LPS22HB_SPI_MODE_ND = 2,
} lps22hb_sim_t;
int32_t lps22hb_spi_mode_set(lps22hb_ctx_t *ctx, lps22hb_sim_t val);
int32_t lps22hb_spi_mode_get(lps22hb_ctx_t *ctx, lps22hb_sim_t *val);

typedef enum
{
  LPS22HB_I2C_ENABLE  = 0,
  LPS22HB_I2C_DISABLE = 1,
  LPS22HB_I2C_MODE_ND = 2,
} lps22hb_i2c_dis_t;
int32_t lps22hb_i2c_interface_set(lps22hb_ctx_t *ctx, lps22hb_i2c_dis_t val);
int32_t lps22hb_i2c_interface_get(lps22hb_ctx_t *ctx, lps22hb_i2c_dis_t *val);

int32_t lps22hb_auto_add_inc_set(lps22hb_ctx_t *ctx, uint8_t val);
int32_t lps22hb_auto_add_inc_get(lps22hb_ctx_t *ctx, uint8_t *val);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*LPS22HB_DRIVER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

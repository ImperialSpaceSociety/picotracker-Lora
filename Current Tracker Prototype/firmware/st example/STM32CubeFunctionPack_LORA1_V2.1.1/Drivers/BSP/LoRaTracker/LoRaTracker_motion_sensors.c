/**
 ******************************************************************************
 * @file    LoRaTracker_motion_sensors.c
 * @author  MEMS Software Solutions Team
 * @brief   This file provides a set of functions needed to manage the motion sensors
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "LoRaTracker_motion_sensors.h"
//#include "motion_sensor.h"

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup LORATRACKER LORATRACKER
 * @{
 */

/** @defgroup LORATRACKER_MOTION_SENSOR LORATRACKER MOTION SENSOR
 * @brief   This module provides a set of functions needed to manage the motion sensors
 * @{
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Exported_Variables Exported Variables
 * @{
 */
extern void *MotionCompObj[LORA_TRACKER_MOTION_INSTANCES_NBR]; /* This "redundant" line is here to fulfil MISRA C-2012 rule 8.4 */
void *MotionCompObj[LORA_TRACKER_MOTION_INSTANCES_NBR];

/**
 * @}
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Private_Variables Private Variables
 * @{
 */

/* We define a jump table in order to get the correct index from the desired function. */
/* This table should have a size equal to the maximum value of a function plus 1.      */
static uint32_t FunctionIndex[5] = { 0, 0, 1, 1, 2 };
static LORA_TRACKER_MOTION_SENSOR_FuncDrv_t *MotionFuncDrv[LORA_TRACKER_MOTION_INSTANCES_NBR][LORA_TRACKER_MOTION_FUNCTIONS_NBR];
static LORA_TRACKER_MOTION_SENSOR_CommonDrv_t *MotionDrv[LORA_TRACKER_MOTION_INSTANCES_NBR];
static LORA_TRACKER_MOTION_SENSOR_Ctx_t MotionCtx[LORA_TRACKER_MOTION_INSTANCES_NBR];

/**
 * @}
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Private_Function_Prototypes Private Function Prototypes
 * @{
 */

#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1) /* LORA_TRACKER CUSTOMIZATION*/
static int32_t LIS2DW12_0_Probe(uint32_t Functions);
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
static int32_t LSM6DSL_0_Probe(uint32_t Functions);
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
static int32_t LSM303AGR_ACC_0_Probe(uint32_t Functions);
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
static int32_t LSM303AGR_MAG_0_Probe(uint32_t Functions);
#endif

/**
 * @}
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief  Initializes the motion sensors
 * @param  Instance Motion sensor instance
 * @param  Functions Environmental sensor functions. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Init(uint32_t Instance, uint32_t Functions)
{
	int32_t ret = BSP_ERROR_NONE;
	uint32_t function = MOTION_GYRO;
	uint32_t i;
	uint32_t component_functions = 0;
	LORA_TRACKER_MOTION_SENSOR_Capabilities_t cap;

	switch (Instance) {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1) /* LORA_TRACKER CUSTOMIZATION*/
	case LORA_TRACKER_LIS2DW12_0:
		if (LIS2DW12_0_Probe(Functions) != BSP_ERROR_NONE) {
			return BSP_ERROR_NO_INIT;
		}
		if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance],
				(void *) &cap) != BSP_ERROR_NONE) {
			return BSP_ERROR_UNKNOWN_COMPONENT;
		}
		if (cap.Acc == 1U) {
			component_functions |= MOTION_ACCELERO;
		}
		if (cap.Gyro == 1U) {
			component_functions |= MOTION_GYRO;
		}
		if (cap.Magneto == 1U) {
			component_functions |= MOTION_MAGNETO;
		}
		break;
#endif   

#if ( USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
		case LORA_TRACKER_LSM6DSL_0:
		if (LSM6DSL_0_Probe(Functions) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_NO_INIT;
		}
		if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_UNKNOWN_COMPONENT;
		}
		if (cap.Acc == 1U)
		{
			component_functions |= MOTION_ACCELERO;
		}
		if (cap.Gyro == 1U)
		{
			component_functions |= MOTION_GYRO;
		}
		if (cap.Magneto == 1U)
		{
			component_functions |= MOTION_MAGNETO;
		}
		break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
		case LORA_TRACKER_LSM303AGR_ACC_0:
		if (LSM303AGR_ACC_0_Probe(Functions) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_NO_INIT;
		}
		if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_UNKNOWN_COMPONENT;
		}
		if (cap.Acc == 1U)
		{
			component_functions |= MOTION_ACCELERO;
		}
		if (cap.Gyro == 1U)
		{
			component_functions |= MOTION_GYRO;
		}
		if (cap.Magneto == 1U)
		{
			component_functions |= MOTION_MAGNETO;
		}
		break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
		case LORA_TRACKER_LSM303AGR_MAG_0:
		if (LSM303AGR_MAG_0_Probe(Functions) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_NO_INIT;
		}
		if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_UNKNOWN_COMPONENT;
		}
		if (cap.Acc == 1U)
		{
			component_functions |= MOTION_ACCELERO;
		}
		if (cap.Gyro == 1U)
		{
			component_functions |= MOTION_GYRO;
		}
		if (cap.Magneto == 1U)
		{
			component_functions |= MOTION_MAGNETO;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	if (ret != BSP_ERROR_NONE) {
		return ret;
	}

	for (i = 0; i < LORA_TRACKER_MOTION_FUNCTIONS_NBR; i++) {
		if (((Functions & function) == function)
				&& ((component_functions & function) == function)) {
			if (MotionFuncDrv[Instance][FunctionIndex[function]]->Enable(
					MotionCompObj[Instance]) != BSP_ERROR_NONE) {
				return BSP_ERROR_COMPONENT_FAILURE;
			}
		}
		function = function << 1;
	}

	return ret;
}

/**
 * @brief  Deinitialize Motion sensor
 * @param  Instance Motion sensor instance
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_DeInit(uint32_t Instance) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else if (MotionDrv[Instance]->DeInit(
			MotionCompObj[Instance]) != BSP_ERROR_NONE) {
		ret = BSP_ERROR_COMPONENT_FAILURE;
	} else {
		ret = BSP_ERROR_NONE;
	}

	return ret;
}

/**
 * @brief  Get motion sensor instance capabilities
 * @param  Instance Motion sensor instance
 * @param  Capabilities pointer to motion sensor capabilities
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetCapabilities(uint32_t Instance,
		LORA_TRACKER_MOTION_SENSOR_Capabilities_t *Capabilities) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance],
			Capabilities) != BSP_ERROR_NONE) {
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	} else {
		ret = BSP_ERROR_NONE;
	}

	return ret;
}

/**
 * @brief  Get WHOAMI value
 * @param  Instance Motion sensor instance
 * @param  Id WHOAMI value
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_ReadID(uint32_t Instance, uint8_t *Id) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else if (MotionDrv[Instance]->ReadID(MotionCompObj[Instance],
			Id) != BSP_ERROR_NONE) {
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	} else {
		ret = BSP_ERROR_NONE;
	}

	return ret;
}

/**
 * @brief  Enable Motion sensor
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable(uint32_t Instance,
		uint32_t Function) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->Enable(
					MotionCompObj[Instance]) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Disable Motion sensor
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Disable(uint32_t Instance,
		uint32_t Function) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->Disable(
					MotionCompObj[Instance]) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Get accelero axes data
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Axes pointer to axes data structure
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetAxes(uint32_t Instance,
		uint32_t Function, LORA_TRACKER_MOTION_SENSOR_Axes_t *Axes) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetAxes(
					MotionCompObj[Instance], Axes) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Get accelero axes raw data
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Axes pointer to axes raw data structure
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetAxesRaw(uint32_t Instance,
		uint32_t Function, LORA_TRACKER_MOTION_SENSOR_AxesRaw_t *Axes) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetAxesRaw(
					MotionCompObj[Instance], Axes) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Get accelero sensitivity
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Sensitivity pointer to sensitivity read value
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetSensitivity(uint32_t Instance,
		uint32_t Function, float *Sensitivity) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetSensitivity(
					MotionCompObj[Instance], Sensitivity) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Get accelero Output Data Rate
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Odr pointer to Output Data Rate read value
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetOutputDataRate(uint32_t Instance,
		uint32_t Function, float *Odr) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetOutputDataRate(
					MotionCompObj[Instance], Odr) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Get accelero Full Scale
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Fullscale pointer to Fullscale read value
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetFullScale(uint32_t Instance,
		uint32_t Function, int32_t *Fullscale) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetFullScale(
					MotionCompObj[Instance], Fullscale) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Set accelero Output Data Rate
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Odr Output Data Rate value to be set
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_SetOutputDataRate(uint32_t Instance,
		uint32_t Function, float Odr) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->SetOutputDataRate(
					MotionCompObj[Instance], Odr) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @brief  Set accelero Full Scale
 * @param  Instance Motion sensor instance
 * @param  Function Motion sensor function. Could be :
 *         - MOTION_GYRO and/or MOTION_ACCELERO for instance 0
 *         - MOTION_ACCELERO for instance 1
 *         - MOTION_MAGNETO for instance 2
 * @param  Fullscale Fullscale value to be set
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_SetFullScale(uint32_t Instance,
		uint32_t Function, int32_t Fullscale) {
	int32_t ret;

	if (Instance >= LORA_TRACKER_MOTION_INSTANCES_NBR) {
		ret = BSP_ERROR_WRONG_PARAM;
	} else {
		if ((MotionCtx[Instance].Functions & Function) == Function) {
			if (MotionFuncDrv[Instance][FunctionIndex[Function]]->SetFullScale(
					MotionCompObj[Instance], Fullscale) != BSP_ERROR_NONE) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		} else {
			ret = BSP_ERROR_WRONG_PARAM;
		}
	}

	return ret;
}

/**
 * @}
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Private_Functions Private Functions
 * @{
 */

#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0  == 1)
/**
 * @brief  Register Bus IOs for instance 0 if component ID is OK
 * @retval BSP status
 */
static int32_t LIS2DW12_0_Probe(uint32_t Functions) /* LORA_TRACKER CUSTOMIZATION*/
{
	LIS2DW12_IO_t io_ctx;
	uint8_t id;
	static LIS2DW12_Object_t lsm6dsl_obj_0;
	LIS2DW12_Capabilities_t cap;
	int32_t ret = BSP_ERROR_NONE;

	/* Configure the accelero driver */
	io_ctx.BusType = LIS2DW12_I2C_BUS; /* I2C */
	io_ctx.Address = LIS2DW12_I2C_ADD_L; /* SA0 = VDD */
	io_ctx.Init = LORA_TRACKER_I2C1_Init; //BSP_LIS2DW12_Init;
	io_ctx.DeInit = LORA_TRACKER_I2C1_DeInit; //BSP_LIS2DW12_DeInit;
	io_ctx.ReadReg = LORA_TRACKER_I2C1_ReadReg; //BSP_LIS2DW12_ReadReg;
	io_ctx.WriteReg = LORA_TRACKER_I2C1_WriteReg; //BSP_LIS2DW12_WriteReg;
	io_ctx.GetTick = BSP_GetTick;

	if (LIS2DW12_RegisterBusIO(&lsm6dsl_obj_0, &io_ctx) != LIS2DW12_OK) {
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	} else if (LIS2DW12_ReadID(&lsm6dsl_obj_0, &id) != LIS2DW12_OK) {
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	} else if (id != LIS2DW12_ID) {
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	} else {
		(void) LIS2DW12_GetCapabilities(&lsm6dsl_obj_0, &cap);
		MotionCtx[LORA_TRACKER_LIS2DW12_0].Functions = ((uint32_t) cap.Gyro)
				| ((uint32_t) cap.Acc << 1) | ((uint32_t) cap.Magneto << 2);

		MotionCompObj[LORA_TRACKER_LIS2DW12_0] = &lsm6dsl_obj_0;
		/* The second cast (void *) is added to bypass Misra R11.3 rule */
		MotionDrv[LORA_TRACKER_LIS2DW12_0] =
				(LORA_TRACKER_MOTION_SENSOR_CommonDrv_t *) (void *) &LIS2DW12_COMMON_Driver;

		if (((Functions & MOTION_ACCELERO) == MOTION_ACCELERO)
				&& (cap.Acc == 1U)) {
			/* The second cast (void *) is added to bypass Misra R11.3 rule */
			MotionFuncDrv[LORA_TRACKER_LIS2DW12_0][FunctionIndex[MOTION_ACCELERO]] =
					(LORA_TRACKER_MOTION_SENSOR_FuncDrv_t *) (void *) &LIS2DW12_ACC_Driver;

			if (MotionDrv[LORA_TRACKER_LIS2DW12_0]->Init(
					MotionCompObj[LORA_TRACKER_LIS2DW12_0]) != LIS2DW12_OK) {
				ret = BSP_ERROR_COMPONENT_FAILURE;
			} else {
				ret = BSP_ERROR_NONE;
			}
		}
	}

	return ret;
}
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0  == 1)
/**
 * @brief  Register Bus IOs for instance 0 if component ID is OK
 * @retval BSP status
 */
static int32_t LSM6DSL_0_Probe(uint32_t Functions)
{
	LSM6DSL_IO_t io_ctx;
	uint8_t id;
	static LSM6DSL_Object_t lsm6dsl_obj_0;
	LSM6DSL_Capabilities_t cap;
	int32_t ret = BSP_ERROR_NONE;

	/* Configure the accelero driver */
	io_ctx.BusType = LSM6DSL_I2C_BUS; /* I2C */
	io_ctx.Address = LSM6DSL_I2C_ADD_H;
	io_ctx.Init = LORA_TRACKER_I2C1_Init;
	io_ctx.DeInit = LORA_TRACKER_I2C1_DeInit;
	io_ctx.ReadReg = LORA_TRACKER_I2C1_ReadReg;
	io_ctx.WriteReg = LORA_TRACKER_I2C1_WriteReg;
	io_ctx.GetTick = LORA_TRACKER_GetTick;

	if (LSM6DSL_RegisterBusIO(&lsm6dsl_obj_0, &io_ctx) != LSM6DSL_OK)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else if (LSM6DSL_ReadID(&lsm6dsl_obj_0, &id) != LSM6DSL_OK)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else if (id != LSM6DSL_ID)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else
	{
		(void)LSM6DSL_GetCapabilities(&lsm6dsl_obj_0, &cap);
		MotionCtx[LORA_TRACKER_LSM6DSL_0].Functions = ((uint32_t)cap.Gyro) | ((uint32_t)cap.Acc << 1) | ((uint32_t)cap.Magneto << 2);

		MotionCompObj[LORA_TRACKER_LSM6DSL_0] = &lsm6dsl_obj_0;
		/* The second cast (void *) is added to bypass Misra R11.3 rule */
		MotionDrv[LORA_TRACKER_LSM6DSL_0] = (LORA_TRACKER_MOTION_SENSOR_CommonDrv_t *)(void *)&LSM6DSL_COMMON_Driver;

		if (((Functions & MOTION_GYRO) == MOTION_GYRO) && (cap.Gyro == 1U))
		{
			/* The second cast (void *) is added to bypass Misra R11.3 rule */
			MotionFuncDrv[LORA_TRACKER_LSM6DSL_0][FunctionIndex[MOTION_GYRO]] = (LORA_TRACKER_MOTION_SENSOR_FuncDrv_t *)(void *)&LSM6DSL_GYRO_Driver;

			if (MotionDrv[LORA_TRACKER_LSM6DSL_0]->Init(MotionCompObj[LORA_TRACKER_LSM6DSL_0]) != LSM6DSL_OK)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		if (((Functions & MOTION_ACCELERO) == MOTION_ACCELERO) && (cap.Acc == 1U))
		{
			/* The second cast (void *) is added to bypass Misra R11.3 rule */
			MotionFuncDrv[LORA_TRACKER_LSM6DSL_0][FunctionIndex[MOTION_ACCELERO]] = (LORA_TRACKER_MOTION_SENSOR_FuncDrv_t *)(
					void *)&LSM6DSL_ACC_Driver;

			if (MotionDrv[LORA_TRACKER_LSM6DSL_0]->Init(MotionCompObj[LORA_TRACKER_LSM6DSL_0]) != LSM6DSL_OK)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
	}
	return ret;
}
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
/**
 * @brief  Register Bus IOs for instance 1 if component ID is OK
 * @retval error status
 */
static int32_t LSM303AGR_ACC_0_Probe(uint32_t Functions)
{
	LSM303AGR_IO_t io_ctx;
	uint8_t id;
	static LSM303AGR_ACC_Object_t lsm303agr_acc_obj_0;
	LSM303AGR_Capabilities_t cap;
	int32_t ret = BSP_ERROR_NONE;

	/* Configure the accelero driver */
	io_ctx.BusType = LSM303AGR_I2C_BUS; /* I2C */
	io_ctx.Address = LSM303AGR_I2C_ADD_XL;
	io_ctx.Init = LORA_TRACKER_I2C1_Init;
	io_ctx.DeInit = LORA_TRACKER_I2C1_DeInit;
	io_ctx.ReadReg = LORA_TRACKER_I2C1_ReadReg;
	io_ctx.WriteReg = LORA_TRACKER_I2C1_WriteReg;
	io_ctx.GetTick = LORA_TRACKER_GetTick;

	if (LSM303AGR_ACC_RegisterBusIO(&lsm303agr_acc_obj_0, &io_ctx) != LSM303AGR_OK)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else if (LSM303AGR_ACC_ReadID(&lsm303agr_acc_obj_0, &id) != LSM303AGR_OK)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else if (id != (uint8_t)LSM303AGR_ID_XL)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else
	{
		(void)LSM303AGR_ACC_GetCapabilities(&lsm303agr_acc_obj_0, &cap);
		MotionCtx[LORA_TRACKER_LSM303AGR_ACC_0].Functions = ((uint32_t)cap.Gyro) | ((uint32_t)cap.Acc << 1) | ((
						uint32_t)cap.Magneto << 2);

		MotionCompObj[LORA_TRACKER_LSM303AGR_ACC_0] = &lsm303agr_acc_obj_0;
		/* The second cast (void *) is added to bypass Misra R11.3 rule */
		MotionDrv[LORA_TRACKER_LSM303AGR_ACC_0] = (LORA_TRACKER_MOTION_SENSOR_CommonDrv_t *)(void *)&LSM303AGR_ACC_COMMON_Driver;

		if (((Functions & MOTION_ACCELERO) == MOTION_ACCELERO) && (cap.Acc == 1U))
		{
			/* The second cast (void *) is added to bypass Misra R11.3 rule */
			MotionFuncDrv[LORA_TRACKER_LSM303AGR_ACC_0][FunctionIndex[MOTION_ACCELERO]] = (LORA_TRACKER_MOTION_SENSOR_FuncDrv_t *)(
					void *)&LSM303AGR_ACC_Driver;

			if (MotionDrv[LORA_TRACKER_LSM303AGR_ACC_0]->Init(MotionCompObj[LORA_TRACKER_LSM303AGR_ACC_0]) != LSM303AGR_OK)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
	}

	return ret;
}
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
/**
 * @brief  Register Bus IOs for instance 1 if component ID is OK
 * @retval error status
 */
static int32_t LSM303AGR_MAG_0_Probe(uint32_t Functions)
{
	LSM303AGR_IO_t io_ctx;
	uint8_t id;
	static LSM303AGR_MAG_Object_t lsm303agr_mag_obj_0;
	LSM303AGR_Capabilities_t cap;
	int32_t ret = BSP_ERROR_NONE;

	/* Configure the magneto driver */
	io_ctx.BusType = LSM303AGR_I2C_BUS; /* I2C */
	io_ctx.Address = LSM303AGR_I2C_ADD_MG;
	io_ctx.Init = LORA_TRACKER_I2C1_Init;
	io_ctx.DeInit = LORA_TRACKER_I2C1_DeInit;
	io_ctx.ReadReg = LORA_TRACKER_I2C1_ReadReg;
	io_ctx.WriteReg = LORA_TRACKER_I2C1_WriteReg;
	io_ctx.GetTick = LORA_TRACKER_GetTick;

	if (LSM303AGR_MAG_RegisterBusIO(&lsm303agr_mag_obj_0, &io_ctx) != LSM303AGR_OK)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else if (LSM303AGR_MAG_ReadID(&lsm303agr_mag_obj_0, &id) != LSM303AGR_OK)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else if (id != (uint8_t)LSM303AGR_ID_MG)
	{
		ret = BSP_ERROR_UNKNOWN_COMPONENT;
	}
	else
	{
		(void)LSM303AGR_MAG_GetCapabilities(&lsm303agr_mag_obj_0, &cap);
		MotionCtx[LORA_TRACKER_LSM303AGR_MAG_0].Functions = ((uint32_t)cap.Gyro) | ((uint32_t)cap.Acc << 1) | ((
						uint32_t)cap.Magneto << 2);

		MotionCompObj[LORA_TRACKER_LSM303AGR_MAG_0] = &lsm303agr_mag_obj_0;
		/* The second cast (void *) is added to bypass Misra R11.3 rule */
		MotionDrv[LORA_TRACKER_LSM303AGR_MAG_0] = (LORA_TRACKER_MOTION_SENSOR_CommonDrv_t *)(void *)&LSM303AGR_MAG_COMMON_Driver;

		if (((Functions & MOTION_MAGNETO) == MOTION_MAGNETO) && (cap.Magneto == 1U))
		{
			/* The second cast (void *) is added to bypass Misra R11.3 rule */
			MotionFuncDrv[LORA_TRACKER_LSM303AGR_MAG_0][FunctionIndex[MOTION_MAGNETO]] = (LORA_TRACKER_MOTION_SENSOR_FuncDrv_t *)(
					void *)&LSM303AGR_MAG_Driver;

			if (MotionDrv[LORA_TRACKER_LSM303AGR_MAG_0]->Init(MotionCompObj[LORA_TRACKER_LSM303AGR_MAG_0]) != LSM303AGR_OK)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
	}

	return ret;
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

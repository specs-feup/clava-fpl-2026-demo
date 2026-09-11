// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xconvolve2d_rep0_hw.h"

extern XConvolve2d_rep0_hw_Config XConvolve2d_rep0_hw_ConfigTable[];

#ifdef SDT
XConvolve2d_rep0_hw_Config *XConvolve2d_rep0_hw_LookupConfig(UINTPTR BaseAddress) {
	XConvolve2d_rep0_hw_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XConvolve2d_rep0_hw_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XConvolve2d_rep0_hw_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XConvolve2d_rep0_hw_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XConvolve2d_rep0_hw_Initialize(XConvolve2d_rep0_hw *InstancePtr, UINTPTR BaseAddress) {
	XConvolve2d_rep0_hw_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XConvolve2d_rep0_hw_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XConvolve2d_rep0_hw_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XConvolve2d_rep0_hw_Config *XConvolve2d_rep0_hw_LookupConfig(u16 DeviceId) {
	XConvolve2d_rep0_hw_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCONVOLVE2D_REP0_HW_NUM_INSTANCES; Index++) {
		if (XConvolve2d_rep0_hw_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XConvolve2d_rep0_hw_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XConvolve2d_rep0_hw_Initialize(XConvolve2d_rep0_hw *InstancePtr, u16 DeviceId) {
	XConvolve2d_rep0_hw_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XConvolve2d_rep0_hw_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XConvolve2d_rep0_hw_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif


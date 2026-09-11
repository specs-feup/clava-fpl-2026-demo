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
#include "xedge_detect_hw.h"

extern XEdge_detect_hw_Config XEdge_detect_hw_ConfigTable[];

#ifdef SDT
XEdge_detect_hw_Config *XEdge_detect_hw_LookupConfig(UINTPTR BaseAddress) {
	XEdge_detect_hw_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XEdge_detect_hw_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XEdge_detect_hw_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XEdge_detect_hw_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEdge_detect_hw_Initialize(XEdge_detect_hw *InstancePtr, UINTPTR BaseAddress) {
	XEdge_detect_hw_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEdge_detect_hw_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEdge_detect_hw_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XEdge_detect_hw_Config *XEdge_detect_hw_LookupConfig(u16 DeviceId) {
	XEdge_detect_hw_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XEDGE_DETECT_HW_NUM_INSTANCES; Index++) {
		if (XEdge_detect_hw_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XEdge_detect_hw_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEdge_detect_hw_Initialize(XEdge_detect_hw *InstancePtr, u16 DeviceId) {
	XEdge_detect_hw_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEdge_detect_hw_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEdge_detect_hw_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif


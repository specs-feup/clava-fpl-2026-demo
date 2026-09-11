// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XEDGE_DETECT_HW_H
#define XEDGE_DETECT_HW_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xedge_detect_hw_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XEdge_detect_hw_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XEdge_detect_hw;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XEdge_detect_hw_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XEdge_detect_hw_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XEdge_detect_hw_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XEdge_detect_hw_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XEdge_detect_hw_Initialize(XEdge_detect_hw *InstancePtr, UINTPTR BaseAddress);
XEdge_detect_hw_Config* XEdge_detect_hw_LookupConfig(UINTPTR BaseAddress);
#else
int XEdge_detect_hw_Initialize(XEdge_detect_hw *InstancePtr, u16 DeviceId);
XEdge_detect_hw_Config* XEdge_detect_hw_LookupConfig(u16 DeviceId);
#endif
int XEdge_detect_hw_CfgInitialize(XEdge_detect_hw *InstancePtr, XEdge_detect_hw_Config *ConfigPtr);
#else
int XEdge_detect_hw_Initialize(XEdge_detect_hw *InstancePtr, const char* InstanceName);
int XEdge_detect_hw_Release(XEdge_detect_hw *InstancePtr);
#endif

void XEdge_detect_hw_Start(XEdge_detect_hw *InstancePtr);
u32 XEdge_detect_hw_IsDone(XEdge_detect_hw *InstancePtr);
u32 XEdge_detect_hw_IsIdle(XEdge_detect_hw *InstancePtr);
u32 XEdge_detect_hw_IsReady(XEdge_detect_hw *InstancePtr);
void XEdge_detect_hw_Continue(XEdge_detect_hw *InstancePtr);
void XEdge_detect_hw_EnableAutoRestart(XEdge_detect_hw *InstancePtr);
void XEdge_detect_hw_DisableAutoRestart(XEdge_detect_hw *InstancePtr);

void XEdge_detect_hw_Set_image_gray(XEdge_detect_hw *InstancePtr, u64 Data);
u64 XEdge_detect_hw_Get_image_gray(XEdge_detect_hw *InstancePtr);
void XEdge_detect_hw_Set_output_r(XEdge_detect_hw *InstancePtr, u64 Data);
u64 XEdge_detect_hw_Get_output_r(XEdge_detect_hw *InstancePtr);

void XEdge_detect_hw_InterruptGlobalEnable(XEdge_detect_hw *InstancePtr);
void XEdge_detect_hw_InterruptGlobalDisable(XEdge_detect_hw *InstancePtr);
void XEdge_detect_hw_InterruptEnable(XEdge_detect_hw *InstancePtr, u32 Mask);
void XEdge_detect_hw_InterruptDisable(XEdge_detect_hw *InstancePtr, u32 Mask);
void XEdge_detect_hw_InterruptClear(XEdge_detect_hw *InstancePtr, u32 Mask);
u32 XEdge_detect_hw_InterruptGetEnabled(XEdge_detect_hw *InstancePtr);
u32 XEdge_detect_hw_InterruptGetStatus(XEdge_detect_hw *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

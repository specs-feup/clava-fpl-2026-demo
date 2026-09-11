// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XCONVOLVE2D_REP0_HW_H
#define XCONVOLVE2D_REP0_HW_H

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
#include "xconvolve2d_rep0_hw_hw.h"

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
} XConvolve2d_rep0_hw_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XConvolve2d_rep0_hw;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XConvolve2d_rep0_hw_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XConvolve2d_rep0_hw_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XConvolve2d_rep0_hw_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XConvolve2d_rep0_hw_ReadReg(BaseAddress, RegOffset) \
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
int XConvolve2d_rep0_hw_Initialize(XConvolve2d_rep0_hw *InstancePtr, UINTPTR BaseAddress);
XConvolve2d_rep0_hw_Config* XConvolve2d_rep0_hw_LookupConfig(UINTPTR BaseAddress);
#else
int XConvolve2d_rep0_hw_Initialize(XConvolve2d_rep0_hw *InstancePtr, u16 DeviceId);
XConvolve2d_rep0_hw_Config* XConvolve2d_rep0_hw_LookupConfig(u16 DeviceId);
#endif
int XConvolve2d_rep0_hw_CfgInitialize(XConvolve2d_rep0_hw *InstancePtr, XConvolve2d_rep0_hw_Config *ConfigPtr);
#else
int XConvolve2d_rep0_hw_Initialize(XConvolve2d_rep0_hw *InstancePtr, const char* InstanceName);
int XConvolve2d_rep0_hw_Release(XConvolve2d_rep0_hw *InstancePtr);
#endif

void XConvolve2d_rep0_hw_Start(XConvolve2d_rep0_hw *InstancePtr);
u32 XConvolve2d_rep0_hw_IsDone(XConvolve2d_rep0_hw *InstancePtr);
u32 XConvolve2d_rep0_hw_IsIdle(XConvolve2d_rep0_hw *InstancePtr);
u32 XConvolve2d_rep0_hw_IsReady(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_Continue(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_EnableAutoRestart(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_DisableAutoRestart(XConvolve2d_rep0_hw *InstancePtr);

void XConvolve2d_rep0_hw_Set_input_image(XConvolve2d_rep0_hw *InstancePtr, u64 Data);
u64 XConvolve2d_rep0_hw_Get_input_image(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_Set_filter(XConvolve2d_rep0_hw *InstancePtr, u64 Data);
u64 XConvolve2d_rep0_hw_Get_filter(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_Set_output_image(XConvolve2d_rep0_hw *InstancePtr, u64 Data);
u64 XConvolve2d_rep0_hw_Get_output_image(XConvolve2d_rep0_hw *InstancePtr);

void XConvolve2d_rep0_hw_InterruptGlobalEnable(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_InterruptGlobalDisable(XConvolve2d_rep0_hw *InstancePtr);
void XConvolve2d_rep0_hw_InterruptEnable(XConvolve2d_rep0_hw *InstancePtr, u32 Mask);
void XConvolve2d_rep0_hw_InterruptDisable(XConvolve2d_rep0_hw *InstancePtr, u32 Mask);
void XConvolve2d_rep0_hw_InterruptClear(XConvolve2d_rep0_hw *InstancePtr, u32 Mask);
u32 XConvolve2d_rep0_hw_InterruptGetEnabled(XConvolve2d_rep0_hw *InstancePtr);
u32 XConvolve2d_rep0_hw_InterruptGetStatus(XConvolve2d_rep0_hw *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xconvolve2d_rep0_hw.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XConvolve2d_rep0_hw_CfgInitialize(XConvolve2d_rep0_hw *InstancePtr, XConvolve2d_rep0_hw_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XConvolve2d_rep0_hw_Start(XConvolve2d_rep0_hw *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL) & 0x80;
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XConvolve2d_rep0_hw_IsDone(XConvolve2d_rep0_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XConvolve2d_rep0_hw_IsIdle(XConvolve2d_rep0_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XConvolve2d_rep0_hw_IsReady(XConvolve2d_rep0_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XConvolve2d_rep0_hw_Continue(XConvolve2d_rep0_hw *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL) & 0x80;
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XConvolve2d_rep0_hw_EnableAutoRestart(XConvolve2d_rep0_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XConvolve2d_rep0_hw_DisableAutoRestart(XConvolve2d_rep0_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_AP_CTRL, 0);
}

void XConvolve2d_rep0_hw_Set_input_image(XConvolve2d_rep0_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_INPUT_IMAGE_DATA, (u32)(Data));
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_INPUT_IMAGE_DATA + 4, (u32)(Data >> 32));
}

u64 XConvolve2d_rep0_hw_Get_input_image(XConvolve2d_rep0_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_INPUT_IMAGE_DATA);
    Data += (u64)XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_INPUT_IMAGE_DATA + 4) << 32;
    return Data;
}

void XConvolve2d_rep0_hw_Set_filter(XConvolve2d_rep0_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_FILTER_DATA, (u32)(Data));
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_FILTER_DATA + 4, (u32)(Data >> 32));
}

u64 XConvolve2d_rep0_hw_Get_filter(XConvolve2d_rep0_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_FILTER_DATA);
    Data += (u64)XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_FILTER_DATA + 4) << 32;
    return Data;
}

void XConvolve2d_rep0_hw_Set_output_image(XConvolve2d_rep0_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_OUTPUT_IMAGE_DATA, (u32)(Data));
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_OUTPUT_IMAGE_DATA + 4, (u32)(Data >> 32));
}

u64 XConvolve2d_rep0_hw_Get_output_image(XConvolve2d_rep0_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_OUTPUT_IMAGE_DATA);
    Data += (u64)XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_OUTPUT_IMAGE_DATA + 4) << 32;
    return Data;
}

void XConvolve2d_rep0_hw_InterruptGlobalEnable(XConvolve2d_rep0_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_GIE, 1);
}

void XConvolve2d_rep0_hw_InterruptGlobalDisable(XConvolve2d_rep0_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_GIE, 0);
}

void XConvolve2d_rep0_hw_InterruptEnable(XConvolve2d_rep0_hw *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_IER);
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_IER, Register | Mask);
}

void XConvolve2d_rep0_hw_InterruptDisable(XConvolve2d_rep0_hw *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_IER);
    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_IER, Register & (~Mask));
}

void XConvolve2d_rep0_hw_InterruptClear(XConvolve2d_rep0_hw *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConvolve2d_rep0_hw_WriteReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_ISR, Mask);
}

u32 XConvolve2d_rep0_hw_InterruptGetEnabled(XConvolve2d_rep0_hw *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_IER);
}

u32 XConvolve2d_rep0_hw_InterruptGetStatus(XConvolve2d_rep0_hw *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConvolve2d_rep0_hw_ReadReg(InstancePtr->Control_BaseAddress, XCONVOLVE2D_REP0_HW_CONTROL_ADDR_ISR);
}


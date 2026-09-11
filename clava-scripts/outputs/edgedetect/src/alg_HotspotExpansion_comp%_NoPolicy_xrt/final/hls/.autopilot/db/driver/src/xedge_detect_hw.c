// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xedge_detect_hw.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XEdge_detect_hw_CfgInitialize(XEdge_detect_hw *InstancePtr, XEdge_detect_hw_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XEdge_detect_hw_Start(XEdge_detect_hw *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL) & 0x80;
    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XEdge_detect_hw_IsDone(XEdge_detect_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XEdge_detect_hw_IsIdle(XEdge_detect_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XEdge_detect_hw_IsReady(XEdge_detect_hw *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XEdge_detect_hw_Continue(XEdge_detect_hw *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL) & 0x80;
    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XEdge_detect_hw_EnableAutoRestart(XEdge_detect_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XEdge_detect_hw_DisableAutoRestart(XEdge_detect_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL, 0);
}

void XEdge_detect_hw_Set_image_gray(XEdge_detect_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IMAGE_GRAY_DATA, (u32)(Data));
    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IMAGE_GRAY_DATA + 4, (u32)(Data >> 32));
}

u64 XEdge_detect_hw_Get_image_gray(XEdge_detect_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IMAGE_GRAY_DATA);
    Data += (u64)XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IMAGE_GRAY_DATA + 4) << 32;
    return Data;
}

void XEdge_detect_hw_Set_output_r(XEdge_detect_hw *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_OUTPUT_R_DATA, (u32)(Data));
    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_OUTPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XEdge_detect_hw_Get_output_r(XEdge_detect_hw *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_OUTPUT_R_DATA);
    Data += (u64)XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_OUTPUT_R_DATA + 4) << 32;
    return Data;
}

void XEdge_detect_hw_InterruptGlobalEnable(XEdge_detect_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_GIE, 1);
}

void XEdge_detect_hw_InterruptGlobalDisable(XEdge_detect_hw *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_GIE, 0);
}

void XEdge_detect_hw_InterruptEnable(XEdge_detect_hw *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IER);
    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IER, Register | Mask);
}

void XEdge_detect_hw_InterruptDisable(XEdge_detect_hw *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IER);
    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IER, Register & (~Mask));
}

void XEdge_detect_hw_InterruptClear(XEdge_detect_hw *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEdge_detect_hw_WriteReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_ISR, Mask);
}

u32 XEdge_detect_hw_InterruptGetEnabled(XEdge_detect_hw *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_IER);
}

u32 XEdge_detect_hw_InterruptGetStatus(XEdge_detect_hw *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEdge_detect_hw_ReadReg(InstancePtr->Control_BaseAddress, XEDGE_DETECT_HW_CONTROL_ADDR_ISR);
}


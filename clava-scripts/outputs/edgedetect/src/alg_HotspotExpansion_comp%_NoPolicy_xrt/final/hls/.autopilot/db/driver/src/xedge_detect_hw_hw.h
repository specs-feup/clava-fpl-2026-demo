// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 4  - ap_continue (Read/Write/SC)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of image_gray
//        bit 31~0 - image_gray[31:0] (Read/Write)
// 0x14 : Data signal of image_gray
//        bit 31~0 - image_gray[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of output_r
//        bit 31~0 - output_r[31:0] (Read/Write)
// 0x20 : Data signal of output_r
//        bit 31~0 - output_r[63:32] (Read/Write)
// 0x24 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XEDGE_DETECT_HW_CONTROL_ADDR_AP_CTRL         0x00
#define XEDGE_DETECT_HW_CONTROL_ADDR_GIE             0x04
#define XEDGE_DETECT_HW_CONTROL_ADDR_IER             0x08
#define XEDGE_DETECT_HW_CONTROL_ADDR_ISR             0x0c
#define XEDGE_DETECT_HW_CONTROL_ADDR_IMAGE_GRAY_DATA 0x10
#define XEDGE_DETECT_HW_CONTROL_BITS_IMAGE_GRAY_DATA 64
#define XEDGE_DETECT_HW_CONTROL_ADDR_OUTPUT_R_DATA   0x1c
#define XEDGE_DETECT_HW_CONTROL_BITS_OUTPUT_R_DATA   64


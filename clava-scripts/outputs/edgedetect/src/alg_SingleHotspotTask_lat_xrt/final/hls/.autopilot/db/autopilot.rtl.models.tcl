set SynModuleInfo {
  {SRCNAME convolve2d_rep0_hw_Pipeline_VITIS_LOOP_16_1_VITIS_LOOP_17_2 MODELNAME convolve2d_rep0_hw_Pipeline_VITIS_LOOP_16_1_VITIS_LOOP_17_2 RTLNAME convolve2d_rep0_hw_convolve2d_rep0_hw_Pipeline_VITIS_LOOP_16_1_VITIS_LOOP_17_2
    SUBMODULES {
      {MODELNAME convolve2d_rep0_hw_flow_control_loop_pipe_sequential_init RTLNAME convolve2d_rep0_hw_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME convolve2d_rep0_hw_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME convolve2d_rep0_hw_Pipeline_VITIS_LOOP_29_3_VITIS_LOOP_30_4 MODELNAME convolve2d_rep0_hw_Pipeline_VITIS_LOOP_29_3_VITIS_LOOP_30_4 RTLNAME convolve2d_rep0_hw_convolve2d_rep0_hw_Pipeline_VITIS_LOOP_29_3_VITIS_LOOP_30_4
    SUBMODULES {
      {MODELNAME convolve2d_rep0_hw_mul_32s_32s_32_1_1 RTLNAME convolve2d_rep0_hw_mul_32s_32s_32_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME convolve2d_rep0_hw_sdiv_32ns_32ns_32_36_1 RTLNAME convolve2d_rep0_hw_sdiv_32ns_32ns_32_36_1 BINDTYPE op TYPE sdiv IMPL auto LATENCY 35 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME convolve2d_rep0_hw MODELNAME convolve2d_rep0_hw RTLNAME convolve2d_rep0_hw IS_TOP 1
    SUBMODULES {
      {MODELNAME convolve2d_rep0_hw_gmem_m_axi RTLNAME convolve2d_rep0_hw_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME convolve2d_rep0_hw_control_s_axi RTLNAME convolve2d_rep0_hw_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}

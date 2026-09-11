set SynModuleInfo {
  {SRCNAME edge_detect_hw_Pipeline_1 MODELNAME edge_detect_hw_Pipeline_1 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_1
    SUBMODULES {
      {MODELNAME edge_detect_hw_flow_control_loop_pipe_sequential_init RTLNAME edge_detect_hw_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME edge_detect_hw_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME edge_detect_hw_Pipeline_2 MODELNAME edge_detect_hw_Pipeline_2 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_2
    SUBMODULES {
      {MODELNAME edge_detect_hw_sdiv_32ns_7ns_32_36_1 RTLNAME edge_detect_hw_sdiv_32ns_7ns_32_36_1 BINDTYPE op TYPE sdiv IMPL auto LATENCY 35 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME edge_detect_hw_Pipeline_3 MODELNAME edge_detect_hw_Pipeline_3 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_3}
  {SRCNAME edge_detect_hw_Pipeline_4 MODELNAME edge_detect_hw_Pipeline_4 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_4}
  {SRCNAME edge_detect_hw_Pipeline_5 MODELNAME edge_detect_hw_Pipeline_5 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_5}
  {SRCNAME edge_detect_hw_Pipeline_6 MODELNAME edge_detect_hw_Pipeline_6 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_6}
  {SRCNAME edge_detect_hw_Pipeline_7 MODELNAME edge_detect_hw_Pipeline_7 RTLNAME edge_detect_hw_edge_detect_hw_Pipeline_7}
  {SRCNAME edge_detect_hw MODELNAME edge_detect_hw RTLNAME edge_detect_hw IS_TOP 1
    SUBMODULES {
      {MODELNAME edge_detect_hw_filter_RAM_AUTO_1R1W RTLNAME edge_detect_hw_filter_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME edge_detect_hw_temp_buf_RAM_AUTO_1R1W RTLNAME edge_detect_hw_temp_buf_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME edge_detect_hw_gmem_m_axi RTLNAME edge_detect_hw_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME edge_detect_hw_control_s_axi RTLNAME edge_detect_hw_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}

; ModuleID = '/home/tls/clava-workspace/clava-fpl-2026-demo/clava-scripts/outputs/edgedetect/src/alg_HotspotExpansion_comp%_NoPolicy_xrt/final/hls/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: noinline
define void @apatb_edge_detect_hw_ir(i32* nocapture "fpga.decayed.dim.hint"="262144" %image_gray, i32* nocapture "fpga.decayed.dim.hint"="262144" %output) local_unnamed_addr #0 {
entry:
  %0 = bitcast i32* %image_gray to [262144 x i32]*
  %1 = call i8* @malloc(i64 1048576)
  %image_gray_copy = bitcast i8* %1 to [262144 x i32]*
  %2 = bitcast i32* %output to [262144 x i32]*
  %3 = call i8* @malloc(i64 1048576)
  %output_copy = bitcast i8* %3 to [262144 x i32]*
  call fastcc void @copy_in([262144 x i32]* %0, [262144 x i32]* %image_gray_copy, [262144 x i32]* %2, [262144 x i32]* %output_copy)
  call void @apatb_edge_detect_hw_hw([262144 x i32]* %image_gray_copy, [262144 x i32]* %output_copy)
  call void @copy_back([262144 x i32]* %0, [262144 x i32]* %image_gray_copy, [262144 x i32]* %2, [262144 x i32]* %output_copy)
  tail call void @free(i8* %1)
  tail call void @free(i8* %3)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in([262144 x i32]* readonly, [262144 x i32]*, [262144 x i32]* readonly, [262144 x i32]*) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %1, [262144 x i32]* %0)
  call fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %3, [262144 x i32]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %dst, [262144 x i32]* readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq [262144 x i32]* %dst, null
  %1 = icmp eq [262144 x i32]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a262144i32([262144 x i32]* nonnull %dst, [262144 x i32]* nonnull %src, i64 262144)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a262144i32([262144 x i32]* %dst, [262144 x i32]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [262144 x i32]* %src, null
  %1 = icmp eq [262144 x i32]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [262144 x i32], [262144 x i32]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [262144 x i32], [262144 x i32]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i32, i32* %src.addr, align 4
  store i32 %3, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out([262144 x i32]*, [262144 x i32]* readonly, [262144 x i32]*, [262144 x i32]* readonly) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %0, [262144 x i32]* %1)
  call fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %2, [262144 x i32]* %3)
  ret void
}

declare i8* @malloc(i64) local_unnamed_addr

declare void @free(i8*) local_unnamed_addr

declare void @apatb_edge_detect_hw_hw([262144 x i32]*, [262144 x i32]*)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back([262144 x i32]*, [262144 x i32]* readonly, [262144 x i32]*, [262144 x i32]* readonly) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %0, [262144 x i32]* %1)
  call fastcc void @onebyonecpy_hls.p0a262144i32([262144 x i32]* %2, [262144 x i32]* %3)
  ret void
}

declare void @edge_detect_hw_hw_stub(i32* nocapture, i32* nocapture)

define void @edge_detect_hw_hw_stub_wrapper([262144 x i32]*, [262144 x i32]*) #5 {
entry:
  call void @copy_out([262144 x i32]* null, [262144 x i32]* %0, [262144 x i32]* null, [262144 x i32]* %1)
  %2 = bitcast [262144 x i32]* %0 to i32*
  %3 = bitcast [262144 x i32]* %1 to i32*
  call void @edge_detect_hw_hw_stub(i32* %2, i32* %3)
  call void @copy_in([262144 x i32]* null, [262144 x i32]* %0, [262144 x i32]* null, [262144 x i32]* %1)
  ret void
}

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="arraycpy_hls" }
attributes #4 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}

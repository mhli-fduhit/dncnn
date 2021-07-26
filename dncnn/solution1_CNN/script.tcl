############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project dncnn
set_top DnCNN
add_files DnCNN.cpp
add_files -tb main.cpp
open_solution "solution1_CNN"
set_part {xc7vx485tffg1157-1}
create_clock -period 10 -name default
#source "./dncnn/solution1_CNN/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

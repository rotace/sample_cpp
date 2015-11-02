#!/bin/bash
source run.sh

proj=$1
freqs=$2
freqe=$3
freqd=$4
ver=$5

### make feap file (at first!)
run preproc-hexa${ver} -stfem "mesh_input/stfem.txt"

run rm -f structuremesh.fea
run rm -f structuremesh.vtk

### make wbm file (at last!)
run preproc-hexa${ver} -wbm "mesh_input/wbm1.txt"
run preproc-hexa${ver} -wbm "mesh_input/wbm2.txt"

run rm -f mesh_input/wbmheader.wbm
run rm -f mesh_input/wbm1.wbm
run rm -f mesh_input/wbm2.wbm
run rm -f mesh_input/hybrid-info.dat

echo "pre-process finished"

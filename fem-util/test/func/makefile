##################################
#     target files               #
##################################

#
.SUFFIXES:
.SUFFIXES: .wbm .fea .csv

proj=SimpleHybridTest
freqs=100
freqe=100
freqd=20

# preproc-hexa version
ver=3.5

##################################
#            rules               #
##################################

#
all	: pre
##################

pre	:
	./pre.sh ${proj} ${freqs} ${freqe} ${freqd} ${ver}


##################
view	:
	paraview &

clean-pre	:
	\rm -f mesh_input/{*.wbm,*.dat}
	\rm -f ${proj}.wbm
	\rm -f I${proj}.fea
	\rm -f *.vtk

clean-all	: clean-pre

clean	: clean-pre


# IsotopeFitLib
Project is split into two parts. Program that fits the mass spectra and library that contains functions needed by the fitting program and possibly in the future by the GUI. Files listed below are only the important ones. Everything is in various stages of unfinished.

Files:

IsotopeFitter
	include
		IsotopeFitter.h
		DesignMatrix.h
		LeastSquares.h
		DebugUtils.h
	src
		IsotopeFitter.cpp
		DesignMatrix.cpp
		LeastSquares.cpp
		DebugUtils.cpp
	Makefile

IsotopeFitLib
	include
		ifl.h
		ifl_data.h
		ifl_dataprocessing.h
		ifl_h5file.h
		ifl_ifdfile.h
	src
		ifl_data.cpp
		ifl_dataprocessing.cpp
		ifl_h5file.cpp
		ifl_ifdfile.cpp

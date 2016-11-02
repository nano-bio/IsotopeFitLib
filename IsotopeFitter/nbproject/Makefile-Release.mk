#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/DebugUtils.o \
	${OBJECTDIR}/src/DesignMatrix.o \
	${OBJECTDIR}/src/IsotopeFitter.o \
	${OBJECTDIR}/src/LeastSquares.o \
	${OBJECTDIR}/storage/Snippets.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f6

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/fittingtest.o \
	${TESTDIR}/tests/fittingtest2.o \
	${TESTDIR}/tests/gsltest.o \
	${TESTDIR}/tests/h5openread.o \
	${TESTDIR}/tests/matiotest.o \
	${TESTDIR}/tests/qrfittingdemo.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DRELEASE -DHAVE_INLINE
CXXFLAGS=-DRELEASE -DHAVE_INLINE

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib ../IsotopeFitLib/dist/Release/GNU-Linux/libifl.a /usr/local/lib/libmatio.a /usr/local/lib/libhdf5_cpp.a /usr/local/lib/libhdf5.a /usr/local/lib/libsz.a /usr/local/lib/libz.a /usr/lib/x86_64-linux-gnu/libc.a /usr/lib/x86_64-linux-gnu/libdl.a /usr/local/lib/libgsl.a /usr/local/lib/libgslcblas.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: ../IsotopeFitLib/dist/Release/GNU-Linux/libifl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libmatio.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libhdf5_cpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libhdf5.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libsz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/lib/x86_64-linux-gnu/libc.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/lib/x86_64-linux-gnu/libdl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libgsl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libgslcblas.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter ${OBJECTFILES} ${LDLIBSOPTIONS} -static

${OBJECTDIR}/src/DebugUtils.o: src/DebugUtils.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DebugUtils.o src/DebugUtils.cpp

${OBJECTDIR}/src/DesignMatrix.o: src/DesignMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DesignMatrix.o src/DesignMatrix.cpp

${OBJECTDIR}/src/IsotopeFitter.o: src/IsotopeFitter.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IsotopeFitter.o src/IsotopeFitter.cpp

${OBJECTDIR}/src/LeastSquares.o: src/LeastSquares.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LeastSquares.o src/LeastSquares.cpp

${OBJECTDIR}/storage/Snippets.o: storage/Snippets.cpp
	${MKDIR} -p ${OBJECTDIR}/storage
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/storage/Snippets.o storage/Snippets.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/fittingtest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/fittingtest2.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/gsltest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}  -static 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/h5openread.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/matiotest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/qrfittingdemo.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/fittingtest.o: tests/fittingtest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/fittingtest.o tests/fittingtest.cpp


${TESTDIR}/tests/fittingtest2.o: tests/fittingtest2.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/fittingtest2.o tests/fittingtest2.cpp


${TESTDIR}/tests/gsltest.o: tests/gsltest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/gsltest.o tests/gsltest.cpp


${TESTDIR}/tests/h5openread.o: tests/h5openread.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/h5openread.o tests/h5openread.cpp


${TESTDIR}/tests/matiotest.o: tests/matiotest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/matiotest.o tests/matiotest.cpp


${TESTDIR}/tests/qrfittingdemo.o: tests/qrfittingdemo.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -I/usr/local/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/qrfittingdemo.o tests/qrfittingdemo.cpp


${OBJECTDIR}/src/DebugUtils_nomain.o: ${OBJECTDIR}/src/DebugUtils.o src/DebugUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DebugUtils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DebugUtils_nomain.o src/DebugUtils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DebugUtils.o ${OBJECTDIR}/src/DebugUtils_nomain.o;\
	fi

${OBJECTDIR}/src/DesignMatrix_nomain.o: ${OBJECTDIR}/src/DesignMatrix.o src/DesignMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DesignMatrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DesignMatrix_nomain.o src/DesignMatrix.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DesignMatrix.o ${OBJECTDIR}/src/DesignMatrix_nomain.o;\
	fi

${OBJECTDIR}/src/IsotopeFitter_nomain.o: ${OBJECTDIR}/src/IsotopeFitter.o src/IsotopeFitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/IsotopeFitter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IsotopeFitter_nomain.o src/IsotopeFitter.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/IsotopeFitter.o ${OBJECTDIR}/src/IsotopeFitter_nomain.o;\
	fi

${OBJECTDIR}/src/LeastSquares_nomain.o: ${OBJECTDIR}/src/LeastSquares.o src/LeastSquares.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/LeastSquares.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LeastSquares_nomain.o src/LeastSquares.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/LeastSquares.o ${OBJECTDIR}/src/LeastSquares_nomain.o;\
	fi

${OBJECTDIR}/storage/Snippets_nomain.o: ${OBJECTDIR}/storage/Snippets.o storage/Snippets.cpp 
	${MKDIR} -p ${OBJECTDIR}/storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/storage/Snippets.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -I/usr/local/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/storage/Snippets_nomain.o storage/Snippets.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/storage/Snippets.o ${OBJECTDIR}/storage/Snippets_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

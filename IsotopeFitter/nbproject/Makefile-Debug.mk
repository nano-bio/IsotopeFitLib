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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/IsotopeFitter.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/h5openread.o \
	${TESTDIR}/tests/h5readatt.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib -L/home/matlab/Michal/glibcinstall/lib ../IsotopeFitLib/dist/Debug/GNU-Linux/libisotopefitlib.a /usr/local/lib/libhdf5_cpp.a /usr/local/lib/libhdf5.a /usr/local/lib/libsz.a /usr/local/lib/libz.a /home/matlab/Michal/glibcinstall/lib/libdl.a /home/matlab/Michal/glibcinstall/lib/libc.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: ../IsotopeFitLib/dist/Debug/GNU-Linux/libisotopefitlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libhdf5_cpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libhdf5.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libsz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /usr/local/lib/libz.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /home/matlab/Michal/glibcinstall/lib/libdl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: /home/matlab/Michal/glibcinstall/lib/libc.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter ${OBJECTFILES} ${LDLIBSOPTIONS} -static

${OBJECTDIR}/IsotopeFitter.o: IsotopeFitter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -I/home/matlab/Michal/glibcinstall/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IsotopeFitter.o IsotopeFitter.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/h5openread.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}  -static -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/h5readatt.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}  -static -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/h5openread.o: tests/h5openread.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -I/home/matlab/Michal/glibcinstall/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/h5openread.o tests/h5openread.cpp


${TESTDIR}/tests/h5readatt.o: tests/h5readatt.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -I/home/matlab/Michal/glibcinstall/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/h5readatt.o tests/h5readatt.cpp


${OBJECTDIR}/IsotopeFitter_nomain.o: ${OBJECTDIR}/IsotopeFitter.o IsotopeFitter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/IsotopeFitter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -I/home/matlab/Michal/glibcinstall/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IsotopeFitter_nomain.o IsotopeFitter.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/IsotopeFitter.o ${OBJECTDIR}/IsotopeFitter_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isotopefitter

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

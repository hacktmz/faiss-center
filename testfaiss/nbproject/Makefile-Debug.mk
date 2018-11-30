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
	${OBJECTDIR}/_ext/b0d353e8/GLogHelper.o \
	${OBJECTDIR}/_ext/b0d353e8/gpu_manager.o \
	${OBJECTDIR}/_ext/b0d353e8/index_manager.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib64 -L/usr/local/cuda-8.0/targets/x86_64-linux/lib/ ../faissjni/glog/libglog.a ../faiss/libfaiss.a ../faiss/gpu/libgpufaiss.a /usr/lib64/libopenblas.so.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss
	${CP} /usr/lib64/libopenblas.so.0 ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss: ../faissjni/glog/libglog.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss: ../faiss/libfaiss.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss: ../faiss/gpu/libgpufaiss.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss: /usr/lib64/libopenblas.so.0

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss ${OBJECTFILES} ${LDLIBSOPTIONS} -fopenmp -lgomp -lblas -lcublas -lcudart -s

${OBJECTDIR}/_ext/b0d353e8/GLogHelper.o: ../faissjni/jnisrc/GLogHelper.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b0d353e8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../faiss -I/usr/local/cuda-8.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0d353e8/GLogHelper.o ../faissjni/jnisrc/GLogHelper.cpp

${OBJECTDIR}/_ext/b0d353e8/gpu_manager.o: ../faissjni/jnisrc/gpu_manager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b0d353e8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../faiss -I/usr/local/cuda-8.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0d353e8/gpu_manager.o ../faissjni/jnisrc/gpu_manager.cpp

${OBJECTDIR}/_ext/b0d353e8/index_manager.o: ../faissjni/jnisrc/index_manager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b0d353e8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../faiss -I/usr/local/cuda-8.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0d353e8/index_manager.o ../faissjni/jnisrc/index_manager.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../faiss -I/usr/local/cuda-8.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopenblas.so.0
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testfaiss

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

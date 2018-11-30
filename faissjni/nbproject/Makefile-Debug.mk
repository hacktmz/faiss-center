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
	${OBJECTDIR}/jnisrc/GLogHelper.o \
	${OBJECTDIR}/jnisrc/com_jiuyan_faiss_NativeClient.o \
	${OBJECTDIR}/jnisrc/gpu_manager.o \
	${OBJECTDIR}/jnisrc/index_manager.o


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
LDLIBSOPTIONS=-L/usr/local/cuda-8.0/targets/x86_64-linux/lib/ ../faiss/libfaiss.a ../faiss/gpu/libgpufaiss.a ./glog/libglog.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/output/libfaissjni.${CND_DLIB_EXT}

build/output/libfaissjni.${CND_DLIB_EXT}: ../faiss/libfaiss.a

build/output/libfaissjni.${CND_DLIB_EXT}: ../faiss/gpu/libgpufaiss.a

build/output/libfaissjni.${CND_DLIB_EXT}: ./glog/libglog.a

build/output/libfaissjni.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p build/output
	g++ -o build/output/libfaissjni.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -fopenmp -lgomp -lblas -lcublas -lcudart -shared -fPIC

${OBJECTDIR}/jnisrc/GLogHelper.o: jnisrc/GLogHelper.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -g -I./jnisrc -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux -I./deps/faiss -I/usr/local/cuda-8.0/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/GLogHelper.o jnisrc/GLogHelper.cpp

${OBJECTDIR}/jnisrc/com_jiuyan_faiss_NativeClient.o: jnisrc/com_jiuyan_faiss_NativeClient.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -g -I./jnisrc -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux -I./deps/faiss -I/usr/local/cuda-8.0/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/com_jiuyan_faiss_NativeClient.o jnisrc/com_jiuyan_faiss_NativeClient.cpp

${OBJECTDIR}/jnisrc/gpu_manager.o: jnisrc/gpu_manager.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -g -I./jnisrc -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux -I./deps/faiss -I/usr/local/cuda-8.0/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/gpu_manager.o jnisrc/gpu_manager.cpp

${OBJECTDIR}/jnisrc/index_manager.o: jnisrc/index_manager.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -g -I./jnisrc -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux -I./deps/faiss -I/usr/local/cuda-8.0/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/index_manager.o jnisrc/index_manager.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

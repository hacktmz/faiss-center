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
CND_PLATFORM=None-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
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
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfaissjni.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfaissjni.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libfaissjni.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/jnisrc/GLogHelper.o: jnisrc/GLogHelper.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/GLogHelper.o jnisrc/GLogHelper.cpp

${OBJECTDIR}/jnisrc/com_jiuyan_faiss_NativeClient.o: jnisrc/com_jiuyan_faiss_NativeClient.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/com_jiuyan_faiss_NativeClient.o jnisrc/com_jiuyan_faiss_NativeClient.cpp

${OBJECTDIR}/jnisrc/gpu_manager.o: jnisrc/gpu_manager.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/gpu_manager.o jnisrc/gpu_manager.cpp

${OBJECTDIR}/jnisrc/index_manager.o: jnisrc/index_manager.cpp
	${MKDIR} -p ${OBJECTDIR}/jnisrc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jnisrc/index_manager.o jnisrc/index_manager.cpp

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

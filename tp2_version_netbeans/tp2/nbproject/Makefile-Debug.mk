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
	${OBJECTDIR}/_ext/f661f5f6/complex.o \
	${OBJECTDIR}/_ext/f661f5f6/lib_parser.o \
	${OBJECTDIR}/_ext/f661f5f6/mandelbrot.o \
	${OBJECTDIR}/_ext/f661f5f6/real_main.o \
	${OBJECTDIR}/_ext/f661f5f6/utils.o


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
LDLIBSOPTIONS=`pkg-config --libs allegro-5.0` `pkg-config --libs allegro_acodec-5.0` `pkg-config --libs allegro_audio-5.0` `pkg-config --libs allegro_color-5.0` `pkg-config --libs allegro_dialog-5.0` `pkg-config --libs allegro_font-5.0` `pkg-config --libs allegro_image-5.0` `pkg-config --libs allegro_main-5.0` `pkg-config --libs allegro_memfile-5.0` `pkg-config --libs allegro_physfs-5.0` `pkg-config --libs allegro_primitives-5.0` `pkg-config --libs allegro_ttf-5.0` -lm   

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/f661f5f6/complex.o: ../../tp2/Project1/Project1/complex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f661f5f6
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f661f5f6/complex.o ../../tp2/Project1/Project1/complex.c

${OBJECTDIR}/_ext/f661f5f6/lib_parser.o: ../../tp2/Project1/Project1/lib_parser.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f661f5f6
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f661f5f6/lib_parser.o ../../tp2/Project1/Project1/lib_parser.c

${OBJECTDIR}/_ext/f661f5f6/mandelbrot.o: ../../tp2/Project1/Project1/mandelbrot.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f661f5f6
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f661f5f6/mandelbrot.o ../../tp2/Project1/Project1/mandelbrot.c

${OBJECTDIR}/_ext/f661f5f6/real_main.o: ../../tp2/Project1/Project1/real_main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f661f5f6
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f661f5f6/real_main.o ../../tp2/Project1/Project1/real_main.c

${OBJECTDIR}/_ext/f661f5f6/utils.o: ../../tp2/Project1/Project1/utils.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f661f5f6
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f661f5f6/utils.o ../../tp2/Project1/Project1/utils.c

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

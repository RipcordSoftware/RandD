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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/_ext/793978143/gason.o \
	${OBJECTDIR}/_ext/882160277/script_array_json_source.o \
	${OBJECTDIR}/_ext/882160277/script_object_json_source.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=../../externals/libscriptobject/src/libscriptobject/dist/Release/GNU-Linux-x86/libscriptobject.a ../../externals/libjsapi/src/libjsapi/dist/Release/GNU-Linux-x86/libjsapi.a ../../externals/libjsapi/externals/installed/lib/libmozjs-31.a -lz -lpthread -ldl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce: ../../externals/libscriptobject/src/libscriptobject/dist/Release/GNU-Linux-x86/libscriptobject.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce: ../../externals/libjsapi/src/libjsapi/dist/Release/GNU-Linux-x86/libjsapi.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce: ../../externals/libjsapi/externals/installed/lib/libmozjs-31.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/793978143/gason.o: ../../externals/libscriptobject/externals/gason/src/gason.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/793978143
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/libscriptobject/src/testlibscriptobject -I../../externals/libscriptobject/src/libscriptobject -I../../externals/libscriptobject/externals/gason/src -I../../externals/libjsapi/src/libjsapi -I../../externals/libjsapi/externals/installed/include/mozjs-31 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/793978143/gason.o ../../externals/libscriptobject/externals/gason/src/gason.cpp

${OBJECTDIR}/_ext/882160277/script_array_json_source.o: ../../externals/libscriptobject/src/testlibscriptobject/script_array_json_source.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/882160277
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/libscriptobject/src/testlibscriptobject -I../../externals/libscriptobject/src/libscriptobject -I../../externals/libscriptobject/externals/gason/src -I../../externals/libjsapi/src/libjsapi -I../../externals/libjsapi/externals/installed/include/mozjs-31 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/882160277/script_array_json_source.o ../../externals/libscriptobject/src/testlibscriptobject/script_array_json_source.cpp

${OBJECTDIR}/_ext/882160277/script_object_json_source.o: ../../externals/libscriptobject/src/testlibscriptobject/script_object_json_source.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/882160277
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/libscriptobject/src/testlibscriptobject -I../../externals/libscriptobject/src/libscriptobject -I../../externals/libscriptobject/externals/gason/src -I../../externals/libjsapi/src/libjsapi -I../../externals/libjsapi/externals/installed/include/mozjs-31 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/882160277/script_object_json_source.o ../../externals/libscriptobject/src/testlibscriptobject/script_object_json_source.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../externals/libscriptobject/src/testlibscriptobject -I../../externals/libscriptobject/src/libscriptobject -I../../externals/libscriptobject/externals/gason/src -I../../externals/libjsapi/src/libjsapi -I../../externals/libjsapi/externals/installed/include/mozjs-31 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../../externals/libscriptobject/src/libscriptobject && ${MAKE}  -f Makefile CONF=Release
	cd ../../externals/libjsapi/src/libjsapi && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mapreduce

# Subprojects
.clean-subprojects:
	cd ../../externals/libscriptobject/src/libscriptobject && ${MAKE}  -f Makefile CONF=Release clean
	cd ../../externals/libjsapi/src/libjsapi && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

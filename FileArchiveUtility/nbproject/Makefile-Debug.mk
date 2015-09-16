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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/versionDB/FileRec.o \
	${OBJECTDIR}/versionDB/VersionRec.o \
	${OBJECTDIR}/versionDB/dbtest.o


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
LDLIBSOPTIONS=/lib/x86_64-linux-gnu/mongo-client-install/lib/libmongoclient.a -lboost_thread -lboost_filesystem -lboost_system -lboost_program_options -lboost_regex -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility: /lib/x86_64-linux-gnu/mongo-client-install/lib/libmongoclient.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/versionDB/FileRec.o: versionDB/FileRec.cpp 
	${MKDIR} -p ${OBJECTDIR}/versionDB
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/versionDB/FileRec.o versionDB/FileRec.cpp

${OBJECTDIR}/versionDB/VersionRec.o: versionDB/VersionRec.cpp 
	${MKDIR} -p ${OBJECTDIR}/versionDB
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/versionDB/VersionRec.o versionDB/VersionRec.cpp

${OBJECTDIR}/versionDB/dbtest.o: versionDB/dbtest.cpp 
	${MKDIR} -p ${OBJECTDIR}/versionDB
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/versionDB/dbtest.o versionDB/dbtest.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

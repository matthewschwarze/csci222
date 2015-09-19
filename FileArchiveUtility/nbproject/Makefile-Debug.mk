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
	${OBJECTDIR}/version/FileHash.o \
	${OBJECTDIR}/version/FileRec.o \
	${OBJECTDIR}/version/VersionRec.o \
	${OBJECTDIR}/version/fileArchiver.o


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

${OBJECTDIR}/version/FileHash.o: version/FileHash.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -I/usr/include/qt4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/FileHash.o version/FileHash.cpp

${OBJECTDIR}/version/FileRec.o: version/FileRec.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -I/usr/include/qt4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/FileRec.o version/FileRec.cpp

${OBJECTDIR}/version/VersionRec.o: version/VersionRec.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -I/usr/include/qt4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/VersionRec.o version/VersionRec.cpp

${OBJECTDIR}/version/fileArchiver.o: version/fileArchiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/lib/x86_64-linux-gnu/mongo-client-install/include/ -I/usr/include/qt4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/fileArchiver.o version/fileArchiver.cpp

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

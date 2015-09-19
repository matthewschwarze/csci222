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
	${OBJECTDIR}/version/FileHash.o \
	${OBJECTDIR}/version/FileRec.o \
	${OBJECTDIR}/version/VersionRec.o \
	${OBJECTDIR}/version/dbtest.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiveutility ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/version/FileHash.o: version/FileHash.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/lib/x86_64-linux-gnu/mongo-client-install/include/mongo -include /lib/x86_64-linux-gnu/mongo-client-install/include/mongo -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/FileHash.o version/FileHash.cpp

${OBJECTDIR}/version/FileRec.o: version/FileRec.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/lib/x86_64-linux-gnu/mongo-client-install/include/mongo -include /lib/x86_64-linux-gnu/mongo-client-install/include/mongo -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/FileRec.o version/FileRec.cpp

${OBJECTDIR}/version/VersionRec.o: version/VersionRec.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/lib/x86_64-linux-gnu/mongo-client-install/include/mongo -include /lib/x86_64-linux-gnu/mongo-client-install/include/mongo -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/VersionRec.o version/VersionRec.cpp

${OBJECTDIR}/version/dbtest.o: version/dbtest.cpp 
	${MKDIR} -p ${OBJECTDIR}/version
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/lib/x86_64-linux-gnu/mongo-client-install/include/mongo -include /lib/x86_64-linux-gnu/mongo-client-install/include/mongo -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/version/dbtest.o version/dbtest.cpp

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

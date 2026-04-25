#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ThermoGaurd_main_v001.c ThermoGaurd_PIR_v001.c ThermoGaurd_Joystick_v001.c LCD_base_library.c LCD_functions.c TempSen.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ThermoGaurd_main_v001.o ${OBJECTDIR}/ThermoGaurd_PIR_v001.o ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o ${OBJECTDIR}/LCD_base_library.o ${OBJECTDIR}/LCD_functions.o ${OBJECTDIR}/TempSen.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ThermoGaurd_main_v001.o.d ${OBJECTDIR}/ThermoGaurd_PIR_v001.o.d ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o.d ${OBJECTDIR}/LCD_base_library.o.d ${OBJECTDIR}/LCD_functions.o.d ${OBJECTDIR}/TempSen.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ThermoGaurd_main_v001.o ${OBJECTDIR}/ThermoGaurd_PIR_v001.o ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o ${OBJECTDIR}/LCD_base_library.o ${OBJECTDIR}/LCD_functions.o ${OBJECTDIR}/TempSen.o

# Source Files
SOURCEFILES=ThermoGaurd_main_v001.c ThermoGaurd_PIR_v001.c ThermoGaurd_Joystick_v001.c LCD_base_library.c LCD_functions.c TempSen.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ThermoGaurd_main_v001.o: ThermoGaurd_main_v001.c  .generated_files/flags/default/7bf306d6dd6317b14b173d42596cfa980c0b81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ThermoGaurd_main_v001.o.d 
	@${RM} ${OBJECTDIR}/ThermoGaurd_main_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ThermoGaurd_main_v001.c  -o ${OBJECTDIR}/ThermoGaurd_main_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ThermoGaurd_main_v001.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ThermoGaurd_PIR_v001.o: ThermoGaurd_PIR_v001.c  .generated_files/flags/default/418f58bb45309b77a89b27d20f05998b77d1b217 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ThermoGaurd_PIR_v001.o.d 
	@${RM} ${OBJECTDIR}/ThermoGaurd_PIR_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ThermoGaurd_PIR_v001.c  -o ${OBJECTDIR}/ThermoGaurd_PIR_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ThermoGaurd_PIR_v001.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ThermoGaurd_Joystick_v001.o: ThermoGaurd_Joystick_v001.c  .generated_files/flags/default/94f458763cd60fc6ca1b592c33e6b7298a6a3637 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o.d 
	@${RM} ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ThermoGaurd_Joystick_v001.c  -o ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ThermoGaurd_Joystick_v001.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LCD_base_library.o: LCD_base_library.c  .generated_files/flags/default/d58599ee42d349d11e896dccab780b29a935dab5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCD_base_library.o.d 
	@${RM} ${OBJECTDIR}/LCD_base_library.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LCD_base_library.c  -o ${OBJECTDIR}/LCD_base_library.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LCD_base_library.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LCD_functions.o: LCD_functions.c  .generated_files/flags/default/2d4431d36bf71e972161715789fd512dad5b1811 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCD_functions.o.d 
	@${RM} ${OBJECTDIR}/LCD_functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LCD_functions.c  -o ${OBJECTDIR}/LCD_functions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LCD_functions.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TempSen.o: TempSen.c  .generated_files/flags/default/a3643c585b545d9e297c2a95a8a62e7fd69f0828 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TempSen.o.d 
	@${RM} ${OBJECTDIR}/TempSen.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TempSen.c  -o ${OBJECTDIR}/TempSen.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TempSen.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/ThermoGaurd_main_v001.o: ThermoGaurd_main_v001.c  .generated_files/flags/default/2b3af2196c943366680ca14944a89e0d48ea323b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ThermoGaurd_main_v001.o.d 
	@${RM} ${OBJECTDIR}/ThermoGaurd_main_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ThermoGaurd_main_v001.c  -o ${OBJECTDIR}/ThermoGaurd_main_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ThermoGaurd_main_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ThermoGaurd_PIR_v001.o: ThermoGaurd_PIR_v001.c  .generated_files/flags/default/6bdd516d24d7fcb061f204c175a99e2391025b62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ThermoGaurd_PIR_v001.o.d 
	@${RM} ${OBJECTDIR}/ThermoGaurd_PIR_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ThermoGaurd_PIR_v001.c  -o ${OBJECTDIR}/ThermoGaurd_PIR_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ThermoGaurd_PIR_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ThermoGaurd_Joystick_v001.o: ThermoGaurd_Joystick_v001.c  .generated_files/flags/default/887cf60fbafa54f7648ecf869e6aaf5dc94a90f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o.d 
	@${RM} ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ThermoGaurd_Joystick_v001.c  -o ${OBJECTDIR}/ThermoGaurd_Joystick_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ThermoGaurd_Joystick_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LCD_base_library.o: LCD_base_library.c  .generated_files/flags/default/a5cfcca298f782bab6a3ab4d066f8245cdf64065 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCD_base_library.o.d 
	@${RM} ${OBJECTDIR}/LCD_base_library.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LCD_base_library.c  -o ${OBJECTDIR}/LCD_base_library.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LCD_base_library.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/LCD_functions.o: LCD_functions.c  .generated_files/flags/default/8f6b446090a6cfdd10501eeb8d278f07e9d87632 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCD_functions.o.d 
	@${RM} ${OBJECTDIR}/LCD_functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LCD_functions.c  -o ${OBJECTDIR}/LCD_functions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/LCD_functions.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TempSen.o: TempSen.c  .generated_files/flags/default/ee5f2cf45e83a9cdbd01cfcbcf6cc35df9c83046 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TempSen.o.d 
	@${RM} ${OBJECTDIR}/TempSen.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TempSen.c  -o ${OBJECTDIR}/TempSen.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TempSen.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/ThermoGuard_v001.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

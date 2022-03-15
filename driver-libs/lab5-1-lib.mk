##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=lab5-1-lib
ConfigurationName      :=Debug
WorkspacePath          :=/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5
ProjectPath            :=/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/lab5-1-lib
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alen Mukaca
Date                   :=03/21/21
CodeLitePath           :=/home/shinzenatt/.codelite
LinkerName             :=/usr/bin/arm-none-eabi-g++
SharedObjectLinkerName :=/usr/bin/arm-none-eabi-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$libMD407.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="lab5-1-lib.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/arm-none-eabi-ar rcu
CXX      := /usr/bin/arm-none-eabi-g++
CC       := /usr/bin/arm-none-eabi-gcc
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/arm-none-eabi-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) $(IntermediateDirectory)/general.c$(ObjectSuffix) $(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) $(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@$(MakeDirCommand) "/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/.build-debug"
	@echo rebuilt > "/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/.build-debug/lab5-1-lib"

PostBuild:
	@echo Executing Post Build commands ...
	cp Debug/ibMD407.a /usr/share/codelite/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp/libMD407.a
	cp ./libMD407.h /usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/libMD407.h
	@echo Done

MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(ConfigurationName):
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix): usart_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/usart_driver.c$(DependSuffix) -MM usart_driver.c
	$(CC) $(SourceSwitch) "/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/lab5-1-lib/usart_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usart_driver.c$(PreprocessSuffix): usart_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usart_driver.c$(PreprocessSuffix) usart_driver.c

$(IntermediateDirectory)/general.c$(ObjectSuffix): general.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/general.c$(ObjectSuffix) -MF$(IntermediateDirectory)/general.c$(DependSuffix) -MM general.c
	$(CC) $(SourceSwitch) "/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/lab5-1-lib/general.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/general.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/general.c$(PreprocessSuffix): general.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/general.c$(PreprocessSuffix) general.c

$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix): keypad_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/keypad_driver.c$(DependSuffix) -MM keypad_driver.c
	$(CC) $(SourceSwitch) "/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/lab5-1-lib/keypad_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keypad_driver.c$(PreprocessSuffix): keypad_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keypad_driver.c$(PreprocessSuffix) keypad_driver.c

$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix): asciidisplay_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/asciidisplay_driver.c$(DependSuffix) -MM asciidisplay_driver.c
	$(CC) $(SourceSwitch) "/home/shinzenatt/OneDrive/Maskinorienterad-programmering/lab5/lab5-1-lib/asciidisplay_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/asciidisplay_driver.c$(PreprocessSuffix): asciidisplay_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/asciidisplay_driver.c$(PreprocessSuffix) asciidisplay_driver.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/



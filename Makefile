#------------------------------------------------------------------------------------------------
#
# Makefile to build locis
# Created 09/17/217
# NOTES:
#	works only on linux for now
#
#------------------------------------------------------------------------------------------------

# FILE EXTENSIONS
EXT_CPP := cpp
EXT_OBJ := o
EXT_LIB := a
EXT_HEADER := h

# DEFAULT CONFIGURATION
ifeq ($(config),)
	config=debug
endif

# REQUIRED FOLDERS
REQUIRED_DIRS = Output/$(config)\
			    Temp/LOCISFrameWork/$(config)

_makeRequiredFolders := $(shell for d in $(REQUIRED_DIRS); \
						do								   \
	  					[[ -d $$d ]] || mkdir -p $$d;	   	   \
						done)

# PROGRAM
NAME_PROGRAM = locis 

# INCLUDE PATHS
PATH_ROOT = $(CURDIR)
PATH_LOCIS_INCLUDE :=	 LOCISFrameWork/LOCISCore/include
PATH_KINSOL_INCLUDE :=	 Solvers/KINSOL/srcdir/include
PATH_SUNDIALS_INCLUDE := Solvers/KINSOL/builddir/include
PATH_IDA_INCLUDE :=		 Solvers/IDA/srcdir/include
PATH_PYTHON_INCLUDE :=	 /usr/include/python2.7
PATH_NUMPY_INCLUDE :=	 /home/$(USER)/.local/lib/python2.7/site-packages/numpy/core/include/numpy

PATH_ALL_INCLUDE =  -I$(PATH_LOCIS_INCLUDE)\
					-I$(PATH_SUNDIALS_INCLUDE)\
					-I$(PATH_KINSOL_INCLUDE)\
					-I$(PATH_IDA_INCLUDE)\
					-I$(PATH_PYTHON_INCLUDE)\
				    -I$(PATH_NUMPY_INCLUDE)

# OUTPUT PATHS
PATH_LOCIS_OUT = Output

# TEMP PATHS
PATH_LOCIS_TEMP = Temp/LOCISFrameWork

# SOURCE PATHS
PATH_LOCIS_SRC = LOCISFrameWork/LOCISCore/src

# LIB PATHS
PATH_KINSOL_LIB := 		Solvers/KINSOL/builddir/src/kinsol
PATH_IDA_LIB :=  		Solvers/IDA/builddir/src/ida
PATH_NVEC_SERIAL_LIB := Solvers/IDA/builddir/src/nvec_ser
PATH_PYTHON_LIB := 		/usr/lib/python2.7/config-x86_64-linux-gnu

PATH_ALL_LIB = 		-L$(PATH_KINSOL_LIB)\
					-L$(PATH_IDA_LIB)\
					-L$(PATH_NVEC_SERIAL_LIB)\
					-L$(PATH_PYTHON_LIB)
# LIBS
LIB_KINSOL := 	-lsundials_kinsol
LIB_IDA := 		-lsundials_ida
LIB_NVEC :=     -lsundials_nvecserial
LIB_PYTHON := 	-lpython2.7

LIB_ALL := 		$(LIB_KINSOL)\
				$(LIB_IDA)\
				$(LIB_NVEC)\
				$(LIB_PYTHON)

# SOURCE/INCLUDE/OBJ NAMES
LOCIS_INC = $(wildcard $(PATH_LOCIS_INCLUDE)/*.$(EXT_HEADER))
LOCIS_SRC = $(notdir $(wildcard $(PATH_LOCIS_SRC)/*.$(EXT_CPP)))
LOCIS_OBJ = $(addprefix $(PATH_LOCIS_TEMP)/$(config)/,$(patsubst %.$(EXT_CPP),%.$(EXT_OBJ),$(LOCIS_SRC)))

# COMPILER AND FLAGS
CXX := g++
ifeq ($(config),debug)
	CXXFLAGS = -Wall -c -std=c++11 -g -fpermissive
else
	CXXFLAGS = -Wall -c -std=c++11 -O3 -fpermissive
endif

# FUNCTIONS
define cleanOutputs	
	@rm -f $(PATH_LOCIS_TEMP)/$1/*.$(EXT_OBJ);		
	@rm -f $(PATH_LOCIS_OUT)/$1/$(NAME_PROGRAM);	
endef

# TARGETS
$(PATH_LOCIS_OUT)/$(config)/$(NAME_PROGRAM): $(LOCIS_OBJ)
	@$(CXX) $^ $(PATH_ALL_LIB) $(LIB_ALL) -o $@ 

$(PATH_LOCIS_TEMP)/$(config)/%.$(EXT_OBJ) : $(PATH_LOCIS_SRC)/%.$(EXT_CPP) $(LOCIS_INC)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(PATH_ALL_INCLUDE) $< -o $@ 

.PHONY : cleand
cleand :
	@$(call cleanOutputs,debug)
	
.PHONY : cleanr
cleanr :
	@$(call cleanOutputs,release)

.PHONY : clean
clean : cleand cleanr

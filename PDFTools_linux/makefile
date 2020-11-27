SRC_DIR=./src/
INCLUDE=./include/
#MUPDF_LIBDIR=/usr/local/lib/

AR			= ar rcs
CC			= g++
RM			= rm -f
cc 			= gcc
WANG			= -Wno-deprecated

#编译标准版
INCLUDES		= -I$(INCLUDE)
CCFLAGS			= $(INCLUDES) -D_LINUX -Wno-deprecated
#LIBS 			= -lm

OBJMPATH=./obj/
BUILDPATH=./bin/
TRAGET=./bin/libPDFTools.a

OBJS= $(OBJMPATH)PDFConvert.o

###  开始建造
all:	prepare $(TRAGET)

prepare:
		@echo  ---------------------------------------------------------------
		@echo   Preparing for compiling ......
		@mkdir -p $(BUILDPATH)
		@mkdir -p $(OBJMPATH)

###  编译源程序
$(OBJMPATH)%.o:	$(SRC_DIR)%.cpp
	$(CC) -fPIC -o $@ $(CCFLAGS) -g -c $<

###  连接目标文件
$(TRAGET):	$(OBJS)
	@echo "---------------ar rcs obj-----------------------"
	$(AR) $(TRAGET) $(OBJS)
	@echo "---------------ar success------------------"
clean:
	@rm -rf $(OBJS)
	@rm -rf $(TRAGET)


#created ls @kinsec.cov
#time: 2020-11-10

DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_ETC = ./etc
DIR_INST = /usr/local/flash-policy-serv

SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = flash-policy-serv

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -Wall -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ)  -o $@
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	find ${DIR_OBJ} -name "*.o" -exec rm -rf {} \;
	find ${DIR_BIN} -name ${TARGET} -exec rm -rf {} \;

install:
	if [ -d $(DIR_INST) ]; \
    then \
    rm -rf $(DIR_INST) ;\
	fi
	mkdir $(DIR_INST) ;\
	cp -r $(DIR_ETC) $(DIR_INST) ;\
    cp -r $(DIR_BIN) $(DIR_INST) ;\
    chmod a+x $(DIR_INST)/$(BIN_TARGET) ;\



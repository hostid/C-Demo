CC = gcc
CFLAGS = -Wall 
LIB = 
#去除编译链接的文件
CLIENT_IGNORE_SOURCE := server.c 
SERVER_IGNORE_SOURCE := client.c 

#分别获取需要链接的文件
CLIENT_LOCAL_SOURCE = $(filter-out $(CLIENT_IGNORE_SOURCE),$(wildcard *.c))
SERVER_LOCAL_SOURCE = $(filter-out $(SERVER_IGNORE_SOURCE),$(wildcard *.c))

CLIENT_LOCAL_OBJ = $(patsubst %.c,%.o,$(notdir ${CLIENT_LOCAL_SOURCE}))
SERVER_LOCAL_OBJ = $(patsubst %.c,%.o,$(notdir ${SERVER_LOCAL_SOURCE}))


all:
	@echo "Wrong build option, please run 'make client' or "make server" to build.";
	@exit 13;
   
client:${CLIENT_LOCAL_OBJ}
	$(CC) $(CLIENT_LOCAL_OBJ) -o  $@ $(LIB) 

server:${SERVER_LOCAL_OBJ}
	$(CC) $(SERVER_LOCAL_OBJ) -o  $@ $(LIB) 

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm *.o client server
RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

CLIENT_NAME = client

SERVER_NAME = server

CLIENT_SRC = client.c

SERVER_SRC =  server.c

CLIENT_OBJ = client.o

SERVER_OBJ =  server.o

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o client
	
$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o server

clean: 
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re: clean fclean all
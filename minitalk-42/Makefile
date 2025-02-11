SOURCES = server.c client.c ft_atoi.c
OBJECTS = $(SOURCES:.c=.o)
PRINTF  = ./ft_printf/libftprintf.a 
CC = cc
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

bonus: $(SERVER) $(CLIENT)

$(PRINTF): ./ft_printf/ft_printf.h
	make -C ft_printf

$(SERVER): server.o  $(PRINTF) minitalk.h
	$(CC) $(CFLAGS) server.o $(PRINTF) -o $(SERVER)

$(CLIENT): client.o $(PRINTF) minitalk.h
	$(CC) $(CFLAGS) client.o $(PRINTF) -o $(CLIENT)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJECTS)
	make -C ft_printf clean
	
fclean: clean
	rm -f $(SERVER) $(CLIENT) $(PRINTF)

re: fclean all

.PHONY: clean fclean re bonus $(PRINTF)

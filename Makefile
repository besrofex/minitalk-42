NAMEC = client
NAMES = server
PRINTF = libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
PRINTF_DIR = ft_printf/

SRCC = client.c
SRCS = server.c

OBJC = $(SRCC:.c=.o)
OBJS = $(SRCS:.c=.o)

all: $(PRINTF) $(NAMEC) $(NAMES)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(NAMEC): $(OBJC) minitalk.h
	$(CC) $(CFLAGS) $(OBJC) $(PRINTF_DIR)$(PRINTF) -o $(NAMEC)

$(NAMES): $(OBJS) minitalk.h
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF_DIR)$(PRINTF) -o $(NAMES)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(PRINTF_DIR)
	$(RM) $(OBJC) $(OBJS)

fclean: clean
	@make fclean -C $(PRINTF_DIR)
	$(RM) $(NAMEC) $(NAMES)

re: fclean all
.PHONY : clean
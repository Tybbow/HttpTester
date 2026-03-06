NAME = httptester
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
HEADERS = -I ./include/

SRC_PATH = ./srcs

SRCS =  httptester.c\
        functions.c\
		http.c\
		options.c\
		usage.c\
		handle.c

OBJS = $(patsubst %.c,$(SRC_PATH)/%.o,$(SRCS))

$(NAME): $(OBJS)
	@($(CC) $(CFLAGS) $(HEADERS) -o $@ $^)
	@echo "--------------------------------------------------"
	@echo "          Compilation of $@ has finish            "
	@echo "             httptester : v 1.1 - By Tybbow            "
	@echo "--------------------------------------------------"

all : $(NAME)

%.o: %.c
	@($(CC) -c $(CFLAGS) $(HEADERS) -o $@ $^)
	@echo " OK  $@"

clean:
	@(rm -rf $(OBJS))
	@echo "--------------------------------------------------"
	@echo " OK          $(NAME): Objects deleted"
	@echo "--------------------------------------------------"

fclean: clean
	@(rm -rf $(NAME))
	@echo "--------------------------------------------------"
	@echo " OK           $(NAME): All deleted"
	@echo "--------------------------------------------------"

re: fclean all

.PHONY: fclean clean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiskow <tiskow@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/16 09:41:27 by tiskow            #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by tiskow           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= httptester
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
HEADERS	= -I ./includes/
LIBS	= -lssl -lcrypto

SRC_PATH = srcs

SRCS	= httptester.c \
		  options.c \
		  http.c \
		  https.c \
		  functions.c \
		  handle.c \
		  usage.c

OBJS = $(patsubst %.c,$(SRC_PATH)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $^ $(LIBS)
	@echo "--------------------------------------------------"
	@echo "          Compilation of $@ has finish            "
	@echo "               $@ : v 1.1 - By Tybbow            "
	@echo "--------------------------------------------------"

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $<
	@echo " OK  $@"

clean:
	@rm -rf $(OBJS)
	@echo "--------------------------------------------------"
	@echo " OK          $(NAME): Objects deleted"
	@echo "--------------------------------------------------"

fclean: clean
	@rm -rf $(NAME)
	@echo "--------------------------------------------------"
	@echo " OK           $(NAME): All deleted"
	@echo "--------------------------------------------------"

re: fclean all

.PHONY: all clean fclean re
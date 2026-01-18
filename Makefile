# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flhensel <flhensel@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/18 13:51:45 by florianh          #+#    #+#              #
#    Updated: 2026/01/18 14:00:45 by flhensel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

$(NAME_SERVER): $(OBJ_SERVER) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(FT_PRINTF) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(FT_PRINTF) -o $(NAME_CLIENT)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -I$(FT_PRINTF_DIR) -c $< -o $@

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
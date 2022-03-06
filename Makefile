# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 15:37:58 by abarchil          #+#    #+#              #
#    Updated: 2022/03/05 21:12:01 by abarchil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_FILE = main.c raycast.c parsing/parsing.c parsing/get_next_line.c

NAME = CUB3D

HEADER = cub3D.h

FLAG = -lmlx -framework OpenGL -framework AppKit

CC = gcc

OBJ = $(SRC_FILE:.c=.o)

BLUE=\033[0;34m

GREEN=\033[0;32m

ORANG=\033[0;33m

PURPLE=\033[0;35m

YELLOW = \033[0;33m

RESET = \033[0m

all : $(NAME) $(HEADER)

%.o:%.c
	@echo "$(ORANG)           		<----------- COMPILING $< -----------> $(RESET)"
	@$(CC) -c $< -o $@

$(NAME) : $(OBJ)
	@echo "$(BLUE) \
		$(BLUE)█████╗  ██╗   ██╗ ██████╗  $(PURPLE)██████╗  ██████╗ $(RESET)\n\
		$(BLUE)██╔══██╗ ██║   ██║ ██╔══██╗ $(PURPLE)╚════██╗ ██╔══██╗$(RESET)\n\
		$(BLUE)██║  ╚═╝ ██║   ██║ ██████╦╝  $(PURPLE)█████╔╝ ██║  ██║$(RESET)\n\
		$(BLUE)██║  ██╗ ██║   ██║ ██╔══██╗  $(PURPLE)╚═══██╗ ██║  ██║$(RESET)\n\
		$(BLUE)╚█████╔╝ ╚██████╔╝ ██████╦╝ $(PURPLE)██████╔╝ ██████╔╝$(RESET)\n\
		$(BLUE)╚════╝   ╚═════╝  ╚═════╝  $(PURPLE)╚═════╝  ╚═════╝ $(RESET)"
	@$(CC) $(FLAG) $(OBJ) -o $(NAME)
clean :
	@echo "$(YELLOW)           		<----------- REMOVING OBJECT FILES ----------->$(RESET)"
	@rm -rf $(OBJ)
fclean : clean
	@echo "$(YELLOW)           		<----------- REMOVING MINISHELL ----------->$(RESET)"
	@rm -rf $(NAME)
re : fclean all
.PHONY : clean fclean all re
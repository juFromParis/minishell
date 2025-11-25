# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/15 12:20:00 by jderachi          #+#    #+#              #
#    Updated: 2025/11/25 11:53:34 by jderachi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Compiler and flags
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g

# Colors
GREEN  = \033[32m
RED    = \033[31m
YELLOW = \033[33m
RESET  = \033[0m

RM = rm -f

# Detect OS
UNAME_S := $(shell uname -s)

# Readline (auto-select per OS)
ifeq ($(UNAME_S),Darwin)
	READLINE_INC = -I$(shell brew --prefix readline)/include
	READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline
else ifeq ($(UNAME_S),Linux)
	READLINE_INC = -I/usr/include
	READLINE_LIB = -lreadline
endif

# Includes
INCLUDES = -I./inc $(READLINE_INC)
# Sources
SRCS = \
	src/main.c \
	src/parsing/utils.c \
	src/parsing/lexer.c \
	src/parsing/token.c \
	src/parsing/parsing.c \
	src/parsing/node.c \
	src/for_tests_to_delete/tests.c \
	src/exit.c

# Objects
OBJS = $(SRCS:.c=.o)

# Rules
all: $(MLX_LIB) $(NAME)

# Compile minishell
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE_LIB) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilé avec succès !$(RESET)"
	@echo "$(GREEN)✓ $(NAME) start..$(RESET)"

# Compile each .c file into a .o file
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleans
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)✓ Fichiers objets supprimés !$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)✓ $(NAME) nettoyés !$(RESET)"

re: fclean all

.PHONY: all clean fclean re asan

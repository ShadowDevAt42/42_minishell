# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 02:35:00 by minishell         #+#    #+#              #
#    Updated: 2025/03/29 19:13:57 by fdi-tria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I./includes -I./libft -I/usr/include
LDFLAGS = -lreadline -L./libft -lft

# Sources
SRCS_DIR = srcs/
PARSER_DIR = $(SRCS_DIR)parser/
EXEC_DIR = $(SRCS_DIR)executor/
BUILTINS_DIR = $(SRCS_DIR)builtins/
SIGNALS_DIR = $(SRCS_DIR)signals/
UTILS_DIR = $(SRCS_DIR)utils/

# Fichiers sources
SRCS =	$(SRCS_DIR)main.c \
		$(PARSER_DIR)tokenizer.c \
		$(PARSER_DIR)lexer.c \
		$(PARSER_DIR)parser.c \
		$(PARSER_DIR)quotes.c \
		$(PARSER_DIR)expand.c \
		$(EXEC_DIR)executor.c \
		$(EXEC_DIR)path.c \
		$(EXEC_DIR)redirections.c \
		$(EXEC_DIR)pipe.c \
		$(BUILTINS_DIR)builtins.c \
		$(BUILTINS_DIR)echo.c \
		$(BUILTINS_DIR)cd.c \
		$(BUILTINS_DIR)pwd.c \
		$(BUILTINS_DIR)export.c \
		$(BUILTINS_DIR)unset.c \
		$(BUILTINS_DIR)env.c \
		$(BUILTINS_DIR)exit.c \
		$(SIGNALS_DIR)signals.c \
		$(UTILS_DIR)errors.c \
		$(UTILS_DIR)env_utils.c

# Objets
OBJS_DIR = objs/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

# Couleurs
GREEN = \033[0;32m
RESET = \033[0m

all: libft $(NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation terminée : $(NAME)$(RESET)"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(MAKE) -C libft clean
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Objets supprimés$(RESET)"

fclean: clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)
	@echo "$(GREEN)Exécutable supprimé$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft 
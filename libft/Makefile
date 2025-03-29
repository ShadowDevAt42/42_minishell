# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 05:05:00 by minishell         #+#    #+#              #
#    Updated: 2025/03/29 02:50:11 by fdi-tria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I.

# Fichiers sources
SRCS = ft_strlen.c ft_strcmp.c ft_strncmp.c ft_strchr.c \
	   ft_strdup.c ft_strjoin.c ft_split.c \
	   ft_malloc.c ft_free.c ft_calloc.c ft_bzero.c \
	   ft_atoi.c

# Objets
OBJS = $(SRCS:.c=.o)

# Couleurs
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "$(GREEN)Compilation terminée : $(NAME)$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)Objets supprimés$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Bibliothèque supprimée$(RESET)"

re: fclean all

.PHONY: all clean fclean re 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 05:00:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:50:23 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>

/* Fonctions de gestion mémoire */
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

/* Fonctions de manipulation de chaînes */
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

/* Fonctions de conversion */
int		ft_atoi(const char *str);

#endif 
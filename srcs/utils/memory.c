/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:00:00 by fdi-tria         #+#    #+#             */
/*   Updated: 2025/03/29 20:00:00 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Alloue de la mémoire et vérifie si l'allocation a réussi
 */
void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * Libère la mémoire et met le pointeur à NULL
 */
void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/**
 * Duplique une chaîne de caractères
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)ft_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * Libère un tableau de chaînes de caractères
 */
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

/**
 * Duplique un tableau de chaînes de caractères
 */
char	**copy_env(char **env)
{
	char	**new_env;
	int		i;
	int		size;

	if (!env)
		return (NULL);
	size = 0;
	while (env[size])
		size++;
	new_env = (char **)ft_malloc(sizeof(char *) * (size + 1));
	new_env[size] = NULL;
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 06:10:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 19:09:49 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Duplique l'environnement
 */
char	**copy_env(char **env)
{
	char	**new_env;
	int		i;
	int		count;

	count = 0;
	while (env[count])
		count++;
	new_env = (char **)ft_malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/**
 * Récupère la valeur d'une variable d'environnement
 */
char	*get_env_value(char **env, char *key)
{
	int		i;
	int		key_len;
	char	*equal_pos;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos && (equal_pos - env[i]) == key_len
			&& !ft_strncmp(env[i], key, key_len))
			return (equal_pos + 1);
		i++;
	}
	return (NULL);
}

/**
 * Compte le nombre de variables d'environnement
 */
static int	env_count(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

/**
 * Met à jour ou ajoute une variable d'environnement
 */
int	set_env_value(char ***env, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_var;
	char	**new_env;

	if (!env || !*env || !key || !value)
		return (ERROR);
	key_len = ft_strlen(key);
	new_var = ft_strjoin(key, "=");
	new_var = ft_strjoin(new_var, value);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, key_len) && (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return (SUCCESS);
		}
		i++;
	}
	new_env = (char **)ft_malloc(sizeof(char *) * (env_count(*env) + 2));
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (SUCCESS);
}

/**
 * Supprime une variable d'environnement
 */
int	remove_env_var(char ***env, char *key)
{
	int		i;
	int		j;
	int		key_len;
	char	**new_env;

	if (!env || !*env || !key)
		return (ERROR);
	key_len = ft_strlen(key);
	new_env = (char **)ft_malloc(sizeof(char *) * env_count(*env));
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) != 0
			|| (*env)[i][key_len] != '=')
		{
			new_env[j] = (*env)[i];
			j++;
		}
		else
			free((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (SUCCESS);
}

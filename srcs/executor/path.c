/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:20:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 19:09:12 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Divise une chaîne en utilisant un délimiteur
 */
char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**result;
	int		count;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	result = (char **)ft_malloc(sizeof(char *) * (count + 1));
	result[count] = NULL;
	i = 0;
	k = 0;
	while (s[i] && k < count)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		result[k] = (char *)ft_malloc(sizeof(char) * (i - j + 1));
		result[k][i - j] = '\0';
		while (j < i)
		{
			result[k][j - (i - (i - j))] = s[j];
			j++;
		}
		k++;
	}
	return (result);
}

/**
 * Vérifie si une commande est un chemin absolu ou relatif
 */
static int	is_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (1);
	return (0);
}

/**
 * Recherche un exécutable dans le PATH
 */
static char	*search_in_path(char *cmd, char **paths)
{
	char	*path;
	char	*temp;
	int		i;

	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

/**
 * Recherche un exécutable
 */
char	*find_executable(char *cmd, char **env)
{
	char	*path_var;
	char	**paths;
	char	*exec_path;

	if (!cmd || !env)
		return (NULL);
	if (is_path(cmd))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		print_error(cmd, strerror(errno));
		return (NULL);
	}
	path_var = get_env_value(env, "PATH");
	if (!path_var)
	{
		print_error(cmd, "aucun fichier ou dossier de ce type");
		return (NULL);
	}
	paths = ft_split(path_var, ':');
	exec_path = search_in_path(cmd, paths);
	if (!exec_path)
		print_error(cmd, "commande introuvable");
	paths = NULL;
	return (exec_path);
}

/**
 * Exécute une commande externe
 */
int	execute_command(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0] || !shell)
		return (ERROR);
	path = find_executable(cmd->args[0], shell->env);
	if (!path)
		return (127);
	execve(path, cmd->args, shell->env);
	print_error(cmd->args[0], strerror(errno));
	free(path);
	return (126);
}

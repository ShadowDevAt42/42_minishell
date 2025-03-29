/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:20:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:33:58 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Change le répertoire courant
 */
static int	change_directory(t_shell *shell, char *path)
{
	char	*old_pwd;
	char	cwd[1024];

	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
	{
		print_error("cd", "impossible de récupérer le répertoire courant");
		return (ERROR);
	}
	if (chdir(path) == -1)
	{
		print_error("cd", strerror(errno));
		return (ERROR);
	}
	set_env_value(&shell->env, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(&shell->env, "PWD", cwd);
	return (SUCCESS);
}

/**
 * Obtient le chemin du répertoire personnel
 */
static char	*get_home_dir(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell->env, "HOME");
	if (!home)
		print_error("cd", "HOME n'est pas défini");
	return (home);
}

/**
 * Commande interne cd
 */
int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->args)
		return (ERROR);
	if (!cmd->args[1])
	{
		path = get_home_dir(shell);
		if (!path)
			return (ERROR);
	}
	else if (!ft_strcmp(cmd->args[1], "~"))
	{
		path = get_home_dir(shell);
		if (!path)
			return (ERROR);
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		path = get_env_value(shell->env, "OLDPWD");
		if (!path)
		{
			print_error("cd", "OLDPWD n'est pas défini");
			return (ERROR);
		}
		printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	return (change_directory(shell, path));
} 
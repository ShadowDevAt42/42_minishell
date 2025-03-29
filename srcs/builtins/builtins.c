/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:10:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:40:55 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si une commande est une commande interne
 */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/**
 * Exécute une commande interne
 */
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (ERROR);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, shell));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd, shell));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(shell));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd, shell));
	return (ERROR);
} 
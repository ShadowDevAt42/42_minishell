/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:45:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:48:37 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si une chaîne est un nombre
 */
static int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Commande interne exit
 */
int	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	status;

	printf("exit\n");
	if (!cmd || !cmd->args)
		return (ERROR);
	status = shell->exit_status;
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			print_error("exit", "argument numérique requis");
			shell->exit_status = 2;
		}
		else if (cmd->args[2])
		{
			print_error("exit", "trop d'arguments");
			return (ERROR);
		}
		else
			status = ft_atoi(cmd->args[1]) % 256;
	}
	shell->running = 0;
	shell->exit_status = status;
	return (SUCCESS);
} 
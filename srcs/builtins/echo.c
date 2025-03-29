/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:15:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 19:09:00 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si l'option -n est présente
 */
static int	check_option_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Commande interne echo
 */
int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_option;

	if (!cmd || !cmd->args)
		return (ERROR);
	n_option = 0;
	i = 1;
	while (cmd->args[i] && check_option_n(cmd->args[i]))
	{
		n_option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
	return (SUCCESS);
}

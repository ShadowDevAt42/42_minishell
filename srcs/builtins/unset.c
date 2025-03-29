/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:35:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:34:39 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si le nom de la variable est valide
 */
static int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0] || !(name[0] == '_' 
			|| (name[0] >= 'a' && name[0] <= 'z')
			|| (name[0] >= 'A' && name[0] <= 'Z')))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(name[i] == '_' || (name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Commande interne unset
 */
int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	status;

	if (!cmd || !cmd->args || !shell || !shell->env)
		return (ERROR);
	status = SUCCESS;
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_name(cmd->args[i]))
			remove_env_var(&shell->env, cmd->args[i]);
		else
		{
			print_error("unset", "identifiant non valable");
			status = ERROR;
		}
		i++;
	}
	return (status);
} 
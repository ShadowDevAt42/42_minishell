/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:30:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:38:01 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Configure un pipe entre deux commandes
 */
int	setup_pipes(t_cmd *cmd, t_cmd *next)
{
	int	pipefd[2];

	if (!cmd || !next)
		return (ERROR);
	if (pipe(pipefd) == -1)
	{
		print_error("pipe", strerror(errno));
		return (ERROR);
	}
	cmd->pipe_out = pipefd[1];
	next->pipe_in = pipefd[0];
	return (SUCCESS);
} 
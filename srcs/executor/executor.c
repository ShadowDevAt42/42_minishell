/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:15:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:47:53 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Attend la fin de tous les processus enfants
 */
static int	wait_for_children(void)
{
	int	status;
	int	last_status;

	status = 0;
	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
	return (last_status);
}

/**
 * Exécute un pipeline de commandes
 */
static int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*next;
	pid_t	pid;

	current = cmds;
	while (current)
	{
		next = current->next;
		if (next)
			setup_pipes(current, next);
		if (is_builtin(current->args[0]) && !current->next && !current->pipe_in)
		{
			handle_redirections(current);
			execute_builtin(current, shell);
			if (current->pipe_out != -1)
				close(current->pipe_out);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				handle_redirections(current);
				if (is_builtin(current->args[0]))
					exit(execute_builtin(current, shell));
				else
					exit(execute_command(current, shell));
			}
			shell->last_pid = pid;
			if (current->pipe_in != -1)
				close(current->pipe_in);
			if (current->pipe_out != -1)
				close(current->pipe_out);
		}
		current = current->next;
	}
	return (wait_for_children());
}

/**
 * Exécuteur principal
 */
int	executor(t_shell *shell)
{
	t_cmd	*cmds;
	int		status;

	if (!shell || !shell->cmds)
		return (ERROR);
	cmds = shell->cmds;
	if (!cmds->next && !cmds->pipe_in && !cmds->pipe_out
		&& is_builtin(cmds->args[0]))
	{
		handle_redirections(cmds);
		status = execute_builtin(cmds, shell);
	}
	else
		status = execute_pipeline(cmds, shell);
	return (status);
} 
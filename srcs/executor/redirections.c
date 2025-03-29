/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:25:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 03:24:11 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Gère les redirections d'entrée
 */
static int	handle_input_redirect(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->file)
		return (ERROR);
	if (redir->type == T_REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			print_error(redir->file, strerror(errno));
			return (ERROR);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == T_HEREDOC)
	{
		print_error("heredoc", "non implémenté");
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * Gère les redirections de sortie
 */
static int	handle_output_redirect(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->file)
		return (ERROR);
	if (redir->type == T_REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error(redir->file, strerror(errno));
			return (ERROR);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == T_REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(redir->file, strerror(errno));
			return (ERROR);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (SUCCESS);
}

/**
 * Configure les redirections pour une commande
 */
int	handle_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd)
		return (ERROR);
	if (cmd->pipe_in != -1)
	{
		dup2(cmd->pipe_in, STDIN_FILENO);
		close(cmd->pipe_in);
		cmd->pipe_in = -1;
	}
	if (cmd->pipe_out != -1)
	{
		dup2(cmd->pipe_out, STDOUT_FILENO);
		close(cmd->pipe_out);
		cmd->pipe_out = -1;
	}
	redir = cmd->redir_in;
	while (redir)
	{
		if (handle_input_redirect(redir) != SUCCESS)
			return (ERROR);
		redir = redir->next;
	}
	redir = cmd->redir_out;
	while (redir)
	{
		if (handle_output_redirect(redir) != SUCCESS)
			return (ERROR);
		redir = redir->next;
	}
	return (SUCCESS);
}

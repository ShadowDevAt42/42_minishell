/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:10:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/31 23:53:57 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Crée une nouvelle redirection
 */
static t_redir	*new_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = (t_redir *)ft_malloc(sizeof(t_redir));
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

/**
 * Ajoute une redirection à la fin de la liste
 */
static void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!redirs)
		return ;
	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/**
 * Crée une nouvelle commande
 */
static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->pipe_in = -1;
	cmd->pipe_out = -1;
	cmd->next = NULL;
	return (cmd);
}

/**
 * Ajoute une commande à la fin de la liste
 */
static void	add_cmd(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!cmds)
		return ;
	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	current = *cmds;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

/**
 * Compte le nombre d'arguments de la commande
 */
static int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_WORD)
		{
			count++;
			if (current->next && (current->next->type == T_REDIR_IN 
				|| current->next->type == T_REDIR_OUT
				|| current->next->type == T_REDIR_APPEND 
				|| current->next->type == T_HEREDOC))
				count--;
		}
		else if (current->type == T_REDIR_IN || current->type == T_REDIR_OUT
			|| current->type == T_REDIR_APPEND || current->type == T_HEREDOC)
		{
			if (current->next)
				current = current->next;
		}
		current = current->next;
	}
	return (count);
}

/**
 * Libère la mémoire utilisée par les redirections
 */
static void	free_redirs(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs;
		redirs = redirs->next;
		free(temp->file);
		free(temp);
	}
}

/**
 * Libère la mémoire utilisée par les commandes
 */
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	int		i;

	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		free_redirs(temp->redir_in);
		free_redirs(temp->redir_out);
		free(temp);
	}
}

/**
 * Parse les tokens pour créer une liste de commandes
 */
t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;
	t_cmd	*current_cmd;
	t_token	*current;
	int		arg_index;

	if (!tokens || lexer_analyze(tokens, shell) != SUCCESS)
		return (NULL);
	cmds = NULL;
	current_cmd = new_cmd();
	add_cmd(&cmds, current_cmd);
	current = tokens;
	arg_index = 0;
	current_cmd->args = (char **)ft_malloc(sizeof(char *)
			* (count_args(tokens) + 1));
	while (current)
	{
		if (current->type == T_WORD)
		{
			current_cmd->args[arg_index] = ft_strdup(current->value);
			arg_index++;
		}
		else if (current->type == T_PIPE)
		{
			current_cmd->args[arg_index] = NULL;
			current_cmd = new_cmd();
			add_cmd(&cmds, current_cmd);
			arg_index = 0;
			current_cmd->args = (char **)ft_malloc(sizeof(char *)
					* (count_args(current->next) + 1));
		}
		else if (current->type == T_REDIR_IN || current->type == T_HEREDOC)
		{
			if (current->next && current->next->type == T_WORD)
			{
				add_redir(&current_cmd->redir_in,
					new_redir(current->type, current->next->value));
				current = current->next;
			}
		}
		else if (current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND)
		{
			if (current->next && current->next->type == T_WORD)
			{
				add_redir(&current_cmd->redir_out,
					new_redir(current->type, current->next->value));
				current = current->next;
			}
		}
		current = current->next;
	}
	current_cmd->args[arg_index] = NULL;
	return (cmds);
}

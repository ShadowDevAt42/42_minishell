/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:05:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 03:24:00 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie s'il y a une erreur de syntaxe dans les tokens
 */
static int	check_syntax_errors(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == T_PIPE)
		{
			if (!next || (next && next->type == T_PIPE))
			{
				print_error(NULL, "erreur de syntaxe près du symbole inattendu '|'");
				return (ERROR);
			}
		}
		else if (current->type == T_REDIR_IN || current->type == T_REDIR_OUT
			|| current->type == T_REDIR_APPEND || current->type == T_HEREDOC)
		{
			if (!next || (next && next->type != T_WORD))
			{
				print_error(NULL, "erreur de syntaxe près du symbole inattendu");
				return (ERROR);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}

/**
 * Vérifie la validité syntaxique des tokens et prépare les expansions
 */
int	lexer_analyze(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	if (!tokens)
		return (ERROR);
	if (check_syntax_errors(tokens) != SUCCESS)
		return (ERROR);
	current = tokens;
	while (current)
	{
		if (current->type == T_WORD && ft_strchr(current->value, '$'))
			expand_variables(shell, &current->value);
		current = current->next;
	}
	return (SUCCESS);
}

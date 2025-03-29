/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:50:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 03:21:58 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Crée un nouveau token
 */
static t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

/**
 * Ajoute un token à la fin de la liste
 */
static void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

/**
 * Libère la mémoire utilisée par les tokens
 */
void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

/**
 * Vérifie si un caractère est un espace
 */
static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * Extrait un mot (token)
 */
static int	extract_word(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;
	int		len;

	start = *i;
	while (input[*i] && !is_space(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			if (handle_quotes(input, i, &word) != SUCCESS)
				return (ERROR);
			add_token(tokens, new_token(T_WORD, word));
			return (SUCCESS);
		}
		(*i)++;
	}
	len = *i - start;
	if (len > 0)
	{
		word = (char *)ft_malloc(sizeof(char) * (len + 1));
		word[len] = '\0';
		while (len--)
			word[len] = input[start + len];
		add_token(tokens, new_token(T_WORD, word));
	}
	return (SUCCESS);
}

/**
 * Tokenise une ligne de commande
 */
t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	int		i;

	if (!input)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, new_token(T_PIPE, ft_strdup("|")));
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(&tokens, new_token(T_HEREDOC, ft_strdup("<<")));
			i += 2;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(&tokens, new_token(T_REDIR_APPEND, ft_strdup(">>")));
			i += 2;
		}
		else if (input[i] == '<')
		{
			add_token(&tokens, new_token(T_REDIR_IN, ft_strdup("<")));
			i++;
		}
		else if (input[i] == '>')
		{
			add_token(&tokens, new_token(T_REDIR_OUT, ft_strdup(">")));
			i++;
		}
		else if (extract_word(input, &i, &tokens) != SUCCESS)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}

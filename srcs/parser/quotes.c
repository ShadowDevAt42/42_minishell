/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:55:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 19:09:42 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Compte la longueur d'une chaîne entre guillemets
 */
static int	quoted_len(char *input, int start, char quote_type)
{
	int	i;

	i = start + 1;
	while (input[i] && input[i] != quote_type)
		i++;
	if (!input[i])
		return (-1);
	return (i - start - 1);
}

/**
 * Extrait le contenu entre guillemets simples
 */
static int	handle_single_quotes(char *input, int *i, char **value)
{
	int		len;
	int		j;

	len = quoted_len(input, *i, '\'');
	if (len == -1)
	{
		print_error(NULL, "guillemet non fermé");
		return (ERROR);
	}
	*value = (char *)ft_malloc(sizeof(char) * (len + 1));
	(*value)[len] = '\0';
	j = 0;
	(*i)++;
	while (j < len)
	{
		(*value)[j] = input[*i];
		j++;
		(*i)++;
	}
	(*i)++;
	return (SUCCESS);
}

/**
 * Extrait le contenu entre guillemets doubles
 */
static int	handle_double_quotes(char *input, int *i, char **value)
{
	int		len;
	int		j;

	len = quoted_len(input, *i, '\"');
	if (len == -1)
	{
		print_error(NULL, "guillemet non fermé");
		return (ERROR);
	}
	*value = (char *)ft_malloc(sizeof(char) * (len + 1));
	(*value)[len] = '\0';
	j = 0;
	(*i)++;
	while (j < len)
	{
		(*value)[j] = input[*i];
		j++;
		(*i)++;
	}
	(*i)++;
	return (SUCCESS);
}

/**
 * Gère l'extraction du contenu entre guillemets
 */
int	handle_quotes(char *input, int *i, char **value)
{
	if (input[*i] == '\'')
		return (handle_single_quotes(input, i, value));
	else if (input[*i] == '\"')
		return (handle_double_quotes(input, i, value));
	return (ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:00:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 03:24:04 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si un caractère est valide pour un nom de variable
 */
static int	is_valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

/**
 * Extrait le nom d'une variable d'environnement
 */
static char	*extract_var_name(char *word, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	while (word[*i] && is_valid_var_char(word[*i]))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (NULL);
	var_name = (char *)ft_malloc(sizeof(char) * (len + 1));
	var_name[len] = '\0';
	while (len--)
		var_name[len] = word[start + len];
	return (var_name);
}

/**
 * Remplace une variable par sa valeur
 */
static int	replace_var(char **word, int pos, char *var_name, char *var_value)
{
	char	*new_word;
	int		new_len;
	int		var_name_len;
	int		var_value_len;

	var_name_len = ft_strlen(var_name) + 1;
	var_value_len = ft_strlen(var_value);
	new_len = ft_strlen(*word) - var_name_len + var_value_len;
	new_word = (char *)ft_malloc(sizeof(char) * (new_len + 1));
	new_word[new_len] = '\0';
	strncpy(new_word, *word, pos);
	strcpy(new_word + pos, var_value ? var_value : "");
	strcpy(new_word + pos + var_value_len,
		*word + pos + var_name_len);
	free(*word);
	*word = new_word;
	return (var_value_len);
}

/**
 * Recherche et remplace les variables spéciales
 */
static int	handle_special_vars(t_shell *shell, char **word, int i)
{
	char	status_str[4];

	if ((*word)[i + 1] == '?')
	{
		sprintf(status_str, "%d", shell->exit_status);
		return (replace_var(word, i, "?", status_str));
	}
	return (0);
}

/**
 * Expansion des variables d'environnement
 */
int	expand_variables(t_shell *shell, char **word)
{
	int		i;
	char	*var_name;
	char	*var_value;
	int		in_quotes;

	if (!word || !*word)
		return (ERROR);
	i = 0;
	in_quotes = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'')
			in_quotes = !in_quotes;
		else if ((*word)[i] == '$' && !in_quotes)
		{
			if ((*word)[i + 1] == '?' || (*word)[i + 1] == '$')
				i += handle_special_vars(shell, word, i);
			else if (is_valid_var_char((*word)[i + 1]))
			{
				i++;
				var_name = extract_var_name(*word, &i);
				var_value = get_env_value(shell->env, var_name);
				i = i - ft_strlen(var_name) + replace_var(word, i - ft_strlen(var_name) - 1,
					var_name, var_value);
				free(var_name);
			}
			else
				i++;
		}
		else
			i++;
	}
	return (SUCCESS);
}

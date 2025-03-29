/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 05:50:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 03:26:43 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compte le nombre de sous-chaînes
 */
static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

/**
 * Calcule la longueur d'un mot
 */
static int	word_len(char const *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

/**
 * Divise une chaîne en utilisant un délimiteur
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)ft_malloc(sizeof(char *) * (word_count + 1));
	result[word_count] = NULL;
	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			result[k] = (char *)ft_malloc(sizeof(char) * (word_len(s, c, i) + 1));
			while (s[i] && s[i] != c)
				result[k][j++] = s[i++];
			result[k++][j] = '\0';
			j = 0;
		}
		else
			i++;
	}
	return (result);
}

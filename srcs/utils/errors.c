/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 06:15:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:46:30 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Affiche un message d'erreur
 */
void	print_error(char *cmd, char *msg)
{
	if (cmd)
		fprintf(stderr, "minishell: %s: %s\n", cmd, msg);
	else
		fprintf(stderr, "minishell: %s\n", msg);
} 
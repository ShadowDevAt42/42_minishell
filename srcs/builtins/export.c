/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:30:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 19:09:05 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Vérifie si le nom de la variable est valide
 */
static int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0] || !(name[0] == '_' || (name[0] >= 'a' && name[0] <= 'z')
			|| (name[0] >= 'A' && name[0] <= 'Z')))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!(name[i] == '_' || (name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Affiche toutes les variables d'environnement triées
 */
static int	print_sorted_env(char **env)
{
	int		i;
	int		j;
	int		env_size;
	char	*temp;

	env_size = 0;
	while (env[env_size])
		env_size++;
	i = 0;
	while (i < env_size - 1)
	{
		j = 0;
		while (j < env_size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (SUCCESS);
}

/**
 * Exporte une variable
 */
static int	export_variable(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (SUCCESS);
	name = ft_strdup(arg);
	name[equal_sign - arg] = '\0';
	if (!is_valid_name(name))
	{
		print_error("export", "identifiant non valable");
		free(name);
		return (ERROR);
	}
	value = equal_sign + 1;
	set_env_value(&shell->env, name, value);
	free(name);
	return (SUCCESS);
}

/**
 * Commande interne export
 */
int	ft_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**sorted_env;

	if (!cmd || !cmd->args || !shell || !shell->env)
		return (ERROR);
	if (!cmd->args[1])
	{
		sorted_env = copy_env(shell->env);
		print_sorted_env(sorted_env);
		i = 0;
		while (sorted_env[i])
		{
			free(sorted_env[i]);
			i++;
		}
		free(sorted_env);
		return (SUCCESS);
	}
	i = 1;
	while (cmd->args[i])
	{
		export_variable(shell, cmd->args[i]);
		i++;
	}
	return (SUCCESS);
}

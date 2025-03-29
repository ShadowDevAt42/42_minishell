/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/29 02:32:03 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

/**
 * Initialise la structure du shell
 */
static void	init_shell(t_shell *shell, char **env)
{
	shell->env = copy_env(env);
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->running = 1;
	shell->last_pid = 0;
}

/**
 * Nettoie la mémoire après chaque commande
 */
static void	cleanup_command(t_shell *shell)
{
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
}

/**
 * Libère toute la mémoire allouée par le shell
 */
static void	free_shell(t_shell *shell)
{
	int	i;

	cleanup_command(shell);
	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
	}
}

/**
 * Traite une ligne de commande
 */
static int	process_input(char *input, t_shell *shell)
{
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (input[0] != '\0')
	{
		add_history(input);
		shell->tokens = tokenizer(input);
		if (shell->tokens)
		{
			shell->cmds = parser(shell->tokens, shell);
			if (shell->cmds)
				shell->exit_status = executor(shell);
		}
	}
	free(input);
	return (1);
}

/**
 * Point d'entrée du programme
 */
int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	setup_signals();
	while (shell.running)
	{
		input = readline("minishell$ ");
		if (!process_input(input, &shell))
		{
			shell.running = 0;
			break ;
		}
		cleanup_command(&shell);
	}
	free_shell(&shell);
	return (shell.exit_status);
} 
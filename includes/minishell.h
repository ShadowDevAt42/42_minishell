/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:32:00 by minishell         #+#    #+#             */
/*   Updated: 2025/03/31 23:53:57 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdbool.h>
# include "libft.h"

/* Codes de retour */
# define SUCCESS 0
# define ERROR 1
# define EXIT_CTRL_D 130

/* Codes pour les types de tokens */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_EOF
}	t_token_type;

/* Structure pour un token */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* Structure pour une redirection */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/* Structure pour une commande */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redir_in;
	t_redir			*redir_out;
	int				pipe_in;
	int				pipe_out;
	struct s_cmd	*next;
}	t_cmd;

/* Structure principale */
typedef struct s_shell
{
	char			**env;
	t_token			*tokens;
	t_cmd			*cmds;
	int				exit_status;
	int				running;
	int				last_pid;
}	t_shell;

/* Variable globale pour la gestion des signaux */
extern int	g_signal_status;

/* Fonctions du parser */
t_token		*tokenizer(char *input);
void		free_tokens(t_token *tokens);
t_cmd		*parser(t_token *tokens, t_shell *shell);
void		free_cmds(t_cmd *cmds);
int			handle_quotes(char *input, int *i, char **value);
int			expand_variables(t_shell *shell, char **word);
int			lexer_analyze(t_token *tokens, t_shell *shell);

/* Fonctions de l'exécuteur */
int			executor(t_shell *shell);
char		*find_executable(char *cmd, char **env);
int			handle_redirections(t_cmd *cmd);
int			setup_pipes(t_cmd *cmd, t_cmd *next);
int			execute_command(t_cmd *cmd, t_shell *shell);

/* Commandes intégrées (builtins) */
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd, t_shell *shell);
int			ft_echo(t_cmd *cmd);
int			ft_cd(t_cmd *cmd, t_shell *shell);
int			ft_pwd(void);
int			ft_export(t_cmd *cmd, t_shell *shell);
int			ft_unset(t_cmd *cmd, t_shell *shell);
int			ft_env(t_shell *shell);
int			ft_exit(t_cmd *cmd, t_shell *shell);

/* Gestion des signaux */
void		setup_signals(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);

/* Fonctions utilitaires */
void		print_error(char *cmd, char *msg);
char		**copy_env(char **env);
void		free_array(char **array);
char		*get_env_value(char **env, char *key);
int			set_env_value(char ***env, char *key, char *value);
int			remove_env_var(char ***env, char *key);

#endif 
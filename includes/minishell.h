/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/22 10:22:37 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DEBUG_MODE 1
# ifndef READLINE_LIBRARY
#  define READLINE_LIBRARY
# endif
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/errno.h>
# include <signal.h>
# include <sys/stat.h>

# include "libft.h"
# include "rlstdc.h"
# include "readline.h"
# include "history.h"

# define PROMPT "Minishell $ "
# define PROG_NAME "minishell"
# define TOKENS "<>|\t "

# define SYNTAX_ERROR 1 
# define NO_FILE 2
# define NO_RIGHT 3
# define IS_DIR 4
# define OPEN_ERROR 5
# define SIGNAL_ERROR 6

typedef struct s_redirections
{
	char	*r_stdin;
	char	*r_stdout;
	int		heredoc;
	int		append;
}		t_redirections;

typedef struct s_command
{
	char			**args;
	int				last;
	t_redirections	redirections;
}					t_command;

t_command	*ms_parser(char *line, char **env);
char		**ms_lexer(char *line);
char		*clean_line(char *line);
size_t		count_tokens(char *line);
char		**get_tokens(char *line, size_t size);
t_command	*get_commands(char **tokens);
void		ms_clean_commands(t_command *commands);
void		parser_clean_commands(t_command *commands, char **env);
char		*clean_tokens(char *token, char **env);
size_t		get_count_var_env(char *token);
size_t		get_env_var_len(char **env_var);
char		**get_env_list(char *token, char **env);
size_t		get_new_token_size(char *token, char **var_env);

int			ms_execute(t_command *commnands, char ***env);
char		*get_command_path(char *command, char **env);
int	set_redirections(t_command command, int *pipe_fd, int last);

// Environment management
char		*ms_getenv(char **env, char *var);
char		**init_env(char **env);
char		**add_var(char **env, char *name, char *content);
char		**remove_var(char **env, char *var);
char		**update_var(char **env, char *var, char *new_content);
int			is_var(char **env, char *var);

//Builtin
int	exec_builtin(t_command cmd, char ***env);

// Signal management
int			ms_init_signals(void);
int			ms_reset_signals(void);

// Memory management
void		ms_free_tokens(char **tokens);
void		ms_clean_commands(t_command *commands);
void		ft_exit(t_command *commands);
void		ft_exit_nb(t_command *commands, int retval);
int			is_dir(char *path);

int			ft_error(void);
void		ft_error_message(char *s, int error_type);
#endif

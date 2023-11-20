/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 13:18:55 by eguefif          ###   ########.fr       */
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

# include "libft.h"
# include "rlstdc.h"
# include "readline.h"
# include "history.h"

# define PROMPT "Minishell $ "
# define PROG_NAME "minishell"
# define TOKENS "<>|\t "

# define SYNTAX_ERROR 1 

typedef struct s_redirections
{
	char	*r_stdin;
	char	*r_stdout;
}			t_redirections;

typedef struct s_command
{
	char			**args;
	int				last;
	t_redirections	redirections;
}					t_command;

t_command	*ms_parser(char *line);
char		**ms_lexer(char *line);
char		*clean_line(char *line);
size_t		count_tokens(char *line);
char		**get_tokens(char *line, size_t size);
t_command	*get_commands(char **tokens);
void		ms_clean_commands(t_command *commands);
void		parser_clean_commands(t_command *commands);
char		*clean_tokens(char *token);
size_t		get_count_var_env(char *token);
size_t		get_env_var_len(char **env_var);
char		**get_env_list(char *token);
size_t		get_new_token_size(char *token, char **var_env);

int			ms_execute(t_command *commnands, char **env);

void		ms_free_tokens(char **tokens);
void		ms_clean_commands(t_command *commands);
void		ft_exit(t_command *commands);

void		ft_error(void);
void		ft_error_message(char *s, int error_type);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/15 17:12:21 by eguefif          ###   ########.fr       */
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

# include "libft.h"
# include "rlstdc.h"
# include "readline.h"
# include "history.h"

# define PROMPT "Minishell $ "
# define TOKENS "<>|\t "

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
}			t_command;	

t_command	*ms_parser(char *line);
char		**ms_lexer(char *line);
char		*clean_line(char *line);
size_t		count_tokens(char *line);
char 		**get_tokens(char *line, size_t size);
t_command	*get_commands(char **tokens);
void		ms_clean_commands(t_command *commands);

int			ms_execute(t_command *commnands, char **env);

void		ms_cleanup(char **commands);
void		ms_clean_tokens(char **tokens);

void		ft_error(void);
#endif

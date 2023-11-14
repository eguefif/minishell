/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/14 16:11:50 by eguefif          ###   ########.fr       */
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
	t_redirections files;
}			t_command;	

t_command	*ms_parser(char *line);
char		**ms_lexer(char *line);
char		*clean_line(char *line);
size_t		count_tokens(char *line);
char 		**get_tokens(char *line, size_t size);
char		*jump_quote(char *line);

int			ms_execute(t_command *commnands, char **env);

void		ms_cleanup(char **commands);
void		ms_clean_tokens(char **tokens);

void		ft_error(char *s, char *name);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 18:13:05 by maxpelle         ###   ########.fr       */
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

typedef	struct s_command
{
	char	*arg;
	int		argc;
}			t_command;	

char	**ms_parser(char *line);
int		ms_execute(char **commands, char **env);
void	ms_cleanup(char **commands);
char	*clean_line(char *line);
size_t	count_tokens(char *line);

#endif

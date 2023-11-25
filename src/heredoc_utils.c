/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:24:27 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/25 10:38:06 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_heredoc_get_new_line
{
	char	*retval;
	size_t	i;
	size_t	j;
	size_t	env_count;
}	t_heredoc_get_new_line;

static size_t	get_line_size(char *line, char **var_env);
static char		*get_new_line(char *line, size_t size, char **var_env);

void	exit_heredoc(char *file_name, t_command *commands, char **env)
{
	free(file_name);
	ms_clean_commands(commands);
	ft_cleansplits(env);
	exit(0);
}

char	*heredoc_get_file_name(int num)
{
	char	*num_str;
	char	*retval;

	num_str = ft_itoa(num);
	retval = ft_strjoin("/tmp/minishell_heredoc", num_str);
	if (num_str)
		free(num_str);
	return (retval);
}

char	*expand_env_vars(char *line, char **env)
{
	char	**var_env;
	size_t	size;
	char	*retval;

	var_env = get_env_list(line, env);
	size = get_line_size(line, var_env);
	retval = get_new_line(line, size, var_env);
	if (var_env)
		ft_cleansplits(var_env);
	if (line)
		free(line);
	return (retval);
}

static size_t	get_line_size(char *line, char **var_env)

{
	size_t	i;
	size_t	count;
	size_t	env_count;

	i = 0;
	count = 0;
	env_count = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			count += ft_strlen(var_env[env_count]);
			env_count++;
			i++;
			while (!ft_strchr("\n \t\'\"$", line[i]))
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	*get_new_line(char *line, size_t size, char **var_env)
{
	t_heredoc_get_new_line	data;

	data.retval = ft_calloc((size + 1), sizeof (char));
	if (!(data.retval))
		return (0);
	data.i = 0;
	data.j = 0;
	data.env_count = 0;
	while (data.i < size)
	{
		if (line[data.j] == '$')
		{
			data.j++;
			while (!ft_strchr("\n \t\'\"$", line[data.j]))
				data.j++;
			if (var_env[data.env_count])
				ft_strcpy(data.retval + data.i, var_env[data.env_count]);
			data.i += ft_strlen(var_env[data.env_count]);
			data.env_count++;
		}
		else
			data.retval[data.i++] = line[data.j++];
	}
	return (data.retval);
}

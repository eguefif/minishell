/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:41:06 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/24 10:49:09 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_heredoc(char *end_cmd, char **env, int num, int flag);
static void	run_heredoc(int fd, char *end_cmd, char **env, int flag);
static char	*get_new_line(char *line, size_t size, char **var_env);
static char	*expand_env_vars(char *line, char **env);
static size_t	get_line_size(char *line, char **var_env);

t_command	*builtin_heredoc(t_command *commands, char **env)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = 0;
	while (!commands[i].last)
	{
		if (commands[i].redirections.heredoc)
		{
			file_name = set_heredoc(commands[i].redirections.r_stdin,
					env, i, commands[i].redirections.heredoc);
			if (!file_name)
			{
				ft_error_message(commands[i].args[0], HEREDOC_ERROR);
				return(0);
			}
			if (ft_strcmp("fork", file_name) == 0)
			{
				free(file_name);
				ms_clean_commands(commands);
				ft_cleansplits(env);
				exit(0);
			}
			if (commands[i].redirections.r_stdin) 
				free(commands[i].redirections.r_stdin);
			commands[i].redirections.r_stdin = file_name;
			file_name = 0;
		}
		i++;
	}
	return (commands);
}

static char	*set_heredoc(char *end_cmd, char **env, int num, int flag)
{
	char	*file_name;
	char	*num_str;
	int		fd;
	int		pid;
	int		stat_loc;

	if (!end_cmd)
		return (0);
	pid = -1;
	num_str = ft_itoa(num);
	file_name = ft_strjoin("/tmp/minishell_heredoc", num_str);
	if (num_str)
		free(num_str);
	fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		ft_error();
		return (0);
	}
	if (!pid)
	{
		ms_heredoc_signals();
		run_heredoc(fd, end_cmd, env, flag) ;
		free(file_name);
		file_name = ft_strdup("fork");
	}
	else
	{
		ms_ignore_signals();
		waitpid(pid, &stat_loc, 0);
		ms_init_signals();
	}
	close(fd);
	return (file_name);
}

static void	run_heredoc(int fd, char *end_cmd, char **env, int flag)
{
	char	*line;

	end_cmd = ft_strjoin(end_cmd, "\n");
	ft_printf("> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(end_cmd, line) == 0)
		{
			free(line);
			free(end_cmd);
			break ;
		}
		if (flag == 2)
			line = expand_env_vars(line, env);	
		ft_dprintf(fd, line);
		free(line);
		ft_printf("> ");
		line = get_next_line(0);
	}
}

void	builtin_heredoc_delete(t_command *commands)
{
	int		i;

	i = 0;
	while (!commands[i].last)
	{
		if (commands[i].redirections.heredoc)
			if (ft_strncmp("/tmp/", commands[i].redirections.r_stdin, 5) == 0)
				unlink(commands[i].redirections.r_stdin);
		i++;
	}
}

static char	*expand_env_vars(char *line, char **env)
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
	char	*retval;
	size_t	i;
	size_t	j;
	size_t	env_count;

	retval = ft_calloc((size + 1), sizeof (char));
	if (!retval)
		return (0);
	i = 0;
	j = 0;
	env_count = 0;
	while (i < size)
	{
		if (line[j] == '$')
		{
			j++;
			while (!ft_strchr("\n \t\'\"$", line[j]))
				j++;
			if (var_env[env_count])
				ft_strcpy(retval + i, var_env[env_count]);
			i += ft_strlen(var_env[env_count]);
			env_count++;
		}
		else
		{
			retval[i] = line[j];
			i++;
			j++;
		}
	}
	return (retval);
}

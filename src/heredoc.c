/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:41:06 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/25 10:37:48 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_heredoc_data
{
	char	*file_name;
	int		fd;
	int		pid;
}	t_heredoc_data;

static char	*set_heredoc(char *end_cmd, char **env, int num, int flag);
static char	*run_heredoc(int fd, char *end_cmd, char **env, int flag);
static void	wait_heredoc(int pid);

// Inside heredoc_utils.c
void		exit_heredoc(char *file_name, t_command *commands, char **env);
char		*heredoc_get_file_name(int num);
char		*expand_env_vars(char *line, char **env);

t_command	*builtin_heredoc(t_command *commands, char **env)
{
	int		i;
	char	*file_name;

	i = -1;
	file_name = 0;
	while (!commands[++i].last)
	{
		if (commands[i].redirections.heredoc)
		{
			file_name = set_heredoc(commands[i].redirections.r_stdin,
					env, i, commands[i].redirections.heredoc);
			if (!file_name)
			{
				ft_error_message(commands[i].args[0], HEREDOC_ERROR);
				return (0);
			}
			if (ft_strcmp("fork", file_name) == 0)
				exit_heredoc(file_name, commands, env);
			if (commands[i].redirections.r_stdin) 
				free(commands[i].redirections.r_stdin);
			commands[i].redirections.r_stdin = file_name;
			file_name = 0;
		}
	}
	return (commands);
}

static char	*set_heredoc(char *end_cmd, char **env, int num, int flag)
{
	t_heredoc_data	data;

	if (!end_cmd)
		return (0);
	data.file_name = heredoc_get_file_name(num);
	data.fd = open(data.file_name, O_APPEND | O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (data.fd < 0)
		return (0);
	data.pid = fork();
	if (data.pid < 0)
	{
		ft_error();
		return (0);
	}
	if (!(data.pid))
	{
		free(data.file_name);
		data.file_name = run_heredoc(data.fd, end_cmd, env, flag);
	}
	else
		wait_heredoc(data.pid);
	close(data.fd);
	return (data.file_name);
}

static char	*run_heredoc(int fd, char *end_cmd, char **env, int flag)
{
	char	*line;

	ms_heredoc_signals();
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
	return (ft_strdup("fork"));
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

static void	wait_heredoc(int pid)
{
	int	stat_loc;

	ms_ignore_signals();
	waitpid(pid, &stat_loc, 0);
	ms_init_signals();
}

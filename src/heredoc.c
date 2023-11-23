/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:41:06 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/23 13:29:10 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_heredoc(char *end_cmd, int num);
static void	run_heredoc(int fd, char *end_cmd);

t_command	*builtin_heredoc(t_command *commands)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = 0;
	while (!commands[i].last)
	{
		if (commands[i].redirections.heredoc)
		{
			file_name = set_heredoc(commands[i].redirections.r_stdin, i);
			if (!file_name)
			{
				ft_error_message(commands[i].args[0], HEREDOC_ERROR);
				return(0);
			}
			if (ft_strcmp("fork", file_name) == 0)
			{
				ms_clean_commands(commands);
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

static char	*set_heredoc(char *end_cmd, int num)
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
	file_name = ft_strjoin("/tmp/minishell_heredoc", ft_itoa(num));
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
		run_heredoc(fd, end_cmd);
		free(file_name);
		file_name = ft_strdup("fork");
	}
	else
		waitpid(pid, &stat_loc, 0);
	close(fd);
	return (file_name);
}

static void	run_heredoc(int fd, char *end_cmd)
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

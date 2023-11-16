/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:15:11 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/16 18:19:23 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_count_var_env(char *token);
char	*clean_tokens(char *token);
char	**get_env_list(char *token);
char	*get_env_var(char *s);
size_t	get_new_token_size(char *token, char **var_env);
char *get_new_token(char *token, size_t size, char **env_var);

void	parser_clean_commands(t_command *commands)
{
	int		i;
	int		j;

	i = 0;
	while (!commands[i].last)
	{
		if (commands[i].args)
		{
			j = -1;
			while (commands[i].args[++j])
				commands[i].args[j] = clean_tokens(commands[i].args[j]);
		}
		if (commands[i].redirections.r_stdin)
			commands[i].redirections.r_stdin
				= clean_tokens(commands[i].redirections.r_stdin);
		if (commands[i].redirections.r_stdout)
			commands[i].redirections.r_stdout
				= clean_tokens(commands[i].redirections.r_stdout);
		i++;
	}
}

char	*clean_tokens(char *token)
{
	char	**var_env;
	size_t	size;
	char	*retval;

	var_env = get_env_list(token);
	size = get_new_token_size(token, var_env);
	retval = get_new_token(token, size, var_env);
	if (token)
		free(token);
	if (var_env)
		free(var_env);
	return (retval);
}

char	**get_env_list(char *token)
{
	int		i;
	int		j;
	size_t	size;	
	char	**retval;

	size = get_count_var_env(token);
	retval = (char **) malloc(sizeof(char *) * (size + 1));
	retval[size] = 0;
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] == '\'')
				i++;
		}
		else
		{
			if (token[i] == '$' && token[i + 1]
					&& !ft_strchr(" \t$", token[i + 1]))
			{
				retval[j] = get_env_var((token + i));
				j++;
			}
		}
		if (token[i])
			i++;
		}
	return (retval);		
}

size_t	get_count_var_env(char *token)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] == '\'')
				i++;
		}
		else
			if (token[i] == '$' && token[i + 1]
					&& !ft_strchr(" \t$", token[i + 1]))
				size++;
		i++;
	}
	return (size);
}

char	*get_env_var(char *s)
{
	size_t	size;
	char	*retval;
	char	*var_name;

	size = 1;
	while (s[size] && !ft_strchr(" \t$", s[size]))
		size++;
	var_name  = ft_strldup(s + 1, size);
	if (!var_name)
		return (0);
	retval = getenv(var_name);
	free(var_name);
	return (retval);
}

size_t	get_new_token_size(char *token, char **var_env)
{
	size_t	retval;
	int		i;
	int		flag;

	retval = 0;
	i = -1;
	while (var_env[++i])
		if (var_env[i])
			retval += ft_strlen(var_env[i]);
	flag = -1;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && flag < 0)
		{
			i++;
			while (token[i] && token[i] != '\'')
			{
				i++;
				retval++;
			}
		}
		else
		{
			if (token[i] == '\"')
				flag *= -1;
			else if (token[i] == '$' && token[i + 1]
					&& !ft_strchr(" \t$", token[i + 1]))
			{
				i++;
				while (token[i] && !ft_strchr(" \t$", token[i]))
					i++;
				i--;
			}
			else
				retval++;
		}
		i++;
	}
	return (retval);
}

char *get_new_token(char *token, size_t size, char **env_var)
{
	int		i;
	int		j;
	int		count_env_var;
	int		flag;
	char	*retval;

	retval = (char *) malloc(sizeof(char) * (size + 1));
	retval[size] = '\0';
	if (!retval)
		return (0);
	flag = -1;
	i = 0;
	j = 0;
	count_env_var = 0;
	while (token[i])
	{
		if (token[i] == '\'' && flag < 0)
		{
			i++;
			while (token[i] && token[i] != '\'')
			{
				retval[j] = token[i];
				i++;
				j++;
			}
		}
		else
		{
			if (token[i] == '\"')
				flag *= -1;
			else if (token[i] == '$' && token[i + 1]
					&& !ft_strchr(" \t$", token[i + 1]))
			{
				i++;
				while (token[i] && !ft_strchr(" \t$", token[i]))
					i++;
				if (env_var[count_env_var])
				{
					ft_memcpy(retval + j, env_var[count_env_var], ft_strlen(env_var[count_env_var]));
					j += ft_strlen(env_var[count_env_var]);
				}
				count_env_var++;
			}
			else
			{
				retval[j] = token[i];
				i++;
				j++;
			}
		}
	}
	return (retval);
}

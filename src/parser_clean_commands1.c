/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_commands1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:15:11 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/25 11:41:47 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_get_new_token
{
	int		i;
	int		j;
	int		count_env_var;
	int		flag;
	char	*retval;
}	t_get_new_token;

char	*get_new_token(char *token, size_t size, char **env_var);
void	get_new_token_part(t_get_new_token *data, char *token, char **env_var);
size_t	get_new_token_size(char *token, char **var_env);
void	get_new_token_size_part(char *token, size_t *retval, int *i, int *flag);

void	parser_clean_commands(t_command *commands, char **env)
{
	int		i;
	int		j;

	i = -1;
	while (!commands[++i].last)
	{
		if (commands[i].args)
		{
			j = -1;
			while (commands[i].args[++j])
				commands[i].args[j] = clean_tokens(commands[i].args[j], env);
		}
		if (commands[i].redirections.r_stdin)
		{
			if (commands[i].redirections.heredoc > 0)
				commands[i].redirections.r_stdin
					= clean_tokens_stdin(commands[i].redirections.r_stdin);
			else
				commands[i].redirections.r_stdin
					= clean_tokens(commands[i].redirections.r_stdin, env);
		}
		if (commands[i].redirections.r_stdout)
			commands[i].redirections.r_stdout
				= clean_tokens(commands[i].redirections.r_stdout, env);
	}
}

void	get_new_token_size_part(char *token, size_t *retval, int *i, int *flag)
{
	if (token[*i] == '\"')
		*flag *= -1;
	else if (token[*i] == '$' && token[*i + 1]
		&& !ft_strchr(" \t$\'\"", token[*i + 1]))
	{
		while (token[++(*i)] && !ft_strchr(" \t$\'\"", token[*i]))
			;
		(*i)--;
	}
	else
		(*retval)++;
}

size_t	get_new_token_size(char *token, char **var_env)
{
	size_t	retval;
	int		i;
	int		flag;

	retval = get_env_var_len(var_env);
	flag = -1;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' && flag < 0)
			while (token[++i] && token[i] != '\'')
				retval++;
		else
			get_new_token_size_part(token, &retval, &i, &flag);
	}
	return (retval);
}

char	*get_new_token(char *token, size_t size, char **env_var)
{
	t_get_new_token	data;	

	data.retval = (char *) ft_calloc(size + 1, sizeof (char));
	if (!data.retval)
		return (0);
	data.flag = -1;
	data.i = 0;
	data.j = 0;
	data.count_env_var = 0;
	while (token[data.i])
	{
		if (token[data.i] == '\'' && data.flag < 0)
		{
			(data.i)++;
			while (token[data.i] && token[data.i] != '\'')
				data.retval[data.j++] = token[data.i++];
			data.i++;
		}
		else
			get_new_token_part(&data, token, env_var);
	}
	return (data.retval);
}

void	get_new_token_part(t_get_new_token *data, char *token, char **env_var)
{
	if (token[data->i] == '\"')
	{
		data->flag *= -1;
		(data->i)++;
	}
	else if (token[data->i] == '$' && token[(data->i) + 1]
		&& !ft_strchr(" \t$\'\"", token[(data->i) + 1]))
	{
		(data->i)++;
		while (token[(data->i)] && !ft_strchr(" \t$\'\"", token[(data->i)]))
			(data->i)++;
		if (env_var[data->count_env_var])
		{
			ft_memcpy((data->retval) + data->j, env_var[data->count_env_var],
				ft_strlen(env_var[data->count_env_var]));
			data->j += ft_strlen(env_var[data->count_env_var]);
		}
		(data->count_env_var)++;
	}
	else
	{
		data->retval[data->j] = token[data->i];
		(data->i)++;
		(data->j)++;
	}
}

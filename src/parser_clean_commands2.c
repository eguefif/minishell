/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_commands2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:59:51 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/23 12:59:52 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_count_var_env(char *token);
char	*get_env_var(char *s, char **env);
char	*get_new_token(char *token, size_t size, char **env_var);

char	*clean_tokens(char *token, char **env)
{
	char	**var_env;
	size_t	size;
	char	*retval;

	var_env = get_env_list(token, env);
	size = get_new_token_size(token, var_env);
	retval = get_new_token(token, size, var_env);
	if (token)
		free(token);
	if (var_env)
		free(var_env);
	return (retval);
}

char	**get_env_list(char *token, char **env)
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
			while (token[++i] && token[i] == '\'')
				;
		else
			if (token[i] == '$' && token[i + 1]
				&& !ft_strchr(" \t$", token[i + 1]))
				retval[j++] = get_env_var((token + i), env);
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

char	*get_env_var(char *s, char **env)
{
	size_t	size;
	char	*retval;
	char	*var_name;

	size = 1;
	while (s[size] && !ft_strchr(" \t$\'\"", s[size]))
		size++;
	var_name = ft_strldup(s + 1, size - 1);
	if (!var_name)
		return (0);
	retval = ms_getenv(env, var_name);
	free(var_name);
	return (retval);
}

size_t	get_env_var_len(char **env_var)
{
	int		i;
	size_t	retval;

	i = -1;
	retval = 0;
	while (env_var[++i])
		if (env_var[i])
			retval += ft_strlen(env_var[i]);
	return (retval);
}

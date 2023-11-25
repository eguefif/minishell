/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:07:54 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 10:47:05 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_error(t_command *commands);

void	builtin_exit(t_command *commands, char ***env)
{
	int	retval;

	if (commands->args && commands->args[0]
		&& ft_strcmp(commands->args[0], "exit") == 0)
	{
		retval = handle_exit_error(commands);
		ft_cleansplits(*env);
		ms_clean_commands(commands);
		exit(retval);
	}
	return ;
}

char	**handle_exit_code(char **env, int retval)
{
	char	*tmp_retval;

	tmp_retval = ft_itoa(retval);
	if (is_var(env, "?"))
		env = update_var(env, "?", tmp_retval);
	else 
		env = add_var(env, "?", tmp_retval);
	free(tmp_retval);
	return (env);
}

static int	handle_exit_error(t_command *commands)
{
	int	retval;

	retval = 0;
	if (commands->args[1] && commands->args[2])
	{
		ft_error_message("exit", EXIT_TOO_MANY_ARGS);
		retval = 1;
	}
	else if (commands->args[1])
	{
		if (ft_is_strnum(commands->args[1]))
			retval = ft_atoi(commands->args[1]);
		else
		{
			ft_error_message(commands->args[1], EXIT_NON_NUM);
			retval = 255;
		}
	}
	return (retval);
}

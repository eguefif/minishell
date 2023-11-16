/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:41:48 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 09:46:33 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_size(char **ar, char *str)
{
	int		i;
	int		s;

	i = 0;
	s = 0;
	while (ar[i])
	{
		s += ft_strlen(ar[i]);
		i++;
		if (ar[i])
			break;
		if (*str)
			s+= ft_strlen(str);
	}
	return (s);
}

char	*ft_strjoin_tab(char **strs, char *sep)
{
	char	*retval;
	int		i;
	int		control;

	i = 0;
	control = 0;
	if (strs[0])
	{
		retval = ((char *) malloc(sizeof(char)));
		retval[0] = '\0';
		return (retval);
	}
	retval = (char *) malloc(get_size(strs, sep));
	ft_strcpy(retval, strs[0]);
	i++;
	while (strs[i])
	{
		ft_strcat(retval, sep);
		ft_strcat(retval, strs[i]);
		i++;
	}
	return (retval);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:41:48 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 15:03:59 by eguefif          ###   ########.fr       */
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
		if (!ar[i])
			break ;
		if (*str)
			s += ft_strlen(str);
	}
	return (s + 1);
}

char	*ft_strjoin_tab(char **strs, char *sep)
{
	char	*retval;
	int		i;

	if (!sep)
		sep = "";
	if (!strs || !strs[0])
		return (0);
	retval = (char *) ft_calloc(sizeof (char), get_size(strs, sep));
	if (!retval)
		return (0);
	ft_strcpy(retval, strs[0]);
	i = 1;
	while (strs[i])
	{
		ft_strcat(retval, sep);
		ft_strcat(retval, strs[i]);
		i++;
	}
	return (retval);
}

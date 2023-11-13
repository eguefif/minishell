/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:57:09 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:27:06 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_ptr(t_conv conv, t_string *str)
{
	char	*nbr;
	char	*temp;

	temp = ft_lutoa_base(conv.d_ptr, "0123456789abcdef");
	nbr = ft_strjoin("0x", temp);
	if (!nbr)
	{
		free(temp);
		return ;
	}
	make_replacement(nbr, conv, str);
	free(nbr);
	free(temp);
}

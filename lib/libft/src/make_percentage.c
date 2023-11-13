/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_percentage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:35:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:26:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_percentage(t_string *str)
{
	str->string = ft_strdup("%");
	str->size = 1;
}

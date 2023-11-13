/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_conversionspe_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:33:35 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 09:21:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_default_values(t_conv *conv)
{
	conv->specifier = 0;
	conv->f_leftjust = 0;
	conv->f_zero = 0;
	conv->min_field = 0;
	conv->precision = 0;
	conv->d_char = 0;
	conv->error = 0;
	conv->d_char = 0;
	conv->d_str = 0;
	conv->d_nbr = 0;
	conv->d_ptr = 0;
	conv->d_unbr = 0;
	conv->d_double = 0;
	conv->d_percentage = 0;
}

void	check(t_conv *conv)
{
	if (conv->precision > 0 || conv->f_leftjust == 1)
		conv->f_zero = 0;
	if (conv->specifier == 's' || conv->specifier == 'c'
		|| conv->specifier == 'p' || conv->specifier == '%')
		conv->f_zero = 0;
	if (conv->specifier == '%')
	{
		conv->precision = 0;
		conv->min_field = 0;
	}
}

char	*is_specifier_letter(char c)
{
	return (ft_strchr(CONVSPE, c));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_conversionspe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:18:01 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 09:21:42 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set_flags(t_conv *conv, char *str)
{
	int		i;

	i = 0;
	while (ft_strchr(FLAGS, *str) && *str && i < MAX_FLAGS)
	{
		if (*str == '-')
			conv->f_leftjust = 1;
		if (*str == '0')
			conv->f_zero = 1;
		str++;
		i++;
	}
	return (str);
}

char	*set_minfield(t_conv *conv, char *str, va_list ap)
{
	if (*str == '*')
	{
		conv->min_field = va_arg(ap, int);
		str++;
	}
	else
		conv->min_field = ft_atoi(str);
	while (ft_isdigit(*str) && *str)
		str++;
	return (str);
}

char	*set_precision(t_conv *conv, char *str, va_list ap)
{
	if (*str == '.')
	{
		str++;
		if (*str == '*')
		{
			conv->precision = va_arg(ap, int);
			str++;
		}
		else
			conv->precision = ft_atoi(str);
		if (conv->precision < 0)
			conv->precision = 0;
		while (ft_isdigit(*str) && *str)
			str++;
	}
	return (str);
}

char	*set_conv(t_conv *conv, char *str)
{
	if (is_specifier_letter(*str))
		conv->specifier = *str;
	else
		return (0);
	return (str);
}

int	set_data(t_conv *conv, va_list ap)
{
	if (conv->specifier == 'd' || conv->specifier == 'i')
		conv->d_nbr = va_arg(ap, int);
	else if (ft_strchr("xXu", conv->specifier))
		conv->d_unbr = va_arg(ap, unsigned int);
	else if (conv->specifier == 's')
		conv->d_str = va_arg(ap, char *);
	else if (conv->specifier == 'c')
		conv->d_char = (char) va_arg(ap, int);
	else if (conv->specifier == '%')
		conv->d_percentage = '%';
	else if (conv->specifier == 'p')
		conv->d_ptr = va_arg(ap, unsigned long int);
	else if (ft_strchr("Ff", conv->specifier))
		conv->d_double = va_arg(ap, double);
	return (1);
}

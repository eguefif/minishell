/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:09:16 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 09:20:02 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		get_str(t_conv conv, t_string *str);
static	int	is_conversionspe_start(char *str);

int	replace_conversion(t_split *splits, va_list ap)
{
	int		i;
	t_conv	conv;

	i = 0;
	while (i < splits->counts)
	{
		if (is_conversionspe_start(splits->list[i].string))
		{
			if (!init_conversionspe(splits->list[i].string, ap, &conv))
				return (0);
			free(splits->list[i].string);
			get_str(conv, &splits->list[i]);
		}
		i++;
	}
	return (1);
}

static	int	is_conversionspe_start(char *str)
{
	return (str[0] == '%');
}

int	init_conversionspe(char *str, va_list ap, t_conv *conv)
{
	str++;
	set_default_values(conv);
	str = set_flags(conv, str);
	if (!*str)
		return (0);
	str = set_minfield(conv, str, ap);
	if (!*str)
		return (0);
	str = set_precision(conv, str, ap);
	if (!*str)
		return (0);
	str = set_conv(conv, str);
	if (!str)
		return (0);
	if (!set_data(conv, ap))
		return (0);
	check(conv);
	return (1);
}

// Following functions are define in files that has the same name.
void	get_str(t_conv conv, t_string *str)
{
	if (ft_strchr("di", conv.specifier))
		make_int(conv, str);
	else if (conv.specifier == 's')
		make_str(conv, str);
	else if (ft_strchr("uxX", conv.specifier))
		make_uint(conv, str);
	else if (conv.specifier == 'p')
		make_ptr(conv, str);
	else if (conv.specifier == 'c')
		make_char(conv, str);
	else if (conv.specifier == '%')
		make_percentage(str);
	if (ft_strchr("fF", conv.specifier))
		make_double(conv, str);
}

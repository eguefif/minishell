/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:20:12 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/30 15:11:41 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_decimal(t_conv conv);
int		get_precision(t_conv conv);

void	make_double(t_conv conv, t_string *str)
{
	char	*whole;
	char	*decimal;
	char	*nbr;

	whole = ft_itoa(conv.d_double);
	decimal = get_decimal(conv);
	nbr = (char *) malloc(sizeof(char) * (ft_strlen(whole)
				+ ft_strlen(decimal) + 2));
	ft_strncpy(nbr, whole, ft_strlen(whole));
	ft_strncat(nbr, ".", 1);
	ft_strncat(nbr, decimal, ft_strlen(decimal));
	make_replacement(nbr, conv, str);
	free(decimal);
	free(nbr);
	free(whole);
}

char	*get_decimal(t_conv conv)
{
	int		whole;
	int		precision;
	double	decimal;
	int		i;

	precision = get_precision(conv);
	whole = (int) conv.d_double;
	decimal = conv.d_double;
	decimal -= (double) whole;
	if (decimal < 0)
		decimal *= -1;
	i = 0;
	while (i < precision)
	{
		decimal *= 10;
		i++;
	}
	return (ft_itoa((int) decimal));
}

int	get_precision(t_conv conv)
{
	if (conv.precision == 0)
		return (PRECISION_DEFAULT);
	if (conv.precision < PRECISION_DEFAULT)
		return (conv.precision);
	return (PRECISION_DEFAULT);
}

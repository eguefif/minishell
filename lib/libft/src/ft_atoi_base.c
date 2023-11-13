/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:06:38 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/03 10:05:35 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	get_index_base(char str, char *base)
{
	int		i;

	i = 0;
	while (*base != '\0')
	{
		if (*base == str)
			return (i);
		i++;
		base++;
	}
	return (-1);
}

int	get_nbr(char *str, char *base)
{
	int		retval;
	int		size;
	int		idx;

	retval = 0;
	size = 0;
	size = ft_strlen(base);
	idx = get_index_base(*str, base);
	while (idx != -1 && *str != '\0')
	{
		retval *= size;
		retval += idx;
		str++;
		idx = get_index_base(*str, base);
	}
	return (retval);
}

int	check_error(char *base)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	while (base[i] != '\0')
		if (base[i] == '+' || base[i++] == '-' || base[i] == '\t'
			|| base[i] == '\n' || base[i] == '\v' || base[i] == '\f'
			|| base[i] == '\r' || base[i] == ' ')
			return (1);
	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (1);
	i = 0;
	while (base[i] != '\0')
	{
		j = 0;
		c = 0;
		while (base[j] != '\0')
			if (base[i] == base[j++])
				c++;
		if (c > 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int		sign;

	sign = 1;
	if (check_error(base))
		return (0);
	while ((*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == ' ') && *str != '\0')
		str++;
	while (*str != '\0')
	{
		if (*str == '+')
			str++;
		else if (*str == '-')
		{
			sign *= -1;
			str++;
		}
		else
			break ;
	}
	return (get_nbr(str, base) * sign);
}

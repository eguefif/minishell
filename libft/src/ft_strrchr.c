/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:06:11 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 12:18:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*retval;

	if (!s)
		return (0);
	str = (char *) s;
	retval = 0;
	while (*str)
	{
		if ((unsigned char) *str == (unsigned char) c)
			retval = str;
		str++;
	}
	if ((unsigned char) c == (unsigned char) *str)
		retval = str;
	return (retval);
}

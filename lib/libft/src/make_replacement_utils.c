/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_replacement_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:14:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 09:12:18 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_replace_size(char *str, t_conv conv);
static char	*get_bed(char *content, t_conv conv, t_string *str);
static void	copy(t_string *str, const char *content, t_conv conv);
static char	*fill_bed(char *str, t_conv conv, int size);

void	make_replacement(char *content, t_conv conv, t_string *str)
{
	get_bed(content, conv, str);
	if (str->string == 0)
		return ;
	copy(str, content, conv);
}

static char	*get_bed(char *content, t_conv conv, t_string *str)
{
	str->size = get_replace_size(content, conv);
	str->string = (char *) ft_strnew(str->size);
	if (str->string == 0)
		return (0);
	fill_bed(str->string, conv, str->size);
	return (str->string);
}

static int	get_replace_size(char *str, t_conv conv)
{
	int		size;

	if (conv.specifier == 'c')
		size = 1;
	else
		size = ft_strlen(str);
	if (size < conv.min_field)
		return (conv.min_field);
	return (size);
}

static char	*fill_bed(char *str, t_conv conv, int size)
{
	int		i;

	if (conv.f_zero)
	{
		i = 0;
		while (i < size)
			str[i++] = '0';
	}
	else
	{
		i = 0;
		while (i < size)
			str[i++] = ' ';
	}
	return (str);
}

static void	copy(t_string *str, const char *content, t_conv conv)
{
	size_t	size_content;
	size_t	i;
	size_t	j;

	if (conv.specifier == 'c')
		size_content = 1;
	else
		size_content = ft_strlen(content);
	j = 0;
	if (conv.f_leftjust)
	{
		while (j < str->size && j < size_content)
		{
			str->string[j] = content[j];
			j++;
		}
	}
	else
	{
		i = str->size - size_content;
		while (i < str->size && j < size_content)
			str->string[i++] = content[j++];
	}
}

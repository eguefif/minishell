/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:36:58 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:34:06 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

# define CONVSPE "cspdiuxX%"
# define FLAGS "-0"
# define MAX_FLAGS 2

int			ft_printf(const char *str, ...);

// Spliting functions in splitter.c and init_splits.c
typedef struct s_string
{
	char	*string;
	size_t	size;
}			t_string;

typedef struct s_split
{
	t_string	*list;
	int			counts;
}				t_split;

t_split		*split(const char *str);
t_split		*init_splits(const char *str);
int			get_counts(const char *str);
char		*is_convspe_end(char c);

// replace function
typedef struct s_conv
{
	char				specifier;
	int					f_leftjust;
	int					f_zero;
	int					min_field;
	int					precision;
	char				d_char;
	char				*d_str;
	int					d_nbr;
	unsigned long int	d_ptr;
	unsigned int		d_unbr;
	char				d_percentage;
	int					error;
}						t_conv;

// In same name file
int			replace_conversion(t_split *splits, va_list ap);
int			init_conversionspe(char *str, va_list ap, t_conv *conv);
void		make_int(t_conv conv, t_string *str);
void		make_char(t_conv conv, t_string *str);
void		make_str(t_conv conv, t_string *str);
void		make_percentage(t_string *str);
void		make_char(t_conv conv, t_string *str);
void		make_ptr(t_conv conv, t_string *str);
void		make_uint(t_conv conv, t_string *str);
void		make_replacement(char *content, t_conv conv, t_string *str);
// In conversion_initializer.c
char		*set_flags(t_conv *conv, char *str);
char		*set_minfield(t_conv *conv, char *str, va_list ap);
char		*set_precision(t_conv *conv, char *str, va_list ap);
char		*set_conv(t_conv *conv, char *str);
int			set_data(t_conv *conv, va_list ap);
char		*is_specifier_letter(char c);
// In conversion_initializer_utils.c
void		set_default_values(t_conv *conv);
void		check(t_conv *conv);

// display function in displayer.c
void		display(t_split *splits);

void		clean(t_split *splits);
#endif

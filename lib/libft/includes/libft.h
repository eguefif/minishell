/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:08:11 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 16:45:00 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/errno.h>

// Memory manipulation functions
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memset(void *s, int i, size_t len);
void			*ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t count, size_t size);

//String manipulation functions
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
char			*ft_strcat(char *dest, char *src);
char			*ft_strncat(char *dest, char *src, unsigned int nb);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(char *s1, char *s2, size_t n);
size_t			ft_strlcat(char *dest, char *src, size_t dstsize);
int				ft_strlen(const char *str);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_strcpy(char *s1, char *s2);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_tab(char **strs, char *sep);
char			*ft_strdup(const char *s);
char			*ft_strldup(char *line, size_t size);
char			**ft_strsplit(const char *s, char c);
void			ft_cleansplits(char **splits);
char			**ft_split(const char *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);

//Printing functions
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_putendl(char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putendl_fd(char *str, int fd);

// Nbr manipulations
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
char			*ft_itoa(int n);
int				ft_atoi(const char *s);
char			*ft_lutoa_base(unsigned long int nbr, char *base);

//is functions
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_is_strnum(char *str);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char			*get_next_line(int fd);
int				build_line(char **line, char *buffer, int size);

//  ft_printf

# define CONVSPE "cspdiuxXFf%"
# define PRECISION_DEFAULT 6
# define FLAGS "-0"
# define MAX_FLAGS 2

int				ft_printf(const char *str, ...);
int				ft_dprintf(int fd, const char *str, ...);
int				ft_sprintf(char *buffer, const char *str, ...);

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

t_split			*split(const char *str);
t_split			*init_splits(const char *str);
int				get_counts(const char *str);
char			*is_convspe_end(char c);

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
	double				d_double;
	int					error;
}						t_conv;

// In same name file
int				replace_conversion(t_split *splits, va_list ap);
int				init_conversionspe(char *str, va_list ap, t_conv *conv);
void			make_int(t_conv conv, t_string *str);
void			make_char(t_conv conv, t_string *str);
void			make_str(t_conv conv, t_string *str);
void			make_percentage(t_string *str);
void			make_char(t_conv conv, t_string *str);
void			make_ptr(t_conv conv, t_string *str);
void			make_uint(t_conv conv, t_string *str);
void			make_double(t_conv conv, t_string *str);
void			make_replacement(char *content, t_conv conv, t_string *str);
char			*make_precision(char *nbr, t_conv conv);
// In conversion_initializer.c
char			*set_flags(t_conv *conv, char *str);
char			*set_minfield(t_conv *conv, char *str, va_list ap);
char			*set_precision(t_conv *conv, char *str, va_list ap);
char			*set_conv(t_conv *conv, char *str);
int				set_data(t_conv *conv, va_list ap);
char			*is_specifier_letter(char c);
// In conversion_initializer_utils.c
void			set_default_values(t_conv *conv);
void			check(t_conv *conv);

// display function in displayer.c
void			display(int fd, t_split *splits);
void			sdisplay(char *buffer, t_split *splits);

void			clean(t_split *splits);

#endif

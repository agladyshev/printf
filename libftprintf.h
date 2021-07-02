#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
typedef struct s_flags {
	int				left_adj;
	int				zero_padded;
	int				precision;
	unsigned int	field_width;
	unsigned int	fw_init;
	int				numerical;
}	t_flags;

char	*ft_utoa_base(unsigned long long num, char *base);
int		get_flag_value(const char *str, int *i, va_list *pargs, int *flag);
int		read_flags(const char *str, int *i, t_flags *flags, va_list *pargs);
void	adjust_flags_conversion(t_flags *flags, char conversion);
int		ft_printf(const char *str, ...);
char	*hex_to_str(unsigned int arg, char conversion);
char	*ptr_to_str(va_list *pargs);
int		concat_chars_to_str(char **str, char c, int len, int left_adj);
void	insert_0_to_neg(char **str, int n);
int		apply_precision(char **str, t_flags flags);
int		apply_padding(char **str, t_flags flags);
size_t	print_str_fmt(char *str);

#endif

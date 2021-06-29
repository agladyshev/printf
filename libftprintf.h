#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
typedef struct s_flags {
	int	left_adj;
	int	zero_padded;
	int	precision;
	int	field_width;
	int	numerical;
}	t_flags;

char	*ft_utoa_base(unsigned long long num, char *base);
int	ft_printf(const char *str, ...);

#endif

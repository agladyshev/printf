#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
typedef struct s_flags {
	int	left_adj;
	int	zero_padded;
	int	precision;
	int	field_width;
}	t_flags;

int	ft_printf(const char *str, ...);

#endif

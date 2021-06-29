#include "libft/libft.h"
#include "libftprintf.h"

int	get_flag_value(const char *str, int *i, va_list *pargs, int def_value)
{
	int	num;

	// TODO error handling
	num = def_value;
	if (str[*i] == '*')
	{
		num = va_arg(*pargs, int);
		(*i)++;
	}
	else if (ft_strchr("0123456789", (int)str[*i]))
	{
		num = ft_atoi(str + *i);
		while (ft_strchr("0123456789", (int)str[*i]))
			(*i)++;
	}
	return (num);
}

void	adjust_flags_conversion(t_flags *flags, char conversion) 
{
	if (conversion == '%')
		*flags = (t_flags){0, 0, -1, -1, 0};
	else if (ft_strchr("diuoxX", (int)conversion))
	{
		flags->numerical = 1;
		if (flags->precision < 0)
			flags->precision = 1;
		else
			flags->zero_padded = 0;
	}
}

int	read_flags(const char *str, int *i, t_flags *flags, va_list *pargs)
{
	*flags = (t_flags){0, 0, -1, -1, 0};
	(*i)++;
	while (!ft_strchr("cspdiuxX%", (int)str[*i]))
	{
		if (str[*i] == '-')
			flags->left_adj = 1;
		else if (str[*i] == '0')
			flags->zero_padded = 1;
		if (ft_strchr("-0", (int)str[*i]))
			(*i)++;
		else if (str[*i] == '.')
		{
			(*i)++;
			flags->precision = get_flag_value(str, i, pargs, 0);
		}
		else if (flags->field_width < 0)
			flags->field_width = get_flag_value(str, i, pargs, -1);
		else
			(*i)++;
	}
	// TODO error handling
	return (0);
}


#include "libft/libft.h"
#include "libftprintf.h"

int	get_flag_value(const char *str, int *i, va_list *pargs, int *flag)
{
	// TODO error handling
	if (str[*i] == '*')
	{
		*flag = va_arg(*pargs, int);
		(*i)++;
		return (1);
	}
	else if (ft_strchr("0123456789", (int)str[*i]))
	{
		*flag = ft_atoi(str + *i);
		while (ft_strchr("0123456789", (int)str[*i]))
			(*i)++;
		return (1);
	}
	return (0);
}

int	get_field_width(const char *str, int *i, va_list *pargs, t_flags *flags)
{
	int 	num;
	int	res;

	num = 0;
	res = get_flag_value(str, i, pargs, &num);
	if (res)
	{
		flags->fw_init = 1;
		if (num < 0)
		{
			flags->left_adj = 1;
			return (unsigned int)(-num);
		}
		else
			return (unsigned int)(num);
	}
	return (flags->field_width);
}

void	adjust_flags_conversion(t_flags *flags, char conversion) 
{
	if (conversion == '%')
		*flags = (t_flags){0, 0, -1, 0, 0, 0};
	else if (ft_strchr("diuoxX", (int)conversion))
	{
		flags->numerical = 1;
		if (flags->precision < 0)
			flags->precision = 1;
		else
			flags->zero_padded = 0;
		if (flags->left_adj == 1)
			flags->zero_padded = 0;
	}
}

int	read_flags(const char *str, int *i, t_flags *flags, va_list *pargs)
{
	*flags = (t_flags){0, 0, -1, 0, 0, 0};
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
			flags->precision = 0;
			get_flag_value(str, i, pargs, &(flags->precision));
		}
		else if (flags->fw_init == 0 && ft_strchr("-0123456789*", (int)str[*i]))
			flags->field_width = get_field_width(str, i, pargs, flags);
		else if (str[*i] == ' ')
			ft_putchar_fd(str[(*i)++], 1);
		else
			(*i)++;
	}
	return (0);
}


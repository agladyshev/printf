#include "libftprintf.h"
#include "libft.h"

#include <stdio.h>

void	ft_print_padding(char c, int len)
{
	int	i;
	
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
}

int	ft_putarg(char *str, t_flags flags)
{
	int	len;
	int	padding_len;
	char	padding_char;
	char	*str_copy;
	
	str_copy = ft_strdup(str);
	if (!flags.numerical && flags.precision >= 0 && flags.precision <= (int)ft_strlen(str_copy))
		str_copy[flags.precision] = 0;
	padding_char = ' ';
	if (flags.zero_padded && flags.numerical)
		padding_char = '0';
	len = ft_strlen(str_copy);
	if (flags.field_width > len)
		padding_len = flags.field_width - len;
	else
		padding_len = 0;
	if (!flags.left_adj && padding_len > 0)
		ft_print_padding(padding_char, padding_len);
	ft_putstr_fd(str_copy, 1);
	if (flags.left_adj && padding_len > 0)
		ft_print_padding(padding_char, padding_len);
	len += padding_len;
	free(str_copy);
	return (len);
}

int	get_flag_value(const char *str, int *i, va_list *pargs, int def_value)
{
	int num;

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

int	read_flags(const char *str, int *i, t_flags *flags, va_list *pargs)
{
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
//	printf("?%d %d %d %d %d?", flags->left_adj, flags->zero_padded, flags->precision, flags->field_width, flags->numerical);
	// TODO error handling
	return (0);
}

int	insert_arg(const char *str, int *i, va_list *pargs)
{
	t_flags	flags;
	char	chr[2];

	flags = (t_flags) {0, 0, -1, -1, 0};
	read_flags(str, i, &flags, pargs);
	if (ft_strchr("diuxX", (int)str[*i]))
		flags.numerical = 1;
	if (str[*i] == 's')
		return (ft_putarg(va_arg(*pargs, char *), flags));
	else if (str[*i] == '%')
	{
		flags = (t_flags) {0, 0, -1, -1, 0};
		return (ft_putarg("%", flags));
	}
	else if (str[*i] == 'c')
	{
		chr[0] = va_arg(*pargs, int);
		chr[1] = 0;
		return (ft_putarg(chr, flags));
	}
	else if (str[*i] == 'd' || str[*i] == 'i')
		return (ft_putarg(ft_itoa(va_arg(*pargs, int)), flags));
	return (-1);
	//TODO error handling
}

int	ft_printf(const char *str, ...)
{
	va_list	pargs;
	int		i;
	int		ins_cnt;

	i = 0;
	ins_cnt = 0;
	va_start(pargs, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ins_cnt += insert_arg(str, &i, &pargs);
		}
		else
		{
			write(1, str + i, 1);
			ins_cnt++;
		}
		i++;
	}
	va_end(pargs);
	return (ins_cnt);
}

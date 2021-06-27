#include "libftprintf.h"
#include "./libft/libft.h"

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

	padding_char = ' ';
	if (flags.zero_padded && flags.numerical)
		padding_char = '0';
	len = ft_strlen(str);
	if (flags.field_width > len)
		padding_len = flags.field_width - len;
	else
		padding_len = 0;
	if (!flags.left_adj && padding_len > 0)
		ft_print_padding(padding_char, padding_len);
	ft_putstr_fd(str, 1);
	if (flags.left_adj && padding_len > 0)
		ft_print_padding(padding_char, padding_len);
	return (ft_strlen(str) + padding_len);
}

int	get_flag_value(const char *str, int *i, va_list *pargs)
{
	int num;

	// TODO error handling
	num = 0;
	num = ft_atoi(str + *i);
	//printf("?%d?", num);
	if (num)
		return (num);
	else if (str[*i] == '*')
		num = va_arg(*pargs, int);
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
		else if (!flags->field_width)
			flags->field_width = get_flag_value(str, i, pargs);
		else if (str[*i] == '.')
		{
			(*i)++;
			flags->precision = get_flag_value(str, i, pargs);
		}
		else
			(*i)++;

	}
	// TODO error handling
	return (0);
}

int	insert_arg(const char *str, int *i, va_list *pargs)
{
	t_flags	flags;

	flags = (t_flags) {0, 0, 0, 0, 0};
	read_flags(str, i, &flags, pargs);
	//printf("~%d %d %d %d~", flags.left_adj, flags.zero_padded, flags.field_width, flags.precision);
	if (ft_strchr("diuxX", (int)str[*i]))
		flags.numerical = 1;
	if (str[*i] == 's')
		return (ft_putarg(va_arg(*pargs, char *), flags));
	if (str[*i] == 'd' || str[*i] == 'i')
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

#include "libftprintf.h"
#include "libft.h"

#include <stdio.h>

int	concat_chars_to_str(char **str, char c, int len, int left_adj)
{
	char	*swap;
	char	*buf;

	swap = *str;
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (-1);
	ft_memset(buf, c, len);
	buf[len] = 0;
	if (left_adj)
		*str = ft_strjoin(swap, buf);
	else
		*str = ft_strjoin(buf, swap);
	free(buf);
	free(swap);
	if (!*str)
		return (-1);
	return (0);
}

int	apply_precision(char **str, t_flags flags)
{
	size_t	len;

	len = ft_strlen(*str);
	if (flags.numerical && (unsigned)flags.precision > len)
		concat_chars_to_str(str, '0', ((size_t)flags.precision - len), 0);
	else if (flags.numerical == 0 && (size_t)flags.precision < len)
		(*str)[flags.precision] = 0;
	return (0);
}

int	apply_padding(char **str, t_flags flags)
{
	char	padding_char;
	size_t	len;

	padding_char = ' ';
	if (flags.zero_padded && flags.numerical)
		padding_char = '0';
	len = ft_strlen(*str);
	if ((size_t)flags.field_width > len)
		concat_chars_to_str(str, padding_char,
			(size_t)flags.field_width - len, flags.left_adj);
	return (0);
}

size_t	print_str_formatted(char *str, t_flags flags)
{
	size_t	len;
	char	*str_copy;

	str_copy = ft_strdup(str);
	if (flags.numerical == 1 && flags.precision == 0 && str[0] == '0')
		str_copy[0] = 0;
	if (flags.precision >= 0)
		apply_precision(&str_copy, flags);
	if (flags.field_width >= 0)
		apply_padding(&str_copy, flags);
	ft_putstr_fd(str_copy, 1);
	len = ft_strlen(str_copy);
	free(str_copy);
	return (len);
}

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
//printf("?%d %d %d %d %d?\n", flags->left_adj, flags->zero_padded, flags->precision, flags->field_width, flags->numerical);
	// TODO error handling
	return (0);
}

int	print_int(va_list *pargs, t_flags flags)
{
	int		arg;
	int		res;
	char	*str;

	arg = va_arg(*pargs, int);
	str = ft_itoa(arg);
	if (!str)
		return (-1);
	res = print_str_formatted(str, flags);
	free(str);
	return (res);
}

int	print_char(va_list *pargs, t_flags flags)
{
	int		res;
	char	str[2];
	//FIXME unsigned char?
	str[0] = va_arg(*pargs, int);
	str[1] = 0;
	if (str[0] == 0)
	{
		if (flags.field_width > 1)
			res = flags.field_width;
		else
			res = 1;
		while(flags.field_width > 1 && flags.left_adj == 0)
		{
			ft_putchar_fd(' ', 1);
			flags.field_width--;
		}
		ft_putchar_fd('\0', 1);
		while(flags.field_width > 1 && flags.left_adj == 1)
		{
			ft_putchar_fd(' ', 1);
			flags.field_width--;
		}
	}
	else
		res = print_str_formatted(str, flags);
	return (res);
}

int	print_hex(va_list *pargs, t_flags flags)
{
	(void)pargs;
	(void)flags;
	return (0);
}

int	print_unsigned(va_list *pargs, t_flags flags)
{
	int		arg;
	int		res;
	char	*str;

	arg = va_arg(*pargs, int);
	str = ft_utoa(arg);
	if (!str)
		return (-1);
	res = print_str_formatted(str, flags);
	free(str);
	return (res);
}

size_t	print_arg(const char *str, int *i, va_list *pargs)
{
	t_flags	flags;

	flags = (t_flags){0, 0, -1, -1, 0};
	read_flags(str, i, &flags, pargs);
	if (ft_strchr("diuoxpX", (int)str[*i]))
	{
		flags.numerical = 1;
		if (flags.precision < 0)
			flags.precision = 1;
		if (str[*i] == 'd' || str[*i] == 'i')
			return (print_int(pargs, flags));
		else if (str[*i] == 'x' || str[*i] == 'X' || str[*i] == 'p')
			return (print_hex(pargs, flags));
		else if (str[*i] == 'u')
			return (print_unsigned(pargs, flags));
	}
	else if (str[*i] == 's')
		return (print_str_formatted(va_arg(*pargs, char *), flags));
	else if (str[*i] == '%')
		return (print_str_formatted("%", ((t_flags){0, 0, -1, -1, 0})));
	else if (str[*i] == 'c')
		return (print_char(pargs, flags));
	return (-1);
	//TODO error handling
}

int	ft_printf(const char *str, ...)
{
	va_list	pargs;
	int		i;
	size_t	printed_chars;

	i = 0;
	printed_chars = 0;
	va_start(pargs, str);
	while (str[i])
	{
		if (str[i] == '%')
			printed_chars += print_arg(str, &i, &pargs);
		else
		{
			write(1, str + i, 1);
			printed_chars++;
		}
		i++;
	}
	va_end(pargs);
	return (printed_chars);
}

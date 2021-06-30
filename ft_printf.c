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

void	insert_0_to_neg(char **str, int n)
{
	char	*swap;
	swap = *str;
	*str = ft_strdup((*str) + 1);
	concat_chars_to_str(str, '0', n, 0);
	concat_chars_to_str(str, '-', 1, 0);
	free(swap);
}

int	apply_precision(char **str, t_flags flags)
{
	size_t	len;

	len = ft_strlen(*str);
	if (flags.numerical && (unsigned)flags.precision > len)
	{
		if ((*str)[0] == '-')
			insert_0_to_neg(str, (size_t)flags.precision - len + 1);
		else
			concat_chars_to_str(str, '0', ((size_t)flags.precision - len), 0);
	}
	else if (flags.numerical == 0 && (size_t)flags.precision < len)
		(*str)[flags.precision] = 0;
	return (0);
}

int	apply_padding(char **str, t_flags flags)
{
	char	padding_char;
	size_t	len;

	len = ft_strlen(*str);
	padding_char = ' ';
	if (flags.zero_padded && flags.numerical)
		padding_char = '0';
	if (flags.fw_init && flags.field_width > len)
	{
		if (flags.numerical && flags.zero_padded && (*str)[0] == '-' && !flags.left_adj)
			insert_0_to_neg(str, flags.field_width - len);
		else
			concat_chars_to_str(str, padding_char,
				flags.field_width - len, flags.left_adj);
	}
	return (0);
}

size_t	print_str_fmt(char *str)
{
	size_t	len;

	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

char	*apply_flags(char *str, t_flags flags)
{
	if (!str)
	{
		if (flags.precision > 0 && flags.precision < 6)
			flags.precision = 0;
		str = ft_strdup("(null)");
	}
	else
		str = ft_strdup(str);
	if (flags.numerical == 1 && flags.precision == 0 && str[0] == '0')
		str[0] = 0;
	if (flags.precision >= 0)
		apply_precision(&str, flags);
	if (flags.fw_init)
		apply_padding(&str, flags);
	return (str);
}
int	print_char(va_list *pargs, t_flags flags)
{
	int		res;
	char	str[2]; //FIXME unsigned char?
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
		return (res);
	}
	else
		return(print_str_fmt(apply_flags(str, flags)));
}
size_t	print_arg(const char *str, int *i, va_list *pargs)
{
	t_flags	flags;
	char	*str_fmt;
	
	if (!read_flags(str, i, &flags, pargs))
		return (0);
	adjust_flags_conversion(&flags, str[*i]);
	if (str[*i] == 'c')
		return (print_char(pargs, flags));
	else if (str[*i] == 'p')
		str_fmt = ptr_to_str(pargs, &flags);
	else if (str[*i] == 's')
	{
		str_fmt = va_arg(*pargs, char *);
		if (str_fmt)
			str_fmt = ft_strdup(str_fmt);
	}
	else if (str[*i] == '%')
		str_fmt = ft_strdup("%"); 
	else if (str[*i] == 'd' || str[*i] == 'i')
		str_fmt = ft_itoa(va_arg(*pargs, int));
	else if (str[*i] == 'x' || str[*i] == 'X')
		str_fmt = hex_to_str(va_arg(*pargs, unsigned int), str[*i]);
	else if (str[*i] == 'u')
		str_fmt = ft_utoa_base(va_arg(*pargs, unsigned int), "0123456789");
	else if (str[*i] == 'o')
		str_fmt = ft_utoa_base(va_arg(*pargs, unsigned int), "01234567");
	return (print_str_fmt(apply_flags(str_fmt, flags)));
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
		if (str[i])
			i++;
	}
	va_end(pargs);
	return (printed_chars);
}

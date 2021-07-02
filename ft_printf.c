/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stiffiny <stiffiny@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:22:33 by stiffiny          #+#    #+#             */
/*   Updated: 2021/06/30 15:59:30 by stiffiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

char	*apply_flags(char *str, t_flags flags)
{
	if (!str)
	{
		if (flags.precision > 0 && flags.precision < 6)
			flags.precision = 0;
		str = ft_strdup("(null)");
	}
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
	int	res;
	int	arg;
	
	arg = va_arg(*pargs, int);
	if (flags.field_width > 1)
		res = flags.field_width;
	else
		res = 1;
	while (flags.field_width > 1 && flags.left_adj == 0)
	{
		ft_putchar_fd(' ', 1);
		flags.field_width--;
	}
	ft_putchar_fd((char)arg, 1);
	while (flags.field_width > 1 && flags.left_adj == 1)
	{
		ft_putchar_fd(' ', 1);
		flags.field_width--;
	}
	return (res);
}

size_t	print_arg(const char *str, int *i, va_list *pargs)
{
	t_flags	flags;
	char	*str_fmt;

	str_fmt = 0;
	if (!read_flags(str, i, &flags, pargs))
		return (0);
	adjust_flags_conversion(&flags, str[*i]);
	if (str[*i] == 'c')
		return (print_char(pargs, flags));
	else if (str[*i] == 'p')
		str_fmt = ptr_to_str(pargs);
	else if (str[*i] == 's')
		str_fmt = ft_strdup(va_arg(*pargs, char *));
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

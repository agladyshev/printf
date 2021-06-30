/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stiffiny <stiffiny@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:22:24 by stiffiny          #+#    #+#             */
/*   Updated: 2021/06/30 15:10:13 by stiffiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

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
		if (flags.numerical && flags.zero_padded
			&& (*str)[0] == '-' && !flags.left_adj)
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

	len = 0;
	if (str)
	{
		ft_putstr_fd(str, 1);
		len = ft_strlen(str);
		free(str);
	}
	return (len);
}

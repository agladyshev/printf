/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stiffiny <stiffiny@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:22:18 by stiffiny          #+#    #+#             */
/*   Updated: 2021/06/30 14:22:19 by stiffiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libftprintf.h"

char	*hex_to_str(unsigned int arg, char conversion)
{
	if (conversion == 'X')
		return (ft_utoa_base(arg, "0123456789ABCDEF"));
	else if (conversion == 'x')
		return (ft_utoa_base(arg, "0123456789abcdef"));
	else if (conversion == 'p')
		return (ft_utoa_base((unsigned long long)&arg, "0123456789abcdef"));
	return (0);
}

char	*ptr_to_str(va_list *pargs)
{
	char				*res;
	void				*ptr;
	unsigned long long	address;

	ptr = va_arg(*pargs, void *);
	if (!ptr)
		return (ft_strdup("(nil)"));
	else
	{
		address = (unsigned long long)ptr;
		ptr = ft_utoa_base(address, "0123456789abcdef");
		if (ptr)
		{
			res = ft_strjoin("0x", ptr);
			free(ptr);
			return (res);
		}
		return (ptr);
	}
}

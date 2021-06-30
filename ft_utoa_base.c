/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stiffiny <stiffiny@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:22:55 by stiffiny          #+#    #+#             */
/*   Updated: 2021/06/30 14:23:47 by stiffiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft/libft.h"

static unsigned int	get_uint_size(unsigned long long n, size_t base_n)
{
	unsigned int	size;

	size = 0;
	while (n != 0)
	{
		n /= base_n;
		size++;
	}
	if (!size)
		size = 1;
	return (size);
}

char	*ft_utoa_base(unsigned long long n, char *base)
{
	unsigned long long	size;
	char				*s;
	size_t				base_n;

	base_n = ft_strlen(base);
	size = get_uint_size(n, base_n);
	s = malloc(sizeof(char) * (size + 1));
	if (s == 0)
		return (0);
	s[size] = 0;
	if (n == 0)
		s[0] = base[n % base_n];
	while (n != 0)
	{
		s[size - 1] = base[n % base_n];
		n /= base_n;
		size--;
	}
	return (s);
}

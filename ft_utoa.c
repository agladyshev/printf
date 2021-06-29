#include "libftprintf.h"

static unsigned	get_uint_size(unsigned n)
{
	unsigned		size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_utoa(unsigned n)
{
	unsigned	size;
	char			*s;

	size = get_uint_size(n);
	s = malloc(size + 1);
	if (s == 0)
		return (0);
	s[size] = 0;
	while (n != 0)
	{
		s[size - 1] = n % 10 + 48;
		n /= 10;
		size--;
	}
	return (s);
}

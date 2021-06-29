#include "libftprintf.h"
#include "libft/libft.h"

static unsigned int	get_uint_size(unsigned int n, unsigned int base_n)
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

char	*ft_utoa_base(unsigned int n, char *base)
{
	unsigned int	size;
	char			*s;
	size_t			base_n;

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

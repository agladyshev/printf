#include <stdio.h>
#include "libftprintf.h"

int	main(void)
{
	printf("Test basic conversions\n");
	printf("OG: %s\n", "string");
	ft_printf("FT: %s\n", "string");
	return (0);
}

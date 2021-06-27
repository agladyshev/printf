#include <stdio.h>
#include "libftprintf.h"
/*
int	run_test(char *str, ...)
{
	int res;
	int ft_res;
	va_list pargs;



	ft_putstr_fd(str)
	res = printf(str, "Hello");
	ft_res = ft_printf(str, "Hello");
	if (res == ft_res)
		printf("RETURN EQUAL\n");
	else
		printf("RETURN DIFF\n");
}
*/

int	main(void)
{
	int i;

	i = 15;
	printf("Test basic conversions\n");
	if (printf("String:		|%s|\n", "Hello") != ft_printf("String ft:	|%s|\n", "Hello"))
		printf("RETURN DIFF\n");
	if (printf("Int d:		|%d|\n", i) != ft_printf("Int ft:		|%d|\n", i))
		printf("RETURN DIFF\n");
	if (printf("Int i:		|%i|\n", i) != ft_printf("Int i ft:	|%i|\n", i))
		printf("RETURN DIFF\n");
	if (printf("Char:		|%c|\n", 'A') != ft_printf("Char ft:	|%c|\n", 'A'))
		printf("RETURN DIFF\n");
	if (printf("Address:	|%p|\n", &i) != ft_printf("Address ft:	|%p|\n", &i))
		printf("RETURN DIFF\n");
	if (printf("Unsigned:	|%u|\n", (unsigned int)i) != ft_printf("Unsigned ft:	|%p|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("hex:		|%x|\n", (unsigned int)i) != ft_printf("hex ft:		|%x|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("HEX:		|%X|\n", (unsigned int)i) != ft_printf("HEX FT:		|%X|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("ESCAPE:		|%%|\n") != ft_printf("ESCAPE FT:	|%%|\n"))
		printf("RETURN DIFF\n");
	return (0);
}

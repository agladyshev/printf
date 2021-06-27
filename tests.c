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
	/*
	int i;

	i = 15;
	printf("Test basic conversions\n");
	if (printf("String:	|%s|\n", "Hello") != ft_printf("String:	|%s|\n", "Hello"))
		printf("RETURN DIFF\n");
	if (printf("Int d:	|%d|\n", i) != ft_printf("Int:	|%d|\n", i))
		printf("RETURN DIFF\n");
	if (printf("Int i:	|%i|\n", i) != ft_printf("Int i:	|%i|\n", i))
		printf("RETURN DIFF\n");
	if (printf("Char:	|%c|\n", 'A') != ft_printf("Char:	|%c|\n", 'A'))
		printf("RETURN DIFF\n");
	if (printf("Address:	|%p|\n", &i) != ft_printf("Address:	|%p|\n", &i))
		printf("RETURN DIFF\n");
	if (printf("Unsigned:	|%u|\n", (unsigned int)i) != ft_printf("Unsigned:	|%p|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("hex:	|%x|\n", (unsigned int)i) != ft_printf("hex:	|%x|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("HEX:	|%X|\n", (unsigned int)i) != ft_printf("HEX:	|%X|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("ESCAPE:	|%%|\n") != ft_printf("ESCAPE:	|%%|\n"))
		printf("RETURN DIFF\n");
	*/

	printf("Test flags INTEGER\n");
	
	int res;
	int ft_res;

	res = printf("-	|%-d|\n", 123);
	ft_res = ft_printf("-	|%-d|\n", 123);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);
	res = printf("-5	|%-5d|\n", 123);
	ft_res = ft_printf("-5	|%-5d|\n", 123);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);
	res = printf("05d	|%05d|\n", 123);
	ft_res = ft_printf("05d	|%05d|\n", 123);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);

	
	/*
	printf("-5d	|%-5d|\n", 123);
	ft_printf("-5d	|%-5d|\n", 123);
	printf("*d	|%*d|\n", 5, 123);
	ft_printf("*d	|%*d|\n", 5, 123);
	printf("5	|%5d|\n", 123);
	ft_printf("5	|%5d|\n", 123);
	printf("5.2	|%5.2d|\n", 123);
	ft_printf("5.2	|%5.2d|\n", 123);
	printf("*.*	|%*.*d|\n", 5, 2, 123);
	ft_printf("*.*	|%*.*d|\n", 5, 2, 123);
	printf("Test flags STRING\n");
	ft_printf("Test flags STRING\n");
	printf("-	|%-s|\n", "yo");
	ft_printf("-	|%-s|\n", "yo");
	printf("-5	|%-5s|\n", "yo");
	ft_printf("-5	|%-5s|\n", "yo");
	printf("*d	|%*s|\n", 5, "yo");
	ft_printf("*d	|%*s|\n", 5, "yo");
	printf("5	|%5s|\n", "yo");
	ft_printf("5	|%5s|\n", "yo");
	printf("5.2	|%5.2s|\n", "yo");
	ft_printf("5.2	|%5.2s|\n", "yo");
	printf("*.*	|%*.*s|\n", 5, 2, "yo");
	ft_printf("*.*	|%*.*s|\n", 5, 2, "yo");
	*/
	return (0);
}

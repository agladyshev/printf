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
*/#include <stddef.h>

int	main(void)
{
	int res;
	int ft_res;
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
	if (printf("Unsigned:	|%u|\n", (unsigned int)i) != ft_printf("Unsigned:	|%u|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("hex:	|%x|\n", (unsigned int)i) != ft_printf("hex:	|%x|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("HEX:	|%X|\n", (unsigned int)i) != ft_printf("HEX:	|%X|\n", (unsigned int)i))
		printf("RETURN DIFF\n");
	if (printf("ESCAPE:	|%%|\n") != ft_printf("ESCAPE:	|%%|\n"))
		printf("RETURN DIFF\n");
	printf("Test flags INTEGER\n");
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
	
	
	printf("-5d	|%-5d|\n", 123);
	ft_printf("-5d	|%-5d|\n", 123);
	printf("*d	|%*d|\n", 5, 123);
	ft_printf("*d	|%*d|\n", 5, 123);
	printf("5	|%5d|\n", 123);
	ft_printf("5	|%5d|\n", 123);
	
	printf("5.2|%5.2d|\n", 23);
	ft_printf("5.2|%5.2d|\n", 23);
	
	printf("*.*	|%*.*d|\n", 5, 2, 123);
	ft_printf("*.*	|%*.*d|\n", 5, 2, 123);
	printf("Test flags STRING\n");
	ft_printf("Test flags STRING\n");
	printf("-	|%-s|\n", "yo");
	ft_printf("-	|%-s|\n", "yo");
	printf("-5	|%-5s|\n", "yo");
	ft_printf("-5	|%-5s|\n", "yo");
	
	printf("05s	|%05s|\n", "yo");	
	ft_printf("05s	|%05s|\n", "yo");	
	printf("*d	|%*s|\n", 5, "yo");
	ft_printf("*d	|%*s|\n", 5, "yo");
	printf("5	|%5s|\n", "yo");
	ft_printf("5	|%5s|\n", "yo");
	printf("5.2|%5.2s|\n", "you");
	ft_printf("5.2|%5.2s|\n", "you");
	printf("*.*	|%*.*s|\n", 5, 2, "yo");
	ft_printf("*.*	|%*.*s|\n", 5, 2, "yo");

	printf("Test flags %%\n");
	ft_printf("Test flags %%\n");
	printf("-	|%-%|\n", "yo");
	ft_printf("-	|%-%|\n", "yo");
	printf("-5	|%-5%|\n", "yo");
	ft_printf("-5	|%-5%|\n", "yo");
	
	printf("05s	|%05%|\n", "yo");	
	ft_printf("05s	|%05%|\n", "yo");	
	printf("*d	|%*%|\n", 5, "yo");
	ft_printf("*d	|%*%|\n", 5, "yo");
	printf("5	|%5%|\n", "yo");
	ft_printf("5	|%5%|\n", "yo");
	printf("5.2	|%5.2%|\n", "yo");
	ft_printf("5.2	|%5.2%|\n", "yo");
	
	printf("*.*	|%*.*%|\n", 5, 2, "yo");
	ft_printf("*.*	|%*.*%|\n", 5, 2, "yo");
	printf("Test flags char\n");
	ft_printf("Test flags char\n");
	printf("-	|%-c|\n", 'c');
	ft_printf("-	|%-c|\n", 'c');
	printf("-5	|%-5c|\n", 'c');
	ft_printf("-5	|%-5c|\n", 'c');
	
	printf("05s	|%05c|\n", 'c');	
	ft_printf("05s	|%05c|\n", 'c');	
	printf("*d	|%*c|\n", 5, 'c');
	ft_printf("*d	|%*c|\n", 5, 'c');
	printf("5	|%5c|\n", 'c');
	ft_printf("5	|%5c|\n", 'c');
	printf("5.2	|%5.2c|\n", 'c');
	ft_printf("5.2	|%5.2c|\n", 'c');
	
	printf("*.*	|%*.*c|\n", 5, 2, 'c');
	ft_printf("*.*	|%*.*c|\n", 5, 2, 'c');
	res = printf("|%.7s|\n", "hello");
	ft_res = ft_printf("|%.7s|\n", "hello");
	printf("%d %d\n", res, ft_res);
	
	res = printf("|%.3s|\n", "hello");
	ft_res = ft_printf("|%.3s|\n", "hello");
	printf("%d %d\n", res, ft_res);

	res = printf("|%.s|\n", "hello");
	ft_res = ft_printf("|%.s|\n", "hello");
	printf("%d %d\n", res, ft_res);
	
	res = printf("|%.0s|\n", "hello");
	ft_res = ft_printf("|%.0s|\n", "hello");
	printf("%d %d\n", res, ft_res);
	
	printf("Test precision on int\n");
	res = printf(".5|%.5d|\n", 123);
	ft_res = ft_printf(".5|%.5d|\n", 123);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);
	res = printf("5.5|%5.5d|\n", 123);
	ft_res = ft_printf("5.5|%5.5d|\n", 123);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);

	res = printf(".0|%.0d|\n", 0);
	ft_res = ft_printf(".0|%.0d|\n", 0);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);

	res = printf("|%c|\n", '\0');
	ft_res = ft_printf("|%c|\n", '\0');
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);

	res = printf("|%5.5c|\n", '\0');
	ft_res = ft_printf("|%5.5c|\n", '\0');
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);

	res = printf("|hello, %s|\n", "world");
	ft_res = ft_printf("|hello, %s|\n", "world");
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);


	res = printf("|hello, %s|\n", 0);
	ft_res = ft_printf("|hello, %s|\n", 0);
	if (res != ft_res)
		printf("sys: %d, ft: %d\n", res, ft_res);


	int j;

	j = 0;

	if (printf("Address:	|%p|\n", &j) != ft_printf("Address:	|%p|\n", &j))
		printf("RETURN DIFF\n");


	j = 123;

	if (printf("Address:	|%p|\n", &j) != ft_printf("Address:	|%p|\n", &j))
		printf("RETURN DIFF\n");

	return (0);
}

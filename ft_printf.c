#include "libftprintf.h"
#include "./libft/libft.h"

int	print_s(char *str)
{
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	insert_arg(const char *str, int *i, va_list *pargs)
{
	t_flags	flags;

	flags = {0, 0, 0, 0};
	(*i)++;
	while (!ft_strchr("cspdiuxX%", (int)str[*i])) //TODO implement flags
		(*i)++;
	if (str[*i] == 's')
		return (print_s(va_arg(*pargs, char *)));
	return (-1);
	//TODO error handling
}

int	ft_printf(const char *str, ...)
{
	va_list	pargs;
	int		i;
	int		ins_cnt;

	i = 0;
	ins_cnt = 0;
	va_start(pargs, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ins_cnt += insert_arg(str, &i, &pargs);
		}
		else
		{
			write(1, str + i, 1);
			ins_cnt++;
		}
		i++;
	}
	va_end(pargs);
	return (ins_cnt);
}

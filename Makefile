# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stiffiny <stiffiny@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/30 14:39:16 by stiffiny          #+#    #+#              #
#    Updated: 2021/06/30 14:39:18 by stiffiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

LIST		=	ft_printf.c ft_utoa_base.c conversions.c\
			flags.c strings.c

LIBFT_DIR	=	./libft/

OBJS		= $(patsubst %.c,%.o,$(LIST))

OBJS_LIBFT	=	ft_putchar_fd.o ft_strlen.o ft_putstr_fd.o\
			ft_atoi.o ft_itoa.o ft_strchr.o \
			ft_strjoin.o ft_strdup.o ft_memset.o

OBJS_TEST	= $(patsubst %.c,%.o,$(LIST_TEST))

D_FILES		= $(wildcard *.d)

CC			= gcc

CFLAGS 		= -Wall -Wextra -Werror

RM			= rm -f

all	:		$(NAME)

$(NAME)	:	make-libft $(OBJS)
			ar rcs $(NAME) $(OBJS) $(addprefix $(LIBFT_DIR), $(OBJS_LIBFT))

.c.o :
	$(CC) $(CFLAGS) -I ./libft -c $< -o ${<:.c=.o} -MD

include	$(wildcard $(D_FILES))

make-libft	:
	$(MAKE) -C libft/

bonus	:

clean-libft:
	$(MAKE) fclean -C libft/

clean	:	clean-libft
			$(RM) $(OBJS) $(OBJS_TEST) $(D_FILES)

fclean	:	clean
			$(RM) $(NAME)

re	:		fclean all

.PHONY: all clean fclean re bonus test

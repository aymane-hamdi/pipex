# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 17:43:15 by ahamdi            #+#    #+#              #
#    Updated: 2024/03/19 17:32:04 by ahamdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


src  = $(wildcard ../get-next-line/*.c) $(wildcard ../libft/*.c) pipex_util2.c pipex.c pipex_util1.c
bonus_src = $(wildcard ../bonus/*.c) $(wildcard ../get-next-line/*.c)  $(wildcard ../libft/*.c) 
obj = $(src:.c=.o)
bonus_obj = $(bonus_src:.c=.o)
NAME = pipex
BONUS_NAME = pipex_bonus

all:  $(NAME)

$(NAME): $(obj)
	gcc -Wall -Wextra -Werror -o $(NAME) $(obj)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(bonus_obj)
	gcc -Wall -Wextra -Werror -o $(BONUS_NAME) $(bonus_obj)

%.o: %.c ../get-next-line/get_next_line.h ../libft/ libft.h pipex.h ../bonus/pipex_bonus.h
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(obj) $(bonus_obj)

fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean fclean re bonus bonus_re NAME BONUS_NAME
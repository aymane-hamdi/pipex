# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 17:43:15 by ahamdi            #+#    #+#              #
#    Updated: 2024/03/24 21:35:40 by ahamdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


src  =  mandatori/pipex_util2.c mandatori/pipex.c mandatori/pipex_util1.c  mandatori/pipex_util3.c
bonus_src =  bonus/fontion_herdoc.c bonus/pipex_bonus.c bonus/pipex_bonus_uil3.c  bonus/pipex_bonus_util2.c bonus/pipex_bonus_utul1.c get-next-line/get_next_line_bonus.c  \
             	get-next-line/get_next_line_utils_bonus.c  
obj = $(src:.c=.o)
bonus_obj = $(bonus_src:.c=.o)
NAME = pipex
BONUS_NAME = pipex_bonus
LIBFT = libft/libft.a

all:  $(NAME)

$(NAME): $(obj)
	$(MAKE) -C libft
	gcc -Wall -Wextra -Werror -o $(NAME) $(obj) $(LIBFT)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(bonus_obj)
	$(MAKE) -C libft
	gcc -Wall -Wextra -Werror -o $(BONUS_NAME) $(bonus_obj) $(LIBFT)

%.o: %.c get-next-line/get_next_line.h  mandatori/pipex.h bonus/pipex_bonus.h
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(obj) $(bonus_obj)

fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean fclean re bonus bonus_re NAME BONUS_NAME
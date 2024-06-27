# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 17:43:15 by ahamdi            #+#    #+#              #
#    Updated: 2024/06/27 10:48:57 by ahamdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


src  =  mandatori/pipex_util2.c mandatori/pipex.c mandatori/pipex_util1.c  mandatori/pipex_util3.c
bonus_src = bonus/herdoc_bonus.c bonus/pipex_bonus.c bonus/pipex_util1_bonus.c  bonus/pipex_util2_bonus.c bonus/pipex_util3_bonus.c getNextLine/get_next_line_bonus.c  \
             	getNextLine/get_next_line_utils_bonus.c  
obj = $(src:.c=.o)
bonus_obj = $(bonus_src:.c=.o)
NAME = pipex
BONUS_NAME = pipex_b
LIBFT = libftt_/libft.a

all:  $(NAME)

$(NAME): $(obj)
	$(MAKE) -C libftt_
	gcc -Wall -Wextra -Werror -o $(NAME) $(obj) $(LIBFT)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(bonus_obj)
	$(MAKE) -C libftt_
	gcc -Wall -Wextra -Werror -o $(BONUS_NAME) $(bonus_obj) $(LIBFT)

%.o: %.c getNextLine/get_next_line.h  mandatori/pipex.h bonus/pipex_bonus.h
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	$(MAKE) -C libftt_ clean
	rm -rf $(obj) $(bonus_obj)

fclean : clean
	$(MAKE) -C libftt_ fclean
	rm -rf $(NAME) $(BONUS_NAME)

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean fclean re bonus bonus_re NAME BONUS_NAME
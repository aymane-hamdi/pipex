/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:35:27 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/27 02:11:16 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libftt_/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_premierstr(char *str, int i);
char	*ft_desiemstr(char *s, size_t i);
char	*get_next_line(int fd);
#endif

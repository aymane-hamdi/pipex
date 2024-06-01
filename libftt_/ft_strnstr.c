/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:30:08 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/14 14:28:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	find_len;

	find_len = ft_strlen(to_find);
	if (find_len == 0)
		return ((char *)str);
	while (*str != '\0' && len >= find_len)
	{
		if (ft_strncmp(str, to_find, find_len) == 0)
		{
			return ((char *)str);
		}
		str++;
		len--;
	}
	return (NULL);
}

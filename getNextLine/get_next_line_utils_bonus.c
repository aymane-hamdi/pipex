/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:35:57 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/21 16:13:30 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_premierstr(char *s, int i)
{
	char	*res;
	int		len;

	len = 0;
	if (!s[0])
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		i++;
		len++;
	}
	if (s[i] == '\n')
		len++; 
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

char	*ft_desiemstr(char *s, size_t i)
{
	char	*r;
	size_t	j;

	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	r = malloc((ft_strlen(s) - i) + 1);
	if (!r)
	{
		free(s);
		return (NULL);
	}
	i++;
	while (s[i])
		r[j++] = s[i++];
	r[j] = '\0';
	free(s);
	return (r);
}

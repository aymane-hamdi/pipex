/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:09:05 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/21 16:14:05 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t numel, size_t size_el)
{
	size_t	size_totat ;
	void	*ma;
	size_t	i;

	i = 0;
	size_totat = numel * size_el;
	ma = malloc(size_totat);
	if (ma == NULL)
		return (NULL);
	while (i < numel)
	{
		((unsigned char *)ma)[i] = 0;
		i++;
	}
	return (ma);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:39:39 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/17 15:48:57 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	int	i;

	if (dest > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i++;
		}
	}
	return (dest);
}

void	*ft_memset(void *str, int chr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char*)str)[i] = chr;
		i++;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:32:54 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 09:39:52 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

void	*ft_memset(void *dest, int chr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char*)dest)[i] = chr;
		i++;
	}
	return (dest);
}

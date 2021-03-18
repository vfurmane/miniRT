/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:00:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 10:01:00 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

char	*ft_strrchr(const char *str, int chr)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i])
	{
		if (str[i] == (unsigned char)chr)
			ptr = (char*)&str[i];
		i++;
	}
	if ((unsigned char)chr == '\0')
		return ((char*)&str[i]);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:50:12 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 09:56:22 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		i;
	int		len;
	int		str1_len;
	char	*new_str;

	str1_len = ft_strlen(str1);
	len = str1_len + ft_strlen(str2) + 1;
	if (!(new_str = malloc(len * sizeof(*new_str))))
		return (NULL);
	i = 0;
	while (i < str1_len)
	{
		new_str[i] = str1[i];
		i++;
	}
	while (i < len)
	{
		new_str[i] = str2[i - str1_len];
		i++;
	}
	return (new_str);
}

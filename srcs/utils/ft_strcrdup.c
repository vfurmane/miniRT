/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:47:51 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 09:48:28 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

char	*ft_strcrdup(const char *str, int chr)
{
	int		str_len;
	char	*new_str;
	char	*last_chr;

	last_chr = ft_strrchr(str, chr);
	str_len = last_chr - str;
	if (!(new_str = malloc(sizeof(*new_str) * (str_len + 1))))
		return (NULL);
	new_str = ft_memcpy(new_str, str, sizeof(*new_str) * str_len);
	new_str[str_len] = '\0';
	return (new_str);
}

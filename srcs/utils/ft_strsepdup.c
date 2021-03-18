/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsepdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:02:06 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 10:02:23 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

char	*ft_strsepdup(const char *str, const char *sep)
{
	int		i;
	int		str_len;
	char	*new_str;

	str_len = 0;
	while (str[str_len] && ft_strchr(sep, str[str_len]) == NULL)
		str_len++;
	new_str = malloc(sizeof(*new_str) * (str_len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(sep, str[i]) == NULL)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[str_len] = '\0';
	return (new_str);
}

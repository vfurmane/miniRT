/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:02:58 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 11:18:18 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

int	ft_wordcount(const char *str, const char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(sep, str[i]) != NULL)
			i++;
		if (str[i])
			count++;
		else
			break ;
		while (str[i] && ft_strchr(sep, str[i]) == NULL)
			i++;
	}
	return (count);
}

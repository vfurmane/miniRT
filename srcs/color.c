/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:44:04 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 13:34:40 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_color(const char *str)
{
	int	i;
	int	nbr;
	int	color;

	i = 0;
	color = 0;
	while (i < 3)
	{
		nbr = ft_atoi(str);
		color = color << 2 * 4;
		color += nbr;
		while (*str && *str >= '0' && *str <= '9')
			str++;
		if (*str == ',')
			str++;
		i++;
	}
	return (color);
}

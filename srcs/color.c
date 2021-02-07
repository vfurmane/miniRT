/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:44:04 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/07 18:18:24 by marvin           ###   ########.fr       */
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

int			ft_color_average(int colors[16])
{
	int					i;
	unsigned long int	red;
	unsigned long int	green;
	unsigned long int	blue;

	i = 0;
	red = 0;
	green = 0;
	blue = 0;
	while (i < 16)
	{
		red += (unsigned long long int)((colors[i] & 16711680) >> 16) * (unsigned long long int)((colors[i] & 16711680) >> 16);
		green += (unsigned long long int)((colors[i] & 65280) >> 8) * (unsigned long long int)((colors[i] & 65280) >> 8);
		blue += (unsigned long long int)(colors[i] & 255) * (unsigned long long int)(colors[i] & 255);
		i++;
	}
	return ((int)(sqrt(red / 16)) << 16 | (int)(sqrt(green / 16)) << 8 | (int)sqrt(blue / 16));
}

double	ft_multiply_color(int color, double intensity)
{
	int	red;
	int	green;
	int	blue;

	blue = (color & 255) * intensity;
	green = ((color >> 8) & 255) * intensity;
	red = ((color >> 16) & 255) * intensity;
	return ((red << 16) | (green << 8) | blue);
}

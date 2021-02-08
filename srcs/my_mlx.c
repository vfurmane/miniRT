/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:03:24 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 17:42:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_put_pixel(t_data *data, int x, int y, int color, int	pixel, t_scene scene)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (i < pixel && (x + i) < scene.plan.width)
	{
		j = 0;
		while (j < pixel && (y - j) >= 0)
		{
			dest = data->addr + ((y - j) * data->line_length +
					(x + i) * (data->bits_per_pixel / 8));
			*(unsigned int*)dest = color;
			j++;
		}
		i++;
	}
}

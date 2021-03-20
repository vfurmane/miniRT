/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:03:24 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 20:05:56 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_put_pixel(t_mlx_data *data, t_pixel pixel, int pixel_size,
		t_scene scene)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (i < pixel_size && (pixel.x + i) < scene.plan.width)
	{
		j = 0;
		while (j < pixel_size && (pixel.y - j) >= 0)
		{
			dest = data->addr + ((int)(pixel.y - j) * data->line_length +
					(int)(pixel.x + i) * (data->bits_per_pixel / 8));
			*(unsigned int*)dest = pixel.color;
			j++;
		}
		i++;
	}
}

int		my_mlx_close_window(t_scene *scene)
{
	mlx_loop_end(scene->mlx);
	return (0);
}

int		my_mlx_put_scene_back(t_scene *scene)
{
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	return (0);
}

int		my_mlx_loop_hook(void *param)
{
	(void)param;
	return (0);
}

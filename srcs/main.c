/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/02 18:08:25 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_pixel		pixel;
	t_vector	origin;
	t_vector	direction;
	t_scene		*scene;
	int			pixel_size;
	int			loading;
#if MINI_RT_BONUS == 1
	int			i;
	double		aa[32] = {	-0.375,	0.375,
							-0.125,	0.375,
							0.125,	0.375,
							0.375,	0.375,
							-0.375,	0.125,
							-0.125,	0.125,
							0.125,	0.125,
							0.375,	0.125,
							-0.375,	-0.125,
							-0.125,	-0.125,
							0.125,	-0.125,
							0.375,	-0.125,
							-0.375,	-0.375,
							-0.125,	-0.375,
							0.125,	-0.375,
							0.375,	-0.375
	};
	int			colors[16];
#endif

	scene = malloc(sizeof(*scene)); /* free this one if error */
	if (scene == NULL)
		return (1);
	if (ft_parameters(argc, argv, scene) == -1)
	{
		ft_free_scene(&scene);
		return (1);
	}
	scene->inter_min = 1;
	scene->inter_max = -1;
	scene->plan.distance = 1;
	scene->plan.viewport = 1;
	scene->mlx = mlx_init();
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	pixel.x = -scene->plan.width / 2;
	scene->img.img = mlx_new_image(scene->mlx, scene->plan.width, scene->plan.height);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	pixel_size = 1;
	(void)loading;
	loading = 10;
	while (pixel.x <= scene->plan.width / 2)
	{
		pixel.y = -scene->plan.height / 2 + 1;
		while (pixel.y <= scene->plan.height / 2)
		{
#if MINI_RT_BONUS == 1
			if (((pixel.x + scene->plan.width / 2) * scene->plan.height + pixel.y) / (scene->plan.width * scene->plan.height) * 100 >= loading)
			{
				printf("Loading... %d%%\n", loading);
				loading += 10;
			}
			pixel.color = 0;
			i = 0;
			while (i < 16)
			{
				direction = ft_canvas_to_viewport_aa(pixel, scene->plan.viewport,
						scene->plan, &aa[i]);
				colors[i] = ft_trace_ray(origin, direction, *scene);
				i++;
			}
			pixel.color = ft_color_average(colors);
#else
			direction = ft_canvas_to_viewport(pixel, scene->plan.viewport,
					scene->plan);
			pixel.color = ft_trace_ray(origin, direction, *scene);
#endif
			my_mlx_put_pixel(&scene->img, ft_translate_pixel(pixel, scene->plan),
					pixel_size, *scene);
			pixel.y += pixel_size;
		}
		pixel.x += pixel_size;
	}
	scene->win = mlx_new_window(scene->mlx, scene->plan.width, scene->plan.height, "miniRT");
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
	my_mlx_events(scene);
	mlx_loop(scene->mlx);
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	ft_free_scene(&scene);
	return (0);
}

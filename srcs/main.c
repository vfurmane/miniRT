/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/06 11:42:45 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_pixel		pixel;
	t_vector	origin; /* ===== DELETE ===== */
	t_vector	direction;
	t_scene		*scene;
	t_data		*img;
	int			pixel_size;
	int			loading;
	t_camera	*camera;
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
	pixel_size = 1;
	camera = scene->cameras;
	while (camera != NULL)
	{
		img = malloc(sizeof(*img));
		if (img == NULL)
			ft_fatal_error("Malloc");
		origin = camera->center;
		img->next = NULL;
		img->img = mlx_new_image(scene->mlx, scene->plan.width, scene->plan.height);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
				&img->endian);
		(void)loading; /* GCC doesn't like that one, find a better way to declare it, maybe not in bonus */
		loading = 10;
		pixel.x = -scene->plan.width / 2;
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
						scene->plan, camera->direction);
				pixel.color = ft_trace_ray(origin, direction, *scene);
#endif
				my_mlx_put_pixel(img, ft_translate_pixel(pixel, scene->plan),
						pixel_size, *scene);
				pixel.y += pixel_size;
			}
			pixel.x += pixel_size;
		}
		ft_lstadd_front((void**)(&scene->img), (void*)(img));
		camera = camera->next;
	}
	img = scene->img;
	while (img->next != NULL)
		img = img->next;
	img->next = scene->img;
	scene->win = mlx_new_window(scene->mlx, scene->plan.width, scene->plan.height, "miniRT");
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	my_mlx_events(scene);
	mlx_loop(scene->mlx);
	img = scene->img;
	camera = scene->cameras;
	while (camera != NULL)
	{
		mlx_destroy_image(scene->mlx, img->img);
		camera = camera->next;
		if (camera != NULL)
			img	= img->next;
	}
	img->next = NULL;
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	ft_free_scene(&scene);
	return (0);
}

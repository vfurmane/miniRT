/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/13 21:39:23 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_pixel		pixel;
	t_vector	direction;
	t_scene		*scene;
	t_data		*img;
	int			loading;
	int			fd;
	int			end_of_line;
	int			camerano;
	t_buffer	buffer;
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

	if (ft_initialize_scene(&scene, argc, argv) == NULL)
		return (1);
	fd = -1;
	end_of_line = 4 - (scene->plan.width * 3) % 4;
	camera = scene->cameras;
	camerano = -1;
	if (camera->next != NULL)
		camerano = ft_lstsize(camera) - 1;
	while (camera != NULL)
	{
		if (ft_strcmp("--save", argv[2]) == 0)
			fd = ft_initialize_bmp_file(scene, &buffer, argv[1], camerano--);
		img = ft_initialize_mlx_img(scene);
		scene->plan.viewport = tan((camera->fov * M_PI / 180) / 2);
		ft_calculate_camera_rotation(camera);
		(void)loading; /* GCC doesn't like that one, find a better way to declare it, maybe not in bonus */
		loading = 10;
		pixel.y = -scene->plan.height / 2;
		while (pixel.y <= scene->plan.height / 2 - (scene->plan.height % 2 == 0))
		{
			pixel.x = -scene->plan.width / 2;
			while (pixel.x <= scene->plan.width / 2 - (scene->plan.height % 2 == 0))
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
					colors[i] = ft_trace_ray(camera->center, direction, *scene);
					i++;
				}
				pixel.color = ft_color_average(colors);
#else
				direction = ft_canvas_to_viewport(pixel, scene->plan.viewport,
						scene->plan, camera);
				pixel.color = ft_trace_ray(camera->center, direction, *scene);
#endif
				if (fd == -1)
					my_mlx_put_pixel(img, ft_translate_pixel(pixel, scene->plan),
							camera->pixel_size, *scene);
				else
					ft_add_pixel_to_bmp(&buffer, pixel.color, (pixel.x == scene->plan.width / 2) * end_of_line);
				pixel.x += camera->pixel_size;
			}
			pixel.y += camera->pixel_size;
		}
		ft_lstadd_front((void**)(&scene->img), (void*)(img));
		camera = camera->next;
		write(fd, buffer.str, 3 * scene->plan.width * scene->plan.height);
		if (fd != -1)
		{
			free(buffer.str);
			close(fd);
		}
	}
	if (fd == -1)
	{
		img = scene->img;
		while (img->next != NULL)
			img = img->next;
		img->next = scene->img;
		scene->win = mlx_new_window(scene->mlx, scene->plan.width, scene->plan.height, scene->title);
		mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
		my_mlx_events(scene);
		mlx_loop(scene->mlx);
	}
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
	if (fd == -1)
		mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	ft_free_scene(&scene);
	return (0);
}

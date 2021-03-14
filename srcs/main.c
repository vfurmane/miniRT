/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/14 09:52:07 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_scene		*scene;
	t_data		*img;
	int			camerano;
	t_buffer	buffer;
	t_camera	*camera;

	if (ft_initialize_scene(&scene, argc, argv) == NULL)
		return (1);
	buffer.fd = -1;
	camera = scene->cameras;
	camerano = -1;
	if (camera->next != NULL)
		camerano = ft_lstsize(camera) - 1;
	while (camera != NULL)
	{
		if (ft_strcmp("--save", argv[2]) == 0)
			buffer.fd = ft_initialize_bmp_file(scene, &buffer, argv[1], camerano--);
		img = ft_initialize_mlx_img(scene);
		scene->plan.viewport = tan((camera->fov * M_PI / 180) / 2);
		ft_calculate_camera_rotation(camera);
		ft_render_scene(scene, camera, &buffer, img);
		ft_lstadd_front((void**)(&scene->img), (void*)(img));
		camera = camera->next;
		write(buffer.fd, buffer.str, 3 * scene->plan.width * scene->plan.height);
		if (buffer.fd != -1)
		{
			free(buffer.str);
			close(buffer.fd);
		}
	}
	if (buffer.fd == -1)
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
	if (buffer.fd == -1)
		mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	ft_free_scene(&scene);
	return (0);
}

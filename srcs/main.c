/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/14 19:47:54 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_scene		*scene;
	t_data		*img;
	t_buffer	buffer;
	t_camera	*camera;

	if (ft_initialize_scene(&scene, argc, argv) == NULL)
		return (1);
	buffer.fd = -1;
	ft_proceed_all_cameras(scene, &buffer, argv);
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

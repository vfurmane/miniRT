/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:37:32 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/16 15:35:53 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_proceed_all_cameras(t_scene *scene, t_buffer *buffer, char **argv)
{
	int			camerano;
	t_data		*img;
	t_camera	*camera;

	camerano = -1;
	camera = scene->cameras;
	if (camera->next != NULL)
		camerano = ft_lstsize(camera) - 1;
	while (camera != NULL)
	{
		if (scene->mlx == NULL)
		{
			buffer->fd = ft_initialize_bmp_file(scene, buffer, argv[1], camerano--);
			if (buffer->fd == -1)
				return (0);
		}
		else
		{
			img = ft_initialize_mlx_img(scene);
			if (img == NULL)
				return (0);
		}
		ft_calculate_camera_rotation_and_fov(scene, camera);
		if (ft_render_scene(scene, camera, buffer, img) == 0)
			return (0);
		camera = camera->next;
		if (scene->mlx == NULL)
		{
			write(buffer->fd, buffer->str, 3 * scene->plan.width * scene->plan.height);
			free(buffer->str);
			close(buffer->fd);
		}
		else
			ft_lstadd_front((void**)(&scene->img), (void*)(img));
	}
	return (1);
}

void	ft_proceed_window(t_scene *scene)
{
	t_data	*img;

	img = scene->img;
	while (img->next != NULL)
		img = img->next;
	img->next = scene->img;
	scene->win = mlx_new_window(scene->mlx, scene->plan.width, scene->plan.height, scene->title);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	my_mlx_events(scene);
	mlx_loop(scene->mlx);
}

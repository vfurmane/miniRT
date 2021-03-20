/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:23:09 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/21 19:25:28 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_proceed_recipient(t_scene *scene, t_buffer *buffer, char **argv,
		t_mlx_data **img)
{
	if (scene->mlx == NULL)
	{
		buffer->fd = ft_initialize_bmp_file(scene, buffer, argv[1],
				buffer->bufferno--);
		if (buffer->fd == -1)
			return (0);
	}
	else
	{
		*img = ft_initialize_mlx_img(scene);
		if (*img == NULL)
			return (0);
	}
	return (1);
}

void	ft_proceed_result(t_scene *scene, t_buffer *buffer, t_mlx_data *img)
{
	if (scene->mlx == NULL)
	{
		write(buffer->fd, buffer->str, 3 * scene->plan.width *
				scene->plan.height);
		free(buffer->str);
		close(buffer->fd);
	}
	else
		ft_lstadd_front((void**)(&scene->img), (void*)(img));
}

int		ft_proceed_all_cameras(t_scene *scene, t_buffer *buffer, char **argv)
{
	t_camera	*camera;
	t_mlx_data	*img;

	buffer->bufferno = -1;
	camera = scene->cameras;
	if (camera->next != NULL)
		buffer->bufferno = ft_lstsize(camera) - 1;
	while (camera != NULL)
	{
		if (ft_proceed_recipient(scene, buffer, argv, &img) == 0)
			return (0);
		ft_calculate_camera_rotation_and_fov(scene, camera);
		if (ft_render_scene(scene, camera, buffer, img) == 0)
			return (0);
		if (camera->next == NULL)
			scene->current_camera = camera;
		camera = camera->next;
		ft_proceed_result(scene, buffer, img);
	}
	return (1);
}

void	ft_proceed_window(t_scene *scene)
{
	t_mlx_data	*img;

	img = scene->img;
	while (img->next != NULL)
		img = img->next;
	img->next = scene->img;
	scene->win = mlx_new_window(scene->mlx, scene->plan.width,
			scene->plan.height, scene->title);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	my_mlx_events(scene);
	mlx_loop(scene->mlx);
}

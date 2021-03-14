/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:37:32 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/14 19:49:51 by vfurmane         ###   ########.fr       */
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
		if (ft_strcmp("--save", argv[2]) == 0)
			buffer->fd = ft_initialize_bmp_file(scene, buffer, argv[1], camerano--);
		img = ft_initialize_mlx_img(scene);
		ft_calculate_camera_rotation_and_fov(scene, camera);
		if (ft_render_scene(scene, camera, buffer, img) == 0)
			ft_fatal_error("Render scene"); /* ===== DELETE ===== */
		ft_lstadd_front((void**)(&scene->img), (void*)(img));
		camera = camera->next;
		if (buffer->fd != -1)
		{
			write(buffer->fd, buffer->str, 3 * scene->plan.width * scene->plan.height);
			free(buffer->str);
			close(buffer->fd);
		}
	}
	return (1);
}

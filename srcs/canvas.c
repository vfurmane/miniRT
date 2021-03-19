/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:31:03 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 11:48:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		ft_calculate_camera_rotation_and_fov(t_scene *scene,
				t_camera *camera)
{
	t_vector	tmp;

	camera->forward = ft_normalize_vector(camera->direction);
	if (camera->forward.x == 0 && camera->forward.y != 0
			&& camera->forward.z == 0)
	{
		camera->right.x = 1 - 2 * (camera->forward.y < 0);
		camera->right.y = 0;
		camera->right.z = 0;
		camera->up.x = 0;
		camera->up.y = 0;
		camera->up.z = -1 + 2 * (camera->forward.y < 0);
	}
	else
	{
		tmp.x = 0;
		tmp.y = 1;
		tmp.z = 0;
		camera->right = ft_cross_product(tmp, camera->forward);
		camera->up = ft_cross_product(camera->forward, camera->right);
	}
	ft_invert_camera_matrix(&camera->right, &camera->up, &camera->forward);
	scene->plan.viewport = tan((camera->fov * M_PI / 180) / 2);
}

void		ft_cam_to_world(t_vector *direction, t_camera *camera)
{
	t_vector	direction_copy;

	direction_copy.x = camera->right.x * direction->x +
						camera->right.y * direction->y +
						camera->right.z * direction->z;
	direction_copy.y = camera->up.x * direction->x +
						camera->up.y * direction->y +
						camera->up.z * direction->z;
	direction_copy.z = camera->forward.x * direction->x +
						camera->forward.y * direction->y +
						camera->forward.z * direction->z;
	direction->x = direction_copy.x;
	direction->y = direction_copy.y;
	direction->z = direction_copy.z;
}

t_vector	ft_canvas_to_viewport(t_pixel *pixel, t_plan *canvas,
				t_camera *camera, int i)
{
	t_vector	direction;

	direction.x = (pixel->x + camera->anti_aliasing_matrix[i]) *
					canvas->viewport / canvas->width;
	direction.y = (pixel->y + camera->anti_aliasing_matrix[i + 1]) *
					canvas->viewport / canvas->width;
	direction.z = (double)canvas->distance;
	ft_cam_to_world(&direction, camera);
	return (direction);
}

t_pixel		ft_translate_pixel(t_pixel pixel, t_plan plan)
{
	t_pixel	new_pixel;

	new_pixel.x = pixel.x + plan.width / 2;
	new_pixel.y = -pixel.y + plan.height / 2;
	new_pixel.color = pixel.color;
	return (new_pixel);
}

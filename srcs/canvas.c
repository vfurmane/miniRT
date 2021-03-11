/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:31:03 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/11 09:36:56 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_calculate_camera_rotation(t_camera *camera)
{
	t_vector	tmp;

	camera->forward = ft_normalize_vector(camera->direction);
	if (camera->forward.x == 0 && camera->forward.y != 0 && camera->forward.z == 0)
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
}

void	ft_cam_to_world(t_vector *direction, t_camera *camera)
{
	t_vector	direction_copy;

	direction_copy.x = camera->right.x * direction->x + camera->right.y * direction->y + camera->right.z * direction->z;
	direction_copy.y = camera->up.x * direction->x + camera->up.y * direction->y + camera->up.z * direction->z;
	direction_copy.z = camera->forward.x * direction->x + camera->forward.y * direction->y + camera->forward.z * direction->z;
	direction->x = direction_copy.x;
	direction->y = direction_copy.y;
	direction->z = direction_copy.z;
}

t_vector	ft_canvas_to_viewport_aa(t_pixel pixel, double viewport, t_plan canvas,
		double *aa)
{
	double		d_viewport;
	double		d_width;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	direction.x = (pixel.x + aa[0]) * d_viewport / d_width;
	direction.y = (pixel.y + aa[1]) * d_viewport / d_width;
	direction.z = (double)canvas.distance;
	return (direction);
}

t_vector	ft_canvas_to_viewport(t_pixel pixel, double viewport, t_plan canvas, t_camera *camera)
{
	double		d_viewport;
	double		d_width;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	direction.x = pixel.x * d_viewport / d_width;
	direction.y = pixel.y * d_viewport / d_width;
	direction.z = (double)canvas.distance;
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

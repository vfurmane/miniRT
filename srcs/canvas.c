/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:31:03 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/09 12:33:32 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_cam_to_world(t_vector direction, t_vector cam_direction)
{
	t_vector	direction_copy;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	t_vector	tmp;

	forward = ft_normalize_vector(cam_direction);
	if (cam_direction.x == 0 && cam_direction.y == 1 && cam_direction.z == 0)
	{
		right.x = 1;
		right.y = 0;
		right.z = 0;
		up.x = 0;
		up.y = 0;
		up.z = -1;
	}
	else
	{
		tmp.x = 0;
		tmp.y = 1;
		tmp.z = 0;
		right = ft_cross_product(tmp, forward);
		up = ft_cross_product(forward, right);
	}
	direction_copy.x = right.x * direction.x + right.y * direction.y + right.z * direction.z;
	direction_copy.y = up.x * direction.x + up.y * direction.y + up.z * direction.z;
	direction_copy.z = forward.x * direction.x + forward.y * direction.y + forward.z * direction.z;
	return (direction_copy);
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

t_vector	ft_canvas_to_viewport(t_pixel pixel, double viewport, t_plan canvas, t_vector cam_direction)
{
	double		d_viewport;
	double		d_width;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	direction.x = pixel.x * d_viewport / d_width;
	direction.y = pixel.y * d_viewport / d_width;
	direction.z = (double)canvas.distance;
	direction = ft_cam_to_world(direction, cam_direction);
	return (direction);
}

t_pixel		ft_translate_pixel(t_pixel pixel, t_plan plan)
{
	static t_pixel	new_pixel;

	new_pixel.x = pixel.x + plan.width / 2;
	new_pixel.y = -pixel.y + plan.height / 2;
	new_pixel.color = pixel.color;
	return (new_pixel);
}

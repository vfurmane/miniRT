/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:31:03 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 21:42:17 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_canvas_to_viewport_aa(t_pixel pixel, int viewport, t_plan canvas,
		double *aa)
{
	double		d_viewport;
	double		d_width;
	double		d_height;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	d_height = (double)canvas.height;
	direction.x = (pixel.x + aa[0]) * d_viewport / d_width;
	direction.y = (pixel.y + aa[1]) * d_viewport / d_width;
	direction.z = (double)canvas.distance;
	return (direction);
}

t_vector	ft_canvas_to_viewport(t_pixel pixel, int viewport, t_plan canvas)
{
	double		d_viewport;
	double		d_width;
	double		d_height;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	d_height = (double)canvas.height;
	direction.x = pixel.x * d_viewport / d_width;
	direction.y = pixel.y * d_viewport / d_width;
	direction.z = (double)canvas.distance;
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

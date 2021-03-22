/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:17:24 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/22 16:54:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_square(t_ray *ray,
		t_square *square, double t[2])
{
	t_vector	ct;
	t_vector	right;
	t_vector	down;
	double		p1;
	double		p2;

	ft_intersect_ray_plane(ray, (t_plane*)square, t);
	ct = ft_add_vectors(ray->origin,
			ft_substract_vectors(ft_multiply_vector_double(ray->direction,
			t[0]), square->center));
	right.x = square->width;
	right.y = 0;
	right.z = 0;
	down.x = 0;
	down.y = square->width;
	down.z = 0;
	p1 = ft_dot_product(ct, right) / square->width;
	p2 = ft_dot_product(ct, down) / square->width;
	if ((p1 < square->width / 2.0 && p1 > -square->width / 2.0) &&
			(p2 < square->width / 2.0 && p2 > -square->width / 2.0) &&
			fabs(ct.x) <= square->width && fabs(ct.y) <= square->width &&
			fabs(ct.z) <= square->width)
		return ;
	t[0] = -1;
	t[1] = -1;
}

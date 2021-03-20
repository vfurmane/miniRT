/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 09:40:19 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 11:47:17 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_triangle(t_ray *ray,
		t_triangle *triangle, double t[2])
{
	t_vector	h, s, q;
	double		a, f, u, v;

	t[0] = -1;
	t[1] = -1;
	h = ft_cross_product(ray->direction, triangle->edge2);
	a = ft_dot_product(triangle->edge1, h);
	f = 1 / a;
	s = ft_substract_vectors(ray->origin, triangle->point1);
	u = f * ft_dot_product(s, h);
	if (u < 0 || u > 1)
		return ;
	q = ft_cross_product(s, triangle->edge1);
	v = f * ft_dot_product(ray->direction, q);
	if (v < 0 || u + v > 1)
		return ;
	t[0] = f * ft_dot_product(triangle->edge2, q);
	t[1] = t[0];
}

void			ft_precalculate_triangle(t_triangle *triangle)
{
	triangle->edge1 = ft_substract_vectors(triangle->point2, triangle->point1);
	triangle->edge2 = ft_substract_vectors(triangle->point3, triangle->point1);
	triangle->normal = ft_cross_product(triangle->edge1, triangle->edge2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:05:19 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 10:11:03 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_sphere(t_ray *ray,
		t_sphere *sphere, double t[2])
{
	double		radius;
	double		k[3];
	t_vector	oc;
	t_vector	center;

	center = sphere->center;
	radius = sphere->radius;
	oc = ft_substract_vectors(ray->origin, center);
	k[0] = ft_dot_product(ray->direction, ray->direction);
	k[1] = 2 * ft_dot_product(oc, ray->direction);
	k[2] = ft_dot_product(oc, oc) - radius * radius;
	if (ft_calculate_intersections(k, t))
		return ;
}

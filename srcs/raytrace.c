/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/02 19:14:56 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_sphere(t_vector origin, t_vector direction,
		t_sphere sphere, double t[2])
{
	int			radius;
	int			discriminant;
	double		k[3];
	t_vector	oc;
	t_vector	center;

	center = sphere.vector;
	radius = sphere.radius;
	oc = ft_substract_vector(origin, center);
	k[0] = ft_dot_product(direction, direction);
	k[1] = 2 * ft_dot_product(oc, direction);
	k[2] = ft_dot_product(oc, oc) - sphere.radius * sphere.radius;
	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0)
	{
		t[0] = -1;
		t[1] = -1;
	}
	else
	{
		t[0] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
		t[1] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
	}
}

int		ft_trace_ray(t_vector origin, t_vector direction, int t_min, int t_max)
{
	int			closest_t;
	int			sphere_color;
	double		t[2];
	t_sphere	sphere;

	sphere_color = -1;
	sphere.vector.x = -2;
	sphere.vector.y = -2;
	sphere.vector.z = 4;
	sphere.radius = 1;
	sphere.color = 0x0000FF00;
	ft_intersect_ray_sphere(origin, direction, sphere, t);
	if (t[0] >= t_min && (t[0] <= t_max || t_max == -1))
	{
		closest_t = t[0];
		sphere_color = sphere.color;
	}
	if (t[1] >= t_min && (t[1] <= t_max || t_max == -1) && t[1] < closest_t)
	{
		closest_t = t[0];
		sphere_color = sphere.color;
	}
	if (sphere_color == -1)
		return (0x00FFFFFF);
	return (sphere_color);
}

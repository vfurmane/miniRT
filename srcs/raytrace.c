/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 18:01:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_sphere(t_vector origin, t_vector direction,
		t_sphere *sphere, double t[2])
{
	int			radius;
	double		discriminant;
	double		k[3];
	t_vector	oc;
	t_vector	center;

	center = sphere->center;
	radius = sphere->radius;
	oc = ft_substract_vectors(origin, center);
	k[0] = ft_dot_product(direction, direction);
	k[1] = 2 * ft_dot_product(oc, direction);
	k[2] = ft_dot_product(oc, oc) - radius * radius;
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

double	ft_compute_lighting(t_vector point, t_sphere *sphere, t_scene scene)
{
	int			i;
	double		normal_len;
	double		intensity;
	double		n_dot_l;
	t_vector	normal;
	t_vector	light_ray;
	t_bulb		*bulb;

	i = 0;
	intensity = scene.ambiant.intensity;
	bulb = scene.bulbs;
	while (bulb != NULL)
	{
		normal = ft_substract_vectors(point, sphere->center);
		normal_len = ft_vector_length(normal);
		normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
		light_ray = ft_substract_vectors(bulb->center, point);
		n_dot_l = ft_dot_product(normal, light_ray);
		if (n_dot_l > 0)
			intensity += bulb->light.intensity * n_dot_l / (normal_len * ft_vector_length(light_ray));
		bulb = bulb->next;
	}
	if (intensity > 1)
		intensity = 1;
	return (intensity);
}

int		ft_trace_ray(t_vector origin, t_vector direction, t_scene scene)
{
	double		closest_inter;
	double		inter[2];
	t_vector	point;
	t_sphere	*sphere;
	t_sphere	*closest_sphere;

	closest_sphere = NULL;
	closest_inter = -1;
	sphere = scene.spheres;
	while (sphere != NULL)
	{
		ft_intersect_ray_sphere(origin, direction, sphere, inter);
		if (inter[0] >= scene.inter_min && (inter[0] <= scene.inter_max || scene.inter_max == -1) && (inter[0] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[0];
			closest_sphere = sphere;
		}
		if (inter[1] >= scene.inter_min && (inter[1] <= scene.inter_max || scene.inter_max == -1) && (inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			closest_sphere = sphere;
		}
		sphere = sphere->next;
	}
	if (closest_sphere == NULL)
		return (ft_multiply_color(0x00FFFFFF, scene.ambiant.intensity));
	point = ft_add_vectors(origin, ft_multiply_vector_double(direction, closest_inter));
	return (ft_multiply_color(closest_sphere->color, ft_compute_lighting(point, closest_sphere, scene)));
}

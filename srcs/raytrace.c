/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/04 19:37:17 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_sphere(t_vector origin, t_vector direction,
		t_sphere sphere, double t[2])
{
	int			radius;
	double		discriminant;
	double		k[3];
	t_vector	oc;
	t_vector	center;

	center = sphere.vector;
	radius = sphere.radius;
	oc = ft_substract_vectors(origin, center);
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

double	ft_compute_lighting(t_vector point, t_sphere sphere, t_light lights[3])
{
	int			i;
	double		normal_len;
	double		intensity;
	double		n_dot_l;
	t_vector	normal;
	t_vector	light_ray;

	i = 0;
	intensity = 0;
	while (i < 3)
	{
		if (lights[i].type == AMBIANT)
			intensity += lights[i].intensity;
		else if (lights[i].type == POINT)
		{
			normal = ft_substract_vectors(point, sphere.vector);
			normal_len = ft_vector_length(normal);
			normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
			light_ray = ft_substract_vectors(lights[i].vector, point);
			n_dot_l = ft_dot_product(normal, light_ray);
			if (n_dot_l > 0)
				intensity += lights[i].intensity * n_dot_l / (normal_len * ft_vector_length(light_ray));
		}
		i++;
	}
	if (intensity > 1)
		intensity = 1;
	return (intensity);
}

double	ft_multiply_color(int color, double intensity)
{
	int	red;
	int	green;
	int	blue;

	blue = (color & 255) * intensity;
	green = ((color >> 8) & 255) * intensity;
	red = ((color >> 16) & 255) * intensity;
	return ((red << 16) | (green << 8) | blue);
}

int		ft_trace_ray(t_vector origin, t_vector direction, int t_min, int t_max)
{
	int			i;
	double		closest_t;
	double		t[2];
	t_vector	point;
	t_sphere	spheres[3];
	t_sphere	closest_sphere;
	t_light		lights[3];

	closest_sphere.color = -1;
	spheres[0].vector.x = 0;
	spheres[0].vector.y = -5001;
	spheres[0].vector.z = 0;
	spheres[0].radius = 5000;
	spheres[0].color = 0x0000FF00;
	spheres[1].vector.x = -1;
	spheres[1].vector.y = -1;
	spheres[1].vector.z = 15;
	spheres[1].radius = 5;
	spheres[1].color = 0x00FFAA88;
	spheres[2].vector.x = 3;
	spheres[2].vector.y = 1;
	spheres[2].vector.z = 3;
	spheres[2].radius = 2;
	spheres[2].color = 0x00FECDBA;
	lights[0].type = AMBIANT;
	lights[0].intensity = 0.7;
	lights[1].type = POINT;
	lights[1].intensity = 0.5;
	lights[1].vector.x = 0;
	lights[1].vector.y = 3;
	lights[2].vector.z = 0;
	lights[2].type = POINT;
	lights[2].intensity = 0.3;
	lights[2].vector.x = 2;
	lights[2].vector.y = 2;
	lights[2].vector.z = 6;
	i = 0;
	closest_t = -1;
	while (i < 3)
	{
		ft_intersect_ray_sphere(origin, direction, spheres[i], t);
		if (t[0] >= t_min && (t[0] <= t_max || t_max == -1) && (t[0] < closest_t || closest_t == -1))
		{
			closest_t = t[0];
			closest_sphere = spheres[i];
		}
		if (t[1] >= t_min && (t[1] <= t_max || t_max == -1) && (t[1] < closest_t || closest_t == -1))
		{
			closest_t = t[1];
			closest_sphere = spheres[i];
		}
		i++;
	}
	if (closest_sphere.color == -1)
		return (ft_multiply_color(0x00FFFFFF, lights[0].intensity));
	point = ft_add_vectors(origin, ft_multiply_vector_double(direction, closest_t));
	return (ft_multiply_color(closest_sphere.color, ft_compute_lighting(point, closest_sphere, lights)));
}

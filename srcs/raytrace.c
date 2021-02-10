/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/10 19:56:10 by vfurmane         ###   ########.fr       */
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

void	ft_intersect_ray_cylinder(t_vector origin, t_vector direction,
		t_cylinder *cylinder, double t[2])
{
	int			radius;
	double		discriminant;
	double		k[3];
	t_vector	oc;
	t_vector	center;
	
	center = cylinder->center;
	radius = cylinder->radius;
	oc = ft_substract_vectors(origin, center);
	k[0] = ft_dot_product(ft_substract_vectors(direction, ft_multiply_vector_double(cylinder->direction, ft_dot_product(direction, cylinder->direction))), ft_substract_vectors(direction, ft_multiply_vector_double(cylinder->direction, ft_dot_product(direction, cylinder->direction))));
	k[1] = 2 * ft_dot_product(ft_substract_vectors(direction, ft_multiply_vector_double(cylinder->direction, ft_dot_product(direction, cylinder->direction))), ft_substract_vectors(oc, ft_multiply_vector_double(cylinder->direction, ft_dot_product(oc, cylinder->direction))));
	k[2] = ft_dot_product(ft_substract_vectors(oc, ft_multiply_vector_double(cylinder->direction, ft_dot_product(oc, cylinder->direction))), ft_substract_vectors(oc, ft_multiply_vector_double(cylinder->direction, ft_dot_product(oc, cylinder->direction)))) - radius * radius;
	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0 || (ft_dot_product(cylinder->direction, ft_substract_vectors(direction, cylinder->center)) <= 0 || ft_dot_product(cylinder->direction, ft_substract_vectors(direction, ft_add_vectors(cylinder->center, ft_multiply_vector_double(cylinder->direction, cylinder->height)))) >= 0))
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

double	ft_compute_lighting(t_vector point, t_obj obj, t_scene scene)
{
	double		normal_len;
	double		n_dot_l;
	t_vector	normal;
	t_vector	light_ray;
	t_bulb		*bulb;

	bulb = scene.bulbs;
	while (bulb != NULL)
	{
		if (obj.type == SPHERE)
		{
			normal = ft_substract_vectors(point, ((t_sphere*)obj.ptr)->center);
			normal_len = ft_vector_length(normal);
			normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
		}
		else if (obj.type == CYLINDER)
		{
			normal = ft_substract_vectors(point, ft_add_vectors(((t_cylinder*)obj.ptr)->center, ft_multiply_vector_double(((t_cylinder*)obj.ptr)->direction, ft_dot_product(ft_substract_vectors(point, ((t_cylinder*)obj.ptr)->center), ((t_cylinder*)obj.ptr)->direction))));
			normal_len = ft_vector_length(normal);
			normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
		}
		light_ray = ft_substract_vectors(bulb->center, point);
		n_dot_l = ft_dot_product(normal, light_ray);
		if (n_dot_l > 0)
			scene.ambiant.intensity += bulb->light.intensity * n_dot_l /
				(normal_len * ft_vector_length(light_ray));
		bulb = bulb->next;
	}
	if (scene.ambiant.intensity > 1)
		scene.ambiant.intensity = 1;
	return (scene.ambiant.intensity);
}

int		ft_trace_ray(t_vector origin, t_vector direction, t_scene scene)
{
	double		closest_inter;
	double		inter[2];
	t_vector	point;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	int			color;
	t_vector	center;
	t_obj		obj;

	color = -1;
	closest_inter = -1;
	sphere = scene.spheres;
	while (sphere != NULL)
	{
		ft_intersect_ray_sphere(origin, direction, sphere, inter);
		if (inter[0] >= scene.inter_min &&
				(inter[0] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[0] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[0];
			color = sphere->color;
			center = sphere->center;
			obj.type = SPHERE;
			obj.ptr = sphere;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			color = sphere->color;
			center = sphere->center;
			obj.type = SPHERE;
			obj.ptr = sphere;
		}
		sphere = sphere->next;
	}

	/* ===== DELETE ===== */

	scene.cylinders = malloc(sizeof(*scene.cylinders));
	scene.cylinders->next = NULL;
	scene.cylinders->center.x = 0;
	scene.cylinders->center.y = -1;
	scene.cylinders->center.z = 5;
	scene.cylinders->radius = 1;
	scene.cylinders->direction.x = 0;
	scene.cylinders->direction.y = 1;
	scene.cylinders->direction.z = 0;
	scene.cylinders->color = 0x00FFFF00;
	scene.cylinders->height = 2;

	/* ===== DELETE ===== */

	cylinder = scene.cylinders;
	while (cylinder != NULL)
	{
		cylinder->direction = ft_normalize_vector(cylinder->direction);
		ft_intersect_ray_cylinder(origin, direction, cylinder, inter);
		if (inter[0] >= scene.inter_min &&
				(inter[0] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[0] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[0];
			color = cylinder->color;
			center = cylinder->center;
			obj.type = CYLINDER;
			obj.ptr = cylinder;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			color = cylinder->color;
			center = cylinder->center;
			obj.type = CYLINDER;
			obj.ptr = cylinder;
		}
		cylinder = cylinder->next;
	}
	if (color == -1)
		return (ft_multiply_color(0x00FFFFFF, scene.ambiant.intensity));
	point = ft_add_vectors(origin, ft_multiply_vector_double(direction,
				closest_inter));
	return (ft_multiply_color(color,
				ft_compute_lighting(point, obj, scene)));
}

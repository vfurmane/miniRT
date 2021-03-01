/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/01 17:34:46 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_plane(t_vector origin, t_vector direction,
		t_plane *plane, double t[2])
{
	t[0] = ft_dot_product(ft_substract_vectors(plane->center, origin), plane->direction) / ft_dot_product(plane->direction, direction);
	t[1] = t[0];
}

void	ft_intersect_ray_sphere(t_vector origin, t_vector direction,
		t_sphere *sphere, double t[2])
{
	double		radius;
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
	double		radius;
	double		discriminant;
	double		k[3];
	t_vector	oc;
	t_vector	center;
	
	center = cylinder->center;
	radius = cylinder->radius;
	oc = ft_substract_vectors(origin, center);
	k[0] = ft_dot_product(direction, direction) - pow(ft_dot_product(direction, cylinder->direction), 2);
	k[1] = 2 * ((ft_dot_product(direction, oc)) - ft_dot_product(direction, cylinder->direction) * ft_dot_product(oc, cylinder->direction));
	k[2] = ft_dot_product(oc, oc) - pow(ft_dot_product(oc, cylinder->direction), 2) - radius * radius;
	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0)
	{
		t[0] = -1;
		t[1] = -1;
	}
	else
	{
		t[0] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
		t[1] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
		if (ft_dot_product(cylinder->direction, ft_substract_vectors(ft_add_vectors(origin, ft_multiply_vector_double(direction, t[0])), cylinder->center)) >= 0 && ft_dot_product(ft_substract_vectors(ft_add_vectors(origin, ft_multiply_vector_double(direction, t[0])), ft_add_vectors(cylinder->center, ft_multiply_vector_double(cylinder->direction, cylinder->height))), cylinder->direction) <= 0)
			t[1] = t[0];
		else if (ft_dot_product(cylinder->direction, ft_substract_vectors(ft_add_vectors(origin, ft_multiply_vector_double(direction, t[1])), cylinder->center)) >= 0 && ft_dot_product(ft_substract_vectors(ft_add_vectors(origin, ft_multiply_vector_double(direction, t[1])), ft_add_vectors(cylinder->center, ft_multiply_vector_double(cylinder->direction, cylinder->height))), cylinder->direction) <= 0)
			t[0] = t[1];
		else
		{
			t[0] = -1;
			t[1] = -1;
		}
	}
}

void	ft_add_light_intensity(double intensity[3], int color, double light_intensity)
{
	intensity[0] += ((double)((color & 16711680) >> 16) / 255) * ((double)((color & 16711680) >> 16) / 255) * light_intensity;
	if (intensity[0] > 1)
		intensity[0] = 1;
	intensity[1] += ((double)((color & 65280) >> 8) / 255) * ((double)((color & 65280) >> 8) / 255) * light_intensity;
	if (intensity[1] > 1)
		intensity[1] = 1;
	intensity[2] += ((double)(color & 255) / 255) * ((double)(color & 255) / 255) * light_intensity;
	if (intensity[2] > 1)
		intensity[2] = 1;
}

int		ft_compute_lighting(t_vector point, t_obj obj, t_scene scene, int color)
{
	double		normal_len;
	double		n_dot_l;
	t_vector	normal;
	t_vector	light_ray;
	t_bulb		*bulb;
	int			new_color;
	double		intensity[3];

	bulb = scene.bulbs;
	intensity[0] = 0;
	intensity[1] = 0;
	intensity[2] = 0;
	ft_add_light_intensity(intensity, scene.ambiant->color, scene.ambiant->intensity);
	while (bulb != NULL)
	{
		if (obj.type == SPHERE)
		{
			normal = ft_substract_vectors(point, ((t_sphere*)obj.ptr)->center);
		}
		else if (obj.type == CYLINDER)
		{
			normal = ft_substract_vectors(point, ft_add_vectors(((t_cylinder*)obj.ptr)->center, ft_multiply_vector_double(((t_cylinder*)obj.ptr)->direction, ft_dot_product(ft_substract_vectors(point, ((t_cylinder*)obj.ptr)->center), ((t_cylinder*)obj.ptr)->direction))));
		}
		else if (obj.type == PLANE)
		{
			normal = ((t_plane*)obj.ptr)->direction;
		}
		normal_len = ft_vector_length(normal);
		normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
		light_ray = ft_substract_vectors(bulb->center, point);
		n_dot_l = ft_dot_product(normal, light_ray) / (normal_len * ft_vector_length(light_ray));
		if (n_dot_l > 0)
		{
			//scene.ambiant.intensity += bulb->light.intensity * n_dot_l;
			ft_add_light_intensity(intensity, bulb->light.color, bulb->light.intensity * n_dot_l);
		}
		bulb = bulb->next;
	}
	new_color = 0;
	new_color += (int)(intensity[0] * ((color & 16711680) >> 16)) << 16;
	new_color += (int)(intensity[1] * ((color & 65280) >> 8)) << 8;
	new_color += (int)(intensity[2] * (color & 255));
	return (new_color);
}

int		ft_trace_ray(t_vector origin, t_vector direction, t_scene scene)
{
	double		closest_inter;
	double		inter[2];
	t_vector	point;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	int			color;
	t_obj		obj;

	color = -1;
	closest_inter = -1;
	plane = scene.planes;
	while (plane != NULL)
	{
		ft_intersect_ray_plane(origin, direction, plane, inter);
		if (inter[0] >= scene.inter_min &&
				(inter[0] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[0] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[0];
			color = plane->color;
			obj.type = PLANE;
			obj.ptr = plane;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			color = plane->color;
			obj.type = PLANE;
			obj.ptr = plane;
		}
		plane = plane->next;
	}

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
			obj.type = SPHERE;
			obj.ptr = sphere;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			color = sphere->color;
			obj.type = SPHERE;
			obj.ptr = sphere;
		}
		sphere = sphere->next;
	}

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
			obj.type = CYLINDER;
			obj.ptr = cylinder;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			color = cylinder->color;
			obj.type = CYLINDER;
			obj.ptr = cylinder;
		}
		cylinder = cylinder->next;
	}
	if (color == -1)
		return (ft_multiply_color(scene.ambiant->color, scene.ambiant->intensity));
	point = ft_add_vectors(origin, ft_multiply_vector_double(direction,
				closest_inter));
	return (ft_compute_lighting(point, obj, scene, color));
}

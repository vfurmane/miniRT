/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 20:57:09 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_calculate_intersections(double k[3], double t[2])
{
	double	discriminant;

	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0)
	{
		t[0] = -1;
		t[1] = -1;
		return (0);
	}
	t[0] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
	t[1] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
	return (1);
}

void	ft_intersect_ray(t_vector origin, t_vector direction, t_obj obj,
		double inter[2])
{
	if (obj.type == PLANE)
		ft_intersect_ray_plane(origin, direction, obj.ptr, inter);
	else if (obj.type == SPHERE)
		ft_intersect_ray_sphere(origin, direction, obj.ptr, inter);
	else if (obj.type == SQUARE)
		ft_intersect_ray_square(origin, direction, obj.ptr, inter);
	else if (obj.type == CYLINDER)
		ft_intersect_ray_cylinder(origin, direction, obj.ptr, inter);
}

double	ft_closest_obj(t_obj *obj1, t_obj *obj2)
{
	if ((obj1->inter <= obj2->inter && obj1->inter != -1) || obj2->inter == -1)
		return (obj1->inter);
	else if (obj2->inter != -1)
	{
		obj1->ptr = obj2->ptr;
		obj1->type = obj2->type;
		return (obj2->inter);
	}
	return (-1);
}

double	ft_closest_intersection(t_vector origin, t_vector direction,
		t_scene scene, t_obj *obj)
{
	double	inter[2];
	double	closest_inter;
	t_obj	obj_copy;
	t_obj	closest_obj;

	obj_copy = *obj;
	closest_inter = -1;
	while (obj_copy.ptr != NULL)
	{
		ft_intersect_ray(origin, direction, obj_copy, inter);
		if (inter[0] >= scene.inter_min &&
				(inter[0] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[0] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[0];
			closest_obj = obj_copy;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			closest_obj = obj_copy;
		}
		obj_copy.ptr = ((t_basic_obj*)obj_copy.ptr)->next;
	}
	obj->ptr = closest_obj.ptr;
	return (closest_inter);
}

int		ft_trace_ray(t_vector origin, t_vector direction, t_scene scene)
{
	int			i;
	void		*objects[4];
	t_obj		obj1;
	t_obj		obj2;
	t_vector	point;
	
	objects[0] = scene.spheres;
	objects[1] = scene.planes;
	objects[2] = scene.squares;
	objects[3] = scene.cylinders;
	obj1.inter = -1;
	i = 0;
	while (i < 4)
	{
		obj2.ptr = objects[i];
		obj2.type = i++;
		obj2.inter = ft_closest_intersection(origin, direction, scene, &obj2);
		obj1.inter = ft_closest_obj(&obj1, &obj2);
	}
	if (obj1.inter == -1)
		return (scene.background_color);
	point = ft_add_vectors(origin, ft_multiply_vector_double(direction,
				obj1.inter));
	return (ft_compute_lighting(point, obj1, scene,
				((t_basic_obj*)obj1.ptr)->color));
}

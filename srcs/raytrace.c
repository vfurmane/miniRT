/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/21 19:29:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray(t_ray *ray, t_obj obj, double inter[2])
{
	if (obj.type == PLANE)
		ft_intersect_ray_plane(ray, obj.ptr, inter);
	else if (obj.type == SPHERE)
		ft_intersect_ray_sphere(ray, obj.ptr, inter);
	else if (obj.type == SQUARE)
		ft_intersect_ray_square(ray, obj.ptr, inter);
	else if (obj.type == TRIANGLE)
		ft_intersect_ray_triangle(ray, obj.ptr, inter);
	else if (obj.type == CYLINDER)
		ft_intersect_ray_cylinder(ray, obj.ptr, inter);
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

void	ft_check_intersections(t_scene scene,
		t_obj *closest_obj, t_obj *obj_copy, double inter[2])
{
	if (inter[0] >= scene.inter_min &&
			(inter[0] <= scene.inter_max || scene.inter_max == -1) &&
			(inter[0] < closest_obj->inter || closest_obj->inter == -1))
	{
		closest_obj->type = obj_copy->type;
		closest_obj->ptr = obj_copy->ptr;
		closest_obj->inter = inter[0];
	}
	if (inter[1] >= scene.inter_min &&
			(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
			(inter[1] < closest_obj->inter || closest_obj->inter == -1))
	{
		closest_obj->type = obj_copy->type;
		closest_obj->ptr = obj_copy->ptr;
		closest_obj->inter = inter[1];
	}
}

double	ft_closest_intersection(t_ray *ray,
		t_scene scene, t_obj *obj)
{
	double	inter[2];
	t_obj	obj_copy;
	t_obj	closest_obj;

	obj_copy = *obj;
	closest_obj.inter = -1;
	while (obj_copy.ptr != NULL)
	{
		ft_intersect_ray(ray, obj_copy, inter);
		ft_check_intersections(scene, &closest_obj, &obj_copy, inter);
		obj_copy.ptr = ((t_basic_obj*)obj_copy.ptr)->next;
	}
	obj->ptr = closest_obj.ptr;
	return (closest_obj.inter);
}

int		ft_trace_ray(t_ray *ray, t_scene scene)
{
	void		*objects[5];
	t_obj		obj1;
	t_obj		obj2;
	t_vector	point;

	objects[0] = scene.spheres;
	objects[1] = scene.planes;
	objects[2] = scene.squares;
	objects[3] = scene.triangles;
	objects[4] = scene.cylinders;
	obj1.inter = -1;
	obj2.type = 0;
	while (obj2.type < 5)
	{
		obj2.ptr = objects[obj2.type];
		obj2.inter = ft_closest_intersection(ray, scene, &obj2);
		obj1.inter = ft_closest_obj(&obj1, &obj2);
		obj2.type++;
	}
	if (obj1.inter == -1)
		return (scene.background_color);
	point = ft_add_vectors(ray->origin,
			ft_multiply_vector_double(ray->direction, obj1.inter));
	return (ft_compute_lighting(point, obj1, scene,
				((t_basic_obj*)obj1.ptr)->color));
}

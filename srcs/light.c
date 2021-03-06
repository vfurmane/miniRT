/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:42:28 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/22 11:31:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		ft_add_light_intensity(double intensity[3], int color,
			double light_intensity)
{
	int	i;
	int	mask;
	int	color_mask;

	i = 0;
	while (i < 3)
	{
		mask = 16 - 8 * i;
		color_mask = (255 << mask);
		intensity[i] +=
			((double)((color & color_mask) >> mask) / 255) *
			((double)((color & color_mask) >> mask) / 255) *
			light_intensity;
		if (intensity[i] > 1)
			intensity[i] = 1;
		i++;
	}
}

int			ft_is_in_shadow(t_vector point, t_scene scene, t_bulb *bulb)
{
	void		*objects[5];
	t_obj		obj;
	t_ray		light_ray;

	scene.inter_min = 0.00000000001;
	scene.inter_max = 1;
	light_ray.origin = point;
	light_ray.direction = ft_substract_vectors(bulb->center, point);
	objects[0] = scene.spheres;
	objects[1] = scene.planes;
	objects[2] = scene.squares;
	objects[3] = scene.triangles;
	objects[4] = scene.cylinders;
	obj.inter = -1;
	obj.type = 0;
	while (obj.type < 5)
	{
		obj.ptr = objects[obj.type];
		obj.inter = ft_closest_intersection(&light_ray, &scene, &obj);
		obj.type++;
		if (obj.inter != -1)
			return (1);
	}
	return (0);
}

double		ft_calculate_ndotl(t_vector normal, t_bulb *bulb, t_vector point)
{
	double		n_dot_l;
	double		normal_len;
	t_vector	light_ray;

	normal_len = ft_vector_length(normal);
	normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
	light_ray = ft_substract_vectors(bulb->center, point);
	n_dot_l = ft_dot_product(normal, light_ray) /
		(normal_len * ft_vector_length(light_ray));
	return (n_dot_l);
}

void		ft_calculate_lights_intensity(t_scene *scene, t_obj obj,
			t_vector point, double intensity[3])
{
	t_bulb		*bulb;
	double		n_dot_l;
	t_vector	normal;

	bulb = scene->bulbs;
	while (bulb != NULL)
	{
		if (ft_is_in_shadow(point, *scene, bulb))
		{
			bulb = bulb->next;
			continue ;
		}
		normal = ft_calculate_primitive_normal(point, obj);
		n_dot_l = ft_calculate_ndotl(normal, bulb, point);
		if (n_dot_l > 0)
			ft_add_light_intensity(intensity, bulb->light.color,
					bulb->light.intensity * n_dot_l);
		bulb = bulb->next;
	}
}

int			ft_compute_lighting(t_vector point, t_obj obj, t_scene *scene,
			int color)
{
	int			new_color;
	double		intensity[3];

	ft_memset(intensity, 0, 3 * sizeof(*intensity));
	ft_add_light_intensity(intensity, scene->ambiant->color,
			scene->ambiant->intensity);
	ft_calculate_lights_intensity(scene, obj, point, intensity);
	new_color = 0;
	new_color += (int)(intensity[0] * ((color & 16711680) >> 16)) << 16;
	new_color += (int)(intensity[1] * ((color & 65280) >> 8)) << 8;
	new_color += (int)(intensity[2] * (color & 255));
	return (new_color);
}

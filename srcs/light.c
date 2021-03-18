/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:42:28 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 12:43:15 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_add_light_intensity(double intensity[3], int color,
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

int		ft_is_in_shadow(t_vector point, t_scene scene, t_bulb *bulb)
{
	double		closest_inter;
	t_obj		obj;

	scene.inter_min = 0.00000000001;
	scene.inter_max = 1;
	obj.ptr = scene.planes;
	obj.type = PLANE;
	closest_inter = ft_closest_intersection(point,
			ft_substract_vectors(bulb->center, point), scene, &obj);
	if (closest_inter != -1)
		return (1);
	obj.ptr = scene.spheres;
	obj.type = SPHERE;
	closest_inter = ft_closest_intersection(point,
			ft_substract_vectors(bulb->center, point), scene, &obj);
	if (closest_inter != -1)
		return (1);
	obj.ptr = scene.cylinders;
	obj.type = CYLINDER;
	closest_inter = ft_closest_intersection(point,
			ft_substract_vectors(bulb->center, point), scene, &obj);
	if (closest_inter != -1)
		return (1);
	return (0);
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
	ft_add_light_intensity(intensity, scene.ambiant->color,
			scene.ambiant->intensity);
	while (bulb != NULL)
	{
		if (ft_is_in_shadow(point, scene, bulb))
		{
			bulb = bulb->next;
			continue ;
		}
		if (obj.type == SPHERE)
		{
			normal = ft_substract_vectors(point, ((t_sphere*)obj.ptr)->center);
		}
		else if (obj.type == CYLINDER)
		{
			normal = ft_substract_vectors(point,
					ft_add_vectors(((t_cylinder*)obj.ptr)->center,
					ft_multiply_vector_double(((t_cylinder*)obj.ptr)->direction,
					ft_dot_product(ft_substract_vectors(point,
					((t_cylinder*)obj.ptr)->center),
					((t_cylinder*)obj.ptr)->direction))));
		}
		else if (obj.type == PLANE || obj.type == SQUARE)
		{
			normal = ((t_plane*)obj.ptr)->direction;
		}
		normal_len = ft_vector_length(normal);
		normal = ft_multiply_vector_double(normal, 1.0 / normal_len);
		light_ray = ft_substract_vectors(bulb->center, point);
		n_dot_l = ft_dot_product(normal, light_ray) /
			(normal_len * ft_vector_length(light_ray));
		if (n_dot_l > 0)
			ft_add_light_intensity(intensity, bulb->light.color,
					bulb->light.intensity * n_dot_l);
		bulb = bulb->next;
	}
	new_color = 0;
	new_color += (int)(intensity[0] * ((color & 16711680) >> 16)) << 16;
	new_color += (int)(intensity[1] * ((color & 65280) >> 8)) << 8;
	new_color += (int)(intensity[2] * (color & 255));
	return (new_color);
}

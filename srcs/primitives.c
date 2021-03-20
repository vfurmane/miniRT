/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:50:12 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/21 19:30:12 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_calculate_primitive_normal(t_vector point, t_obj obj)
{
	t_vector	normal;

	if (obj.type == SPHERE)
		normal = ft_substract_vectors(point, ((t_sphere*)obj.ptr)->center);
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
		normal = ((t_plane*)obj.ptr)->direction;
	else if (obj.type == TRIANGLE)
		normal = ((t_triangle*)obj.ptr)->normal;
	else
		normal = point;
	return (normal);
}

int			ft_calculate_intersections(double k[3], double t[2])
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

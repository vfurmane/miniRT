/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:08:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 12:26:32 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int		ft_check_cylinder_cap(double inter, t_vector direction,
					t_cylinder *cylinder, t_vector origin)
{
	return (ft_dot_product(cylinder->direction,
			ft_substract_vectors(ft_add_vectors(origin,
			ft_multiply_vector_double(direction, inter)),
			cylinder->center)) >= 0 &&
			ft_dot_product(ft_substract_vectors(ft_add_vectors(origin,
			ft_multiply_vector_double(direction, inter)),
			ft_add_vectors(cylinder->center,
			ft_multiply_vector_double(cylinder->direction, cylinder->height))),
			cylinder->direction) <= 0);
}

void			ft_intersect_ray_cylinder(t_vector origin, t_vector direction,
					t_cylinder *cylinder, double t[2])
{
	double		radius;
	double		k[3];
	t_vector	oc;
	t_vector	center;
	
	center = cylinder->center;
	radius = cylinder->radius;
	oc = ft_substract_vectors(origin, center);
	cylinder->direction = ft_normalize_vector(cylinder->direction);
	k[0] = ft_dot_product(direction, direction) -
		pow(ft_dot_product(direction, cylinder->direction), 2); /* ===== DELETE ===== */
	k[1] = 2 * ((ft_dot_product(direction, oc)) -
			ft_dot_product(direction, cylinder->direction) *
			ft_dot_product(oc, cylinder->direction));
	k[2] = ft_dot_product(oc, oc) -
		pow(ft_dot_product(oc, cylinder->direction), 2) - radius * radius; /* ===== DELETE ===== */
	if (!ft_calculate_intersections(k, t))
		return ;
	if (ft_check_cylinder_cap(t[0], direction, cylinder, origin))
		t[1] = t[0];
	if (ft_check_cylinder_cap(t[1], direction, cylinder, origin))
		t[0] = t[1];
	else
		t[0] = -1;
	if (t[0] == -1)
		t[1] = -1;
}

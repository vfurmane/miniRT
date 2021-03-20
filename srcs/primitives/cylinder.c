/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:08:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/21 19:43:58 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int		ft_check_cylinder_cap(double inter, t_cylinder *cylinder,
		t_ray *ray)
{
	return (ft_dot_product(cylinder->direction,
			ft_substract_vectors(ft_add_vectors(ray->origin,
			ft_multiply_vector_double(ray->direction, inter)),
			cylinder->center)) >= 0 &&
			ft_dot_product(cylinder->direction,
			ft_substract_vectors(ft_add_vectors(ray->origin,
			ft_multiply_vector_double(ray->direction, inter)),
			cylinder->top)) <= 0);
}

static void		ft_set_cylinder_intersection(t_ray *ray, t_cylinder *cylinder,
				double t[2])
{
	if (ft_check_cylinder_cap(t[0], cylinder, ray))
		t[1] = t[0];
	if (ft_check_cylinder_cap(t[1], cylinder, ray))
		t[0] = t[1];
	else
		t[0] = -1;
	if (t[0] == -1)
		t[1] = -1;
}

void			ft_intersect_ray_cylinder(t_ray *ray,
					t_cylinder *cylinder, double t[2])
{
	double		radius;
	double		k[3];
	t_vector	oc;
	t_vector	center;

	center = cylinder->center;
	radius = cylinder->radius;
	oc = ft_substract_vectors(ray->origin, center);
	cylinder->direction = cylinder->direction;
	k[0] = ft_dot_product(ray->direction, ray->direction) -
		ft_dot_product(ray->direction, cylinder->direction) *
		ft_dot_product(ray->direction, cylinder->direction);
	k[1] = 2 * ((ft_dot_product(ray->direction, oc)) -
			ft_dot_product(ray->direction, cylinder->direction) *
			ft_dot_product(oc, cylinder->direction));
	k[2] = ft_dot_product(oc, oc) -
		ft_dot_product(oc, cylinder->direction) *
		ft_dot_product(oc, cylinder->direction) - radius * radius;
	if (!ft_calculate_intersections(k, t))
		return ;
	ft_set_cylinder_intersection(ray, cylinder, t);
}

void			ft_precalculate_cylinder(t_cylinder *cylinder)
{
	cylinder->top = ft_add_vectors(cylinder->center,
			ft_multiply_vector_double(cylinder->direction, cylinder->height));
}

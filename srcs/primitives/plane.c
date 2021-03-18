/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:16:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 12:17:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_intersect_ray_plane(t_vector origin, t_vector direction,
		t_plane *plane, double t[2])
{
	t[0] = ft_dot_product(ft_substract_vectors(plane->center, origin),
			plane->direction) / ft_dot_product(plane->direction, direction);
	t[1] = t[0];
}

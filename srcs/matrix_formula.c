/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_formula.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/23 12:28:28 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_invert_camera_matrix(t_vector *right, t_vector *up,
		t_vector *forward)
{
	double	tmp;

	tmp = up->x;
	up->x = right->y;
	right->y = tmp;
	tmp = forward->x;
	forward->x = right->z;
	right->z = tmp;
	tmp = forward->y;
	forward->y = up->z;
	up->z = tmp;
}

double	*ft_initialize_anti_aliasing_matrix(int level)
{
	int		i;
	int		matrix_len;
	double	*matrix;
	double	raysize;

	matrix_len = level * level * 2;
	matrix = malloc(sizeof(*matrix) * matrix_len);
	if (matrix == NULL)
		return (ft_fatal_error_null("Cannot allocate the anti aliasing array"));
	raysize = 1.0 / level;
	i = 0;
	while (i < matrix_len / 2)
	{
		matrix[i * 2] = -0.5 + (raysize / 2) + (raysize * (i % level));
		matrix[i * 2 + 1] = 0.5 - (raysize / 2) + (raysize * (i % level));
		i++;
	}
	return (matrix);
}

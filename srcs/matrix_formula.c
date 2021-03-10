/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_formula.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/10 10:30:28 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_invert_camera_matrix(t_vector *right, t_vector *up, t_vector *forward)
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

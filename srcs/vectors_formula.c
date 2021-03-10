/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_formula.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:15:53 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/10 14:24:35 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double		ft_dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		ft_vector_length(t_vector vector)
{
	return (sqrt(ft_dot_product(vector, vector)));
}

t_vector	ft_cross_product(t_vector v1, t_vector v2)
{
	t_vector vector;

	vector.x = v1.y * v2.z - v2.y * v1.z;
	vector.y = v1.z * v2.x - v2.z * v1.x;
	vector.z = v1.x * v2.y - v2.x * v1.y;
	return (vector);
}

t_vector	ft_normalize_vector(t_vector vector)
{
	double			len;
	t_vector	new_vector;

	len = ft_vector_length(vector);
	new_vector = ft_multiply_vector_double(vector, 1.0 / len);
	return (new_vector);
}

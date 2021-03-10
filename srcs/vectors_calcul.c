/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calcul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:54:30 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/10 14:24:27 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_add_vectors(t_vector v1, t_vector v2)
{
	t_vector	vector;

	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	vector.z = v1.z + v2.z;
	return (vector);
}

t_vector	ft_substract_vectors(t_vector v1, t_vector v2)
{
	t_vector	vector;

	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	vector.z = v1.z - v2.z;
	return (vector);
}

t_vector	ft_multiply_vectors(t_vector v1, t_vector v2)
{
	t_vector	vector;

	vector.x = v1.x * v2.x;
	vector.y = v1.y * v2.y;
	vector.z = v1.z * v2.z;
	return (vector);
}

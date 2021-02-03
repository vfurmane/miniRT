/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_double_calcul.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:17:25 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/03 17:18:57 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_add_vector_double(t_vector v1, double nbr)
{
	static t_vector	vector;

	vector.x = v1.x + nbr;
	vector.y = v1.y + nbr;
	vector.z = v1.z + nbr;
	return (vector);
}

t_vector	ft_substract_vector_double(t_vector v1, double nbr)
{
	static t_vector	vector;

	vector.x = v1.x - nbr;
	vector.y = v1.y - nbr;
	vector.z = v1.z - nbr;
	return (vector);
}

t_vector	ft_multiply_vector_double(t_vector v1, double nbr)
{
	static t_vector	vector;

	vector.x = v1.x * nbr;
	vector.y = v1.y * nbr;
	vector.z = v1.z * nbr;
	return (vector);
}

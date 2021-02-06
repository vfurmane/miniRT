/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:22:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 13:28:30 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	*ft_new_sphere(char *vector, double diameter, char *color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->next = NULL;
	sphere->center = ft_str_to_vector(vector);
	sphere->radius = diameter / 2.0;
	sphere->color = ft_parse_color(color);
	return (sphere);
}

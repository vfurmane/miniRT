/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:22:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/10 20:11:23 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	*ft_new_sphere(char *vector, double diameter, char *color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
		ft_fatal_error("Failed to create a new sphere");
	sphere->next = NULL;
	sphere->center = ft_str_to_vector(vector);
	sphere->radius = diameter / 2.0;
	sphere->color = ft_parse_color(color);
	return (sphere);
}

t_cylinder	*ft_new_cylinder(char **vector, double diameter, double height, char *color)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(*cylinder));
	if (cylinder == NULL)
		ft_fatal_error("Failed to create a new cylinder");
	cylinder->next = NULL;
	cylinder->center = ft_str_to_vector(vector[0]);
	cylinder->direction = ft_str_to_vector(vector[1]);
	cylinder->height = height;
	cylinder->radius = diameter / 2.0;
	cylinder->color = ft_parse_color(color);
	return (cylinder);
}

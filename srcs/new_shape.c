/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:22:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/28 19:44:59 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	*ft_new_sphere(char **args, int line)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
		ft_fatal_error("Failed to create a new sphere");
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_atof(args[1], "", line) ||
			!ft_check_parse_color(args[2], line))
	{
		free(sphere);
		return (NULL);
	}
	sphere->next = NULL;
	sphere->center = ft_str_to_vector(args[0]);
	sphere->radius = ft_atof(args[1]) / 2.0;
	sphere->color = ft_parse_color(args[2]);
	return (sphere);
}

t_plane		*ft_new_plane(char **args, int line)
{
	t_plane	*plane;

	plane = malloc(sizeof(*plane));
	if (plane == NULL)
		ft_fatal_error("Failed to create a new plane");
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_str_to_vector(args[1], 1, line) ||
			!ft_check_parse_color(args[2], line))
	{
		free(plane);
		return (NULL);
	}
	plane->next = NULL;
	plane->center = ft_str_to_vector(args[0]);
	plane->direction = ft_str_to_vector(args[1]);
	plane->color = ft_parse_color(args[2]);
	return (plane);
}

t_cylinder	*ft_new_cylinder(char **args, int line)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(*cylinder));
	if (cylinder == NULL)
		ft_fatal_error("Failed to create a new cylinder");
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_str_to_vector(args[1], 1, line) ||
			!ft_check_atof(args[2], "", line) ||
			!ft_check_atof(args[3], "", line) ||
			!ft_check_parse_color(args[4], line))
	{
		free(cylinder);
		return (NULL);
	}
	cylinder->next = NULL;
	cylinder->center = ft_str_to_vector(args[0]);
	cylinder->direction = ft_str_to_vector(args[1]);
	cylinder->radius = ft_atof(args[2]) / 2.0;
	cylinder->height = ft_atof(args[3]);
	cylinder->color = ft_parse_color(args[4]);
	return (cylinder);
}

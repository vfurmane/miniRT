/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:22:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 11:41:45 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	*ft_new_sphere(char **args, int line)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
	{
		ft_fatal_error("Failed to create a new sphere");
		return (NULL);
	}
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
	{
		ft_fatal_error("Failed to create a new plane");
		return (NULL);
	}
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_str_to_vector(args[1], 1, line) ||
			!ft_check_parse_color(args[2], line))
	{
		free(plane);
		return (NULL);
	}
	plane->next = NULL;
	plane->center = ft_str_to_vector(args[0]);
	plane->direction = ft_normalize_vector(ft_str_to_vector(args[1]));
	plane->color = ft_parse_color(args[2]);
	return (plane);
}

t_square	*ft_new_square(char **args, int line)
{
	t_square	*square;

	square = malloc(sizeof(*square));
	if (square == NULL)
	{
		ft_fatal_error("Failed to create a new square");
		return (NULL);
	}
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_str_to_vector(args[1], 1, line) ||
			!ft_check_atof(args[2], "", line) ||
			!ft_check_parse_color(args[3], line))
	{
		free(square);
		return (NULL);
	}
	square->next = NULL;
	square->center = ft_str_to_vector(args[0]);
	square->direction = ft_normalize_vector(ft_str_to_vector(args[1]));
	square->width = ft_atof(args[2]);
	square->color = ft_parse_color(args[3]);
	return (square);
}

t_cylinder	*ft_new_cylinder(char **args, int line)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(*cylinder));
	if (cylinder == NULL)
	{
		ft_fatal_error("Failed to create a new cylinder");
		return (NULL);
	}
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
	cylinder->direction = ft_normalize_vector(ft_str_to_vector(args[1]));
	cylinder->radius = ft_atof(args[2]) / 2.0;
	cylinder->height = ft_atof(args[3]);
	cylinder->color = ft_parse_color(args[4]);
	ft_precalculate_cylinder(cylinder);
	return (cylinder);
}

t_triangle	*ft_new_triangle(char **args, int line)
{
	t_triangle	*triangle;

	triangle = malloc(sizeof(*triangle));
	if (triangle == NULL)
	{
		ft_fatal_error("Failed to create a new triangle");
		return (NULL);
	}
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_str_to_vector(args[1], 0, line) ||
			!ft_check_str_to_vector(args[2], 0, line) ||
			!ft_check_parse_color(args[3], line))
	{
		free(triangle);
		return (NULL);
	}
	triangle->next = NULL;
	triangle->point1 = ft_str_to_vector(args[0]);
	triangle->point2 = ft_str_to_vector(args[1]);
	triangle->point3 = ft_str_to_vector(args[2]);
	triangle->color = ft_parse_color(args[3]);
	ft_precalculate_triangle(triangle);
	return (triangle);
}

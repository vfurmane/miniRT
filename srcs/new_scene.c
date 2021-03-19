/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:38:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 19:01:13 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light			*ft_new_ambiant(char **args, int line)
{
	t_light	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
	{
		ft_fatal_error("Failed to create the ambiant light");
		return (NULL);
	}
	if (!ft_check_atof(args[0], "", line) ||
			!ft_check_parse_color(args[1], line))
	{
		free(light);
		return (NULL);
	}
	light->intensity = ft_atof(args[0]);
	light->color = ft_parse_color(args[1]);
	return (light);
}

static t_camera	*ft_check_new_camera(char **args, int line)
{
	t_camera	*camera;

	camera = malloc(sizeof(*camera));
	if (camera == NULL)
	{
		ft_fatal_error("Failed to create a new camera");
		return (NULL);
	}
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_str_to_vector(args[1], 1, line) ||
			!ft_check_atoi(args[2], "", line))
	{
		free(camera);
		return (NULL);
	}
	return (camera);
}

t_camera		*ft_new_camera(char **args, int line)
{
	t_camera	*camera;

	camera = ft_check_new_camera(args, line);
	camera->center = ft_str_to_vector(args[0]);
	camera->direction = ft_str_to_vector(args[1]);
	camera->fov = ft_atoi(args[2]);
	camera->pixel_size = 1;
	camera->anti_aliasing_level = 1 * !!MINI_RT_BONUS + 1 * !MINI_RT_BONUS;
	camera->anti_aliasing_matrix = ft_initialize_anti_aliasing_matrix(
			camera->anti_aliasing_level);
	if (camera->anti_aliasing_matrix == NULL)
	{
		free(camera);
		return (NULL);
	}
	camera->next = NULL;
	return (camera);
}

t_bulb			*ft_new_light(char **args, int line)
{
	t_bulb	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
	{
		ft_fatal_error("Failed to create a new light bulb");
		return (NULL);
	}
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_atof(args[1], "", line) ||
			!ft_check_parse_color(args[2], line))
	{
		free(light);
		return (NULL);
	}
	light->center = ft_str_to_vector(args[0]);
	light->light.intensity = ft_atof(args[1]);
	light->light.color = ft_parse_color(args[2]);
	light->next = NULL;
	return (light);
}

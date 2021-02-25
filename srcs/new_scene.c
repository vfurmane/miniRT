/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:38:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/28 19:44:02 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light		*ft_new_ambiant(char **args, int line)
{
	t_light	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
		ft_fatal_error("Failed to create the ambiant light");
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

t_bulb		*ft_new_light(char **args, int line)
{
	t_bulb	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
		ft_fatal_error("Failed to create a new light bulb");
	if (!ft_check_str_to_vector(args[0], 0, line) ||
			!ft_check_atof(args[1], "", line) ||
			!ft_check_parse_color(args[2], line))
	{
		free(light);
		return (NULL);
	}
	light->center = ft_str_to_vector(args[0]);
	light->light.intensity = ft_atof(args[1]);;
	light->light.color = ft_parse_color(args[2]);
	light->next = NULL;
	return (light);
}

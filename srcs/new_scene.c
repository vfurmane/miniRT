/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:38:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 21:42:39 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		ft_set_ambiant(t_scene *scene, double intensity, const char *color)
{
	scene->ambiant.intensity = intensity;
	scene->ambiant.color = ft_parse_color(color);
}

t_bulb		*ft_new_light(const char *vector, double intensity,
		const char *color)
{
	t_bulb	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
		ft_fatal_error("Failed to create a new light bulb");
	light->center = ft_str_to_vector(vector);
	light->light.intensity = intensity;
	light->light.color = ft_parse_color(color);
	light->next = NULL;
	return (light);
}

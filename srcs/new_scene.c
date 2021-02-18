/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:38:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/18 14:18:14 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light		*ft_new_ambiant(double intensity, const char *color)
{
	t_light	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
		ft_fatal_error("Failed to create the ambiant light");
	light->intensity = intensity;
	light->color = ft_parse_color(color);
	return (light);
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

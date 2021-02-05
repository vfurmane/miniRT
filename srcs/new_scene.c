/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:38:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/05 12:48:54 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light	*ft_new_ambiant(double intensity, const char *color)
{
	t_light	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
		return (NULL);
	light->type = AMBIANT;
	light->intensity = intensity;
	light->color = ft_parse_color(color);
	light->next = NULL;
	return (light);
}

t_light	*ft_new_light(const char *vector, double intensity, const char *color)
{
	t_light	*light;

	(void)vector;
	light = malloc(sizeof(*light));
	if (light == NULL)
		return (NULL);
	light->type = POINT;
	light->vector.x = 0;
	light->vector.y = 0;
	light->vector.z = 0;
	light->intensity = intensity;
	light->color = ft_parse_color(color);
	light->next = NULL;
	return (light);
}

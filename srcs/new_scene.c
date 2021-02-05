/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:38:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/05 18:09:49 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		ft_set_ambiant(t_scene *scene, double intensity, const char *color)
{
	scene->ambiant.intensity = intensity;
	scene->ambiant.color = ft_parse_color(color);
}

t_vector	ft_str_to_vector(const char *str)
{
	int				i;
	static t_vector	vector;

	i = 0;
	vector.x = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		i++;
	vector.y = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		i++;
	vector.z = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (vector);
}

t_bulb		*ft_new_light(const char *vector, double intensity, const char *color)
{
	t_bulb	*light;

	light = malloc(sizeof(*light));
	if (light == NULL)
		return (NULL);
	light->vector = ft_str_to_vector(vector);
	light->light.intensity = intensity;
	light->light.color = ft_parse_color(color);
	light->next = NULL;
	return (light);
}

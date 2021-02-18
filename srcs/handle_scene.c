/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:47:22 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/18 14:18:40 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_handle_resolution(char **args, t_scene *scene)
{
	int	nbr;

	nbr = atoi(args[0]);
	if (nbr < 0)
		return (-1);
	scene->plan.width = nbr;
	nbr = atoi(args[1]);
	if (nbr < 0)
		return (-1);
	scene->plan.height = nbr;
	return (0);
}

int	ft_handle_ambiant(char **args, t_scene *scene)
{
	double	nbr;

	nbr = ft_atof(args[0]);
	if (nbr < 0)
		return (-1);
	ft_lstadd_front((void**)&scene->ambiant,
			ft_new_ambiant(nbr, args[1]));
	return (0);
}

int	ft_handle_light(char **args, t_scene *scene)
{
	double	nbr;

	nbr = ft_atof(args[1]);
	if (nbr < 0)
		return (-1);
	ft_lstadd_front((void**)&scene->bulbs,
			(void*)ft_new_light(args[0], nbr, args[2]));
	return (0);
}

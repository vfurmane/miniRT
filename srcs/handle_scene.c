/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:47:22 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/23 09:55:53 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_handle_resolution(char **args, t_scene *scene, int line)
{
	int	nbr;

	if (scene->plan.width != -1)
		return (ft_error_line("Resolution declared twice", line));
	if (!ft_check_args_count(args, 2, line))
		return (-1);
	if (!ft_check_atoi(args[0], "", line) ||
			!ft_check_atoi(args[1], "", line))
		return (-1);
	nbr = atoi(args[0]);
	if (nbr <= 0)
		return (ft_error_line("Width cannot be null or negative", line));
	scene->plan.width = nbr;
	nbr = atoi(args[1]);
	if (nbr <= 0)
		return (ft_error_line("Height cannot be null or negative", line));
	scene->plan.height = nbr;
	return (0);
}

int	ft_handle_ambiant(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (scene->ambiant != NULL)
	{
		printf("Error\nline %d: Ambiant light has already been set\n",
				line);
		return (-1);
	}
	if (!ft_check_args_count(args, 2, line))
		return (-1);
	ret = ft_new_ambiant(&args[0], line);
	if (ret == NULL)
		return (-1);
	scene->ambiant = ret;
	if (scene->ambiant->intensity < 0 || scene->ambiant->intensity > 1)
	{
		printf("Error\nline %d: Light intensity must be in range [0.0,1.0]\n",
				line);
		return (-1);
	}
	return (0);
}

int	ft_handle_camera(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 3, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->cameras,
			(void*)ft_new_camera(&args[0], line));
	if (ret == NULL)
		return (-1);
	if (scene->cameras->fov < 0 || scene->cameras->fov > 180)
	{
		printf("Error\nline %d: Camera fov must be in range [0,180]\n", line);
		return (-1);
	}
	return (0);
}

int	ft_handle_light(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 3, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->bulbs,
			(void*)ft_new_light(&args[0], line));
	if (ret == NULL)
		return (-1);
	return (0);
}

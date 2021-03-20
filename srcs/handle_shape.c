/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:18:02 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 11:27:25 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_handle_sphere(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 3, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->spheres,
			(void*)ft_new_sphere(&args[0], line));
	if (ret == NULL)
		return (-1);
	return (0);
}

int	ft_handle_plane(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 3, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->planes,
			(void*)ft_new_plane(&args[0], line));
	if (ret == NULL)
		return (-1);
	return (0);
}

int	ft_handle_square(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 4, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->squares,
			(void*)ft_new_square(&args[0], line));
	if (ret == NULL)
		return (-1);
	return (0);
}

int	ft_handle_cylinder(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 5, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->cylinders,
			(void*)ft_new_cylinder(&args[0], line));
	if (ret == NULL)
		return (-1);
	return (0);
}

int	ft_handle_triangle(char **args, t_scene *scene, int line)
{
	void	*ret;

	if (!ft_check_args_count(args, 4, line))
		return (-1);
	ret = ft_lstadd_front((void**)&scene->triangles,
			(void*)ft_new_triangle(&args[0], line));
	if (ret == NULL)
		return (-1);
	return (0);
}

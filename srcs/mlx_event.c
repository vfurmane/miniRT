/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:03:13 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/01 19:02:49 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_close_window(t_scene *scene)
{
	mlx_loop_end(scene->mlx);
	return (0);
}

int		ft_loop_hook(void *param)
{
	(void)param;
	return (0);
}

void	my_mlx_events(t_scene *scene)
{
	mlx_loop_hook(scene->mlx, ft_loop_hook, scene);
	mlx_hook(scene->win, 33, 1L << 17, ft_close_window, scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:03:13 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 20:13:13 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_close_window(t_scene *scene)
{
	mlx_loop_end(scene->mlx);
	return (0);
}

int		ft_put_scene_back(t_scene *scene)
{
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	return (0);
}

void	ft_move_camera(t_scene *scene, int key)
{
	t_vector	direction;

	direction.x = 0 + 0.2 * (key == XK_Right) - 0.2 * (key == XK_Left);
	direction.y = 0;
	direction.z = 0 + 0.2 * (key == XK_Up) - 0.2 * (key == XK_Down);
	scene->current_camera->pixel_size = scene->plan.width * scene->plan.height /
		138240;
	if (scene->current_camera->pixel_size == 0)
		scene->current_camera->pixel_size = 1;
	scene->current_camera->center = ft_add_vectors(scene->current_camera->center, direction);
	ft_render_scene(scene, scene->current_camera, NULL, scene->img);
	ft_put_scene_back(scene);
}

void	ft_refresh_camera(t_scene *scene, int pixel_size)
{
	if (pixel_size > 0)
		scene->current_camera->pixel_size = pixel_size;
	ft_render_scene(scene, scene->current_camera, NULL, scene->img);
	ft_put_scene_back(scene);
}

int		ft_loop_hook(void *param)
{
	(void)param;
	return (0);
}

int		ft_handle_key(int code, t_scene *scene)
{
	if (code == XK_c)
	{
		scene->img = scene->img->next;
		mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
		scene->current_camera = scene->current_camera->next;
		if (scene->current_camera == NULL)
			scene->current_camera = scene->cameras;
	}
	else if (code == XK_Escape)
		ft_close_window(scene);
	else if (MINI_RT_BONUS && code >= XK_Left && code <= XK_Down)
		ft_move_camera(scene, code);
	else if (MINI_RT_BONUS && code == XK_r)
		ft_refresh_camera(scene, 1);
	return (0);
}

void	my_mlx_events(t_scene *scene)
{
	mlx_loop_hook(scene->mlx, ft_loop_hook, scene);
	mlx_hook(scene->win, KeyPress, KeyPressMask, ft_handle_key, scene);
	mlx_hook(scene->win, VisibilityNotify, VisibilityChangeMask,
			ft_put_scene_back, scene);
	mlx_hook(scene->win, ClientMessage, StructureNotifyMask, ft_close_window,
			scene);
}

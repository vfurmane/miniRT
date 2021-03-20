/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:03:13 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 09:20:23 by vfurmane         ###   ########.fr       */
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
	t_camera	*camera;
	t_vector	center;

	camera = scene->current_camera;
	ft_invert_camera_matrix(&camera->right, &camera->up, &camera->forward);
	center = scene->current_camera->center;
	if (key == XK_Up)
		center = ft_add_vectors(center, ft_multiply_vector_double(camera->forward, 0.2));
	else if (key == XK_Down)
		center = ft_substract_vectors(center, ft_multiply_vector_double(camera->forward, 0.2));
	else if (key == XK_Right)
		center = ft_add_vectors(center, ft_multiply_vector_double(camera->right, 0.2));
	else if (key == XK_Left)
		center = ft_substract_vectors(center, ft_multiply_vector_double(camera->right, 0.2));
	ft_invert_camera_matrix(&camera->right, &camera->up, &camera->forward);
	scene->current_camera->pixel_size = scene->plan.width * scene->plan.height /
		138240 * 2;
	if (scene->current_camera->pixel_size == 0)
		scene->current_camera->pixel_size = 1;
	scene->current_camera->center = center;
	ft_render_scene(scene, scene->current_camera, NULL, scene->img);
	ft_put_scene_back(scene);
}

void	ft_rotate_camera(t_scene *scene, int key)
{
	t_vector	direction;

	scene->current_camera->angle += 2 * (key == XK_v) - 2 * (key == XK_x);
	direction.x = sin(scene->current_camera->angle * M_PI / 180);
	direction.y = scene->current_camera->direction.y;
	direction.z = cos(scene->current_camera->angle * M_PI / 180);
	scene->current_camera->pixel_size = scene->plan.width * scene->plan.height /
		138240 * 2;
	if (scene->current_camera->pixel_size == 0)
		scene->current_camera->pixel_size = 1;
	scene->current_camera->direction = direction;
	ft_calculate_camera_rotation_and_fov(scene, scene->current_camera);
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
	else if (MINI_RT_BONUS && (code == XK_x || code == XK_v))
		ft_rotate_camera(scene, code);
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

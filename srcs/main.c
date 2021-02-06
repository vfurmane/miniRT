/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 18:56:53 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_canvas_to_viewport(int x, int y, int viewport, t_plan canvas)
{
	double		d_viewport;
	double		d_width;
	double		d_height;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	d_height = (double)canvas.height;
	direction.x = x * d_viewport / d_width;
	direction.y = y * d_viewport / d_width;
	direction.z = (double)canvas.distance;
	return (direction);
}

int			main(int argc, char **argv)
{
	t_pixel		pixel;
	t_vector	origin;
	t_vector	direction;
	void		*mlx;
	void		*win;
	t_data		img;
	t_scene		scene;
	int			pixel_size;

	if (ft_parameters(argc, argv, &scene) == -1)
		return (ft_error());
	scene.inter_min = 1;
	scene.inter_max = -1;
	scene.plan.distance = 1;
	scene.plan.viewport = 2;
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	pixel.x = -scene.plan.width / 2;
	mlx = mlx_init();
	win = mlx_new_window(mlx, scene.plan.width, scene.plan.height, "miniRT");
	img.img = mlx_new_image(mlx, scene.plan.width, scene.plan.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	pixel_size = 1;
	while (pixel.x < scene.plan.width / 2)
	{
		pixel.y = -scene.plan.height / 2;
		while (pixel.y < scene.plan.height / 2)
		{
			direction = ft_canvas_to_viewport(pixel.x, pixel.y, scene.plan.viewport,
					scene.plan);
			pixel.color = ft_trace_ray(origin, direction, scene);
			my_mlx_put_pixel(&img, pixel.x + scene.plan.width / 2,
					-pixel.y + scene.plan.height / 2, pixel.color, pixel_size, scene);
			pixel.y += pixel_size;
		}
		pixel.x += pixel_size;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

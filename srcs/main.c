/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/05 09:14:24 by vfurmane         ###   ########.fr       */
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
	t_plan		canvas;
	t_vector	origin;
	t_vector	direction;
	void		*mlx;
	void		*win;
	t_data		img;
	t_scene		scene;

	canvas.width = 1440;
	canvas.height = 960;
	canvas.distance = 1;
	canvas.viewport = 2;
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	pixel.x = -canvas.width / 2;
	mlx = mlx_init();
	win = mlx_new_window(mlx, canvas.width, canvas.height, "miniRT");
	img.img = mlx_new_image(mlx, canvas.width, canvas.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	ft_parameters(argc, argv, &scene);
	while (pixel.x < canvas.width / 2)
	{
		pixel.y = -canvas.height / 2;
		while (pixel.y < canvas.height / 2)
		{
			direction = ft_canvas_to_viewport(pixel.x, pixel.y, canvas.viewport,
					canvas);
			pixel.color = ft_trace_ray(origin, direction, 1, -1);
			my_mlx_put_pixel(&img, pixel.x + canvas.width / 2,
					-pixel.y + canvas.height / 2, pixel.color);
			pixel.y++;
		}
		pixel.x++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

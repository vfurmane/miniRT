/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 21:41:46 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_canvas_to_viewport_aa(int x, int y, int viewport, t_plan canvas, double aa[32], int i)
{
	double		d_viewport;
	double		d_width;
	double		d_height;
	t_vector	direction;

	d_viewport = (double)viewport;
	d_width = (double)canvas.width;
	d_height = (double)canvas.height;
	direction.x = (x + aa[2 * i]) * d_viewport / d_width;
	direction.y = (y + aa[2 * i + 1]) * d_viewport / d_width;
	direction.z = (double)canvas.distance;
	return (direction);
}

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

int			ft_color_average(int colors[16])
{
	int					i;
	unsigned long int	red;
	unsigned long int	green;
	unsigned long int	blue;

	i = 0;
	red = 0;
	green = 0;
	blue = 0;
	while (i < 16)
	{
		red += (unsigned long long int)((colors[i] & 16711680) >> 16) * (unsigned long long int)((colors[i] & 16711680) >> 16);
		green += (unsigned long long int)((colors[i] & 65280) >> 8) * (unsigned long long int)((colors[i] & 65280) >> 8);
		blue += (unsigned long long int)(colors[i] & 255) * (unsigned long long int)(colors[i] & 255);
		i++;
	}
	return ((int)(sqrt(red / 16)) << 16 | (int)(sqrt(green / 16)) << 8 | (int)sqrt(blue / 16));
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
#if MINI_RT_BONUS == 1
	int			i;
	double		aa[32] = {	-0.375,	0.375,
							-0.125,	0.375,
							0.125,	0.375,
							0.375,	0.375,
							-0.375,	0.125,
							-0.125,	0.125,
							0.125,	0.125,
							0.375,	0.125,
							-0.375,	-0.125,
							-0.125,	-0.125,
							0.125,	-0.125,
							0.375,	-0.125,
							-0.375,	-0.375,
							-0.125,	-0.375,
							0.125,	-0.375,
							0.375,	-0.375
	};
	int			colors[16];
#endif

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
#if MINI_RT_BONUS == 1
			pixel.color = 0;
			i = 0;
			while (i < 16)
			{
				direction = ft_canvas_to_viewport_aa(pixel.x, pixel.y, scene.plan.viewport,
						scene.plan, aa, i);
				colors[i] = ft_trace_ray(origin, direction, scene);
				i++;
			}
			pixel.color = ft_color_average(colors);
#else
			direction = ft_canvas_to_viewport(pixel.x, pixel.y, scene.plan.viewport,
					scene.plan);
			pixel.color = ft_trace_ray(origin, direction, scene);
#endif
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

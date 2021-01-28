/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:56:01 by vfurmane          #+#    #+#             */
/*   Updated: 2021/01/28 12:52:52 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

void			my_mlx_square_put(t_data *data, int x, int y, int width, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < width)
			my_mlx_pixel_put(data, x + i, y + j, color);
	}
}

int				main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_square_put(&img, 5, 5, 20,  0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:05:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/16 09:40:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_set_bmp_header(t_scene *scene, int fd)
{
	char	*header;

	header = malloc(55 * sizeof(*header));
	if (header == NULL)
		return (ft_fatal_error("Cannot allocate memory for the BMP file's header") * 0);
	header[54] = '\0';
	ft_memcpy(&header[0], "BM\0\0\0\0\0\0\0\0\1\0\0\0(\0\0\0\1\0\0\0\1\0\0\0\1\0\1\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 54);
	ft_memcpy(&header[18], (char*)&scene->plan.width, 4);
	ft_memcpy(&header[22], (char*)&scene->plan.height, 4);
	header[10] = 54;
	header[26] = 1;
	header[28] = 24;
	write(fd, header, 54);
	free(header);
	return (1);
}

void	ft_add_pixel_to_bmp(t_buffer *buffer, int color, int end_of_line)
{
	ft_memcpy(&buffer->str[buffer->i], (char*)&color, 3);
	buffer->i += 3;
	if (end_of_line > 0)
	{
		ft_memcpy(&buffer->str[buffer->i], "\0\0\0\0", end_of_line);
		buffer->i += end_of_line;
	}
}

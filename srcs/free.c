/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:31:03 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/10 14:44:29 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_split(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != NULL)
		free(strarr[i++]);
	free(strarr);
}

void	ft_free_gnl(int fd)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		free(line);
	}
	free(line);
}

void	ft_free_scene(t_scene **scene)
{
	free((*scene)->title);
	free((*scene)->ambiant);
	(*scene)->ambiant = NULL;
	ft_free_lst((*scene)->img);
	ft_free_lst((*scene)->cameras);
	ft_free_lst((*scene)->bulbs);
	ft_free_lst((*scene)->spheres);
	ft_free_lst((*scene)->planes);
	ft_free_lst((*scene)->cylinders);
	free((*scene)->mlx);
	free(*scene);
	*scene = NULL;
}

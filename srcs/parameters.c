/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:13:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/16 18:59:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_line(char *line, t_scene *scene)
{
	int		ret;
	char	**args;

	ret = 0;
	args = ft_split(line, "\t\v\f\r ");
	if (args == NULL)
		return (-1);
	if (ft_strcmp(args[0], "R") == 0)
		ret = ft_handle_resolution(&args[1], scene);
	else if (ft_strcmp(args[0], "A") == 0)
		ret = ft_handle_ambiant(&args[1], scene);
	else if (ft_strcmp(args[0], "l") == 0)
		ret = ft_handle_light(&args[1], scene);
	else if (ft_strcmp(args[0], "sp") == 0)
		ret = ft_handle_sphere(&args[1], scene);
	else if (ft_strcmp(args[0], "pl") == 0)
		ret = ft_handle_plane(&args[1], scene);
	else if (ft_strcmp(args[0], "cy") == 0)
		ret = ft_handle_cylinder(&args[1], scene);
	else if (args[0] != NULL)
		ret = -1;
	ft_free_split(args);
	return (ret);
}

int	ft_parse_scene(char *file, t_scene *scene)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDWR);
	if (fd == -1)
		return (-1);
	ret = get_next_line(fd, &line);
	while (ret != 0)
	{
		if (ret == -1)
			return (-1);
		if (ft_parse_line(line, scene) == -1)
			return (-1);
		free(line);
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (0);
}

int	ft_parameters(int argc, char **argv, t_scene *scene)
{
	int		i;
	char	*file;

	if (argc != 2)
		return (-1);
	i = 1;
	scene->bulbs = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	while (i < argc)
	{
		file = argv[i];
		if (ft_strcmp(ft_strrchr(file, '.'), ".rt") != 0)
		{
			errno = 22;
			ft_fatal_error("File extension is not .rt");
		}
		if (ft_parse_scene(file, scene) == -1)
			return (-1);
		i++;
	}
	return (0);
}

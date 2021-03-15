/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:13:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/17 09:27:02 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_line(char *line, t_scene *scene)
{
	static int	line_nbr;
	int			ret;
	char		**args;

	line_nbr++;
	ret = 0;
	args = ft_split(line, "\t\v\f\r ");
	free(line);
	if (args == NULL)
	{
		ft_fatal_error("Cannot parse the file's line");
		return (-1);
	}
	if (args[0] != NULL && args[0][0] == '#')
		ret = 0;
	else if (ft_strcmp(args[0], "R") == 0)
		ret = ft_handle_resolution(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "A") == 0)
	{
		if (scene->ambiant == NULL)
			ret = ft_handle_ambiant(&args[1], scene, line_nbr);
		else
		{
			printf("Error\nline %d: Ambiant light has already been set\n", line_nbr);
			ret = -1;
		}
	}
	else if (ft_strcmp(args[0], "c") == 0)
		ret = ft_handle_camera(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "l") == 0)
		ret = ft_handle_light(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "sp") == 0)
		ret = ft_handle_sphere(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "pl") == 0)
		ret = ft_handle_plane(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "cy") == 0)
		ret = ft_handle_cylinder(&args[1], scene, line_nbr);
	else if (args[0] != NULL)
	{
		printf("Error\nline %d: Unknown identifier '%s'\n", line_nbr, args[0]);
		ret = -1;
	}
	ft_free_split(args);
	return (ret);
}

int	ft_parse_scene(char *file, t_scene *scene)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = get_next_line(fd, &line);
	while (ret != 0)
	{
		if (ret == -1)
		{
			ft_fatal_error("Could not read the file");
			return (-1);
		}
		if (ft_parse_line(line, scene) == -1)
		{
			ft_free_gnl(fd);
			return (-1);
		}
		ret = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (0);
}

int	ft_parameters(int argc, char **argv, t_scene *scene)
{
	char	*file;

	scene->mlx = NULL;
	scene->win = NULL;
	scene->img = NULL;
	scene->plan.width = 0;
	scene->ambiant = NULL;
	scene->cameras = NULL;
	scene->bulbs = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	if (argc < 2 || argc > 3)
	{
		printf("Error\nUsage: %s scene [--save]\n", argv[0]);
		return (-1);
	}
	file = argv[1];
	if (ft_strcmp(ft_strrchr(file, '.'), ".rt") != 0)
	{
		printf("Error\nFile extension is not .rt\n");
		return (-1);
	}
	if (ft_parse_scene(file, scene) == -1)
		return (-1);
	if (scene->ambiant == NULL)
	{
		printf("Error\nAmbiant light never set\n");
		return (-1);
	}
	if (scene->cameras == NULL)
	{
		printf("Error\n0 camera defined, at least 1 needed\n");
		return (-1);
	}
	return (0);
}

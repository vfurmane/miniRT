/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:13:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 09:55:44 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_line(char *line, t_scene *scene)
{
	char	**args;

	args = ft_split(line, ' ');
	if (args == NULL)
		return (-1);
	if (ft_strcmp(args[0], "R") == 0)
		ft_handle_resolution(&args[1], scene);
	else if (ft_strcmp(args[0], "A") == 0)
		ft_handle_ambiant(&args[1], scene);
	else if (ft_strcmp(args[0], "l") == 0)
		ft_handle_light(&args[1], scene);
	else if (ft_strcmp(args[0], "") != 0)
		return (-1);
	return (0);
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
	scene->lights = NULL;
	while (i < argc)
	{
		file = argv[i];
		if (ft_parse_scene(file, scene) == -1)
			return (-1);
		i++;
	}
	return (0);
}

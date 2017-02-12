/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:33:34 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/02 15:22:05 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_count(char **line)
{
	int i;

	i = 0;
	while (line[i] != NULL)
		i++;
	return (i);
}

void	ft_count_lines_and_chars(char *file, t_win *infos)
{
	int		fd;
	int		ret;
	char	*line;
	char	**line_without_spaces;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("open");
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (infos->size_line == -1)
		{
			line_without_spaces = ft_strsplit(line, ' ');
			infos->size_line = ft_count(line_without_spaces);
			ft_destroy_tab_char(line_without_spaces);
		}
		free(line);
		(infos->nb_lines)++;
	}
	if (ret == -1)
		ft_error("get_next_line");
	free(line);
}

void	ft_copy(int i, t_win *infos, char **line_without_spaces)
{
	int j;

	j = 0;
	while (j < infos->size_line)
	{
		(infos->tab)[i][j] = ft_atoi(line_without_spaces[j]);
		ft_fill_color(i, j, infos, line_without_spaces);
		j++;
	}
}

void	ft_fill_tab(char *file, t_win *infos)
{
	int		fd;
	int		i;
	int		ret;
	char	*line;
	char	**line_without_spaces;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("open");
	i = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		line_without_spaces = ft_strsplit(line, ' ');
		if (ft_count(line_without_spaces) != infos->size_line)
			ft_error(" ");
		free(line);
		ft_copy(i, infos, line_without_spaces);
		ft_destroy_tab_char(line_without_spaces);
		i++;
	}
	if (ret == -1)
		ft_error("get_next_line");
	free(line);
}

void	get_infos(char *file, t_win *infos)
{
	int		i;

	ft_count_lines_and_chars(file, infos);
	infos->tab = (int **)malloc(sizeof(int *) * (infos->nb_lines + 1));
	infos->color = (int **)malloc(sizeof(int *) * (infos->nb_lines + 1));
	if (infos->tab == NULL || infos->color == NULL)
		ft_error("malloc");
	(infos->tab)[infos->nb_lines] = NULL;
	(infos->color)[infos->nb_lines] = NULL;
	i = 0;
	while (i < infos->nb_lines)
	{
		(infos->tab)[i] = (int *)malloc(sizeof(int) * (infos->size_line));
		(infos->color)[i] = (int *)malloc(sizeof(int) * (infos->size_line));
		if ((infos->tab)[i] == NULL || infos->color[i] == NULL)
			ft_error("malloc");
		i++;
	}
	ft_fill_tab(file, infos);
}

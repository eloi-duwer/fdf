/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:09:49 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/06 12:09:14 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_destroy_tab_int(int **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_destroy_tab_char(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		high(t_win *infos)
{
	int max_high;
	int high;
	int i;
	int j;

	i = 0;
	max_high = -100;
	while (i < infos->nb_lines)
	{
		j = 0;
		while (j < infos->size_line)
		{
			high = infos->tab[i][j] * infos->glob_size * 2.5;
			high -= (i * infos->glob_size + (infos->size_line - j - 1) \
					* infos->glob_size);
			if (max_high < high)
			{
				infos->max_high = infos->tab[i][j];
				max_high = high;
			}
			j++;
		}
		i++;
	}
	return (max_high);
}

void	ft_fill_color(int i, int j, t_win *infos, char **line)
{
	int k;

	if (infos->automatic_color == 0)
	{
		k = 0;
		while (line[j][k] >= '0' && line[j][k] <= '9')
			k++;
		if (line[j][k] == ',')
			(infos->color)[i][j] = (int)strtol(&line[j][k + 1], NULL, 16);
		else
			(infos->color)[i][j] = COLOR_WHITE;
	}
}

void	set_automatic_color(t_win *infos)
{
	int i;
	int j;
	int color_per_unit;

	color_per_unit = (0x00FF0000 - 0x000000FF) / (infos->max_high - 1);
	i = 0;
	while (i < infos->nb_lines)
	{
		j = 0;
		while (j < infos->size_line)
		{
			infos->color[i][j] = 0x000000FF + color_per_unit * infos->tab[i][j];
			j++;
		}
		i++;
	}
}

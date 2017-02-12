/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:39:43 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/06 11:16:55 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_find_the_size(t_win *infos)
{
	int		nb_lines;
	int		size_line;

	infos->glob_size = 20;
	nb_lines = infos->nb_lines;
	size_line = infos->size_line;
	infos->size_x = 99999999;
	infos->size_y = 99999999;
	while ((infos->size_x > 2400 || infos->size_y > 1400) \
				&& infos->glob_size >= 1)
	{
		infos->size_x = (nb_lines + size_line - 2) * infos->glob_size * 2;
		infos->size_y = ((nb_lines + size_line - 2) * infos->glob_size) \
						+ high(infos);
		infos->glob_size--;
	}
	(infos->glob_size)++;
	infos->size_x += 100;
	infos->size_y += 100;
	ft_find_coord_first_point(infos);
}

void	ft_find_coord_first_point(t_win *info)
{
	info->first_x = (double)50;
	info->first_y = (double)(info->size_y - 50 - info->nb_lines \
						* info->glob_size);
	info->x = 0;
	info->y = 0;
	info->win = mlx_new_window(info->mlx, info->size_x, info->size_y, "fdf");
	ft_do_it(info);
}

void	ft_do_it(t_win *info)
{
	if (info->automatic_color == 1)
		set_automatic_color(info);
	while (info->y < info->nb_lines)
	{
		calc_one_line(info);
		(info->y)++;
	}
	ft_destroy_tab_int(info->tab);
	ft_destroy_tab_int(info->color);
}

void	calc_one_line(t_win *inf)
{
	double	pt1[3];
	double	y;

	pt1[0] = inf->first_x + (double)((inf->x + inf->y) * inf->glob_size * 2);
	y = inf->first_y - (double)((inf->x - inf->y) * inf->glob_size);
	pt1[1] = y - ((double)((inf->tab)[inf->y][inf->x] * inf->glob_size * 2.5));
	pt1[2] = (double)(inf->color)[inf->y][inf->x];
	if (inf->x < inf->size_line - 1)
	{
		(inf->x)++;
		calc_second_pt(inf, pt1);
		calc_one_line(inf);
		(inf->x)--;
	}
	if (inf->y < inf->nb_lines - 1)
	{
		(inf->y)++;
		calc_second_pt(inf, pt1);
		(inf->y)--;
	}
}

void	calc_second_pt(t_win *inf, double pt1[3])
{
	double pt2[3];
	double y;

	pt2[0] = inf->first_x + (double)((inf->x + inf->y) * inf->glob_size * 2);
	y = inf->first_y - (double)((inf->x - inf->y) * inf->glob_size);
	pt2[1] = y - ((double)((inf->tab)[inf->y][inf->x] * inf->glob_size * 2.5));
	pt2[2] = (double)(inf->color)[inf->y][inf->x];
	draw_a_line(inf, pt1, pt2);
}

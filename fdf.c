/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:29:17 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/06 16:23:15 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_error(char *s)
{
	if (*s != ' ')
		perror(s);
	else
		write(2, "Found wrong line lenght. Exiting.\n", 34);
	exit(0);
}

void		redraw_the_line(t_win *info, double pt1[3], double pt2[3])
{
	double x;
	double y;
	double a;
	double b;
	double y_max;

	y = nearbyint(fmin(pt1[1], pt2[1]));
	y_max = nearbyint(fmax(pt1[1], pt2[1]));
	if (pt1[1] < pt2[1])
		info->color_to_put = pt1[2];
	else
		info->color_to_put = pt2[2];
	if (pt1[1] != pt2[1])
	{
		a = ((pt2[0] - pt1[0]) / (pt2[1] - pt1[1]));
		b = pt1[0] - (pt1[1] * a);
		while (y <= y_max)
		{
			x = nearbyint(a * y + b);
			mlx_pixel_put(info->mlx, info->win, x, y, info->color_to_put);
			y++;
		}
	}
}

void		draw_a_line(t_win *infos, double cor1[3], double cor2[3])
{
	double x;
	double y;
	double a;
	double b;
	double x_max;

	x = nearbyint(fmin(cor1[0], cor2[0]));
	x_max = nearbyint(fmax(cor1[0], cor2[0]));
	infos->color_to_put = cor1[2];
	if (cor1[0] != cor2[0])
	{
		a = ((cor2[1] - cor1[1]) / (cor2[0] - cor1[0]));
		b = cor1[1] - (cor1[0] * a);
		while (x <= x_max)
		{
			y = nearbyint(a * x + b);
			mlx_pixel_put(infos->mlx, infos->win, x, y, infos->color_to_put);
			x++;
		}
	}
	redraw_the_line(infos, cor1, cor2);
}

int			funct_key_escape(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(((t_win *)param)->mlx, ((t_win *)param)->win);
		exit(1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_win infos;

	if (argc == 1 || argc >= 4)
	{
		write(2, "Usage : ./fdf [-c] <filename>\n", 31);
		exit(0);
	}
	infos.size_line = -1;
	infos.nb_lines = 0;
	if (ft_strncmp(argv[1], "-c", 3) == 0)
	{
		infos.automatic_color = 1;
		get_infos(argv[2], &infos);
	}
	else
	{
		infos.automatic_color = 0;
		get_infos(argv[1], &infos);
	}
	infos.mlx = mlx_init();
	ft_find_the_size(&infos);
	mlx_key_hook(infos.win, funct_key_escape, &infos);
	mlx_loop(infos.mlx);
	return (0);
}

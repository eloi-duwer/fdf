/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:09:27 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/06 16:24:27 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define COLOR_WHITE 0xFFFFFF
# include <mlx.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>

typedef struct	s_win
{
	void	*mlx;
	void	*win;
	int		**tab;
	int		**color;
	int		size_line;
	int		nb_lines;
	int		size_x;
	int		size_y;
	int		glob_size;
	int		x;
	int		y;
	double	first_x;
	double	first_y;
	int		automatic_color;
	int		max_high;
	int		color_to_put;
	int		red_to_add;
	int		green_to_add;
	int		blue_to_add;
}				t_win;

void			ft_error(char *s);
void			draw_a_line(t_win *infos, double cor1[3], double cor2[3]);
void			redraw_the_line(t_win *infos, double cor1[3], double cpr2[3]);
int				funct_key_escape(int keycode, void *param);
int				ft_count(char **line);
void			ft_count_lines_and_chars(char *file, t_win *infos);
void			ft_copy(int i, t_win *infos, char **line_without_spaces);
void			ft_fill_tab(char *file, t_win *infos);
void			get_infos(char *file, t_win *infos);
void			ft_find_the_size(t_win *infos);
void			ft_find_coord_first_point(t_win *infos);
void			ft_do_it(t_win *info);
void			calc_one_line(t_win *info);
void			calc_second_pt(t_win *info, double pt1[3]);
void			ft_destroy_tab_int(int **tab);
void			ft_destroy_tab_char(char **tab);
int				high(t_win *infos);
void			ft_fill_color(int i, int j, t_win *infos, char **line);
void			set_automatic_color(t_win *infos);

#endif

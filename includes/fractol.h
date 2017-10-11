/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:12:24 by cweather          #+#    #+#             */
/*   Updated: 2017/10/10 21:36:29 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "keys.h"
# include <time.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

typedef struct	s_fract
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	char		*argv;
	int			bpp;
	int			endian;
	int			sizeline;
	float		x;
	float		y;
	int			padding;
	double		c_1;
	double		c_2;
	double		zoom;
	float		size_tree;
	float		size_tree2;
	int			n;
	int			r;
	int			g;
	int			b;
	int			c;
	clock_t		clock_prg;
	int			tree;
	int			(*f)(struct s_fract *, int, int);
	int			draw_end;
	int			power;
}				t_fract;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

int				expose_hook(t_fract *f);
int				key_hook(int key, t_fract *f);
int				mouse_move(int x, int y, t_fract *f);
int				mouse_hook(int button, int x, int y, t_fract *f);
void			init_fractal(t_fract *f, char *argv);
void			error(char *reason);
void			draw_tree(t_fract *f, t_coord start, double angle, int iter);
void			draw_fractal(t_fract *fr, int (*f)(t_fract *, int, int));
void			draw(t_fract *fr, int (*f)(t_fract *, int, int));
void			parse(t_fract *f, int argc, char **argv);
void			put_pixel(t_fract *f, int x, int y, int c);
int				mandelbrot(t_fract *f, int x, int y);
int				julia(t_fract *f, int x, int y);
int				burning_ship(t_fract *f, int x, int y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 19:31:17 by cweather          #+#    #+#             */
/*   Updated: 2017/10/09 20:45:01 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		put_line(t_fract *f, t_coord start, t_coord end, int c)
{
	double		dd;
	double		x;
	double		y;
	double		dx;
	double		dy;

	x = start.x;
	y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	dd = sqrt((dx * dx) + (dy * dy));
	dx = dx / dd;
	dy = dy / dd;
	while (dd-- >= 0)
	{
		put_pixel(f, x, y, c);
		x += dx;
		y += dy;
	}
}

void			draw_tree(t_fract *f, t_coord start, double angle, int iter)
{
	t_coord		end;
	int			c;

	if (iter > 0)
	{
		end.x = start.x + (cos(angle) * iter * 6) * f->zoom;
		end.y = start.y + (sin(angle) * iter * 9) * f->zoom;
		c = ((50 + f->r * iter) << 16) + ((f->g * iter) << 8)
			+ (155 - f->b * iter);
		put_line(f, start, end, c);
		draw_tree(f, end, angle - (M_PI / 8 * f->size_tree * 2), iter - 1);
		draw_tree(f, end, angle + (M_PI / 8 * f->size_tree2 * 2), iter - 1);
	}
}

void			draw_fractal(t_fract *fr, int (*f)(t_fract *, int, int))
{
	int			x;
	int			y;
	int			i;
	int			c;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 600)
		{
			i = (*f)(fr, x, y);
			c = ((255 - i * fr->r) << 16) + ((255 - i * fr->g) << 8)
				+ (255 - i * fr->b);
			if (i != fr->n)
				put_pixel(fr, x, y, c);
			x++;
		}
		y++;
	}
}

static void		fill_image(t_fract *fr, int (*f)(t_fract *, int, int))
{
	t_coord		coord;

	coord.x = 300 - (fr->x * (fr->zoom / 4.1));
	coord.y = 580 + (fr->y * (fr->zoom / 1.2));
	if (!(fr->data = mlx_get_data_addr(fr->img,
					&fr->bpp, &fr->sizeline, &fr->endian)))
		error("Map error");
	else if (!fr->tree)
		draw_fractal(fr, f);
	else
		draw_tree(fr, coord, -(M_PI / 2), fr->n);
}

void			draw(t_fract *fr, int (*f)(t_fract *, int, int))
{
	if ((fr->img = mlx_new_image(fr->mlx, 600, 600)))
	{
		fill_image(fr, f);
		mlx_put_image_to_window(fr->mlx, fr->win, fr->img, 0, 0);
		mlx_destroy_image(fr->mlx, fr->img);
	}
}

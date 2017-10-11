/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 02:49:52 by cweather          #+#    #+#             */
/*   Updated: 2017/10/09 21:29:11 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mandelbrot(t_fract *f, int x, int y)
{
	int			i;
	double		z_1;
	double		z_2;
	double		temp;

	f->c_1 = 1.5 * (x - 300) / (0.5 * f->zoom * 600)
		+ (f->x / 600 / 1.37) - 0.5;
	f->c_2 = (y - 300) / (0.5 * f->zoom * 600)
		- (f->y / 600 / 1.92);
	z_1 = 0;
	z_2 = 0;
	i = 0;
	while (z_1 * z_1 + z_2 * z_2 <= 4 && i < f->n)
	{
		temp = z_1;
		z_1 = temp * temp - z_2 * z_2 + f->c_1;
		z_2 = 2 * temp * z_2 + f->c_2;
		i++;
	}
	return (i);
}

int				julia(t_fract *f, int x, int y)
{
	double		z_1;
	double		z_2;
	double		temp;
	int			i;

	z_1 = ((4 * (float)x / 600 - 2) / f->zoom) + ((f->x / 600));
	z_2 = ((-4 * (float)y / 600 + 2) / f->zoom) + ((f->y / 600));
	i = 0;
	while (z_1 * z_1 + z_2 * z_2 <= 4 && i < f->n)
	{
		temp = z_1;
		z_1 = z_1 * z_1 - z_2 * z_2 + f->c_1;
		z_2 = 2 * temp * z_2 + f->c_2;
		i++;
	}
	return (i);
}

int				burning_ship(t_fract *f, int x, int y)
{
	int			i;
	double		z_1;
	double		z_2;
	double		temp;

	f->c_1 = 1.5 * (x - 300) / (0.5 * f->zoom * 600)
		+ (f->x / 600 / 1.30) - 0.5;
	f->c_2 = (y - 300) / (0.5 * f->zoom * 600)
		- (f->y / 600 / 1.97);
	z_1 = 0;
	z_2 = 0;
	i = 0;
	while (z_1 * z_1 + z_2 * z_2 <= 4 && i < f->n)
	{
		temp = z_1;
		z_1 = ft_fabs(temp * temp) - z_2 * z_2 + f->c_1;
		z_2 = 2 * ft_fabs(temp * z_2) + f->c_2;
		i++;
	}
	return (i);
}

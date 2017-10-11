/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 23:11:00 by cweather          #+#    #+#             */
/*   Updated: 2017/10/06 03:16:10 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				expose_hook(t_fract *f)
{
	draw(f, f->f);
	return (0);
}

int				key_hook(int key, t_fract *f)
{
	(key == K_ESC) ? exit(0) : (0);
	(key == K_ARU) ? f->y += 50 / f->zoom : (0);
	(key == K_ARD) ? f->y -= 50 / f->zoom : (0);
	(key == K_ARL) ? f->x -= 50 / f->zoom : (0);
	(key == K_ARR) ? f->x += 50 / f->zoom : (0);
	(key == K_NUM_P) ? f->n++ : (0);
	(key == K_NUM_N) ? f->n-- : (0);
	if (key == K_C)
		f->c = (f->c) ? 0 : 1;
	(key == K_R && !f->tree) ? init_fractal(f, f->argv) : (0);
	(key == K_NUM1 && f->r > 0) ? f->r-- : (0);
	(key == K_NUM2 && f->g > 0) ? f->g-- : (0);
	(key == K_NUM3 && f->b > 0) ? f->b-- : (0);
	(key == K_NUM4) ? f->r = 5 : (0);
	(key == K_NUM5) ? f->g = 5 : (0);
	(key == K_NUM6) ? f->b = 5 : (0);
	(key == K_NUM7) ? f->r++ : (0);
	(key == K_NUM8) ? f->g++ : (0);
	(key == K_NUM9) ? f->b++ : (0);
	draw(f, f->f);
	return (0);
}

int				mouse_move(int x, int y, t_fract *f)
{
	if (((200) * (clock() - f->clock_prg)) /
			CLOCKS_PER_SEC > 1 && f->c && !f->tree)
	{
		f->clock_prg = clock();
		x -= 300;
		y -= 300;
		f->c_1 = ((float)x / 600) * 2;
		f->c_2 = ((float)y / 600) * 2;
		draw(f, f->f);
	}
	else if (((950) * (clock() - f->clock_prg)) /
			CLOCKS_PER_SEC > 1 && f->c && f->tree)
	{
		f->clock_prg = clock();
		f->size_tree = (float)y / 600;
		f->size_tree2 = (float)x / 600;
		draw(f, f->f);
	}
	return (0);
}

int				mouse_hook(int button, int x, int y, t_fract *f)
{
	x -= 300;
	y -= 300;
	if (button == M_SCROLL_P)
	{
		f->zoom *= 1.1;
		f->x += x / f->zoom / 2.51;
		f->y -= y / f->zoom / 2.51;
	}
	else if (button == M_SCROLL_N && f->zoom > 0.1)
		f->zoom /= 1.1;
	if (button == M_SCROLL_P || button == M_SCROLL_N)
		draw(f, f->f);
	return (0);
}

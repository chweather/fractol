/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:32:44 by cweather          #+#    #+#             */
/*   Updated: 2017/10/10 21:35:42 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		instructions(void)
{
	ft_putendl("\t Fractol is controlled with the");
	ft_putendl("\t      numpad mapped as:\n");
	ft_putendl("\t C : lock/unlock mouse move hook\n");
	ft_putendl("\t       R : reset to default\n");
	ft_putendl("\t\e[90m┌──────┬──────┬──────┬──────┐\e[0m");
	ft_putendl("\t\e[90m| clear|    = |    / |    * |\e[0m");
	ft_putendl("\t\e[90m|      |      |      |      |\e[0m");
	ft_putendl("\t\e[90m├──────┼──────┼──────┼──────┤\e[0m");
	ft_putendl("\t\e[90m|    7 |    8 |    9 |    - |\e[0m");
	ft_putstr("\t\e[90m|  \e[1;31mR+\e[90m  |  \e[1;32mG+\e[90m  |  ");
	ft_putstr("\e[1;94mB+\e[90m  |  \e[93mN-\e[90m  |\n\e[0m");
	ft_putendl("\t\e[90m├──────┼──────┼──────┼──────┤\e[0m");
	ft_putendl("\t\e[90m|    4 |    5 |    6 |    + |\e[0m");
	ft_putstr("\t\e[90m|  \e[1;31mRR\e[90m  |  \e[1;32mGR\e[90m  |  ");
	ft_putstr("\e[1;94mBR\e[90m  |  \e[93mN+\e[90m  |\n\e[0m");
	ft_putendl("\t\e[90m├──────┼──────┼──────┼──────┤\e[0m");
	ft_putendl("\t\e[90m|    1 |    2 |    3 |      |\e[0m");
	ft_putstr("\t\e[90m|  \e[1;31mR-\e[90m  |  \e[1;32mG-\e[90m  |  ");
	ft_putstr("\e[1;94mB-\e[90m  |      |\n\e[0m");
	ft_putendl("\t\e[90m├──────┴──────┼──────┤      |\e[0m");
	ft_putendl("\t\e[90m|             |      |      |\e[0m");
	ft_putendl("\t\e[90m|      0      |    . | enter|\e[0m");
	ft_putendl("\t\e[90m└─────────────┴──────┴──────┘\e[0m");
	ft_putendl("\n\t  \e[1;104;97m Press [ESC] to quit Fractol \e[0m\n\n");
}

void			put_pixel(t_fract *f, int x, int y, int c)
{
	int			r;
	int			g;
	int			b;

	r = (c & 0xFF0000) >> 16;
	g = (c & 0xFF00) >> 8;
	b = (c & 0xFF);
	if (y >= 0 && x >= 0 && y < 600 && x < 600)
	{
		f->data[(y * f->sizeline) + ((f->bpp / 8) * x) + 2] = r;
		f->data[(y * f->sizeline) + ((f->bpp / 8) * x) + 1] = g;
		f->data[(y * f->sizeline) + ((f->bpp / 8) * x)] = b;
	}
}

void			init_fractal(t_fract *f, char *argv)
{
	instructions();
	f->img = NULL;
	f->x = 0;
	f->y = 0;
	f->argv = ft_strdup(argv);
	f->padding = 10;
	f->c_1 = 0;
	f->c_2 = 0;
	f->zoom = 1;
	f->n = 100;
	f->r = 6;
	f->g = 2;
	f->b = 10;
	f->size_tree = 1;
	f->size_tree2 = 1;
	f->tree = 0;
	f->c = 1;
}

void			error(char *reason)
{
	ft_putendl_fd("\e[1;31mKO\n", 2);
	ft_putendl_fd(reason, 2);
	ft_putstr_fd("\e[0m", 2);
	exit(EXIT_FAILURE);
}

int				main(int argc, char **argv)
{
	t_fract		f;

	if (argc < 2 || ft_strlen(argv[1]) != 2)
		error("Usage: ./fractol [-J | -M | -B | -T]");
	else
	{
		init_fractal(&f, argv[0]);
		parse(&f, argc, argv);
	}
	if ((f.mlx = mlx_init()))
	{
		if (!(f.win = mlx_new_window(f.mlx, 600, 600, "fractol")))
			error("Failed to make window");
		else
		{
			mlx_key_hook(f.win, key_hook, &f);
			mlx_expose_hook(f.win, expose_hook, &f);
			mlx_hook(f.win, 6, (1L << 6), mouse_move, &f);
			mlx_hook(f.win, 4, (1L << 2), mouse_hook, &f);
			mlx_loop(f.mlx);
		}
	}
	else
		error("Failed to initialize");
	return (0);
}

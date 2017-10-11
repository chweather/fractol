/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cweather <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 01:55:57 by cweather          #+#    #+#             */
/*   Updated: 2017/10/09 21:32:02 by cweather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		parse_2(t_fract *f, char **argv, int *i, int *j)
{
	f->f = (argv[*i][*j] == 'J') ? julia : f->f;
	if (argv[*i][*j] == 'M')
		f->f = mandelbrot;
	else if (argv[*i][*j] == 'B')
		f->f = burning_ship;
	else if (argv[*i][*j] == 'T')
	{
		f->tree = 1;
		f->n = 10;
	}
	else if (f->f != julia)
		return (0);
	return (1);
}

static void		print_arg_error(void)
{
	ft_error("Usage: ./fractol [-J | -M | -B | -T]");
}

void			parse(t_fract *f, int argc, char **argv)
{
	int			i;
	int			j;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1])
		{
			j = 1;
			while (argv[i][j])
			{
				if (parse_2(f, argv, &i, &j))
					;
				else
					print_arg_error();
				j++;
			}
		}
		else
			print_arg_error();
		i++;
	}
}

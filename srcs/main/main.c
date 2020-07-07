/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:16:15 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/07 20:51:48 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		escape(void)
{
	exit(1);
	return (0);
}

int		key_press(int key, t_data *p)
{
	p = NULL;
	if (key == 53)
		exit(escape());
	return (0);
}

void 	print_vec(t_vector v)
{
	printf("x = %f\ny = %f\nz = %f\n", v.x, v.y, v.z);
}

void	test(t_data *p, char **av)
{
	t_orb o;

	//o = orb_init(0, 0, 3, 1, 0xFF0000);
	o = orb_init(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]), 16711680);
	render(p, &o);
	drow(p);
}

int main(int ac, char **av)
{
	t_data	p;

	if (ac)
	{
		//if ((read_file(&p, av[1])) == -1)
		//	return (0);
		init(&p);
		test(&p, av);
		mlx_put_image_to_window(p.mlx.mlx, p.mlx.win, p.img.img, 0, 0);
		mlx_hook(p.mlx.win, 2, 0, key_press, &p);
		mlx_hook(p.mlx.win, 17, 1L << 17, escape, &p);
		mlx_loop(p.mlx.mlx);
	}
	/*else
		ft_putstr("\nUsage: ./RTv1 <scene>\n\n");*/
	return(0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:16:15 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/30 18:35:00 by mgalt            ###   ########.fr       */
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

int main(int ac, char **av)
{
	t_data	p;

	if (ac == 2)
	{
		if ((read_file(&p, av[1])) == -1)
			return (0);
		mlx_put_image_to_window(p.mlx.mlx, p.mlx.win, p.img.img, 0, 0);
		mlx_hook(p.mlx.win, 2, 0, key_press, &p);
		mlx_hook(p.mlx.win, 17, 1L << 17, escape, &p);
		mlx_loop(p.mlx.mlx);
	}
	else
		error_output(USAGE);
	return(0);
}
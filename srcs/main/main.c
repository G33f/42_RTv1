/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:16:15 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 15:16:19 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 	print_vec(t_vector v)
{
	printf("x = %f\ny = %f\nz = %f\n", v.x, v.y, v.z);
}

void	test(t_data *p)
{
	t_orb o;

	o = orb_init(2, 2, 7, 1, 0xAAAAAA, 800);
	render(p, &o);
	drow(p);
}

int main()
{
	t_data	p;

	init(&p);
	test(&p);
	mlx_put_image_to_window(p.mlx.mlx, p.mlx.win, p.img.img, 0, 0);
	mlx_loop(p.mlx.mlx);
	return(0);
}

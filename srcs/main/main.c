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

void	test(t_data *p)
{
	render(p, init_orb(0, 0, 750, 20, 0xFF0000));
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
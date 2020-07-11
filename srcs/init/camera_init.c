/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:55:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/11 14:50:53 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_orb	orb_init(int x, int y, int z, int r, int color, double spec)
{
	t_orb orb;

	orb.x = x;
	orb.y = y;
	orb.z = z;
	orb.r = r;
	orb.color = color;
	orb.specular = spec;
	return(orb);
}

void	init_mlx(t_data *p)
{
	int w;
	int h;

	w = WIN_SIZE_X;
	h = WIN_SIZE_Y;
	if(!(p->mlx.mlx = mlx_init()))
		error(-13);
	if(!(p->mlx.win = mlx_new_window(p->mlx.mlx, w, h, "RTv1")))
		error(-13);
	if(!(p->img.img = mlx_new_image(p->mlx.mlx, w, h)))
		error(-13);
	if(!(p->img.img_data = (int *)mlx_get_data_addr(p->img.img, &p->img.bit_per_pixel,
			&p->img.size_line, &p->img.endline)))
		error(-13);
	if(!(p->canv.img = mlx_new_image(p->mlx.mlx, p->camera.canv_w, p->camera.canv_h)))
		error(-13);
	if(!(p->canv.img_data = (int *)mlx_get_data_addr(p->canv.img, &p->canv.bit_per_pixel,
			&p->canv.size_line, &p->canv.endline)))
		error(-13);
}


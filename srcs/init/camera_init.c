/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:55:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 15:55:14 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_img	*creat_image(t_data *p, int w, int h)
{
	t_img	img;

	if(!(img.img = mlx_new_image(p->mlx.mlx, w, h)))
		error(-13);
	if(!(img.img_data = (int *)mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.size_line
			, &img.endline)))
		error(-13);
	return(&img);
}

void	init_mlx(t_data *p)
{
	if(!(p->mlx.mlx = mlx_init()))
		error(-13);
	if(!(p->mlx.win = mlx_new_window(p->mlx.mlx, WIN_SIZE_X, WIN_SIZE_Y, "wolf3d")))
		error(-13);
	if(!(p->img.img = mlx_new_image(p->mlx.mlx, WIN_SIZE_X, WIN_SIZE_Y)))
		error(-13);
	if(!(p->img.img_data = (int *)mlx_get_data_addr(p->img.img, &p->img.bit_per_pixel, &p->img.size_line
			, &p->img.endline)))
		error(-13);
}

int		init(t_data *p)
{
	camera_init(p);
	init_mlx(p);
	return(0);
}
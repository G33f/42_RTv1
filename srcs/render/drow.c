/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 04:00:23 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/08 17:27:53 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	drow(t_data *p)
{
	int x;
	int y;

	y = 0;
	ft_putstr("draw\n");
	while (y < WIN_SIZE_Y)
	{
		x = 0;
		while (x < WIN_SIZE_X)
		{
			p->img.img_data[x + y * WIN_SIZE_X] = p->canv.img_data[(x * p->camera.canv_w / WIN_SIZE_X) + p->camera.canv_w * (y * p->camera.canv_h / WIN_SIZE_Y)];
			x++;
		}
		y++;
	}
	return(0);
}

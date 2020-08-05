/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 10:20:34 by wpoudre           #+#    #+#             */
/*   Updated: 2020/08/05 16:42:10 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		color(int color, double i)
{
	int		red;
	int		green;
	int		blue;

	red = (color >> 16) & 0xFF;
	red = (int)(red * i);
	//0xF1FFCC
	if (red > 0x0000FF)
		red = 0x0000FF;
	green = (color >> 8) & 0xFF;
	green = (int)(green * i);
	if (green > 0x0000FF)
		green = 0x0000FF;
	blue = (color & 0xFF);
	blue = (int)(blue * i);
	if (blue > 0x0000FF)
		blue = 0x0000FF;
	return ((red << 16) | (green << 8) | blue);
}

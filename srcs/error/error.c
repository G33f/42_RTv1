/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 18:21:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/30 18:36:27 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error_log(int cod)
{
	if (cod == 1)
		ft_putstr("Low memory((\n");
	else if (cod == 2)
		ft_putstr("Incorect SCEN");
	exit(0);
}

void	usage(int cod)
{
	if (cod == 1)
		ft_putstr("Use ./RTv1 [any_scen.rce]\n");
	else if (cod == 2)
		ft_putstr("Use corect ./RTv1 [any_scen.rce]\n");
	exit(0);
}

void	error(int cod)
{
	if (cod == -10)
		usage(1);
	else if (cod == -11)
		usage(2);
	else if (cod == -12)
		error_log(1);
	else if (cod == -13)
		error_log(2);
}

int		error_output(int err)
{
	if (err == USAGE)
		ft_putstr("\nUsage: ./RTv1 <scene>\n\n");
	if (err == NO_CAMERA)
		ft_putstr("\nFile is invalid: no camera in a scene\n\n");
	if (err == NO_OBJECTS)
		ft_putstr("\nFile is invalid: no objects found\n\n");
	if (err == NO_FD)
		ft_putstr("\nError: cannot open file\n\n");
	if (err == PARAMETERS)
		ft_putstr("\nObject is invalid: wrong number of parameters\n\n");
	if (err == INVALID)
		ft_putstr("\nInvalid Parameter\n\n");
	return (-1);
}

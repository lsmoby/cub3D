/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 19:54:17 by marvin            #+#    #+#             */
/*   Updated: 2020/10/22 05:26:15 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*s2;

	i = ft_strlen(s);
	s2 = (char*)s;
	while (i >= 0)
	{
		if (s2[i] == c)
		{
			return (&s2[i]);
		}
		i--;
	}
	return (NULL);
}

int		rgbtoint(int r, int g, int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

double	dis_2_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

float	normalise_angle(float angle)
{
	angle = remainder(angle, 360);
	(angle < 0) ? angle += 360 : 0;
	return (angle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:38:07 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 05:30:06 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_assign(int cf, int cd, char const *s)
{
	char	*ret;

	ret = NULL;
	if (cf >= (int)ft_strlen(s))
	{
		if (!(ret = (char*)malloc(1)))
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	else if ((cf + cd) != 0 && cf != (int)ft_strlen(s))
	{
		if ((ret = (char *)ft_calloc(ft_strlen(s)
		- (cd + cf) + 1, sizeof(char))))
			ft_strlcpy(ret, (s + cd), (ft_strlen(s) - (cd + cf)) + 1);
	}
	else
		ret = ft_strdup(s);
	return (ret);
}

char		*ft_strtrim(char const *s, char const *set)
{
	int		len;
	int		cd;
	int		cf;

	if (!s)
		return (NULL);
	if (!set)
		return (ft_strdup(s));
	cd = 0;
	cf = 0;
	len = (ft_strlen(s) - 1);
	while (ft_strchr(set, s[cd]))
		cd++;
	while (ft_strchr(set, s[len]))
	{
		len--;
		cf++;
	}
	return (ft_assign(cf, cd, s));
}

int			map_size(char **line)
{
	char	**save;
	int		i;

	save = line;
	g_game_data.map.columns = 0;
	g_game_data.map.rows = 1;
	i = 0;
	while (*save)
	{
		i = ft_strlen(*save);
		(i > g_game_data.map.columns) ? g_game_data.map.columns = i : 0;
		g_game_data.map.rows++;
		save++;
	}
	g_game_data.map.columns += 2;
	return (1);
}

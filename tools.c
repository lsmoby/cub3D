/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:34 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/02 15:41:36 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *dst, size_t nbyte)
{
	if (nbyte > 0)
		ft_memset(dst, 0, nbyte);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*str;

	if (size == 0)
	{
		n = 1;
		size = 1;
	}
	if ((str = MALLOC(n * size)) == NULL)
		return (NULL);
	ft_bzero(str, n * size);
	return (str);
}

int		ft_comp(char *str, char *f)
{
	while (*str && *f)
	{
		if (*str != *f)
			return (0);
		str++;
		f++;
	}
	if (*f == '\0')
		return (1);
	return (0);
}

char	*ft_strtrimall(char *s, char *set)
{
	char	*ret;
	int		i;
	int		j;
	size_t	len;
	size_t	size;

	len = ft_strlen(s) + 1;
	size = 0;
	i = 0;
	j = 0;
	while (len-- != 0)
		if (!(ft_strchr(set, s[i++])))
			size++;
	ret = ft_calloc(size + 1, sizeof(char));
	i = 0;
	while (s[i])
	{
		if (!(ft_strchr(set, s[i])))
			ret[j++] = s[i];
		i++;
	}
	return (ret);
}

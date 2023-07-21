/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:23:24 by rsabbah           #+#    #+#             */
/*   Updated: 2023/07/08 08:02:05 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*s1cast;
	const char	*s2cast;
	size_t		i;

	s1cast = (const char *)s1;
	s2cast = (const char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s1cast[i] == s2cast[i] && i < n - 1)
		i++;
	return ((unsigned char)s1cast[i] - (unsigned char)s2cast[i]);
}

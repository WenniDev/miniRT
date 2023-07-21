/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:23:35 by rsabbah           #+#    #+#             */
/*   Updated: 2023/07/08 08:02:05 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 @brief duplicate a string
 @param s the string
*/
char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:32:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 10:51:57 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	k = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (0);
	while (s1[j] && isset(s1[j], set))
		j++;
	while (k > j && isset(s1[k], set))
		k--;
	str = ft_malloc(sizeof(char) * ((k + 1) - j + 1));
	if (!str)
		return (NULL);
	while (j <= k)
		str[i++] = s1[j++];
	str[i] = '\0';
	return (str);
}

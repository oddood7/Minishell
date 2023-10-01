/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:32:39 by lde-mais          #+#    #+#             */
/*   Updated: 2022/11/18 16:01:49 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == 0)
		return (NULL);
	if (len < start)
		len = 0;
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (len != 0)
		ft_strlcpy(str, s + start, len + 1);
	else
		*str = 0;
	return (str);
}

/* int    main()
{
    char str[] = "tripouille";
    //int    start = 7;
    //int    len = 3;
    printf(" %s", ft_substr(str, 100, 1));
	free(str);
	return (0);
} */
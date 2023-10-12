/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:32:39 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/12 17:04:01 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_substr(const char *s, unsigned int start, size_t len)
{
    char        *str;

    if (!s)
        return (NULL);
    if (ft_strlen(s) < start)
        len = 0;
    else if (ft_strlen(s + start) < len)
        len = ft_strlen(s + start);
    str = malloc(sizeof(char) * len + 2);
    if (!str)
        return (NULL);
    if (len != 0)
        ft_strlcpy(str, s + start, len);
    else
        *str = 0;
    return (str);
}

/* int    main()
{
    char str[] = "tripouille";
    //int    start = 7;
    //int    len = 3;
    ft_printf(" %s", ft_substr(str, 100, 1));
	free(str);
	return (0);
} */
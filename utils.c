/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:47:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/06/29 14:25:42 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (count);
	while (s[count])
		count++;
	return (count);
}

long	ft_atol(const char *nptr)
{
	long		ans;
	long		pos;
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)nptr;
	ans = 0;
	pos = 1;
	while (ptr[i] && ((ptr[i] >= '\t' && ptr[i] <= '\r') || ptr[i] == ' '))
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			pos = -1;
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		ans = (ans * 10) + ptr[i] - '0';
		i++;
	}
	return (ans * pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:46:28 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/02 16:29:14 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check(char	**argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]) || ft_atol(argv[i]) >= INT_MAX
			|| ft_atol(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

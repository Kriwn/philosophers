/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:58:25 by krwongwa          #+#    #+#             */
/*   Updated: 2024/08/04 13:21:29 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	del_mutex_fork(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]) != 0)
			ft_error(data, "cannot destroy fork mutex\n");
		if (pthread_mutex_destroy(&data->philo[i].general) != 0)
			ft_error(data, "cannot destroy general mutex\n");
		i++;
	}
	if (pthread_mutex_destroy(data->print_lock) != 0)
		ft_error(data, "cannot destroy print lock mutex\n");
}

void	freeall(t_program *data)
{
	del_mutex_fork(data);
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
	if (data->print_lock)
		free(data->print_lock);
}

void ft_error(t_program *data, char *str)
{
	dprintf(2, "%s",str);
	freeall(data);
	exit(0);
}

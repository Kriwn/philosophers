/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:29:09 by krwongwa          #+#    #+#             */
/*   Updated: 2024/09/03 17:30:46 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_die(t_philo	*philo)
{
	pthread_mutex_lock(&philo->general);
	if (diff_time(philo->last_time_eat, get_current_time()) > philo->rule->time_die)
	{
		pthread_mutex_unlock(&philo->general);
		pthread_mutex_lock(philo->print_lock);
		if (*philo->status == 1)
		{
			printf("%ld %d died\n", diff_time(philo->rule->start_time,get_current_time()), philo->id);
			set_status(philo, 0);
		}
		pthread_mutex_unlock(philo->print_lock);
	}
	else
		pthread_mutex_unlock(&philo->general);
}

void		check_philo_die(t_program *data)
{
	int	i;

	i = 0;
	while (data->status == 1)
	{
		pthread_mutex_lock(data->check_die);
		check_die(&data->philo[i]);
		pthread_mutex_unlock(data->check_die);
		if (data->philo_full == data->max_eat)
			set_status(&data->philo[0],0);
		if (i == data->max_philo)
			i = 0;
	}
}


int	check_reach_max(t_program *data)
{
	int	i;
	int	count;

	count	= 0;
	i = 0;
	if (data->max_eat == -1)
		return (0);
	while (i < data->max_philo)
	{
		if (data->philo[i].count == data->max_eat)
			i++;
	}
	if (i == data->max_philo)
		return (1);
	return (0);
}

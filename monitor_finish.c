/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:29:09 by krwongwa          #+#    #+#             */
/*   Updated: 2024/11/16 21:39:47 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_die(t_philo	*philo)
{
	pthread_mutex_lock(philo->general);
	if (diff_time(philo->last_time_eat, get_current_time()) > philo->rule->time_die)
	{
		pthread_mutex_unlock(philo->general);
		pthread_mutex_lock(philo->print_lock);
		if (*philo->status == 1)
		{
			printf("%ld %d died\n", diff_time(philo->rule->start_time,get_current_time()), philo->id);
			set_status(philo, 0);
		}
		pthread_mutex_unlock(philo->print_lock);
	}
	else
		pthread_mutex_unlock(philo->general);
}

void		check_philo_die(t_program *data)
{
	int	i;

	i = 0;
	while (check_end_rotine(data))
	{
		pthread_mutex_lock(data->check_die);
		check_die(&data->philo[i]);
		pthread_mutex_unlock(data->check_die);
		if (i == data->max_philo)
			i = 0;
	}
}

int	check_all_philo_done(t_program *program)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	if (program->max_eat == -1)
		return (0);
	pthread_mutex_lock(program->check_die);
	while (i < program->max_philo)
	{
		pthread_mutex_lock(program->general);
		if (program->philo[i].count < program->max_eat)
		{
			done = 0;
			pthread_mutex_unlock(program->general);
			break ;
		}
		else
			pthread_mutex_unlock(program->general);
		i++;
	}
	pthread_mutex_unlock(program->check_die);
	return done;
}

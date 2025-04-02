/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:02:13 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/02 16:07:12 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(t_philo *philo, long time)
{
	long	difftime;

	difftime = 0;
	philo->time = get_current_time();
	if (philo->status == 0)
		return ;
	while (difftime < time)
	{
		usleep(100);
		difftime = diff_time(philo->time, get_current_time());
	}
}

void	print_report(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_lock);
	if (check_end_rotine(philo->rule))
		printf("%ld %d %s\n", diff_time(philo->rule->start_time, \
			get_current_time()), philo->id, str);
	pthread_mutex_unlock(philo->print_lock);
}

void	fork_up(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->lfork);
	}
}

void	fork_down(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
}

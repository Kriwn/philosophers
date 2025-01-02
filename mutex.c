/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:27:15 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/02 16:08:14 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->general);
	philo->last_time_eat = time;
	pthread_mutex_unlock(philo->general);
}

void	set_status(t_philo *philo, int status)
{
	pthread_mutex_lock(philo->general);
	*philo->status = status;
	pthread_mutex_unlock(philo->general);
}

void	set_eat_done(t_program	*program, int status)
{
	pthread_mutex_lock(program->general);
	program->status = status;
	pthread_mutex_unlock(program->general);
}

void	increase_count(t_philo *philo)
{
	pthread_mutex_lock(philo->general);
	philo->count++;
	if (philo->count >= philo->rule->max_eat)
	{
		pthread_mutex_unlock(philo->general);
		return ;
	}
	pthread_mutex_unlock(philo->general);
}

int	check_end_rotine(t_program *program)
{
	int	temp;

	pthread_mutex_lock(program->general);
	temp = program->status;
	pthread_mutex_unlock(program->general);
	return (temp);
}

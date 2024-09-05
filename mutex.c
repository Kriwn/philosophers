/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:27:15 by krwongwa          #+#    #+#             */
/*   Updated: 2024/09/05 14:12:11 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time(t_philo *philo, size_t time)
{
	pthread_mutex_lock(&philo->general);
	philo->last_time_eat = time;
	pthread_mutex_unlock(&philo->general);
}

void	set_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->general);
	*philo->status = status;
	pthread_mutex_unlock(&philo->general);
}

void	set_eat_done(t_program	*program,int status)
{
	pthread_mutex_lock(program->check_die);
	program->status = 0;
	pthread_mutex_unlock(program->check_die);
}

void increase_count(t_philo *philo)
{
    pthread_mutex_lock(&philo->general);
    philo->count++;  // Safely update the eat count
    if (philo->count >= philo->rule->max_eat)
    {
        pthread_mutex_unlock(&philo->general);
        return;  // Stop the philosopher if they have eaten enough
    }
    pthread_mutex_unlock(&philo->general);
}


int	check_end_rotine(t_program *program)
{
	int	temp;

	pthread_mutex_lock(program->check_die);
	temp = program->status;
	pthread_mutex_unlock(program->check_die);
	return (temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:01:00 by krwongwa          #+#    #+#             */
/*   Updated: 2024/06/29 15:29:17 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (philo->status == 0)
		return ;
	if ((philo->id) % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->lfork);
	}
	print_report(philo, "has take a fork");
	print_report(philo,"is eating");
	philo->last_time_eat = get_current_time();
	ft_sleep(philo, philo->rule->time_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);

}

static void	check_die(t_philo	*philo)
{
	if (diff_time(philo->last_time_eat, get_current_time()) > philo->rule->time_die)
	{
		pthread_mutex_lock(philo->print_lock);
		if (*philo->status == 1)
		{
			printf("%ld %d died\n", diff_time(philo->rule->start_time,get_current_time()), philo->id);
			*philo->status = 0;
		}
		pthread_mutex_unlock(philo->print_lock);
	}
}

void		check_philo_die(t_program *data)
{
	int	i;

	i = 0;
	while (data->status == 1)
	{
		check_die(&data->philo[i]);
		i++;
		if (i == data->max_philo)
			i = 0;
	}
}


void	routine(void *data)
{
	t_philo 	*philo;
	t_program	*rule;
	int			count;

	philo = (t_philo *)data;
	count = 0;
	rule = philo->rule;
	philo->last_time_eat = get_current_time();
	if (rule->max_philo == 1)
	{
		ft_sleep(philo, rule->time_die);
		return ;
	}
	while (philo->status)
	{
		print_report(philo, "is thinking");
		ft_sleep(philo, rule->time_think);
		eat(philo);
		count++;
		if (count == rule->max_eat)
			return ;
		print_report(philo, "is sleeping");
		ft_sleep(philo, rule->time_sleep);
	}
}

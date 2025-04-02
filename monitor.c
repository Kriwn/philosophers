/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:01:00 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/02 16:15:11 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (philo->count >= philo->rule->max_eat && philo->rule->max_eat != -1)
		return ;
	fork_up(philo);
	print_report(philo, "has taken a fork");
	print_report(philo, "is eating");
	set_time(philo, get_current_time());
	ft_sleep(philo, philo->rule->time_eat);
	fork_down(philo);
}

static	void	philo_think(t_philo *philo)
{
	print_report(philo, "is thinking");
}

static	void	philo_sleep(t_philo *philo)
{
	print_report(philo, "is sleeping");
	ft_sleep(philo, philo->rule->time_sleep);
}

static	void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print_report(philo, "has taken a fork");
	ft_sleep(philo, philo->rule->time_die);
	pthread_mutex_unlock(philo->rfork);
	return ;
}

void	routine(void *data)
{
	t_philo		*philo;
	t_program	*rule;

	philo = (t_philo *)data;
	rule = philo->rule;
	set_time(philo, get_current_time());
	if (rule->max_eat == 0)
		return ;
	if (rule->max_philo == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		ft_sleep(philo, 2);
	while (check_end_rotine(philo->rule))
	{
		philo_think(philo);
		eat(philo);
		if (!check_end_rotine(philo->rule))
			break ;
		increase_count(philo);
		if (check_all_philo_done(rule))
			set_eat_done(rule, 0);
		philo_sleep(philo);
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:04:41 by krwongwa          #+#    #+#             */
/*   Updated: 2024/07/06 22:21:08 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_program *data,t_program **temp)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		data->philo[i].id = i;
		data->philo[i].rfork = &data->fork[i];
		data->philo[i].print_lock = data->print_lock;
		data->philo[i].last_time_eat = 0;
		data->philo[i].status = &data->status;
		data->philo[i].rule = data;
		if (data->max_philo == 1)
		{
			data->philo[i].rfork = NULL;
			data->philo[i].lfork = NULL;
		}
		else if (i == data->max_philo - 1)
			data->philo[i].lfork = &data->fork[0];
		else
			data->philo[i].lfork = &data->fork[i+1];
		i++;
	}
}

static int	allocate_data(t_program *data)
{
	data->fork = malloc(sizeof(pthread_mutex_t) * data->max_philo);
	if (!data->fork)
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->max_philo);
	if (!data->philo)
		return (0);
	data->print_lock = malloc(sizeof(pthread_mutex_t) * 1);
	if (!data->print_lock)
		return (0);
	return (1);
}

static void	mutex_fork(t_program *data)
{
	int	i;

	i = 0;
	// valgrind error on broke
	while (i < data->max_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			ft_error(data, "Mutex init error\n");
		i++;
	}
	if (pthread_mutex_init(data->print_lock, NULL) != 0)
			ft_error(data, "Mutex init error\n");
}

void	init_data(t_program *data,int argc,char **argv)
{

	data->start_time = get_current_time();
	printf("%ld\n",data->start_time);
	data->status = 1;
	if (data->start_time == -1)
		ft_error(data, "gettimeofday error\n");
	data->max_philo = ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_sleep = ft_atol(argv[4]);
	if (argc == 7)
		data->max_eat = ft_atol(argv[6]);
	else
		data->max_eat = -1;
	if (!allocate_data(data))
		ft_error(data, "Malloc Error\n");
	mutex_fork(data);
	init_philo(data,&data);
}

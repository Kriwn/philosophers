/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:34:53 by krwongwa          #+#    #+#             */
/*   Updated: 2024/06/27 21:08:27 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		dprintf(2, "start \n");
		if (pthread_create(&data->philo[i].thread, NULL,(void *)routine,(void *)(&(data->philo[i]))) != 0)
			return (0);
		dprintf(2, "tread [%d] = %ld\n", i, data->philo[i].thread);
		i++;
	}
	return (1);

}

// ./philo num timedie timeeat timesleep timethink [number of time to eat](optional)
int	main(int argc, char **argv)
{
	t_program	data;
	int			i;

	i = 0;
	if ((argc != 6 && argc != 7 ) || !check(argv))
		return (0);
	init_data(&data, argc, argv); // need fix
	if (start_philo(&data) == 0)
		ft_error(&data, "Create thread fail\n");
	check_philo_die(&data);
	while (i < data.max_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	freeall(&data);
	exit(1);

	// long a = get_current_time();
	// printf("%ld\n",a);
	// usleep(1000000);
	// printf("%ld\n", get_current_time() - a);
}

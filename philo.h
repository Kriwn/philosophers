/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:10:02 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/02 16:47:44 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo
{
	int				id;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*general;
	struct program	*rule;
	volatile int	*status;
	pthread_t		thread;
	size_t			last_time_eat;
	int				count;
	int				time;
}	t_philo;

typedef struct program
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*check_die;
	pthread_mutex_t	*general;
	t_philo			*philo;
	volatile int	status;
	size_t			time_eat;
	long			time_die;
	size_t			time_sleep;
	int				max_eat;
	ssize_t			start_time;
	int				max_philo;
}	t_program;

//-----------check.c------------//
int		check(char	**argv);

//------------free.c------------//
void	freeall(t_program *data);
int		ft_error(t_program *data, char *str);

//------------init.c------------//
int		init_data(t_program *data, int argc, char **argv);

//-----------moitor_finish.c----/
void	check_philo_die(t_program *data);
int		check_all_philo_done(t_program *program);

//------------moitor.c----------//
void	routine(void *data);

//------------mutex.c----------//
void	set_time(t_philo *philo, size_t time);
void	set_eat_done(t_program	*data, int status);
void	set_status(t_philo *philo, int status);
int		check_end_rotine(t_program *program);
void	increase_count(t_philo *philo);

//------------utils.c-----------//
size_t	ft_strlen(const char *s);
long	ft_atol(const char *nptr);
long	diff_time(int x, int y);

//-----------utils2.c-----------//
size_t	get_current_time(void);
void	ft_sleep(t_philo *philo, long time);
void	print_report(t_philo *philo, char *str);
void	fork_up(t_philo *philo);
void	fork_down(t_philo *philo);

#endif

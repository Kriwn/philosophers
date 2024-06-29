/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:10:02 by krwongwa          #+#    #+#             */
/*   Updated: 2024/06/29 15:30:52 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct philo
{
	int				id;
	pthread_mutex_t *print_lock;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	struct program		*rule;
	int				*status;
	pthread_t		thread;
	size_t			last_time_eat;
	int				count;
	int				time;
	size_t			time_eat;
	size_t			time_die;
	size_t			time_sleep;
	size_t			time_think;

}t_philo;

typedef	struct program
{
	pthread_mutex_t	*fork;
	pthread_mutex_t *print_lock;
	t_philo			*philo;
	int				status;
	size_t			time_eat;
	size_t			time_die;
	size_t			time_sleep;
	size_t			time_think;
	int				max_eat;
	size_t			start_time;
	int				max_philo;
}t_program;

//-----------check.c------------//
int	check(char	**argv);

//------------free.c------------//
void	freeall(t_program *data);
void ft_error(t_program *data, char *str);

//------------init.c------------//
void	init_data(t_program *data,int argc,char **argv);

//------------moitor.c----------//
void	routine(void *data);
void		check_philo_die(t_program *data);

//------------utils.c-----------//
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
long		ft_atol(const char *nptr);


//-----------utils2.c-----------//
size_t	get_current_time(void);
long		diff_time(int x,int y);
void	ft_sleep(t_philo *philo,size_t time);
void	print_report(t_philo *philo, char *str);

#endif

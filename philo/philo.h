/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:51 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 13:10:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define MICROSEC_MULTIPLIER 1000
# define SMALL_DELAY 100
# define MONITOR_DELAY 5000
# define NO_MEAL_LIMIT -1

typedef struct s_philo
{
	int				id;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_must_eat;
	int				eaten_count;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	int				*someone_died;
	pthread_mutex_t	*death_mutex;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;
}					t_data;

void	*philo_routine(void *arg);
long	get_current_time(void);
void	print_status(t_philo *philo, char *status);
void	cleanup(t_data *data);
void	*monitor_philos(void *arg);
void	philo_eat(t_philo *philo);
int		init_data(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
void	init_philosophers(t_data *data);
int		create_threads(t_data *data, pthread_t *monitor);
int		validate_args(t_data *data, int argc, char **argv);
void	handle_single_philo(t_data *data);
int		should_philo_continue(t_philo *philo);
int		has_eaten_enough(t_philo *philo);
void	philo_sleep_and_think(t_philo *philo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:08 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:36:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

# define FORK_SEM_NAME "/forks"
# define PRINT_SEM_NAME "/print_sem"
# define PERMISSION_MODE 0644
# define MICROSEC_MULTIPLIER 1000
# define SMALL_DELAY 100
# define MONITOR_DELAY 1000
# define EXIT_DEATH 1
# define EXIT_SUCCESS 0
# define NO_MEAL_LIMIT -1

typedef struct s_philo
{
	int			id;
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_times_must_eat;
	int			eaten_count;
	long		last_meal;
	pid_t		pid;
	pthread_t	monitor_thread;
	sem_t		*forks;
	sem_t		*print_sem;
}				t_philo;

typedef struct s_data
{
	t_philo		*philos;
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_times_must_eat;
	sem_t		*forks;
	sem_t		*print_sem;
}				t_data;

/* philo_bonus.c */
int		validate_args(t_data *data, int argc, char **argv);

/* philo_routine.c */
void	philo_eat(t_philo *philo);
void	handle_single_philo(t_philo *philo, pthread_t monitor);
void	check_meals_limit(t_philo *philo, pthread_t monitor);
void	philo_routine(t_philo *philo);
void	*monitor_routine(void *arg);

/* utils.c */
long	get_current_time(void);
void	print_status(t_philo *philo, char *status);
int		create_processes(t_data *data);

/* init.c */
int		init_semaphores(t_data *data);
int		init_data(t_data *data, int argc, char **argv);
void	init_philosophers(t_data *data);

/* cleanup.c */
void	cleanup(t_data *data);

#endif
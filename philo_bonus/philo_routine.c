/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:11 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:06:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = get_current_time();
	usleep(philo->time_to_eat * MICROSEC_MULTIPLIER);
	philo->eaten_count++;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	handle_single_philo(t_philo *philo, pthread_t monitor)
{
	void	*ret;

	sem_wait(philo->forks);
	print_status(philo, "has taken a fork");
	usleep(philo->time_to_die * MICROSEC_MULTIPLIER);
	print_status(philo, "died");
	sem_post(philo->forks);
	pthread_cancel(monitor);
	pthread_join(monitor, &ret);
	sem_close(philo->forks);
	sem_close(philo->print_sem);
	exit(EXIT_DEATH);
}

void	check_meals_limit(t_philo *philo, pthread_t monitor)
{
	void	*ret;

	if (philo->num_times_must_eat != NO_MEAL_LIMIT
		&& philo->eaten_count >= philo->num_times_must_eat)
	{
		pthread_cancel(monitor);
		pthread_join(monitor, &ret);
		sem_close(philo->forks);
		sem_close(philo->print_sem);
		exit(EXIT_SUCCESS);
	}
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	philo->last_meal = get_current_time();
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
	{
		perror("pthread_create");
		sem_close(philo->forks);
		sem_close(philo->print_sem);
		exit(EXIT_DEATH);
	}
	philo->monitor_thread = monitor;
	if (philo->id % 2 == 0)
		usleep(SMALL_DELAY);
	if (philo->num_philos == 1)
		handle_single_philo(philo, monitor);
	while (1)
	{
		philo_eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->time_to_sleep * MICROSEC_MULTIPLIER);
		print_status(philo, "is thinking");
		check_meals_limit(philo, monitor);
	}
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)arg;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while (1)
	{
		current_time = get_current_time();
		if (current_time - philo->last_meal >= philo->time_to_die)
		{
			print_status(philo, "died");
			sem_close(philo->forks);
			sem_close(philo->print_sem);
			exit(EXIT_DEATH);
		}
		usleep(MONITOR_DELAY);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:42 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:05:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->death_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->death_mutex);
	usleep(philo->time_to_eat * MICROSEC_MULTIPLIER);
	philo->eaten_count++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!should_philo_continue(philo))
			break ;
		philo_eat(philo);
		if (has_eaten_enough(philo))
			return (NULL);
		if (!should_philo_continue(philo))
			break ;
		philo_sleep_and_think(philo);
		usleep(100);
	}
	return (NULL);
}

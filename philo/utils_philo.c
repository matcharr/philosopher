/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:11:03 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 13:11:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_philo_continue(t_philo *philo)
{
	int	should_continue;

	pthread_mutex_lock(philo->death_mutex);
	should_continue = !(*philo->someone_died);
	pthread_mutex_unlock(philo->death_mutex);
	return (should_continue);
}

int	has_eaten_enough(t_philo *philo)
{
	return (philo->num_times_must_eat != NO_MEAL_LIMIT
		&& philo->eaten_count >= philo->num_times_must_eat);
}

void	philo_sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->time_to_sleep * MICROSEC_MULTIPLIER);
	print_status(philo, "is thinking");
}

void	handle_single_philo(t_data *data)
{
	print_status(&data->philos[0], "has taken a fork");
	usleep(data->time_to_die * MICROSEC_MULTIPLIER);
	print_status(&data->philos[0], "died");
}

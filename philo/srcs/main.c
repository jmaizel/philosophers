/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:54 by jmaizel           #+#    #+#             */
/*   Updated: 2025/03/18 14:58:31 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("\n=== Simulation Initialized ===\n");
	printf("Philosophers: %d\n", data->num_philo);
	printf("Time to die: %d ms\n", data->time_to_die);
	printf("Time to eat: %d ms\n", data->time_to_eat);
	printf("Time to sleep: %d ms\n", data->time_to_sleep);
	printf("Meals required: %d\n", data->meals_required);
	printf("\n=== Forks and Philosophers ===\n");
	while (i < data->num_philo)
	{
		printf("Philosopher %d:\n", data->philos[i].id + 1);
		printf("  Left fork:  %d\n", data->philos[i].index_left_fork);
		printf("  Right fork: %d\n", data->philos[i].index_right_fork);
		printf("  Meals eaten: %d\n", data->philos[i].meals_eaten);
		printf("  Last meal time: %lld ms\n", data->philos[i].last_meal);
		i++;
	}
} */

void	clean_data(t_data *data)
{
	int	i;

	usleep(100000);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		end;

	if (ac < 5 || ac > 6)
		return (printf("Error: incorrect number of arguments\n"), 1);
	if (init_data(&data, ac, av))
		return (1);
	if (start_threads(&data))
		return (1);
	while (1)
	{
		usleep(10000);
		pthread_mutex_lock(&data.end_mutex);
		end = data.simulation_end;
		pthread_mutex_unlock(&data.end_mutex);
		if (end)
		{
			usleep(100000);
			break ;
		}
	}
	return (clean_data(&data), 0);
}

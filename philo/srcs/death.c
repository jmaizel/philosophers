/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:44 by jmaizel           #+#    #+#             */
/*   Updated: 2025/03/18 15:09:28 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
Vérifie si un philosophe est mort (n'a pas mangé depuis trop longtemps)
Si c'est le cas, marque le philosophe comme mort et termine la simulation
*/
static int	check_death(t_data *data)
{
	int			i;
	long long	current_time;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		current_time = get_time();
		if (current_time - data->philos[i].last_meal >= data->time_to_die)
		{
			data->philos[i].is_dead = 1;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			pthread_mutex_lock(&data->write_mutex);
			printf("%lld %d died\n", current_time - data->start_time,
				data->philos[i].id + 1);
			pthread_mutex_unlock(&data->write_mutex);
			pthread_mutex_lock(&data->end_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->end_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (0);
}

/*
Traite le cas où le nombre de repas requis est zéro
Dans ce cas, les philosophes ont déjà mangé assez
*/
static int	handle_zero_meals(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->end_mutex);
	pthread_mutex_lock(&data->write_mutex);
	printf("All philosophers have eaten enough\n");
	pthread_mutex_unlock(&data->write_mutex);
	return (1);
}

/*
Vérifie si tous les philosophes ont mangé le nombre requis de repas
Si c'est le cas, termine la simulation
*/
static int	check_meals_completed(t_data *data)
{
	int	i;

	if (data->meals_required == -1)
		return (0);
	if (data->meals_required == 0)
		return (handle_zero_meals(data));
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten < data->meals_required)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->end_mutex);
	pthread_mutex_lock(&data->write_mutex);
	printf("All philosophers have eaten enough\n");
	pthread_mutex_unlock(&data->write_mutex);
	return (1);
}

/*
Fonction de surveillance qui s'exécute dans un thread séparé
Vérifie périodiquement si un philosophe est mort ou si tous ont assez mangé
*/
void	*monitor_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_meals_completed(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:22:51 by jmaizel           #+#    #+#             */
/*   Updated: 2025/03/18 14:58:23 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
Gère le cas particulier d'un seul philosophe qui ne peut pas manger
Il prend une fourchette puis attend sa mort
*/
void	*handle_single_philo(t_philo *philo)
{
	print_state(philo, "is thinking");
	pthread_mutex_lock(&philo->data->forks[philo->index_left_fork]);
	print_state(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	return (NULL);
}

/*
Obtient l'heure actuelle en millisecondes
Cette fonction utilise gettimeofday pour obtenir l'heure système actuelle
et la convertit en millisecondes depuis l'époque Unix.

 */
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
Affiche l'état actuel d'un philosophe
Cette fonction affiche de manière thread-safe l'état d'un philosophe
avec un timestamp relatif au début de la simulation. Elle n'affiche rien
si la simulation est terminée.
 */
void	print_state(t_philo *philo, char *state)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->simulation_end)
	{
		current_time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", current_time, philo->id + 1, state);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

/**
 Démarre tous les threads nécessaires à la simulation
 Cette fonction initialise le temps de démarrage de la simulation,
 initialise le dernier repas des philosophes, crée un thread pour chaque
 philosophe et un thread pour surveiller la mort des philosophes.
 Tous les threads sont détachés pour se terminer automatiquement.

 */
int	start_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = get_time();
	data->simulation_end = 0;
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (printf("Error: Failed to create philosopher thread\n"), 1);
		pthread_detach(data->philos[i].thread);
		usleep(100);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_death, data) != 0)
		return (printf("Error: Failed to create monitor thread\n"), 1);
	return (pthread_detach(monitor_thread), 0);
}

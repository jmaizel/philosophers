/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:25:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/03/18 15:01:13 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
Détermine l'ordre de prise des fourchettes selon l'ID
Les philosophes pairs prennent d'abord la fourchette droite
Les philosophes impairs prennent d'abord la fourchette gauche
*/
static void	determine_forks_order(t_philo *philo, int *first_fork,
		int *second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->index_right_fork;
		*second_fork = philo->index_left_fork;
		usleep(philo->data->time_to_eat / 2 * 1000);
	}
	else
	{
		*first_fork = philo->index_left_fork;
		*second_fork = philo->index_right_fork;
	}
}

/*
Vérifie si la simulation est terminée
Retourne 1 si terminée, 0 sinon
*/
static int	is_simulation_ended(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->data->end_mutex);
	end = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (end);
}

/*
Calcule le temps de réflexion adaptatif
Plus un philosophe a faim, moins il réfléchit
*/
static long long	calculate_think_time(t_philo *philo)
{
	long long	think_time;

	pthread_mutex_lock(&philo->meal_mutex);
	think_time = (philo->data->time_to_die - (get_time() - philo->last_meal))
		/ 4;
	if (think_time > 200)
		think_time = 200;
	else if (think_time < 0)
		think_time = 0;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (think_time);
}

/*
Fait manger le philosophe:
- Prend les deux fourchettes
- Met à jour l'heure du dernier repas
- Incrémente le compteur de repas
- Relâche les fourchettes après avoir mangé
*/
static void	eat_action(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
}

/*
Routine principale du philosophe
Gère le cycle: penser, manger, dormir
Utilise différentes stratégies pour éviter les deadlocks
*/
void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			first_fork;
	int			second_fork;
	long long	think_time;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
		return (handle_single_philo(philo));
	determine_forks_order(philo, &first_fork, &second_fork);
	while (1)
	{
		if (is_simulation_ended(philo))
			break ;
		print_state(philo, "is thinking");
		think_time = calculate_think_time(philo);
		usleep(think_time * 1000);
		eat_action(philo, first_fork, second_fork);
		print_state(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_NAME_LENGTH 20
#define MAX_LOG_LENGTH 100

// Structure to represent the state of a philosopher
typedef struct
{
	int number;
	char name[MAX_NAME_LENGTH];
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_eats;
	struct timeval last_meal_time;
	pthread_t thread;
} Philosopher;

// Function to get the current timestamp in milliseconds
long long current_timestamp()
{
	struct timeval te;
	gettimeofday(&te, NULL);
	return (long long)te.tv_sec * 1000LL + te.tv_usec / 1000;
}

// Function to log the state change of a philosopher
void log_state(Philosopher *philosopher, const char *state)
{
	long long timestamp = current_timestamp();
	printf("%lld %d %s\n", timestamp, philosopher->number, state);
	fflush(stdout);
}

// Function for the philosopher thread
void *philosopher_thread(void *arg)
{
	Philosopher *philosopher = (Philosopher *)arg;
	int eat_count = 0;

	while (1)
	{
		// Check if the philosopher has eaten enough times
		if (philosopher->num_eats > 0 && eat_count >= philosopher->num_eats)
			break;

		// Start thinking
		log_state(philosopher, "is thinking");
		usleep(rand() % 1000);

		// Start eating
		pthread_mutex_lock(philosopher->left_fork);
		log_state(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->right_fork);
		log_state(philosopher, "has taken a fork");
		log_state(philosopher, "is eating");
		gettimeofday(&(philosopher->last_meal_time), NULL);
		usleep(philosopher->time_to_eat * 1000);
		eat_count++;

		// Start sleeping
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		log_state(philosopher, "is sleeping");
		usleep(philosopher->time_to_sleep * 1000);

		// Check if the philosopher has exceeded the time to die
		long long current_time = current_timestamp();
		long long elapsed_time = current_time - philosopher->last_meal_time.tv_sec * 1000LL -
								 philosopher->last_meal_time.tv_usec / 1000;
		if (elapsed_time >= philosopher->time_to_die)
		{
			log_state(philosopher, "died");
			break;
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return 1;
	}

	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	int num_eats = (argc == 6) ? atoi(argv[5]) : -1;

	if (num_philosophers <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
	{
		printf("Invalid arguments\n");
		return 1;
	}

	// Initialize mutexes for forks
	pthread_mutex_t forks[num_philosophers];
	for (int i = 0; i < num_philosophers; i++)
		pthread_mutex_init(&forks[i], NULL);

	// Create philosophers
	Philosopher philosophers[num_philosophers];
	for (int i = 0; i < num_philosophers; i++)
	{
		philosophers[i].number = i + 1;
		snprintf(philosophers[i].name, MAX_NAME_LENGTH, "Philosopher %d", i + 1);
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].num_eats = num_eats;
		gettimeofday(&(philosophers[i].last_meal_time), NULL);
		pthread_create(&(philosophers[i].thread), NULL, philosopher_thread, &(philosophers[i]));
	}

	// Wait for philosophers to finish
	for (int i = 0; i < num_philosophers; i++)
		pthread_join(philosophers[i].thread, NULL);

	// Destroy mutexes for forks
	for (int i = 0; i < num_philosophers; i++)
		pthread_mutex_destroy(&forks[i]);

	return 0;
}
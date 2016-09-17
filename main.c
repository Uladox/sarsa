#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATES 4

float table[STATES][STATES];

typedef struct {
	float discount;
	float weight;
	int state;
	int action;
} Sarsa;

void
print_table(void)
{
	int i = 0;
	int j;

	printf("S A↦\n");
	printf("↧ ");

	for (; i < STATES; ++i)
		printf("%7i ", i);

	printf("\n");
	i = 0;

	for (; i < STATES; ++i) {
		printf("%i", i);

		for (j = 0; j < STATES; ++j)
			printf(" %7.3f", table[i][j]);

		printf("\n");
	}
}

void
print_sarsa(Sarsa *sarsa)
{
	printf("╔═════════╗\n"
	       "║  Sarsa  ╚════════╗\n"
	       "║  discount: %.3f ║\n"
	       "║  weight:   %.3f ║\n"
	       "║  state:    %3i   ║\n"
	       "║  action:   → %1i   ║\n"
	       "╚══════════════════╝\n",
	       sarsa->discount, sarsa->weight,
	       sarsa->state, sarsa->action);
}

void
update_table(Sarsa *sarsa, int s_p, int a_p, float r)
{
	table[sarsa->state][sarsa->action] += sarsa->weight *
		(r + sarsa->discount * table[s_p][a_p]
		 - table[sarsa->state][sarsa->action]);
}

float
rand_prob(void)
{
	return (float) rand() / (float) RAND_MAX ;
}

int
e_greedy(int s, float e)
{

	if (rand_prob() <= e)
		return rand() % STATES;

	int a = 0;
	float max   = table[s][0];
	int i = 1;

	for (; i < STATES; ++i) {
		if (table[s][i] > max) {
			a = i;
			max = table[s][i];
		}
	}

	return a;
}

void
run(Sarsa *sarsa, float e)
{
	float r;
	int s_p, a_p;

	sarsa->action = e_greedy(sarsa->state, e);

	while (1) {
		print_sarsa(sarsa);
		print_table();
		printf(" ───────────────────────\n");

		/* Takes the action, in this case the action is
		 * going to another state.
		 */
		s_p = sarsa->action;

		printf("> ");

		/* Gets reward */
		if (scanf("%f", &r) == EOF) {
			printf("\n");
			break;
		}

		/* Finding new state is already done */

		a_p = e_greedy(s_p, e);

		update_table(sarsa, s_p, a_p, r);

		sarsa->state  = s_p;
		sarsa->action = a_p;
	}
}

int
main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	Sarsa sarsa = {
		.discount = 0.5,
		.weight   = 0.5,
		.state    = 1
	};

	srand(time(NULL));
	run(&sarsa, 0.5);
}

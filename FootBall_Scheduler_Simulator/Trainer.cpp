#include "Trainer.h"
#include <stdlib.h>
#include <time.h>


const char* Trainer::TrainerDecisionNames[] = { "No Decision", "Change Player" };

TrainerDecision Trainer::MakeDecision(bool isTeamAttacking) const
{
	srand(time(NULL));
	if (isTeamAttacking)
	{ return TrainerDecision::NO_DECISION; }
	else
	{ return (TrainerDecision)(rand() % 2); }
}

#include "Trainer.h"
#include <stdlib.h>
#include <time.h>


const char* Trainer::TrainerDecisionNames[] = { "Change Player", "Move Player" };

TrainerDecision Trainer::MakeDecision(bool isTeamAttacking) const
{
	srand(time(NULL));
	if (isTeamAttacking)
	{ return TrainerDecision::NO_DECISION; }
	else
	{ return (TrainerDecision)(rand() % 2); }
}

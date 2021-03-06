#include "Trainer.h"
#include <stdlib.h>
#include <time.h>
#include <string>


const std::string Trainer::TrainerDecisionNames[] = { "No Decision", "Change Player" };

TrainerDecision Trainer::MakeDecision(bool isTeamAttacking) const
{
	if (isTeamAttacking)
	{ return TrainerDecision::NO_DECISION; }
	else
	{ return (TrainerDecision)(rand() % 2); }
}

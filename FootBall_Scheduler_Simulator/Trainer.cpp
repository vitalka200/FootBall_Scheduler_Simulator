#include "Trainer.h"
#include <stdlib.h>
#include <time.h>


const char* Trainer::TrainerDecisionNames[] = { "Change Player", "Move Player" };

TrainerDecision Trainer::MakeDecision(bool isTeamAttacking) const
{
	srand(time(NULL));
	return (TrainerDecision)(rand() % 2);
}

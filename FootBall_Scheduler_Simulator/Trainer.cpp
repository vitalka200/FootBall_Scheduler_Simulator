#include "Trainer.h"
#include <stdlib.h>
#include <time.h>


const char* Trainer::TrainerDecisionNames[] = { "Change Player", "Move Player" };

TrainerDecision Trainer::MakeDecision()
{
	srand(time(NULL));
	return (TrainerDecision)(rand() % 2);
}

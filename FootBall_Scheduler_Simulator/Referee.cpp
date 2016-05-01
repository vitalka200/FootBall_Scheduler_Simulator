#include "Referee.h"
#include <stdlib.h>
#include <time.h>

const char* Referee::CardNames[] = { "No Card", "Yellow", "Red" };

CardType Referee::MakeDecision()
{
	srand(time(NULL));
	return (CardType)(rand() % 3);
}

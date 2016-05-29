#include "Referee.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

const std::string Referee::CardNames[] = { "No Card", "Yellow", "Red" };

CardType Referee::MakeDecision()
{ return (CardType)(rand() % 3); }

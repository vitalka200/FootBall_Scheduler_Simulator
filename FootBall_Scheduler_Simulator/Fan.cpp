#include "Fan.h"
#include "Team.h"

void Fan::Cheer()
{
	std::cout << *this << std::endl;
	std::cout << "Cheer for Team : " << m_team->GetName();
}

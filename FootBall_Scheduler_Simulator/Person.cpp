#include "Person.h"

const Person& Person::operator=(const Person& p)
{
	if (this != &p)
	{
		SetName(p.GetName());
		SetFName(p.GetName());
	}
	return *this;
}

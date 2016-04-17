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

bool Person::operator==(const Person& p) const
{
	return (
		this->GetId() == p.GetId() &&
		strcmp(this->GetName(), p.GetName()) == 0 &&
		strcmp(this->GetFName(), p.GetFName()) == 0
		);
}

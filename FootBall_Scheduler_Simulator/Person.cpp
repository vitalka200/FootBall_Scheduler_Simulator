#include "Person.h"
#include <string>
#include <vector>

const Person& Person::operator=(const Person& p)
{
	if (this != &p)
	{
		SetId(p.GetId());
		SetName(p.GetName());
		SetFName(p.GetFName());
	}
	return *this;
}

bool Person::operator==(const Person& p) const
{
	return (
		this->GetId() == p.GetId() &&
		this->GetName() == p.GetName() &&
		this->GetFName() == p.GetFName()
		);
}

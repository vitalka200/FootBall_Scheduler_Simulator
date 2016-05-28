#ifndef __PERSON_H
#define __PERSON_H

#include <iostream>
#include <string>
#include <vector>
//#include <string>

class Person
{
public:
	// c-tors, d-tors
	Person(const std::string name, const std::string f_name, long id)
		: m_name(name), m_fname(f_name), m_id(id)     { SetName(name); SetFName(f_name); }
	Person(const Person& p)
		: m_name(p.m_name), m_fname(p.m_fname), m_id(p.m_id) { *this = p; }
	virtual ~Person()                               { }
	// Methods
	const std::string    GetName()     const { return m_name; }
	const std::string    GetFName()    const { return m_fname; }
	long                 GetId()       const { return m_id; }

	void  SetName(const std::string name)    { m_name = name; }
	void  SetFName(const std::string f_name) { m_fname = f_name; }
	void  SetId(long id)                     { m_id = id; }

	// Operators
	const Person& operator=(const Person& p);
	bool          operator==(const Person& p) const;

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Person& p)
	{ os << " Name: " << p.m_name << " FName: " << p.m_fname; return os; }

protected:
	std::string m_name;
	std::string m_fname;
	long        m_id;
};


#endif
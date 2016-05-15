#ifndef __PERSON_H
#define __PERSON_H

#include <iostream>

class Person
{
public:
	// c-tors, d-tors
	Person(const char* name, const char* f_name, long id)
		: m_name(NULL), m_fname(NULL), m_id(id)     { SetName(name); SetFName(f_name); }
	Person(const Person& p)
		: m_name(NULL), m_fname(NULL), m_id(p.m_id) { *this = p; }
	virtual ~Person()                  { delete []m_name; delete []m_fname; }
	// Methods
	const char*    GetName()     const { return m_name; }
	const char*    GetFName()    const { return m_fname; }
	long           GetId()       const { return m_id; }

	void  SetName(const char* name)    { delete []m_name;  m_name = strdup(name); }
	void  SetFName(const char* f_name) { delete []m_fname; m_fname = strdup(f_name); }
	void  SetId(long id)               { m_id = id; }

	// Operators
	const Person& operator=(const Person& p);
	bool          operator==(const Person& p) const;

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Person& p)
	{ os << " Name: " << p.m_name << " FName: " << p.m_fname; return os; }

protected:
	char* m_name;
	char* m_fname;
	long  m_id;
};


#endif
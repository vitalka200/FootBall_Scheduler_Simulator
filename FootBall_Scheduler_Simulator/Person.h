#ifndef __PERSON_H
#define __PERSON_H

#include <iostream>

class Person
{
public:
	// c-tors, d-tors
	Person(const char* name, const char* f_name, long id)
		: m_name(NULL), m_fname(NULL) {SetName(name); SetFName(f_name); SetId(id);}
	Person(const Person& p)
		: m_name(NULL), m_fname(NULL) { *this = p; }
	~Person()                         { delete []m_name; delete []m_fname; }
	const Person&  operator=(const Person& p);
	// Methods
	const char*    GetName()     const { return m_name; }
	const char*    GetFName()    const { return m_fname; }
	const long     GetId()       const { return m_id; }

	void  SetName(const char* name)    { delete []m_name; m_name = strdup(name); }
	void  SetFName(const char* f_name) { delete []m_fname; m_fname = strdup(f_name); }
	void  SetId(long id)               { id = m_id; }

	// Method Overrides
	friend std::ostream& operator<<(std::ostream& os, const Person& p);

protected:
	char* m_name;
	char* m_fname;
	long  m_id;
};


#endif
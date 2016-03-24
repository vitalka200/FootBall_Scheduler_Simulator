#ifndef __PERSON_H
#define __PERSON_H

class Person
{
public:
	// c-tors, d-tors
	Person(const char* name, const char* f_name, long id)
		: m_name(NULL), m_fname(NULL) {SetName(name); SetFName(f_name); SetId(id);}
	Person(const Person& p);
	~Person()              {delete []m_name; delete []m_fname;}
	// Methods
	char* GetName()  const {return m_name;}
	char* GetFName() const {return m_fname;}
	long  GetId()    const {return m_id;}

	void  SetName(const char* name);
	void  SetFName(const char* f_name);
	void  SetId(long id) {id = m_id;}

protected:
	char* m_name;
	char* m_fname;
	long  m_id;
};


#endif
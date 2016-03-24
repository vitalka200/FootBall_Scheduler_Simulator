#ifndef __TIMEANDDATE_H
#define __TIMEANDDATE_H


class Time
{
public:
	// c-tors, d-tors
	Time(int minute, int hour);
	Time(const Time& t);
	// Operators

	// Methods


private:
	int m_minute;
	int m_hour;
};

class Date
{
public:
	// c-tors, d-tors
	Date(int date, int month, int year);
	Date(const Date& d);
	// Operators

	// Methods

private:
	int m_date;
	int m_month;
	int m_year;
};

class TimeAndDate
{
public:
	// c-tors, d-tors
	TimeAndDate(int minute, int hour, int date, int month, int year)
		:m_time(minute, hour), m_date(date, month, year) { }
	TimeAndDate(const TimeAndDate& tad);
	// Operators

	// Methods

private:
	Time m_time;
	Date m_date;
};


#endif
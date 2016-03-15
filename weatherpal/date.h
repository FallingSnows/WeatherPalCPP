#pragma once

#ifndef DATE_H
#define DATE_H

class Date
{
	unsigned int	m_year;
	unsigned int	m_month;
	unsigned int	m_day;

public:
	Date(unsigned int year, unsigned int month, unsigned int day);
	//copy constructor, donot need, use defaut copy constructor
	//Date(const Date& date);

	unsigned int	GetYear(void) const;
	void			SetYear(const unsigned int & year);

	unsigned int	GetMonth(void) const;
	void			SetMonth(const unsigned int & month);

	unsigned int	GetDay(void) const;
	void			SetDay(const unsigned int & day);

	void			AddOneDay();
	void			display();

	Date&			operator++();
	Date			operator++(int);
	bool			operator<(Date date) const;
	bool			operator=(Date date) const;
	
	void			ShiftDays(unsigned int day);

};

#endif // !DATE_H

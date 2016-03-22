#include "date.h"
#include <vector>
#include <iostream>

Date::Date(unsigned int year, unsigned int month, unsigned int day) :
	m_year(year), m_month(month), m_day(day)
{};


void Date::AddOneDay()
{
	unsigned int flag = 0;
	if (m_year % 4 == 0)
	{
		if (m_year % 100 == 0)
		{
			flag = (m_year % 400 == 0)? 1 : 0;
		}
		else
		{
			flag = 1;
		}
	}

	std::vector<int> lengthOfMonths = {31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};

	lengthOfMonths[1] += flag;

	if (m_day < lengthOfMonths[m_month - 1])
	{
		m_day++;
	}
	else
	{
		m_day = 1;
		if (m_month == 12)
		{
			m_month = 1;
			m_year++;
		}
		else
		{
			m_month++;
		}
	}

	return;
}

void Date::display()
{
	std::cout << m_year << "-" << m_month << "-" << m_day << " ";
	return;
};

unsigned int Date::GetYear(void) const
{
	return m_year;
};
void Date::SetYear(const unsigned int & year)
{
	m_year = year;
	return;
};

unsigned int Date::GetMonth(void) const
{
	return m_month;
};
void Date::SetMonth(const unsigned int & month)
{
	m_month = month;
	return;
};;

unsigned int Date::GetDay(void) const
{
	return m_day;
};
void Date::SetDay(const unsigned int & day)
{
	m_day = day;
	return;
};

Date& Date::operator++()
{
	AddOneDay();
	return *this;
};
Date Date::operator++(int)
{
	Date tem = *this;
	this->AddOneDay();
	return tem;
};

bool Date::operator<(Date date) const
{
	if (m_year < date.GetYear())
	{
		return true;
	}
	else if (m_year == date.GetYear())
	{
		if (m_month < date.GetMonth())
		{
			return true;
		}
		else if (m_month == date.GetMonth())
		{
			if (m_day < date.GetDay())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
};
bool Date::operator==(Date date) const
{
	if (m_year == date.GetYear() & m_month == date.GetMonth() & m_day == date.GetDay())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Date::ShiftDays(unsigned int day)
{
	while (day != 0)
	{
		this ->operator++();
		day--;
	}

	return;
};
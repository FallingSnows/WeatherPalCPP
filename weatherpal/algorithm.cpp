#include "algorithm.h"
#include <iostream>


double FindMinOfAVector(const std::vector<double>& vect)
{
	std::size_t index = 0;
	if (vect.empty())
	{
		std::cerr << "You are looking for a min in an empty vector!" << std::endl;
		exit(0);
	}
	else
	{
		for (std::size_t i = 0; i < vect.size(); ++i)
		{
			index = vect[index] < vect[i] ? index : i;
		}
	}
		
	return vect[index];
};

double FindMaxOfAVector(const std::vector<double>& vect)
{
	std::size_t index = 0;
	if (vect.empty())
	{
		std::cerr << "You are looking for a min in an empty vector!" << std::endl;
		exit(0);
	}
	else
	{
		for (std::size_t i = 0; i < vect.size(); ++i)
		{
			index = vect[index] < vect[i] ? i : index;
		}
	}

	return vect[index];
};
int compare(const void * a, const void * b)
{
	return (*(double*)a > *(double*)b)? 1 : -1;
}

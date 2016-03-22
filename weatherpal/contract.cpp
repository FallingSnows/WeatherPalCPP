#pragma once

#include "contract.h"
#include "historicaldata.h"
#include "algorithm.h"

Contract::Contract(std::vector<std::string> clientRecord)
{
	m_amount = std::stoul(clientRecord[0], nullptr, 0);
	
	m_price = std::stoul(clientRecord[1], nullptr, 0);

	m_payout = std::stoul(clientRecord[2], nullptr, 0);

	m_strike = std::stoul(clientRecord[3], nullptr, 0);

	m_protectedBeginMonth = std::stoul(clientRecord[4], nullptr, 0);

	m_protectedBeginDay = std::stoul(clientRecord[5], nullptr, 0);

	std::size_t i = 6;
	while (i != clientRecord.size())
	{
		if (clientRecord[i] != "")
		{
			m_protectedDestination.push_back(clientRecord[i]);
		}
		i++;
	}
		
};

unsigned int Contract::GetAmount() const
{
	return m_amount;
};
std::vector<std::string> Contract::GetDestinationPath() const
{
	return m_protectedDestination;
};
std::string Contract::GetContractInformation() const
{
	std::string result = "ContractInformation: ";
	result.append(std::to_string(m_amount) + " ");
	result.append(std::to_string(m_price) + " ");
	result.append(std::to_string(m_payout) + " ");
	result.append(std::to_string(m_strike) + " ");
	result.append(std::to_string(m_protectedBeginMonth) + " ");
	result.append(std::to_string(m_protectedBeginDay) + " ");
	for (auto i = 0; i < m_protectedDestination.size(); ++i)
	{
		result.append(m_protectedDestination[i] + " ");
	}
	
	return result;
};
Date Contract::GetProtectionEndDate() const
{
	Date protectionBeginDate(2015, m_protectedBeginMonth, m_protectedBeginDay);
	/*
	unsigned int protectedDays = m_protectedDestination.size();
	unsigned int i = 0;

	while (i != protectedDays)
	{
		protectionBeginDate++;
		i++;
	}
	*/

	protectionBeginDate.ShiftDays(m_protectedDestination.size());
	return protectionBeginDate;
};

bool Contract::IsExpired(Date today) const
{
	if (today < this->GetProtectionEndDate())
	{
		return false;
	}
	else
	{
		return true;
	}
		
};

std::vector<double> ClassicalTouristPrecipitationContract::GetHistoricalRiskDistribution(std::map<std::string, std::vector<SimpleHistoricalRecordUnit> > historicalRecord)
{
	std::vector<double> result(20);
	
	unsigned int strikeDayNumber = ProtectedDayNumberToStrikeDayNumber();
	
	for (auto i = 0; i != m_protectedDestination.size(); ++i)
	{
		
		std::vector<SimpleHistoricalRecordUnit> record = historicalRecord.find(m_protectedDestination[i])->second;
		
		for (auto ite = record.begin(); ite != record.end(); ++ite)
		{
			if (ite->GetYear() > 1994 && ite ->GetMonth() == m_protectedBeginMonth && ite->GetDay() == m_protectedBeginDay + i)
			{
				result[ite->GetYear() - 1995] += ( ite->GetPrecipitationFrom20OClockTo20OClock() >=  m_strike? 1 : 0);
			}
		}

	}


	
	


	for (auto i = 0; i != result.size(); ++i)
	{
		if (result[i] >= ProtectedDayNumberToStrikeDayNumber())
		{
			result[i] = ((double)m_price - (double)m_payout) * (double)m_amount;
		}
		else
		{
			result[i] = (double)(m_price * m_amount);
		}
		
	}
	
	return result;
};

unsigned int ClassicalTouristPrecipitationContract::ProtectedDayNumberToStrikeDayNumber()
{
	unsigned int protectedDayNumber = m_protectedDestination.size();
	unsigned int strikeDayNumber = 2;
	
	if (protectedDayNumber < 6)
	{
		if (protectedDayNumber > 1)
		{
			return strikeDayNumber;
		}
		else
		{
			return 1;
		}
	}
	else if(protectedDayNumber < 15)
	{
		return protectedDayNumber / 2;
	}
	else
	{
		std::cout << "the protected period is too long for this contract!" << std::endl;
		return 0;
	}
};


AgriculturalContracts::AgriculturalContracts(Date  pretectionBeginDate, unsigned int protectedDays, std::string protectedLocation, double price, IndiceType indiceType) :
	m_pretectionBeginDate(pretectionBeginDate), m_protectedDays(protectedDays), m_protectedLocation(protectedLocation), m_price(price), m_indiceType(indiceType)
{};
//getter and setter of Agricultural Contracts
Date AgriculturalContracts::GetProtectionBeginDate() const
{
	return m_pretectionBeginDate;
};
void AgriculturalContracts::SetProtectionBeginDate(Date pretectionBeginDate)
{
	m_pretectionBeginDate = pretectionBeginDate;
	return;
};
unsigned int AgriculturalContracts::GetProtectedDays() const
{
	return m_protectedDays;
};
void AgriculturalContracts::SetProtectedDays(unsigned int protectedDays)
{
	m_protectedDays = protectedDays;
	return;
};

std::string AgriculturalContracts::GetProtectedLocation() const
{
	return m_protectedLocation;
};
void AgriculturalContracts::SetProtectedLocation(std::string location)
{
	m_protectedLocation = location;
	return;
};


void AgriculturalContinualContracts::SetMode(Mode m)
{
	m_mode = m;
	return;
};

void AgriculturalContinualContracts::SetContinualDays(unsigned int d)
{
	m_continualDays = d;
	return;
};


std::vector<double> AgriculturalContinualContracts::MultiCalculator(SimpleRecordFile& sRF) const
{
	std::vector<double> result(20);
	std::vector<SimpleHistoricalRecordUnit> historicalData = sRF.GetSimpleRecordFileData();
	Date beginDate = m_pretectionBeginDate;
	Date endDate = m_pretectionBeginDate;
	endDate.ShiftDays(m_protectedDays - m_continualDays + 1);
	std::vector<double> bigWindows;
	std::vector<double> smallWindows(m_continualDays, 9999);
	if (m_mode == PriceMode)
	{
		std::size_t index = 0;
		for (auto ite = historicalData.begin(); ite != historicalData.end(); ++ite)
		{
			if (ite->GetYear() > 1995)
			{
				beginDate.SetYear(ite->GetYear());
				endDate.SetYear(ite->GetYear());
				
				if(((beginDate < ite->GetDate()) || (beginDate == ite->GetDate()))  & ((ite->GetDate() < endDate) || (ite->GetDate() == endDate)))
				{
					index++;
					std::vector<double> record = ite->GetRecord();
					double temp = record[m_indiceType - 4];
					smallWindows[index%m_continualDays] = temp;
					if (index > 1)
					{
						bigWindows.push_back(FindMinOfAVector(smallWindows));
					}
				}

				if (ite->GetDate() == endDate)
				{
					result[ite->GetYear() - 1996] = FindMaxOfAVector(bigWindows);
					bigWindows.clear();
				}

			}
		}
		
	}
	else
	{

	}

	

	return result;
};



void AgriculturalAllInContracts::SetMode(Mode m)
{
	m_mode = m;
	return;
};

std::vector<double> AgriculturalAllInContracts::MultiCalculator(SimpleRecordFile& sRF) const
{
	std::vector<double> result(20);
	std::vector<SimpleHistoricalRecordUnit> historicalData = sRF.GetSimpleRecordFileData();
	Date beginDate = m_pretectionBeginDate;
	Date endDate = m_pretectionBeginDate;
	endDate.ShiftDays(m_protectedDays - 1);
	double  partSum = 0;
	if (m_mode == PriceMode)
	{
		std::size_t index = 0;
		for (auto ite = historicalData.begin(); ite != historicalData.end(); ++ite)
		{
			if (ite->GetYear() > 1995)
			{
				beginDate.SetYear(ite->GetYear());
				endDate.SetYear(ite->GetYear());

				if (((beginDate < ite->GetDate()) || (beginDate == ite->GetDate()))  & ((ite->GetDate() < endDate) || (ite->GetDate() == endDate)))
				{
					std::vector<double> record = ite->GetRecord();
					double temp = record[m_indiceType - 4];
					partSum += temp;
				}

				if (ite->GetDate() == endDate)
				{
					result[ite->GetYear() - 1996] = partSum;
					partSum = 0;
				}

			}
		}

	}
	else
	{

	}



	return result;
};

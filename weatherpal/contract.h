#pragma once

#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "file.h"

enum IndiceType
{
	Precipitation = 4
};

class Contract
{
protected:
	unsigned int					m_amount;
	unsigned int					m_price;
	unsigned int					m_payout;
	unsigned int					m_strike;
	unsigned int					m_protectedBeginMonth;
	unsigned int					m_protectedBeginDay;
	std::vector<std::string>		m_protectedDestination;
	
public:
	Contract(std::vector<std::string> clientRecord);
	virtual ~Contract() {};

	unsigned int GetAmount() const;
	std::vector<std::string> GetDestinationPath() const;
		
	std::string GetContractInformation() const;

	Date GetProtectionEndDate() const;

	bool IsExpired(Date today) const;
};

class ClassicalTouristPrecipitationContract : public Contract
{
	IndiceType m_indiceType;

public:
	ClassicalTouristPrecipitationContract(std::vector<std::string>	record) :
		Contract(record),
		m_indiceType(Precipitation)
	{};
	

	~ClassicalTouristPrecipitationContract() {};

	unsigned int ProtectedDayNumberToStrikeDayNumber();
	std::vector<double> GetHistoricalRiskDistribution(std::map<std::string, std::vector<SimpleHistoricalRecordUnit> > historicalRecord);
};

class HignTempretureContract: public Contract
{


};

#endif
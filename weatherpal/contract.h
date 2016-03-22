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
	Precipitation = 4,
	HighTemperature = 5,
	LowTemperature = 6
};

enum Mode
{
	PriceMode = 0,
	RiskMode = 1
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

class AgriculturalContracts
{
protected:
	Date							m_pretectionBeginDate;
	unsigned int					m_protectedDays;
	std::string						m_protectedLocation;
	double							m_price;
	IndiceType						m_indiceType;

public:
	AgriculturalContracts(Date pretectionBeginDate, unsigned int protectedDays, std::string protectedLocation, double price, IndiceType indiceType);
	//getter and setter
	Date GetProtectionBeginDate() const;
	void SetProtectionBeginDate(Date);
	unsigned int GetProtectedDays() const;
	void SetProtectedDays(unsigned int);
	std::string GetProtectedLocation() const;
	void SetProtectedLocation(std::string location);
};

class AgriculturalContinualContracts :public AgriculturalContracts
{
	Mode							m_mode;
	double							m_strike;
	unsigned int					m_continualDays;
public:
	AgriculturalContinualContracts(Date pretectionBeginDate, unsigned int protectedDays, std::string protectedLocation, double price, IndiceType indiceType) : AgriculturalContracts(pretectionBeginDate, protectedDays, protectedLocation, price, indiceType) {};

	void SetMode(Mode m);
	void SetContinualDays(unsigned int d);
	std::vector<double> MultiCalculator(SimpleRecordFile& sRF) const;
};

class AgriculturalAllInContracts :public AgriculturalContracts
{
	Mode							m_mode;
	double							m_strike;
public:
	AgriculturalAllInContracts(Date pretectionBeginDate, unsigned int protectedDays, std::string protectedLocation, double price, IndiceType indiceType) : AgriculturalContracts(pretectionBeginDate, protectedDays, protectedLocation, price, indiceType) {};

	void SetMode(Mode m);
	std::vector<double> MultiCalculator(SimpleRecordFile& sRF) const;
};


#endif
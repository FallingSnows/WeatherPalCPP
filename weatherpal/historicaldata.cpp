#include "historicaldata.h"


StandardHistoricalRecordUnit::StandardHistoricalRecordUnit(std::vector<std::string> lineRecord)
{
	std::vector<unsigned int> lineRecord_(20);//20 is the vol of a standard record
	
	if(lineRecord.size() == 20)
	{
		for (std::size_t i = 0; i != lineRecord.size(); ++i)
		{
			lineRecord_[i] = std::stoul(lineRecord[i], nullptr, 0);
		}
	}

	m_record = lineRecord_;
	
	/*	
	m_StationId = lineRecord_[0];
	m_Year = lineRecord_[1];
	m_Month = lineRecord_[2];
	m_Day = lineRecord_[3];
	m_PrecipitationFrom20OClockTo20OClock = lineRecord_[4];
	m_LocalMaximunWindSpeed = lineRecord_[5];
	m_DirectionOfLocalMaximunWindSpeed = lineRecord_[6];
	m_AveragePressure = lineRecord_[7];
	m_AverageWindSpeed = lineRecord_[8];
	m_AverageTempreture = lineRecord_[9];
	m_AverageWaterVoporPressure = lineRecord_[10];
	m_AverageRelativeHuminity = lineRecord_[11];
	m_SunshineDuration = lineRecord_[12];
	m_DailyMinimumPressure = lineRecord_[13];
	m_DailyMinimumTempreture = lineRecord_[14];
	m_DailyMaximumPressure = lineRecord_[15];
	m_DailyMaximumTempreture = lineRecord_[16];
	m_MaximumWindSpeed = lineRecord_[17];
	m_DirectionOfMaximumWindSpeed = lineRecord_[18];
	m_DailyMaximumRelativeHuminity = lineRecord_[19];
	*/

};

std::vector<unsigned int> StandardHistoricalRecordUnit::GetRecord() const
{
	return m_record;
};
void StandardHistoricalRecordUnit::SetRecord(std::vector<unsigned int> record)
{
	m_record = record;
	return;
};

Date SimpleHistoricalRecordUnit::GetDate() const
{
	return m_date;
};
void SimpleHistoricalRecordUnit::SetDate(const Date & date)
{
	m_date = date;
	return;
};


SimpleHistoricalRecordUnit::SimpleHistoricalRecordUnit(std::vector<std::string> record) :
	m_date(std::stoul(record[0], nullptr, 0), std::stoul(record[1], nullptr, 0), std::stoul(record[2], nullptr, 0))
{
	m_record.push_back(std::stoul(record[3], nullptr, 0));
	m_record.push_back(std::stoul(record[4], nullptr, 0));
	m_record.push_back(std::stoul(record[5], nullptr, 0));
	//m_record[1] = std::stoul(record[4], nullptr, 0);
	//m_record[2] = std::stoul(record[5], nullptr, 0);
};


unsigned int SimpleHistoricalRecordUnit::GetYear() const
{
	return m_date.GetYear();
};
void SimpleHistoricalRecordUnit::SetYear(const unsigned int & year)
{
	m_date.SetYear(year);
	return;
};

unsigned int SimpleHistoricalRecordUnit::GetMonth() const
{
	return m_date.GetMonth();
};
void SimpleHistoricalRecordUnit::SetMonth(const unsigned int & month)
{
	m_date.SetMonth(month); 
	return;
};

unsigned int SimpleHistoricalRecordUnit::GetDay() const
{
	return m_date.GetDay();
};
void SimpleHistoricalRecordUnit::SetDay(const unsigned int & day)
{
	m_date.SetDay(day);
	return;
};

double SimpleHistoricalRecordUnit::GetPrecipitationFrom20OClockTo20OClock() const
{
	return m_record[0];
};
void SimpleHistoricalRecordUnit::SetPrecipitationFrom20OClockTo20OClock(const double & precipitationFrom20OClockTo20OClock)
{
	m_record[0] = precipitationFrom20OClockTo20OClock;
	return;
};

double SimpleHistoricalRecordUnit::GetDailyMaximunTempreture() const
{
	return m_record[1];
};
void SimpleHistoricalRecordUnit::SetDailyMaximunTempreture(const double & dailyMaximunTempreture)
{
	m_record[1] = dailyMaximunTempreture;
	return;
};

double SimpleHistoricalRecordUnit::GetDailyMinimunTempreture() const
{
	return m_record[2];
};
void SimpleHistoricalRecordUnit::SetDailyMinimunTempreture(const double & dailyMinimunTempreture)
{
	m_record[2] = dailyMinimunTempreture;
	return;
};

std::vector<double> SimpleHistoricalRecordUnit::GetRecord() const
{
	return m_record;
};


/*
SimpleHistoricalRecord::SimpleHistoricalRecord(std::string cityName):
	m_cityName(cityName)
{
	std::string csvPath = FILE_PATH + fileName;

	std::ifstream		data(csvPath);
	std::string			line;

	while (std::getline(data, line))
	{
		std::stringstream			lineStream(line);
		std::string					cell;
		std::vector<std::string>	recordString;

		while (std::getline(lineStream, cell, ';'))
		{
			recordString.push_back(cell);
		}

		StandardHistoricalRecordUnit record_(recordString);
		m_data.push_back(record_);

		recordString.clear();
	}
};
std::string SimpleHistoricalRecord::GetCityName() const
{
	return m_cityName;
};
HistoricalRecord SimpleHistoricalRecord::GetHistoricalRecord() const
{
	return m_historicalRecord;
};
*/

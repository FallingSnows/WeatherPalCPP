#include "file.h"

File::File(std::string FileName):m_fileName(FileName){};

std::string File::GetFileName() const
{
	return m_fileName;
};
void File::SetFileName(const std::string & fileName)
{
	m_fileName = fileName;
	return;
};


std::vector<StandardHistoricalRecordUnit> StandardRecordFile::GetStandardRecordFileData(void) const
{
	return m_data;
};
void StandardRecordFile::SetStandardRecordFileData(std::vector<StandardHistoricalRecordUnit> data)
{
	m_data = data;
	return;
};

std::vector<SimpleHistoricalRecordUnit> SimpleRecordFile::GetSimpleRecordFileData(void) const
{
	return m_data;
};
void SimpleRecordFile::SetSimpleRecordFileData(std::vector<SimpleHistoricalRecordUnit> data)
{
	m_data = data;
	return;
};

StandardRecordFile::StandardRecordFile(std::string fileName): File(fileName)
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

SimpleRecordFile::SimpleRecordFile(std::string fileName) :File(fileName)
{
	std::string csvPath = FILE_PATH + fileName + ".csv";
	m_ifFileExists = false;

	std::ifstream		data(csvPath);
	std::string			line;

	std::getline(data, line);
	while (std::getline(data, line))
	{
		if (!m_ifFileExists)
		{
			m_ifFileExists = true;
		}

		std::stringstream			lineStream(line);
		std::string					cell;
		std::vector<std::string>	recordString;

		while (std::getline(lineStream, cell, ';'))
		{
			recordString.push_back(cell);
		}

		SimpleHistoricalRecordUnit record_(recordString);
		m_data.push_back(record_);

		recordString.clear();
	}

	if (!m_ifFileExists)
	{
		std::cerr << m_fileName << " historical data doesn't exists!" << std::endl;
	}
}

ClientInformationFile::ClientInformationFile(std::string fileName): File(fileName)
{
	std::string			csvPath = CLIENT_FILE_PATH + "client.csv";

	std::ifstream		data(csvPath);
	std::string			line;
	
	
	std::getline(data, line);

	while (std::getline(data, line))
	{
		std::stringstream			lineStream(line);
		std::string					cell;
		std::vector<std::string>	recordString;

		while (std::getline(lineStream, cell, ';'))
		{
			recordString.push_back(cell);
		}

		m_record.push_back(recordString);

		recordString.clear();
	}
};

std::vector<std::vector<std::string> > ClientInformationFile::GetRecord(void) const
{
	return m_record;
};
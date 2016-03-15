#pragma once
#ifndef FILE_H
#define FILE_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "historicaldata.h"

//where to store all the resource file
const std::string FILE_PATH = "C:\\Users\\Haifeng\\Desktop\\WPData\\";
const std::string CLIENT_FILE_PATH = "C:\\Users\\Haifeng\\Desktop\\Client\\";

//basic file definition
class File
{
protected:
	std::string m_fileName;	

public:
	File(std::string fileName);
	virtual ~File() {};

	//getter and setter
	std::string GetFileName(void) const;
	void SetFileName(const std::string & fileName);

};

//standard historical data file
class StandardRecordFile: public File
{
	std::vector<StandardHistoricalRecordUnit> m_data;

public:
	//constructor
	StandardRecordFile(std::string fileName);

	//getter and setter
	std::vector<StandardHistoricalRecordUnit> GetStandardRecordFileData(void) const;
	void SetStandardRecordFileData(std::vector<StandardHistoricalRecordUnit> data);
};

//simple historical data file
class SimpleRecordFile: public File
{
	std::vector<SimpleHistoricalRecordUnit>			m_data;
	bool											m_ifFileExists;

public:
	SimpleRecordFile(std::string fileName);

	//getter and setter
	std::vector<SimpleHistoricalRecordUnit> GetSimpleRecordFileData(void) const;
	void SetSimpleRecordFileData(std::vector<SimpleHistoricalRecordUnit> data);
};

//client information file
class ClientInformationFile : public File
{
	std::vector<std::vector<std::string> >		m_record;
public:
	//constructor
	ClientInformationFile(std::string fileName);

	//getter
	std::vector<std::vector<std::string> > GetRecord(void) const;
};
#endif

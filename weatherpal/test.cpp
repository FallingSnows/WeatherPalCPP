#include "test.h"
#include <iostream>
#include <map>
#include "file.h"
#include "historicaldata.h"
#include "date.h" 
#include "contract.h"

void RiskClaculator()
{
	ClientInformationFile clientFile = ClientInformationFile("client.csv");
	auto a = clientFile.GetRecord();

	std::map<std::string, std::vector<SimpleHistoricalRecordUnit> > historicalRecord;
	std::vector<ClassicalTouristPrecipitationContract> contractSeries;

	Date today(2015, 3, 14);

	for (auto i = 0; i < a.size(); ++i)
	{
		contractSeries.push_back(ClassicalTouristPrecipitationContract(a[i]));

		bool status = !contractSeries[i].IsExpired(today);
		if (status)
		{
			std::vector<std::string> path = contractSeries[i].GetDestinationPath();

			for (auto j = 0; j < path.size(); ++j)
			{
				if (historicalRecord.find(path[j]) == historicalRecord.end() & path[j] != "")
				{
					SimpleRecordFile sRF(path[j]);
					std::pair<std::string, std::vector<SimpleHistoricalRecordUnit> > sRF2Pair(path[j], sRF.GetSimpleRecordFileData());
					historicalRecord.insert(sRF2Pair);
				}
			}
		}
	}
	std::cerr << "File check done! Please enter any key + Enter: " << std::endl;
	getchar();
	std::cerr << "Risk calculs begin......" << std::endl;

	std::vector<std::vector<double> > result(contractSeries.size());
	for (auto i = 0; i < contractSeries.size(); ++i)
	{
		if (!contractSeries[i].IsExpired(today))
		{
			result[i] = contractSeries[i].GetHistoricalRiskDistribution(historicalRecord);
		}
		else
		{
			result[i].resize(20);
		}
		for (auto j = 0; j != 20; ++j)
		{
			std::cerr << result[i][j] << "  ";
		}
		std::cerr << std::endl;

	}
	std::cerr << "Risk calculs done and the historical result is: " << std::endl;

	std::vector<double> dis(20);
	for (auto i = 0; i != dis.size(); ++i)
	{
		for (auto j = 0; j != result.size(); ++j)
		{
			dis[i] += result[j][i];
		}

		std::cerr << dis[i] << "  ";
	}
	std::cerr << std::endl;

	
};
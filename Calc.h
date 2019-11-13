#pragma once

#include <iostream>
#include <map>

#include "Config.h"
#include "Building.h"

using namespace std;

class Calc
{
public:
    Calc();
    virtual ~Calc();

	multimap<double, unordered_map<string, double> > Start();

private:

    vector<unordered_map<string, Building*> > GetComb(const unordered_map<string, Building*> &mapData);

    void AddAdditionBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff);

    void ResetAdditionBuff(const unordered_map<string, Building*> &mapBuilding);

    void AddTargetBuff(const string &sTargetId, const unordered_map<string, Building*> &mapBuilding, double dBuff);

    void PrepareBuff(const unordered_map<string, Building*> &mapResidence, const unordered_map<string, Building*> &mapBusiness, const unordered_map<string, Building*> &mapIndustrial, const unordered_map<string, Building*> &mapAllBuilding);

    void CalcProfit(const string &sCategory, const unordered_map<string, Building*> &mapBuilding, multimap<double, unordered_map<string, double> > &mapTotalProfit);

    void ShowResult(const multimap<double, unordered_map<string, double> > &mapTotalProfit, int topN);

	multimap<double, unordered_map<string, double> > CreateScenes(const string& sCategory, const vector<unordered_map<string, Building*> > &vResidence, const vector<unordered_map<string, Building*> > &vBusiness, const vector<unordered_map<string, Building*> > &vIndustrial);

};
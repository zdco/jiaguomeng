#include <iostream>
#include <map>

#include "Config.h"
#include "Building.h"

vector<unordered_map<string, Building*> > GetComb(const unordered_map<string, Building*> &mapData)
{
    vector<unordered_map<string, Building*> > vOut;
    vector<pair<string, Building*> > vData;
    for (auto it = mapData.begin(); it != mapData.end(); it++)
    {
        vData.push_back(make_pair(it->first, it->second));
    }

    if (vData.size() >= 3)
    {
        for (size_t i = 0; i < vData.size() - 2; i++)
        {
            for (size_t j = i + 1; j < vData.size() - 1; j++)
            {
                for (size_t k = j + 1; k < vData.size(); k++)
                {
                    unordered_map<string, Building*> mapTemp;
                    mapTemp[vData[i].first] = vData[i].second;
                    mapTemp[vData[j].first] = vData[j].second;
                    mapTemp[vData[k].first] = vData[k].second;
                    vOut.push_back(mapTemp);
                }
            }
        }
    }
    return vOut;
}

void AddAdditionBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->AddAdditionBuff(sCategory, dBuff);
    }
}

void ResetAdditionBuff(const unordered_map<string, Building*> &mapBuilding)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->ResetAdditionBuff();
    }
}

void AddTargetBuff(const string &sTargetId, const unordered_map<string, Building*> &mapBuilding, double dBuff)
{
    auto it = mapBuilding.find(sTargetId);
    if (it != mapBuilding.end())
    {
        it->second->AddAdditionBuff(CategoryAll, dBuff);
    }
}

void PrepareBuff(const unordered_map<string, Building*> &mapResidence, const unordered_map<string, Building*> &mapBusiness, const unordered_map<string, Building*> &mapIndustrial, const unordered_map<string, Building*> &mapAllBuilding)
{
    for (auto it = mapAllBuilding.begin(); it != mapAllBuilding.end(); it++)
    {
        vector<pair<string, double> > vStarBuff = it->second->GetStarBuff();
        for (size_t j = 0; j < vStarBuff.size(); j++)
        {
            const pair<string, double> &buff = vStarBuff[j];
            if (buff.first == CategorySupply
                || buff.first == CategoryAll
                || buff.first == CategoryOnline
                || buff.first == CategoryOffline)
            {
                AddAdditionBuff(mapAllBuilding, buff.first, buff.second);
            }
            else if (buff.first == CategoryResidence)
            {
                AddAdditionBuff(mapResidence, CategoryAll, buff.second);
            }
            else if (buff.first == CategoryBusiness)
            {
                AddAdditionBuff(mapBusiness, CategoryAll, buff.second);
            }
            else if (buff.first == CategoryIndustrial)
            {
                AddAdditionBuff(mapIndustrial, CategoryAll, buff.second);
            }
            else
            {
                AddTargetBuff(buff.first, mapAllBuilding, buff.second);
            }
        }
    }
}

void CalcProfit(const string &sCategory, const unordered_map<string, Building*> &mapBuilding, multimap<double, unordered_map<string, double> > &mapTotalProfit)
{
    unordered_map<string, double> mapBuildingProfit;
    double totalProfit = 0;
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        double dProfit = it->second->GetTotalProfit(sCategory);
        totalProfit += dProfit;
        mapBuildingProfit[it->first] = dProfit;
    }
    mapTotalProfit.insert(make_pair(totalProfit, mapBuildingProfit));
}

void ShowResult(const multimap<double, unordered_map<string, double> > &mapTotalProfit, int topN)
{
    int count = 0;
    for (auto it = mapTotalProfit.rbegin(); it != mapTotalProfit.rend(); it++)
    {
        if (count++ >= topN)
        {
            break;
        }

        cout << it->first << endl;
        for (auto data_it = it->second.begin(); data_it != it->second.end(); data_it++)
        {
            Building* building = Config::GetInstance()->GetBuilding(data_it->first);
            if (building)
            {
                cout << data_it->first << "(" << building->GetName() << "):" << data_it->second << endl;
            }
        }
    }
}

void CreateScenes(const string& sCategory, const vector<unordered_map<string, Building*> > &vResidence, const vector<unordered_map<string, Building*> > &vBusiness, const vector<unordered_map<string, Building*> > &vIndustrial)
{
    multimap<double, unordered_map<string, double> > mapTotalProfit;
    for (size_t i = 0; i < vResidence.size(); i++)
    {
        cout << "progress complete " << i * 100 / vResidence.size() << " %" << endl;
        unordered_map<string, Building*> mapResidence = vResidence[i];
        for (size_t j = 0; j < vBusiness.size(); j++)
        {
            unordered_map<string, Building*> mapBusiness = vBusiness[j];
            for (size_t k = 0; k < vIndustrial.size(); k++)
            {
                unordered_map<string, Building*> mapIndustrial = vIndustrial[k];

                unordered_map<string, Building*> mapAllBuilding;
                mapAllBuilding.insert(mapResidence.begin(), mapResidence.end());
                mapAllBuilding.insert(mapBusiness.begin(), mapBusiness.end());
                mapAllBuilding.insert(mapIndustrial.begin(), mapIndustrial.end());
                PrepareBuff(mapResidence, mapBusiness, mapIndustrial, mapAllBuilding);
                CalcProfit(sCategory, mapAllBuilding, mapTotalProfit);
                ResetAdditionBuff(mapAllBuilding);
            }
        }
    }

    ShowResult(mapTotalProfit, 3);
}

int main()
{
    Config::GetInstance()->LoadData();

    unordered_map<string, vector<vector<string> > > mapCategoryComb;
    unordered_map<string, Building*> mapResidence =  Config::GetInstance()->GetCategoryBuilding(CategoryResidence);
    unordered_map<string, Building*> mapBusiness =  Config::GetInstance()->GetCategoryBuilding(CategoryBusiness);
    unordered_map<string, Building*> mapIndustrial =  Config::GetInstance()->GetCategoryBuilding(CategoryIndustrial);
    vector<unordered_map<string, Building*> > vResidence = GetComb(mapResidence);
    vector<unordered_map<string, Building*> > vBusiness = GetComb(mapBusiness);
    vector<unordered_map<string, Building*> > vIndustrial = GetComb(mapIndustrial);
    cout << "vResidence:" << vResidence.size() << ", vBusiness:" << vBusiness.size() << ", vIndustrial:" << vIndustrial.size() << endl;

    CreateScenes(CategoryOnline, vResidence, vBusiness, vIndustrial);
    
    return 0;
}
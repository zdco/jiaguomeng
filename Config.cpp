#include "Config.h"
#include "Building.h"

Config* Config::m_instance;
Config::Config()
{
}

Config::~Config()
{
    ClearBuilding();
}

Config* Config::GetInstance()
{
    if (m_instance == 0)
    {
        m_instance = new Config;
    }
    return m_instance;
}

void Config::CloseInstance()
{
    if (m_instance)
    {
        delete m_instance;
    }
}

void Config::ClearBuilding()
{
    for (auto it = m_mapBuilding.begin(); it != m_mapBuilding.end(); it++)
    {
        delete it->second;
    }
    m_mapBuilding.clear();
}

void Config::LoadData()
{
    LoadBuildingUpgrade();
    LoadBuffStatus();
    LoadBuildingName();
    LoadBuilding();
    LoadConfig();
}

Building* Config::GetBuilding(const string &sBuildingId)
{
    auto it = m_mapBuilding.find(sBuildingId);
    if (it != m_mapBuilding.end())
    {
        return it->second;
    }
    return NULL;
}

unordered_map<string, Building*> Config::GetBuilding()
{
    return m_mapBuilding;
}

unordered_map<string, Building*> Config::GetCategoryBuilding(const string &sCategory)
{
    unordered_map<string, Building*> mapBuilding;
    auto it = m_mapCategoryBuilding.find(sCategory);
    if (it != m_mapCategoryBuilding.end())
    {
        for (size_t i = 0; i < it->second.size(); i++)
        {
            const string &sBuildingId = it->second[i];
            if (m_setValidBuilding.count(sBuildingId) > 0)
            {
                mapBuilding[sBuildingId] = GetBuilding(sBuildingId);
            }
        }
    }
    return mapBuilding;
}

vector<string> Config::SepStr(const string sStr, const string &sSep)
{
    vector<string> vResult;
    string strTemp = sStr;
    size_t nPos = strTemp.find(sSep);
    while (nPos != string::npos)
    {
        vResult.push_back(strTemp.substr(0, nPos));
        strTemp = strTemp.substr(nPos + sSep.length());
        nPos = strTemp.find(sSep);
    }
    vResult.push_back(strTemp);
    return vResult;
}

void Config::LoadBuildingUpgrade()
{
    string sLine;
    ifstream ifs("data/BuildingUpgrade.csv");
    getline(ifs, sLine); //跳过第一行表头
    cout << sLine << endl;
    while (getline(ifs, sLine))
    {
        vector<string> vField = SepStr(sLine, ",");
        if (vField.size() >= 2)
        {
            int nLevel = atoi(vField[0].c_str());
            double dProfit = atof(vField[1].c_str());
            streamsize csize = cout.precision();
            cout.precision(numeric_limits<double>::digits10);
            cout << "nLevel:" << nLevel << ",dProfit:" << dProfit << endl;
            cout.precision(csize);
            m_mapLevelProfit[nLevel] = dProfit;
        }
    }
}

void Config::LoadBuffStatus()
{
    string sLine;
    ifstream ifs("data/BuffStatus.csv");
    getline(ifs, sLine); //跳过第一行表头
    cout << sLine << endl;
    while (getline(ifs, sLine))
    {
        vector<string> vField = SepStr(sLine, ",");
        if (vField.size() >= 4)
        {
            string sAttrId = vField[0];
            string sEffectId = vField[1];
            double dEffectValue = atof(vField[2].c_str());
            string sTargetId = vField[3];
            cout << "sAttrId:" << sAttrId << ",sEffectId:" << sEffectId << ",dEffectValue:" << dEffectValue << ",sTargetId:" << sTargetId << endl;

            if (sTargetId == "-1")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategorySupply, dEffectValue);
            }
            else if (sTargetId == "1" && sEffectId == "11")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategoryAll, dEffectValue);
            }
            else if (sTargetId == "1" && sEffectId == "21")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategoryOnline, dEffectValue);
            }
            else if (sTargetId == "1" && sEffectId == "31")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategoryOffline, dEffectValue);
            }
            else if (sTargetId == "2")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategoryResidence, dEffectValue);
            }
            else if (sTargetId == "3")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategoryBusiness, dEffectValue);
            }
            else if (sTargetId == "4")
            {
                m_mapBuffStatus[sAttrId] = make_pair(CategoryIndustrial, dEffectValue);
            }
            else
            {
                m_mapBuffStatus[sAttrId] = make_pair(sTargetId, dEffectValue);
            }
        }
    }
}

void Config::LoadBuildingName()
{
    string sLine;
    ifstream ifs("data/BuildingName.csv");
    getline(ifs, sLine); //跳过第一行表头
    cout << sLine << endl;
    while (getline(ifs, sLine))
    {
        vector<string> vField = SepStr(sLine, ",");
        if (vField.size() >= 2)
        {
            string sBuildingId = vField[0];
            string sName = vField[1];
            cout << "sBuildingId:" << sBuildingId << ",sName:" << sName << endl;

            Building* building = GetBuilding(sBuildingId);
            if (building == NULL)
            {
                building = new Building(sName);
                m_mapBuilding[sBuildingId] = building;
            }
        }
    }
}

void Config::LoadBuilding()
{
    string sLine;
    ifstream ifs("data/Building.csv");
    getline(ifs, sLine); //跳过第一行表头
    cout << sLine << endl;
    while (getline(ifs, sLine))
    {
        vector<string> vField = SepStr(sLine, ",");
        if (vField.size() >= 6)
        {
            string sStar = vField[0];
            string sBuildingId = vField[1];
            string sCategory = vField[2];
            //string rarity = vField[3];
            double dProfit = atof(vField[4].c_str());

            vector<pair<string, double> > vBuff;
            string sAttrId1 = vField[5];
            if (sAttrId1 != "0")
            {
                vBuff.push_back(m_mapBuffStatus[sAttrId1]);
            }
            string sAttrId2 = vField[6];
            if (sAttrId2 != "0")
            {
                vBuff.push_back(m_mapBuffStatus[sAttrId2]);
            }
            cout << "sStar:" << sStar << ",sBuildingId:" << sBuildingId << ",sCategory:" << sCategory << ",dProfit:" << dProfit << ",sAttrId1:" << sAttrId1 << ",sAttrId2:" << sAttrId2 << endl;

            Building* building = GetBuilding(sBuildingId);
            if (building)
            {
                building->AddStarProfit(sStar, dProfit);
                building->AddStarBuff(sStar, vBuff);
                m_mapCategoryBuilding[sCategory].push_back(sBuildingId);
            }
        }
    }
}

void Config::LoadConfig()
{
    string sLine;
    ifstream ifs("config/config.csv");
    getline(ifs, sLine); //跳过第一行表头
    while (getline(ifs, sLine))
    {
        vector<string> vField = SepStr(sLine, ",");
        if (vField.size() >= 4)
        {
            string sBuildingId = vField[0];
            string sStar = vField[1];
            int nLevel = atoi(vField[2].c_str());
            bool bValid = atoi(vField[3].c_str());
            Building* building = GetBuilding(sBuildingId);
            if (bValid && building)
            {
                m_setValidBuilding.insert(sBuildingId);
                building->SetStar(sStar);
                building->SetLevel(nLevel);
                building->InitProfit();
            }
        }
    }
}

double Config::GetLevelProfit(int nLevel)
{
    return m_mapLevelProfit[nLevel];
}
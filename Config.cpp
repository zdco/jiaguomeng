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

vector<vector<string> > Config::ParseConfig(const string &configFile)
{
    vector<vector<string> > vConfig;
    ifstream ifs(configFile);
    string sLine;
    getline(ifs, sLine); //跳过第一行表头
    while (getline(ifs, sLine))
    {
        sLine = sLine.substr(0, sLine.find_last_of('\r'));
        if (!sLine.empty())
        {
            vector<string> vField = SepStr(sLine, ",");
            vConfig.push_back(vField);
        }
    }
    return vConfig;
}

void Config::LoadData()
{
    LoadBuildingUpgrade();
    LoadBuffStatus();
    LoadPhotoBuff();
    LoadPolicyBuff();
    LoadBuildingName();
    LoadBuilding();

    LoadPhotoConfig();
    LoadPolicyConfig();
    LoadBuildingConfig();
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

void Config::LoadBuildingUpgrade()
{
    vector<vector<string> > vConfig = ParseConfig("data/BuildingUpgrade.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
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
    vector<vector<string> > vConfig = ParseConfig("data/BuffStatus.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
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
            else if (sTargetId == "1")
            {
                if (sEffectId >= "11" && sEffectId <= "14")
                {
                    m_mapBuffStatus[sAttrId] = make_pair(CategoryAll, dEffectValue);
                }
                else if (sEffectId >= "21" && sEffectId <= "24")
                {
                    m_mapBuffStatus[sAttrId] = make_pair(CategoryOnline, dEffectValue);
                }
                else if (sEffectId >= "31" && sEffectId <= "34")
                {
                    m_mapBuffStatus[sAttrId] = make_pair(CategoryOffline, dEffectValue);
                }
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

void Config::LoadPhotoBuff()
{
    vector<vector<string> > vConfig = ParseConfig("data/PhotoBuff.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            string sPhotoId = vField[0];
            string sEffectId = vField[1];
            cout << "sPhotoId:" << sPhotoId << ",sEffectId:" << sEffectId << endl;
            m_mapPhotoBuff[sPhotoId] = sEffectId;
        }
    }
}

void Config::LoadPolicyBuff()
{
    vector<vector<string> > vConfig = ParseConfig("data/PolicyBuff.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            string sPolicyId = vField[0];
            string sEffectId = vField[1];
            cout << "sPolicyId:" << sPolicyId << ",sEffectId:" << sEffectId << endl;
            m_mapPolicyBuff[sPolicyId].push_back(sEffectId);
        }
    }
}

void Config::LoadBuildingName()
{
    vector<vector<string> > vConfig = ParseConfig("data/BuildingName.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
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
    vector<vector<string> > vConfig = ParseConfig("data/Building.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
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

void Config::AddPhotoBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, int nBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->AddPhotoBuff(sCategory, nBuff);
    }
}

void Config::LoadPhotoConfig()
{
    vector<vector<string> > vConfig = ParseConfig("config/photo.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 1)
        {
            string sPhotoId = vField[0];
            auto it = m_mapPhotoBuff.find(sPhotoId);
            if (it != m_mapPhotoBuff.end())
            {
                auto buff_it = m_mapBuffStatus.find(it->second);
                if (buff_it != m_mapBuffStatus.end())
                {
                    const pair<string, double> &buff = buff_it->second;
                    if (buff.first == CategoryAll
                        || buff.first == CategoryOnline
                        || buff.first == CategoryOffline)
                    {
                        AddPhotoBuff(m_mapBuilding, buff.first, buff.second * 100);
                    }
                    else if (buff.first == CategoryResidence
                        || buff.first == CategoryBusiness
                        || buff.first == CategoryIndustrial)
                    {
                        unordered_map<string, Building*> mapBuilding = GetCategoryBuilding(buff.first);
                        AddPhotoBuff(mapBuilding, CategoryAll, buff.second * 100);
                    }
                }
            }
        }
    }
}

void Config::AddPolicyBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, int nBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->AddPolicyBuff(sCategory, nBuff);
    }
}

void Config::AddPolicyBuff(const string &sEffectId)
{
    auto buff_it = m_mapBuffStatus.find(sEffectId);
    if (buff_it != m_mapBuffStatus.end())
    {
        const pair<string, double> &buff = buff_it->second;
        if (buff.first == CategoryAll
            || buff.first == CategoryOnline
            || buff.first == CategoryOffline)
        {
            AddPolicyBuff(m_mapBuilding, buff.first, buff.second * 100);
        }
        else if (buff.first == CategoryResidence
            || buff.first == CategoryBusiness
            || buff.first == CategoryIndustrial)
        {
            unordered_map<string, Building*> mapBuilding = GetCategoryBuilding(buff.first);
            AddPolicyBuff(mapBuilding, CategoryAll, buff.second * 100);
        }
    }
}

void Config::LoadPolicyConfig()
{
    string sMinPolicyId;
    vector<vector<string> > vConfig = ParseConfig("config/policy.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            string sPolicyId = vField[0];
            int nLevel = atoi(vField[1].c_str());
            cout << "sPolicyId:" << sPolicyId << ",nLevel:" << nLevel << endl;

            if (sMinPolicyId.empty() || sMinPolicyId > sPolicyId)
            {
                sMinPolicyId = sPolicyId;
            }

            if (nLevel > 0)
            {
                auto it = m_mapPolicyBuff.find(sPolicyId);
                if (it != m_mapPolicyBuff.end() && it->second.size() >= nLevel)
                {
                    string sEffectId = it->second[nLevel - 1];
                    AddPolicyBuff(sEffectId);
                }
            }
        }
    }

    //叠加该阶段之前的所有政策buff
    for (auto it = m_mapPolicyBuff.begin(); it != m_mapPolicyBuff.end(); it++)
    {
        if (it->first < sMinPolicyId)
        {
            string sEffectId = it->second.back();
            AddPolicyBuff(sEffectId);
        }
    }
}

void Config::LoadBuildingConfig()
{
    vector<vector<string> > vConfig = ParseConfig("config/building.csv");
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
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
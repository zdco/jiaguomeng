#ifdef WIN32
#include "stdafx.h"
#endif

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

void Config::SaveConfig(const string &configFile, const vector<vector<string> > &vConfig)
{
    ofstream ofs(configFile);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> vField = vConfig[i];
        for (size_t j = 0; j < vField.size(); j++)
        {
            if (j > 0)
            {
                ofs << ",";
            }
            ofs << vField[j];
        }
        ofs << endl;
    }
}

void Config::Init()
{
	LoadBuildingUpgrade();
	LoadBuffStatus();
	LoadPhotoBuff();
	LoadPolicyBuff();
	LoadMissionBuff();
	LoadBuildingName();
	LoadBuilding();
}

void Config::ResetData()
{
	m_setValidBuilding.clear();

	for (auto it = m_mapBuilding.begin(); it != m_mapBuilding.end(); it++)
	{
		it->second->Reset();
	}
}

void Config::LoadData()
{
	ResetData();

    LoadBuildingConfig();
    LoadPhotoConfig();
    LoadPolicyConfig();
    LoadMissionConfig();
    LoadJiaguoConfig();

    InitBuildingProfit();
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
    vector<vector<string> > vConfig = ParseConfig(BuildingUpgradeData);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            int nLevel = atoi(vField[0].c_str());
            double dProfit = atof(vField[1].c_str());
            // streamsize csize = cout.precision();
            // cout.precision(numeric_limits<double>::digits10);
            // cout << "nLevel:" << nLevel << ",dProfit:" << dProfit << endl;
            // cout.precision(csize);
            m_mapLevelProfit[nLevel] = dProfit;
        }
    }
}

void Config::ParseBuffStatus(const string &sEffectId, double dEffectValue, const string &sTargetId, vector<pair<string, double> > &vBuffStatus)
{
    if (sEffectId != "-1")
    {
        if (sTargetId == "-1")
        {
            vBuffStatus.push_back(make_pair(CategorySupply, dEffectValue));
        }
        else if (sTargetId == "1")
        {
            if (sEffectId >= "11" && sEffectId <= "14")
            {
                vBuffStatus.push_back(make_pair(CategoryAll, dEffectValue));
            }
            else if (sEffectId >= "21" && sEffectId <= "24")
            {
                vBuffStatus.push_back(make_pair(CategoryOnline, dEffectValue));
            }
            else if (sEffectId >= "31" && sEffectId <= "34")
            {
                vBuffStatus.push_back(make_pair(CategoryOffline, dEffectValue));
            }
        }
        else if (sTargetId == "2")
        {
            vBuffStatus.push_back(make_pair(CategoryResidence, dEffectValue));
        }
        else if (sTargetId == "3")
        {
            vBuffStatus.push_back(make_pair(CategoryBusiness, dEffectValue));
        }
        else if (sTargetId == "4")
        {
            vBuffStatus.push_back(make_pair(CategoryIndustrial, dEffectValue));
        }
        else
        {
            vBuffStatus.push_back(make_pair(sTargetId, dEffectValue));
        }
    }
}

void Config::LoadBuffStatus()
{
    vector<vector<string> > vConfig = ParseConfig(BuffStatusData);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 13)
        {
            string sBuffId = vField[0];
			for (int j = 0; j < 3; j++)
			{
				string sEffectId = vField[j * 3 + 1];
				double dEffectValue = atof(vField[j * 3 + 2].c_str());
				string sTargetId = vField[j * 3 + 3];
				ParseBuffStatus(sEffectId, dEffectValue, sTargetId, m_mapBuffStatus[sBuffId]);
            }
        }
    }
}

unordered_map<string, vector<pair<string, double> > > Config::GetBuffStatus()
{
	return m_mapBuffStatus;
}

void Config::LoadPhotoBuff()
{
    vector<vector<string> > vConfig = ParseConfig(PhotoBuffData);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            string sPhotoId = vField[0];
            string sBuffId = vField[1];
            //cout << "sPhotoId:" << sPhotoId << ",sBuffId:" << sBuffId << endl;
            m_mapPhotoBuff[sPhotoId] = sBuffId;
        }
    }
}

void Config::LoadPolicyBuff()
{
    vector<vector<string> > vConfig = ParseConfig(PolicyBuffData);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 3)
        {
			string sPolicyId = vField[1];
            string sBuffId = vField[2];
            //cout << "sPolicyId:" << sPolicyId << ",sBuffId:" << sBuffId << endl;
            m_mapPolicyBuff[sPolicyId].push_back(sBuffId);
        }
    }
}

void Config::LoadMissionBuff()
{
    vector<vector<string> > vConfig = ParseConfig(MissionBuffData);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
			string sMissionId = vField[0];
			string sMissionName = vField[1];
			m_mapMissionName[sMissionId] = sMissionName;
			for (int j = 0; j < 5; j++)
			{
				string sBuffId = vField[j + 2];
				m_mapMissionBuff[sMissionId].push_back(sBuffId);
			}
        }
    }
}

unordered_map<string, vector<string> > Config::GetMissionBuff()
{
	return m_mapMissionBuff;
}

unordered_map<string, string> Config::GetMissionName()
{
	return m_mapMissionName;
}

void Config::LoadBuildingName()
{
    vector<vector<string> > vConfig = ParseConfig(BuildingNameData);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            string sBuildingId = vField[0];
            string sName = vField[1];
            //cout << "sBuildingId:" << sBuildingId << ",sName:" << sName << endl;

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
    vector<vector<string> > vConfig = ParseConfig(BuildingData);
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
            for (int j = 0; j < 2; j++)
            {
                string sBuffId = vField[5 + j];
                if (sBuffId != "0")
                {
                    auto it = m_mapBuffStatus.find(sBuffId);
                    if (it != m_mapBuffStatus.end())
                    {
                        vBuff.insert(vBuff.end(), it->second.begin(), it->second.end());
                    }
                }
            }
            //cout << "sStar:" << sStar << ",sBuildingId:" << sBuildingId << ",sCategory:" << sCategory << ",dProfit:" << dProfit << endl;

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

void Config::LoadBuildingConfig()
{
    vector<vector<string> > vConfig = ParseConfig(BuildingConfig);
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
            }
        }
    }
}

void Config::AddPhotoBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->AddPhotoBuff(sCategory, dBuff);
    }
}

void Config::AddPhotoBuff(const string &sBuffId)
{
    auto buff_it = m_mapBuffStatus.find(sBuffId);
    if (buff_it != m_mapBuffStatus.end())
    {
        const vector<pair<string, double> > &vBuff = buff_it->second;
        for (size_t j = 0; j < vBuff.size(); j++)
        {
            const pair<string, double> &buff = vBuff[j];
            if (buff.first == CategoryAll
                || buff.first == CategoryOnline
                || buff.first == CategoryOffline)
            {
                AddPhotoBuff(m_mapBuilding, buff.first, buff.second);
            }
            else if (buff.first == CategoryResidence
                || buff.first == CategoryBusiness
                || buff.first == CategoryIndustrial)
            {
                unordered_map<string, Building*> mapBuilding = GetCategoryBuilding(buff.first);
                AddPhotoBuff(mapBuilding, CategoryAll, buff.second);
            }
        }
    }
}

void Config::LoadPhotoConfig()
{
    vector<vector<string> > vConfig = ParseConfig(PhotoConfig);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 1)
        {
            string sPhotoId = vField[0];
            auto it = m_mapPhotoBuff.find(sPhotoId);
            if (it != m_mapPhotoBuff.end())
            {
                AddPhotoBuff(it->second);
            }
        }
    }
}

void Config::AddPolicyBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->AddPolicyBuff(sCategory, dBuff);
    }
}

void Config::AddPolicyBuff(const string &sBuffId)
{
    auto buff_it = m_mapBuffStatus.find(sBuffId);
    if (buff_it != m_mapBuffStatus.end())
    {
        const vector<pair<string, double> > &vBuff = buff_it->second;
        for (size_t j = 0; j < vBuff.size(); j++)
        {
            const pair<string, double> &buff = vBuff[j];
            if (buff.first == CategoryAll
                || buff.first == CategoryOnline
                || buff.first == CategoryOffline)
            {
                AddPolicyBuff(m_mapBuilding, buff.first, buff.second);
            }
            else if (buff.first == CategoryResidence
                || buff.first == CategoryBusiness
                || buff.first == CategoryIndustrial)
            {
                unordered_map<string, Building*> mapBuilding = GetCategoryBuilding(buff.first);
                AddPolicyBuff(mapBuilding, CategoryAll, buff.second);
            }
        }
    }
}

void Config::LoadPolicyConfig()
{
    string sMinPolicyId;
    vector<vector<string> > vConfig = ParseConfig(PolicyConfig);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
            string sPolicyId = vField[0];
            int nLevel = atoi(vField[1].c_str());
            //cout << "sPolicyId:" << sPolicyId << ",nLevel:" << nLevel << endl;

            if (sMinPolicyId.empty() || sMinPolicyId > sPolicyId)
            {
                sMinPolicyId = sPolicyId;
            }

            if (nLevel > 0)
            {
                auto it = m_mapPolicyBuff.find(sPolicyId);
                if (it != m_mapPolicyBuff.end() && it->second.size() >= nLevel)
                {
                    string sBuffId = it->second[nLevel - 1];
                    AddPolicyBuff(sBuffId);
                }
            }
        }
    }

    //叠加该阶段之前的所有政策buff
    for (auto it = m_mapPolicyBuff.begin(); it != m_mapPolicyBuff.end(); it++)
    {
		//由于ID排序不规则，使用不等于来判断，相等时终止循环
        if (it->first == sMinPolicyId)
        {
			break;
        }
		string sBuffId = it->second.back();
		AddPolicyBuff(sBuffId);
    }
}

void Config::AddMissionBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        it->second->AddMissionBuff(sCategory, dBuff);
    }
}

void Config::AddMissionBuff(const string &sBuffId)
{
    auto buff_it = m_mapBuffStatus.find(sBuffId);
    if (buff_it != m_mapBuffStatus.end())
    {
        const vector<pair<string, double> > &vBuff = buff_it->second;
        for (size_t j = 0; j < vBuff.size(); j++)
        {
            const pair<string, double> &buff = vBuff[j];
            if (buff.first == CategoryAll
                || buff.first == CategoryOnline
                || buff.first == CategoryOffline)
            {
                AddMissionBuff(m_mapBuilding, buff.first, buff.second);
            }
            else if (buff.first == CategoryResidence
                || buff.first == CategoryBusiness
                || buff.first == CategoryIndustrial)
            {
                unordered_map<string, Building*> mapBuilding = GetCategoryBuilding(buff.first);
                AddMissionBuff(mapBuilding, CategoryAll, buff.second);
            }
            else
            {
                Building* building = GetBuilding(buff.first);
                if (building)
                {
                    building->AddMissionBuff(CategoryAll, buff.second);
                }
            }
        }
    }
}

void Config::LoadMissionConfig()
{
    vector<vector<string> > vConfig = ParseConfig(MissionConfig);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 2)
        {
			string sMissionId = vField[0];
			string sBuffId = vField[1];
			//cout << "sMissionId:" << sMissionId << ",sBuffId:" << sBuffId << endl;
            AddMissionBuff(sBuffId);
        }
    }
}

void Config::LoadJiaguoConfig()
{
    vector<vector<string> > vConfig = ParseConfig(JiaguoConfig);
    for (size_t i = 0; i < vConfig.size(); i++)
    {
        const vector<string> &vField = vConfig[i];
        if (vField.size() >= 1)
        {
            double dBuff = atoi(vField[0].c_str()) / 100.0f;
            AddPolicyBuff(m_mapBuilding, CategoryAll, dBuff);
        }
    }
}

void Config::InitBuildingProfit()
{
    for (auto it = m_mapBuilding.begin(); it != m_mapBuilding.end(); it++)
    {
        it->second->InitProfit();
    }
}

double Config::GetLevelProfit(int nLevel)
{
    return m_mapLevelProfit[nLevel];
}

void Config::SaveBuildingConfig(vector<vector<string> > &vConfig)
{
    vector<string> vHead;
    vHead.push_back("Id");
    vHead.push_back("StarLevel");
    vHead.push_back("Level");
    vHead.push_back("IsCalc");
    vConfig.insert(vConfig.begin(), vHead);
    SaveConfig(BuildingConfig, vConfig);
}

void Config::SavePhotoConfig(vector<vector<string> > &vConfig)
{
    vector<string> vHead;
    vHead.push_back("Id");
    vConfig.insert(vConfig.begin(), vHead);
    SaveConfig(PhotoConfig, vConfig);
}

void Config::SavePolicyConfig(vector<vector<string> > &vConfig)
{
    vector<string> vHead;
    vHead.push_back("NameID");
    vHead.push_back("Level");
    vConfig.insert(vConfig.begin(), vHead);
    SaveConfig(PolicyConfig, vConfig);
}

void Config::SaveMissionConfig(vector<vector<string> > &vConfig)
{
    vector<string> vHead;
	vHead.push_back("NameID");
	vHead.push_back("Effect");
    vConfig.insert(vConfig.begin(), vHead);
    SaveConfig(MissionConfig, vConfig);
}

void Config::SaveJiaguoConfig(vector<vector<string> > &vConfig)
{
    vector<string> vHead;
    vHead.push_back("Effect");
    vConfig.insert(vConfig.begin(), vHead);
    SaveConfig(JiaguoConfig, vConfig);
}

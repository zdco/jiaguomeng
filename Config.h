#pragma once

#include <unordered_map>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>
#include <limits>

using namespace std;

const string BuildingNameData = "data/BuildingName.csv";
const string BuildingData = "data/Building.csv";
const string BuildingUpgradeData = "data/BuildingUpgrade.csv";
const string BuffStatusData = "data/BuffStatus.csv";
const string PhotoNameData = "data/PhotoName.csv";
const string PhotoBuffData = "data/PhotoBuff.csv";
const string PolicyBuffData = "data/PolicyBuff.csv";
const string MissionBuffData = "data/MissionBuff.csv";

const string BuildingConfig = "config/building.csv";
const string PhotoConfig = "config/photo.csv";
const string PolicyConfig = "config/policy.csv";
const string MissionConfig = "config/mission.csv";
const string JiaguoConfig = "config/jiaguo.csv";

const string CategorySupply = "Supply"; //供货
const string CategoryAll = "All"; //所有建筑
const string CategoryOnline = "Online"; //建筑在线
const string CategoryOffline = "Offline"; //建筑离线
const string CategoryResidence = "Residence"; //住宅建筑
const string CategoryBusiness = "Business"; //商业建筑
const string CategoryIndustrial = "Industrial"; //工业建筑

class Building;
class Config
{
public:
    Config();
    virtual ~Config();

    static Config* GetInstance();
    static void CloseInstance();

	void Init();

    void LoadData();

    Building* GetBuilding(const string &sBuildingId);
    //查询等级对应收入
    double GetLevelProfit(int nLevel);
    //查询类别建筑
    unordered_map<string, Building*> GetCategoryBuilding(const string &sCategory);

	vector<vector<string> > ParseConfig(const string &configFile);

    void SaveBuildingConfig(vector<vector<string> > &vConfig);
    void SavePhotoConfig(vector<vector<string> > &vConfig);
    void SavePolicyConfig(vector<vector<string> > &vConfig);
    void SaveMissionConfig(vector<vector<string> > &vConfig);
    void SaveJiaguoConfig(vector<vector<string> > &vConfig);

	unordered_map<string, vector<pair<string, double> > > GetBuffStatus();
	unordered_map<string, vector<string> > GetMissionBuff();
	unordered_map<string, string> GetMissionName();

private:
	void ResetData();
    void ClearBuilding();

    vector<string> SepStr(const string sStr, const string &sSep);

    void SaveConfig(const string &configFile, const vector<vector<string> > &vConfig);

    void LoadBuildingUpgrade();
    void LoadBuffStatus();
    void LoadPhotoBuff();
    void LoadPolicyBuff();
    void LoadMissionBuff();
    void LoadBuildingName();
    void LoadBuilding();

	void LoadBuildingConfig();
	void LoadPhotoConfig();
	void LoadPolicyConfig();
	void LoadMissionConfig();
	void LoadJiaguoConfig();

    void InitBuildingProfit();

	void ParseBuffStatus(const string &sEffectId, double dEffectValue, const string &sTargetId, vector<pair<string, double> > &vBuffStatus);
    void AddPhotoBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff);
    void AddPhotoBuff(const string &sBuffId);
    void AddPolicyBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff);
    void AddPolicyBuff(const string &sBuffId);
    void AddMissionBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff);
    void AddMissionBuff(const string &sBuffId);

private:
    static Config* m_instance;
    unordered_map<int, double> m_mapLevelProfit; //等级对应收益
    unordered_map<string, vector<pair<string, double> > > m_mapBuffStatus; //buff，属性ID->建筑ID->buff
    unordered_map<string, string> m_mapPhotoBuff; //照片buff，照片ID->buff
    unordered_map<string, vector<string> > m_mapPolicyBuff; //政策buff，政策ID->级别->buff
	unordered_map<string, vector<string> > m_mapMissionBuff; //城市任务buff，城市任务ID->buff
	unordered_map<string, string> m_mapMissionName; //城市任务名称，城市任务ID->名称
    unordered_map<string, string> m_mapJiaguoBuff; //家国之光buff，家国之光等级->buff
    unordered_map<string, vector<string> > m_mapCategoryBuilding; //类别对应的建筑ID
    unordered_map<string, Building*> m_mapBuilding; //建筑列表，ID->建筑
    set<string> m_setValidBuilding; //可用建筑列表
};
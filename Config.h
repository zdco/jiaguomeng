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

    void LoadData();

    //查询等级对应收入
    double GetLevelProfit(int nLevel);
    unordered_map<string, Building*> GetBuilding();
    Building* GetBuilding(const string &sBuildingId);
    //查询类别建筑
    unordered_map<string, Building*> GetCategoryBuilding(const string &sCategory);

private:
    void ClearBuilding();

    vector<string> SepStr(const string sStr, const string &sSep);

    void LoadBuildingUpgrade();
    void LoadBuffStatus();
    void LoadBuildingName();
    void LoadBuilding();
    void LoadConfig();

private:
    static Config* m_instance;
    unordered_map<int, double> m_mapLevelProfit; //等级对应收益
    unordered_map<string, pair<string, double> > m_mapBuffStatus; //buff，属性ID->建筑ID->buff
    unordered_map<string, vector<string> > m_mapCategoryBuilding; //类别对应的建筑ID
    unordered_map<string, Building*> m_mapBuilding; //建筑列表，ID->建筑
    set<string> m_setValidBuilding; //可用建筑列表
};
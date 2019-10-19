#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Building
{
public:
    Building(const string &sName);
    
    void AddStarProfit(string sStar, double dProfit);
    void AddStarBuff(string sStar, const vector<pair<string, double> > &vBuff);
    
    void SetLevel(int level);
    void SetStar(string sStar);
    void InitProfit();

    void AddPolicyBuff(const string &sCategory, double dBuff);
    void AddPhotoBuff(const string &sCategory, double dBuff);
    void AddMissionBuff(const string &sCategory, double dBuff);

    void AddAdditionBuff(const string &sCategory, double dBuff);
    void ResetAdditionBuff();

    vector<pair<string, double> > GetStarBuff();
    //获取基础收益
    double GetBaseProfit();
    //获取总收益
    double GetTotalProfit(const string &sCategory);
    string GetName();

private:
    string m_sName; //建筑名称
    double m_dLevelProfit; //建筑等级收益
    string m_sStar; //建筑星级
    double m_starProfit; //星级收益
    
    double m_dOnlineProfit;
    double m_dOfflineProfit;

    //政策buff
    double m_dPolicyBuffAll;
    double m_dPolicyBuffOnline;
    double m_dPolicyBuffOffline;

    //照片buff
    double m_dPhotoBuffAll;
    double m_dPhotoBuffOnline;
    double m_dPhotoBuffOffline;

    //城市任务buff
    double m_dMissionBuffAll;
    double m_dMissionBuffOnline;
    double m_dMissionBuffOffline;

    //建筑加成buff，按其它建筑星级对应
    double m_dAdditionBuffAll;
    double m_dAdditionBuffOnline;
    double m_dAdditionBuffOffline;

    unordered_map<string, vector<pair<string, double> > > m_mapStarBuff; //建筑星级加成其它建筑buff，星级->其它建筑->buff
    unordered_map<string, double> m_mapStarProfit; //建筑星级收入，星级->收益

};

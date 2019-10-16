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

    void AddPolicyBuff(const string &sCategory, int nBuff);
    void AddPhotoBuff(const string &sCategory, int nBuff);
    void AddMissionBuff(const string &sCategory, int nBuff);

    void AddAdditionBuff(const string &sCategory, int nBuff);
    void ResetAdditionBuff();

    vector<pair<string, double> > GetStarBuff();
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
    int m_nPolicyBuffAll;
    int m_nPolicyBuffOnline;
    int m_nPolicyBuffOffline;

    //照片buff
    int m_nPhotoBuffAll;
    int m_nPhotoBuffOnline;
    int m_nPhotoBuffOffline;

    //城市任务buff
    int m_nMissionBuffAll;
    int m_nMissionBuffOnline;
    int m_nMissionBuffOffline;

    //建筑加成buff，按其它建筑星级对应
    int m_nAdditionBuffAll;
    int m_nAdditionBuffOnline;
    int m_nAdditionBuffOffline;

    unordered_map<string, vector<pair<string, double> > > m_mapStarBuff; //建筑星级加成其它建筑buff，星级->其它建筑->buff
    unordered_map<string, double> m_mapStarProfit; //建筑星级收入，星级->收益

};

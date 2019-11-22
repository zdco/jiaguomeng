#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <map>

#include "Config.h"
#include "Building.h"

using namespace std;

class CJiaGuoMengDlg;
class Calc
{
public:
    Calc();
	virtual ~Calc();

	void Start(const int &nThreadCount, CJiaGuoMengDlg* pDlg);
	void Stop();
	//计算完成百分比
	int GetCalcPercent();

private:
    vector<unordered_map<string, Building*> > GetComb(const unordered_map<string, Building*> &mapData);

    void AddAdditionBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff, unordered_map<string, map<string, double> > &mapAdditionBuff);
    void AddTargetBuff(const string &sTargetId, const unordered_map<string, Building*> &mapBuilding, double dBuff, unordered_map<string, map<string, double> > &mapAdditionBuff);
    void PrepareBuff(const unordered_map<string, Building*> &mapResidence, const unordered_map<string, Building*> &mapBusiness, const unordered_map<string, Building*> &mapIndustrial, const unordered_map<string, Building*> &mapAllBuilding, unordered_map<string, map<string, double> > &mapAdditionBuff);

	void CalcThread(const int &nIndex, const int &nCount, const string& sCategory, const vector<unordered_map<string, Building*> > &vResidence, const vector<unordered_map<string, Building*> > &vBusiness, const vector<unordered_map<string, Building*> > &vIndustrial);
    void CalcProfit(const string &sCategory, const unordered_map<string, Building*> &mapBuilding, unordered_map<string, map<string, double> > &mapAdditionBuff, multimap<double, unordered_map<string, double> > &mapTotalProfit);

	void CreateScenes(const int &nThreadCount, const string& sCategory, const vector<unordered_map<string, Building*> > &vResidence, const vector<unordered_map<string, Building*> > &vBusiness, const vector<unordered_map<string, Building*> > &vIndustrial);

private:
	bool m_bRun;
	thread *m_pThread;
	mutex m_mutex;
	multimap<double, unordered_map<string, double> > m_mapTotalProfit;
	unsigned long m_startTime;
	int m_nCurCount; //当前次数
	int m_nTotalCount; //总次数

	CJiaGuoMengDlg* m_pDlg;
};
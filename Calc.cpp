#ifdef WIN32
#include "stdafx.h"
#endif

#include "Calc.h"
#include "JiaGuoMengDlg.h"

Calc::Calc()
{
	m_bRun = false;
	m_pThread = NULL;
	m_startTime = 0;
	m_nCurCount = 0;
	m_nTotalCount = 0;
}

Calc::~Calc()
{
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = NULL;
	}
}

vector<unordered_map<string, Building*> > Calc::GetComb(const unordered_map<string, Building*> &mapData)
{
    vector<unordered_map<string, Building*> > vOut;
    vector<pair<string, Building*> > vData;
    for (auto it = mapData.begin(); it != mapData.end(); it++)
    {
        vData.push_back(make_pair(it->first, it->second));
    }

    if (vData.size() > 3)
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
    else
    {
        vOut.push_back(mapData);
    }
    
    return vOut;
}

void Calc::AddAdditionBuff(const unordered_map<string, Building*> &mapBuilding, const string &sCategory, double dBuff, unordered_map<string, map<string, double> > &mapAdditionBuff)
{
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
		mapAdditionBuff[it->first][sCategory] += dBuff;
    }
}

void Calc::AddTargetBuff(const string &sTargetId, const unordered_map<string, Building*> &mapBuilding, double dBuff, unordered_map<string, map<string, double> > &mapAdditionBuff)
{
    auto it = mapBuilding.find(sTargetId);
    if (it != mapBuilding.end())
    {
		mapAdditionBuff[it->first][CategoryAll] += dBuff;
    }
}

void Calc::PrepareBuff(const unordered_map<string, Building*> &mapResidence, const unordered_map<string, Building*> &mapBusiness, const unordered_map<string, Building*> &mapIndustrial, const unordered_map<string, Building*> &mapAllBuilding, unordered_map<string, map<string, double> > &mapAdditionBuff)
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
                AddAdditionBuff(mapAllBuilding, buff.first, buff.second, mapAdditionBuff);
            }
            else if (buff.first == CategoryResidence)
            {
                AddAdditionBuff(mapResidence, CategoryAll, buff.second, mapAdditionBuff);
            }
            else if (buff.first == CategoryBusiness)
            {
                AddAdditionBuff(mapBusiness, CategoryAll, buff.second, mapAdditionBuff);
            }
            else if (buff.first == CategoryIndustrial)
            {
                AddAdditionBuff(mapIndustrial, CategoryAll, buff.second, mapAdditionBuff);
            }
            else
            {
                AddTargetBuff(buff.first, mapAllBuilding, buff.second, mapAdditionBuff);
            }
        }
    }
}

pair<double, unordered_map<string, double> > Calc::CalcProfit(const string &sCategory, const unordered_map<string, Building*> &mapBuilding, unordered_map<string, map<string, double> > &mapAdditionBuff)
{
    unordered_map<string, double> mapBuildingProfit;
    double totalProfit = 0;
    for (auto it = mapBuilding.begin(); it != mapBuilding.end(); it++)
    {
        double dProfit = it->second->GetProfit(sCategory);
		auto addition_it = mapAdditionBuff[it->first];
		if (sCategory == CategoryOnline)
		{
			dProfit = (1 + addition_it[CategoryAll] + addition_it[CategoryOnline]) * dProfit;
		}
		else if (sCategory == CategoryOffline)
		{
			dProfit = (1 + addition_it[CategoryAll] + addition_it[CategoryOffline]) * dProfit;
		}
        totalProfit += dProfit;
        mapBuildingProfit[it->first] = dProfit;
    }
	return make_pair(totalProfit, mapBuildingProfit);
}

void Calc::CalcThread(const int &nIndex, const int &nCount, const string& sCategory, const vector<unordered_map<string, Building*> > &vResidence, const vector<unordered_map<string, Building*> > &vBusiness, const vector<unordered_map<string, Building*> > &vIndustrial)
{
	int nStartIndex = nIndex * nCount;
	int nCurIndex = 0;
	double dMaxProfit = 0;
	unordered_map<string, double> maxProfitBuilding;
	for (size_t i = 0; i < vResidence.size(); i++)
	{
		unordered_map<string, Building*> mapResidence = vResidence[i];
		for (size_t j = 0; j < vBusiness.size(); j++)
		{
			unordered_map<string, Building*> mapBusiness = vBusiness[j];
			for (size_t k = 0; k < vIndustrial.size(); k++)
			{
				if (!m_bRun || nCurIndex >= nStartIndex + nCount)
				{//超过计算区间，退出
					goto finish;
				}
				if (nCurIndex++ < nStartIndex)
				{//未开始位置
					continue;
				}

				unordered_map<string, Building*> mapIndustrial = vIndustrial[k];

				unordered_map<string, map<string, double> > mapAdditionBuff;
				unordered_map<string, Building*> mapAllBuilding;
				mapAllBuilding.insert(mapResidence.begin(), mapResidence.end());
				mapAllBuilding.insert(mapBusiness.begin(), mapBusiness.end());
				mapAllBuilding.insert(mapIndustrial.begin(), mapIndustrial.end());
				PrepareBuff(mapResidence, mapBusiness, mapIndustrial, mapAllBuilding, mapAdditionBuff);
				pair<double, unordered_map<string, double> > totalProfit = CalcProfit(sCategory, mapAllBuilding, mapAdditionBuff);
				if (dMaxProfit < totalProfit.first)
				{
					dMaxProfit = totalProfit.first;
					maxProfitBuilding = totalProfit.second;
				}

				++m_nCurCount;
			}
		}
	}

finish:
	m_mutex.lock();
	m_mapTotalProfit.insert(make_pair(dMaxProfit, maxProfitBuilding));
	m_mutex.unlock();
}

void Calc::CreateScenes(const int &nThreadCount, const string& sCategory, const vector<unordered_map<string, Building*> > &vResidence, const vector<unordered_map<string, Building*> > &vBusiness, const vector<unordered_map<string, Building*> > &vIndustrial)
{
	m_nCurCount = 0;
	m_mapTotalProfit.clear();

	m_nTotalCount = vResidence.size() * vBusiness.size() * vIndustrial.size();
	int nCountPerThread = (m_nTotalCount + nThreadCount - 1) / nThreadCount;

	vector<thread*> vThread;
	for (int i = 0; i < nThreadCount; i++)
	{
		vThread.push_back(new thread(&Calc::CalcThread, this, i, nCountPerThread, sCategory, vResidence, vBusiness, vIndustrial));
	}

	for (size_t i = 0; i < vThread.size(); i++)
	{
		vThread[i]->join();
		delete vThread[i];
	}

	m_nCurCount = m_nTotalCount; //避免出现进度条不到100%的情况

	//运行结果后，通知完成
	if (m_bRun && m_pDlg)
	{
		m_pDlg->HandleCalcData(m_mapTotalProfit, GetTickCount() - m_startTime);
	}
}

void Calc::Start(const int &nThreadCount, CJiaGuoMengDlg* pDlg)
{
	Stop();

	m_pDlg = pDlg;
	m_bRun = true;

    Config::GetInstance()->LoadData();

	m_startTime = GetTickCount();
    unordered_map<string, vector<vector<string> > > mapCategoryComb;
    unordered_map<string, Building*> mapResidence =  Config::GetInstance()->GetCategoryBuilding(CategoryResidence);
    unordered_map<string, Building*> mapBusiness =  Config::GetInstance()->GetCategoryBuilding(CategoryBusiness);
    unordered_map<string, Building*> mapIndustrial =  Config::GetInstance()->GetCategoryBuilding(CategoryIndustrial);
    vector<unordered_map<string, Building*> > vResidence = GetComb(mapResidence);
    vector<unordered_map<string, Building*> > vBusiness = GetComb(mapBusiness);
    vector<unordered_map<string, Building*> > vIndustrial = GetComb(mapIndustrial);
    cout << "vResidence:" << vResidence.size() << ", vBusiness:" << vBusiness.size() << ", vIndustrial:" << vIndustrial.size() << endl;

	m_pThread = new thread(&Calc::CreateScenes, this, nThreadCount, CategoryOnline, vResidence, vBusiness, vIndustrial);
}

void Calc::Stop()
{
	m_bRun = false;
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = NULL;
	}
	m_nCurCount = 0;
}

int Calc::GetCalcPercent()
{
	return m_nTotalCount > 0 ? (m_nCurCount * 100 / m_nTotalCount) : 0;
}
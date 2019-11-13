#ifdef WIN32
#include "stdafx.h"
#endif

#include "Building.h"
#include "Config.h"

Building::Building(const string &sName)
    : m_sName(sName)
{
	Reset();
}

void Building::Reset()
{
	m_dLevelProfit = 0;
	m_starProfit = 0;
	m_dOnlineProfit = 0;
	m_dOfflineProfit = 0;

	m_dPolicyBuffAll = 0;
	m_dPolicyBuffOnline = 0;
	m_dPolicyBuffOffline = 0;

	m_dPhotoBuffAll = 0;
	m_dPhotoBuffOnline = 0;
	m_dPhotoBuffOffline = 0;

	m_dMissionBuffAll = 0;
	m_dMissionBuffOnline = 0;
	m_dMissionBuffOffline = 0;

	ResetAdditionBuff();
}

void Building::AddStarProfit(string sStar, double dProfit)
{
    m_mapStarProfit[sStar] = dProfit;
}

void Building::AddStarBuff(string sStar, const vector<pair<string, double> > &vBuff)
{
    m_mapStarBuff[sStar] = vBuff;
}

void Building::SetLevel(int level)
{
    m_dLevelProfit = Config::GetInstance()->GetLevelProfit(level);
}

void Building::SetStar(string sStar)
{
    m_sStar = sStar;
    m_starProfit = m_mapStarProfit[sStar];
}

void Building::InitProfit()
{
    m_dOnlineProfit = m_dLevelProfit * m_starProfit * (1 + m_dPolicyBuffAll + m_dPolicyBuffOnline)
        * (1 + m_dPhotoBuffAll + m_dPhotoBuffOnline) * (1 + m_dMissionBuffAll + m_dMissionBuffOnline);
    m_dOfflineProfit = m_dLevelProfit * m_starProfit * (1 + m_dPolicyBuffAll + m_dPolicyBuffOffline)
        * (1 + m_dPhotoBuffAll + m_dPhotoBuffOffline) * (1 + m_dMissionBuffAll + m_dMissionBuffOffline);
}

void Building::AddPolicyBuff(const string &sCategory, double dBuff)
{
    if (sCategory == CategoryAll)
    {
        m_dPolicyBuffAll += dBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_dPolicyBuffOnline += dBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_dPolicyBuffOffline += dBuff;
    }
}

void Building::AddPhotoBuff(const string &sCategory, double dBuff)
{
    if (sCategory == CategoryAll)
    {
        m_dPhotoBuffAll += dBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_dPhotoBuffOnline += dBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_dPhotoBuffOffline += dBuff;
    }
}

void Building::AddMissionBuff(const string &sCategory, double dBuff)
{
    if (sCategory == CategoryAll)
    {
        m_dMissionBuffAll += dBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_dMissionBuffOnline += dBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_dMissionBuffOffline += dBuff;
    }
}

void Building::AddAdditionBuff(const string &sCategory, double dBuff)
{
    if (sCategory == CategoryAll)
    {
        m_dAdditionBuffAll += dBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_dAdditionBuffOnline += dBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_dAdditionBuffOffline += dBuff;
    }
}

void Building::ResetAdditionBuff()
{
    m_dAdditionBuffAll = 0;
    m_dAdditionBuffOnline = 0;
    m_dAdditionBuffOffline = 0;
}

vector<pair<string, double> > Building::GetStarBuff()
{
    return m_mapStarBuff[m_sStar];
}

double Building::GetBaseProfit()
{
    return m_dLevelProfit * m_starProfit;
}

double Building::GetTotalProfit(const string &sCategory)
{
    if (sCategory == CategoryOnline)
    {
        return (1 + m_dAdditionBuffAll + m_dAdditionBuffOnline) * m_dOnlineProfit;
    }
    else if (sCategory == CategoryOffline)
    {
        return (1 + m_dAdditionBuffAll + m_dAdditionBuffOffline) * m_dOfflineProfit;
    }
    return 0;
}

string Building::GetName()
{
    return m_sName;
}
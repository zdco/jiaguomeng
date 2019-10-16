#include "Building.h"
#include "Config.h"

Building::Building(const string &sName)
    : m_sName(sName)
{
    m_dOnlineProfit = 0;
    m_dOfflineProfit = 0;

    m_nPolicyBuffAll = 0;
    m_nPolicyBuffOnline = 0;
    m_nPolicyBuffOffline = 0;

    m_nPhotoBuffAll = 0;
    m_nPhotoBuffOnline = 0;
    m_nPhotoBuffOffline = 0;

    m_nMissionBuffAll = 0;
    m_nMissionBuffOnline = 0;
    m_nMissionBuffOffline = 0;

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
    m_dOnlineProfit = m_dLevelProfit * m_starProfit * (1 + (m_nPolicyBuffAll + m_nPolicyBuffOnline) / 100.0)
        * (1 + (m_nPhotoBuffAll + m_nPhotoBuffOnline) / 100.0) * (1 + (m_nMissionBuffAll + m_nMissionBuffOnline) / 100.0);
    m_dOfflineProfit = m_dLevelProfit * m_starProfit * (1 + (m_nPolicyBuffAll + m_nPolicyBuffOffline) / 100.0)
        * (1 + (m_nPhotoBuffAll + m_nPhotoBuffOffline) / 100.0) * (1 + (m_nMissionBuffAll + m_nMissionBuffOffline) / 100.0);
}

void Building::AddPolicyBuff(const string &sCategory, int nBuff)
{
    if (sCategory == CategoryAll)
    {
        m_nPolicyBuffAll += nBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_nPolicyBuffOnline += nBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_nPolicyBuffOffline += nBuff;
    }
}

void Building::AddPhotoBuff(const string &sCategory, int nBuff)
{
    if (sCategory == CategoryAll)
    {
        m_nPhotoBuffAll += nBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_nPhotoBuffOnline += nBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_nPhotoBuffOffline += nBuff;
    }
}

void Building::AddMissionBuff(const string &sCategory, int nBuff)
{
    if (sCategory == CategoryAll)
    {
        m_nMissionBuffAll += nBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_nMissionBuffOnline += nBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_nMissionBuffOffline += nBuff;
    }
}

void Building::AddAdditionBuff(const string &sCategory, int nBuff)
{
    if (sCategory == CategoryAll)
    {
        m_nAdditionBuffAll += nBuff;
    }
    else if (sCategory == CategoryOnline)
    {
        m_nAdditionBuffOnline += nBuff;
    }
    else if (sCategory == CategoryOffline)
    {
        m_nAdditionBuffOffline += nBuff;
    }
}

void Building::ResetAdditionBuff()
{
    m_nAdditionBuffAll = 0;
    m_nAdditionBuffOnline = 0;
    m_nAdditionBuffOffline = 0;
}

vector<pair<string, double> > Building::GetStarBuff()
{
    return m_mapStarBuff[m_sStar];
}

double Building::GetTotalProfit(const string &sCategory)
{
    if (sCategory == CategoryOnline)
    {
        return (1 + m_nAdditionBuffAll + m_nAdditionBuffOnline) * m_dOnlineProfit;
    }
    else if (sCategory == CategoryOffline)
    {
        return (1 + m_nAdditionBuffAll + m_nAdditionBuffOffline) * m_dOfflineProfit;
    }
    return 0;
}

string Building::GetName()
{
    return m_sName;
}
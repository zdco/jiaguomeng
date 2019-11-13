#include "Calc.h"

int main()
{
    Config::GetInstance()->Init();
    
    Calc pCalc;
    pCalc.Start();
    
    return 0;
}
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "Config.h"
#include "vector"

using namespace std;

int main()
{
    if (!Config::instance()->init())
    {
        cout << "main() : Config 객체의 init() 메서드 실행 실패" << endl;
        return -1;
    }

    vector<string> testKeys{"TEMS_IP_ADDREESS", "TEMS_MASSAGE_QUEUE_KEY", "TRACE", "LOG_LEVEL"};

    cout << "[ Config 객체에 저장되어 있는 설정 출력 ]" << endl;
    for (const string &s : testKeys)
    {
        string val = Config::instance()->GetValueFromMap(s);
        cout << s << " = " << val << endl;
    }

    return 0;
}
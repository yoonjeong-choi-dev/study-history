// Config 클래스 정의

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "Config.h"

// 싱글톤 객체 초기화
Config *Config::_instance = nullptr;

Config *Config::instance()
{
    // 객체가 null인 경우에만 새로운 객체 생성
    if (_instance == nullptr)
    {
        _instance = new Config();
    }
    return _instance;
}

bool Config::init()
{
    std::cout << "<< Config::init() method >>" << std::endl;

    // 설정 파일을 저장한 시스템 변수 체크 및 설정 파일 이름 설정
    char const *confFile = getenv(CONFIG_FILE_ENV_VAR);
    if (!confFile)
    {
        std::cout << "시스템 변수 조회 실패, 디폴트 파일 사용" << std::endl;
        confFile = DEFAULT_CONFIG.c_str();
    }

    // 설정 파일 열기
    std::ifstream *configFilePtr = new std::ifstream(confFile, std::ios_base::in);
    if (!configFilePtr || configFilePtr->fail())
    {
        std::cout << "설정 파일을 여는데 실패했습니다." << std::endl;
        return false;
    }

    // 설정 파일을 읽어 map에 저장
    bool parseResult = readConfig(configFilePtr);
    if (!parseResult)
    {
        return false;
    }

    // 파일 스트림 리소스 해제
    configFilePtr->close();
    delete configFilePtr;

    return true;
}

bool Config::readConfig(std::ifstream *ifstr)
{
    std::cout << "<< Config::readConfig() method >>" << std::endl;

    // 설정 파일을 한 줄씩 읽어 파싱
    while (!ifstr->eof())
    {
        char buf[256];
        ifstr->getline(buf, 256);

        // 버퍼가 공백인 경우, 다음 줄로 이동
        if (strcmp(buf, "") == 0)
            continue;

        // 버퍼 내용을 문자열에 저장
        std::string curLine(buf);

        // #으로 시작하면 주석이므로 pass
        if (curLine[0] == '#')
        {
            continue;
        }
        else
        {
            // = 을 기준으로 key, value 나눈다
            int sepIndex = curLine.find("=");
            if (sepIndex == std::string::npos)
            {
                std::cout << "Line = " << curLine.c_str() << std::endl;
                std::cout << "설정 파일은 (key)=(value) 형태여야 합니다" << std::endl;
                continue;
            }

            std::string key = curLine.substr(0, sepIndex);
            std::string value = curLine.substr(sepIndex + 1, curLine.size() - 1);

            _config_map[key] = value;
        }    
    }
    return true;
}

std::string Config::GetValueFromMap(std::string key)
{
    return _config_map[key];
}
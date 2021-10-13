#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <map>

// 시스템 변수 이름 설정
#define CONFIG_FILE_ENV_VAR "MY_CONFIG_FILE"

// 디폴트 설정 파일 이름
static std::string DEFAULT_CONFIG = "./ConfigFile";

// 정의된 설정 파일 포맷을 관리하는 클래스(싱글턴 패턴 적용)
typedef std::map<std::string, std::string> config_pair;

class Config
{
public:
    // 싱글턴 패턴을 위한 메서드
    static Config *instance();
    bool init();
    std::string GetValueFromMap(std::string key);

private:
    // 싱글턴 패턴을 위해 생성자를 감춘다
    Config() {}
    static Config *_instance;

    // 파일 스트림을 통해 파일을 읽고 map에 해당 정보 저장
    config_pair _config_map;
    bool readConfig(std::ifstream *ifstr);
};

#endif
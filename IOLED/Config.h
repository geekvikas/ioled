#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>
#include <FS.H>
#include "Logger.h"
//#include "Network.h"

class Config {
    

private:
    static Config *s_instance;
    const char* CONFIG_FILE_NAME = "/device2.json";
    const char* __AP_PWD = "admin@12345";
    const char* __SERVER_TIME_URL = "http://172.20.10.4:3000/api/getTime";
    bool __IsValid();
    bool __SaveDefaultConfig();
    
    
public:
   const char* DEFAULT_AP_NAME = "$DEVICE_DISCOVERY$";
    
   static Config *Instance()
    {
        if (!s_instance)
          s_instance = new Config;
        return s_instance;
    }
  const char* Get(const char*);
	bool Update();
};

#endif

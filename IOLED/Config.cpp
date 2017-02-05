#include "Config.h"

bool Config::__IsValid()
{
  Logger::Instance()->Debugln("Entering Config::__IsValid");
   
  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file");
    return false;
  }
    
  Logger::Instance()->Debugln("Exiting Config::__IsValid");
  
  return true;
  
}

bool Config::__SaveDefaultConfig(){
  Logger::Instance()->Debugln("Entering Config::__SaveDefaultConfig");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["apName"] = DEFAULT_AP_NAME;
  json["apPwd"] = __AP_PWD;
  json["serverTimeUrl"] = __SERVER_TIME_URL;

  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "w");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  Logger::Instance()->Debugln("Exiting Config::__SaveDefaultConfig");
  return true;
}

const char* Config::Get(const char* configName)
{
  
  Logger::Instance()->Debugln("Entering Config::Get");
  
  if(!__IsValid()){
    Logger::Instance()->Debugln("Config::Init - Missing Config. Saving Default Config");
    __SaveDefaultConfig();
  }

   File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file");
    return false;
  }
    
  size_t size = configFile.size();
  if (size > 1024) {
    Logger::Instance()->Debugln("Config file size is too large");
    return '\0';
  }
  
  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  
  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& jsonObject = jsonBuffer.parseObject(buf.get());

  if (!jsonObject.success()) {
    Logger::Instance()->Debugln("Failed to parse config file");
    return '\0';
  }

  return jsonObject[configName];
    
}

bool Config::Update()
{
    Logger::Instance()->Debugln("Entering Config::Update");
    
    Logger::Instance()->Debugln("Exiting Config::Update");
    return false;
}




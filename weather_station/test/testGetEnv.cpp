#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
void    getEnvValue()
{
  std::string   line;
  std::string   ssid;
  std::string   password;

  std::ifstream env;
  env.open("../.env");
  if (env.is_open()) {
    while (std::getline(env, line)) {
        size_t  pos = line.find("=");
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        if (key == "WIFI_SSID")
            ssid = value;
        else if (key == "WIFI_PASSWORD")
            password = value;
    }
    env.close();
  }
  std::cout << "SSID: " << ssid << std::endl;
  std::cout << "Password: " << password << std::endl;
}


int main(void) {
    getEnvValue();
    return 0;
}
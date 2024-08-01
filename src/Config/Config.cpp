#include "Config/Config.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

const int JSON_INDENT_SIZE = 4;

namespace BlenderRenderer {
Config::Config() {}

Config::Config(const std::string &configPath) : m_configPath(configPath) {}

Config::~Config() {}

void Config::ChangePath(const std::string &configPath) {
  m_configPath = configPath;
  _WriteTemplate();
}

void Config::SetTemplate(const std::vector<std::string> &options) {
  m_template = options;

  _WriteTemplate();
}

void Config::_WriteTemplate() {
  nlohmann::json configOptions;

  // File Exists Validation
  if (!_FileExists(m_configPath)) {
    for (const auto option : m_template) {
      configOptions[option] = "";
    }

    _WriteJson(m_configPath, configOptions);

  } else {

    _ReadJson(m_configPath, configOptions);

    for (const auto option : m_template) {
      if (configOptions[option] == nullptr) {
        configOptions[option] = "";
      }
    }

    _WriteJson(m_configPath, configOptions);
  }
}

void Config::Set(const std::string &key, const std::string &value) {
  nlohmann::json configOptions;

  _ReadJson(m_configPath, configOptions);
  configOptions[key] = value;
  _WriteJson(m_configPath, configOptions);
}

std::string Config::Get(const std::string &key) {
  nlohmann::json configOptions;

  _ReadJson(m_configPath, configOptions);
  return configOptions[key];
}

/// Read JSON from file into JSON object
void Config::_ReadJson(const std::string &path, nlohmann::json &json) {
  std::fstream file;
  file.open(path, std::fstream::in);

  json = nlohmann::json::parse(file);

  file.close();
}

/// Write JSON to file from JSON object
void Config::_WriteJson(const std::string &path, const nlohmann::json &json) {
  std::fstream file;
  std::string buffer;

  file.open(path, std::fstream::out);
  buffer = json.dump(JSON_INDENT_SIZE);
  file.write(buffer.c_str(), buffer.length());
  file.close();
}

/// Returns true if file exists else false
bool Config::_FileExists(const std::string &path) {
  std::ifstream file(path, std::fstream::in | std::fstream::binary);
  if (file.is_open()) {
    file.close();
    return true;
  } else {
    file.close();
    return false;
  }
}

} // namespace BlenderRenderer

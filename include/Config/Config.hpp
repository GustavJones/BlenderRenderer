#pragma once
#include "nlohmann/json.hpp"
#include <string>
#include <vector>

namespace BlenderRenderer {
class Config {
public:
  Config();
  Config(const std::string &configPath);
  Config(Config &&) = delete;
  Config(const Config &) = delete;
  Config &operator=(Config &&) = delete;
  Config &operator=(const Config &) = delete;
  ~Config();

  void ChangePath(const std::string &configPath);
  void SetTemplate(const std::vector<std::string> &options);
  void Set(const std::string &key, const std::string &value);
  std::string Get(const std::string &key);

private:
  std::string m_configPath;
  std::vector<std::string> m_template;

  void _WriteTemplate();
  static void _ReadJson(const std::string &path, nlohmann::json &json);
  static void _WriteJson(const std::string &path, const nlohmann::json &json);
  static bool _FileExists(const std::string &path);
};

} // namespace BlenderRenderer

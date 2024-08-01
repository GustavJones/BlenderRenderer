#include "Config/Config.hpp"
#include "GArgs.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void _ParseCommands(GArgs::Parser &parser, BlenderRenderer::Config &config,
                    const std::vector<std::string> &template_options);

int main(int argc, char *argv[]) {
  std::string argument;

  std::vector<std::string> template_options = {"runCommand",  "renderEngine",
                                               "startFrame",  "endFrame",
                                               "threadCount", "cyclesDevice"};

  BlenderRenderer::Config config("config.json");
  config.SetTemplate(template_options);
  GArgs::Parser parser("Blender Renderer", "V1.0", true);

  parser.AddStructure(
      "[flag:help=Flags,value_amount=0,argument_filter=--;"
      "command:value_amount=1,help=Command/"
      "Function;argument:value_amount=0,argument_filter=,help=Argument "
      "after command]");
  parser.AddKey(GArgs::Key("flag", "--help", "Displays this message"));
  parser.AddKey(GArgs::Key("command", "change_command",
                           "Changes the run command of Blender"));
  parser.AddKey(
      GArgs::Key("command", "set_engine", "Set the render engine of Blender"));
  parser.AddKey(GArgs::Key("command", "set_start_frame",
                           "Sets the start frame of the render"));
  parser.AddKey(GArgs::Key("command", "set_end_frame",
                           "Sets the end frame of the render"));
  parser.AddKey(GArgs::Key("command", "set_thread_count",
                           "Sets the amount of threads for render"));
  parser.AddKey(GArgs::Key("command", "set_device",
                           "Sets the amount of threads for render"));
  parser.AddKey(GArgs::Key("command", "run", "Run a Blender Render"));
  parser.ParseArgs(argc, argv);

  try {
    if (parser.Contains("flag", "--help")) {
      parser.DisplayHelp();
    }

    // Check if an argument is given when running commands
    if (parser["command"] != "") {
      argument = parser["argument"];
      if (argument == "") {
        throw GArgs::ArgumentsException("No Arguments Given");
      }

      // Parse Commands
      _ParseCommands(parser, config, template_options);
    }

  } catch (const GArgs::ArgumentsException &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}

/// Parse all commands and arguments given
void _ParseCommands(GArgs::Parser &parser, BlenderRenderer::Config &config,
                    const std::vector<std::string> &template_options) {
  if (parser["command"] == "change_command") {
    std::string argument = parser["argument"];
    int i = 0;

    while (true) {
      i = argument.find('\t');
      if (i > 0) {
        argument.replace(i, 1, " ");
      } else
        break;
    }

    config.Set(template_options[0], argument);
  } else if (parser["command"] == "set_engine") {
    config.Set(template_options[1], parser["argument"]);
  } else if (parser["command"] == "set_start_frame") {
    config.Set(template_options[2], parser["argument"]);
  } else if (parser["command"] == "set_end_frame") {
    config.Set(template_options[3], parser["argument"]);
  } else if (parser["command"] == "set_thread_count") {
    config.Set(template_options[4], parser["argument"]);
  } else if (parser["command"] == "set_device") {
    config.Set(template_options[5], parser["argument"]);
  } else if (parser["command"] == "run") {
    if (config.Get(template_options[0]) == "") {
      throw std::runtime_error("Run command not set");
    } else if (config.Get(template_options[1]) == "") {
      throw std::runtime_error("Render engine not set");
    } else if (config.Get(template_options[2]) == "") {
      throw std::runtime_error("Start Frame not set");
    } else if (config.Get(template_options[3]) == "") {
      throw std::runtime_error("End Frame not set");
    }

    std::string command = config.Get(template_options[0]);
    std::string engine = config.Get(template_options[1]);
    std::string start_frame = config.Get(template_options[2]);
    std::string end_frame = config.Get(template_options[3]);
    std::string threads = config.Get(template_options[4]);
    std::string device = config.Get(template_options[5]);

    if (threads == "") {
      threads = "1";
    }
    if (device == "") {
      device = "CPU";
    }

    std::string command_out =
        (command + " -b " + parser["argument"] + " -o ~/Desktop/output" +
         " -E " + engine + " -s " + start_frame + " -e " + end_frame + " -t " +
         threads + " -a " + " -- " + " --cycles-device " + device);

    std::cout << "Running : " << command_out << std::endl;

    system(command_out.c_str());
  }
}

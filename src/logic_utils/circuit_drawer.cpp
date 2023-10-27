#include "circuit_drawer.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "token.h"

using namespace std;

string join(vector<string> items, string delimiter) {
  ostringstream result;
  for (size_t i = 0; i < items.size(); ++i) {
    result << items[i];
    if (i < items.size() - 1) {
      result << delimiter;
    }
  }
  return result.str();
}

// ToDo: take the minimized expression

string SoPToWaveJSON(vector<Token> tokens) {
  ostringstream json_output;

  json_output << "{\n";
  json_output << "  \"assign\": [\n";
  json_output << "    [\"out\",\n";

  vector<string> all_items;
  vector<string> and_group;

  for (size_t i = 0; i < tokens.size(); ++i) {
    Token token = tokens[i];

    if (token.type == TokenType::OR) {
      if (!and_group.empty()) {
        if (and_group.size() > 1) {
          all_items.push_back("        [\"&\",\n" + string("          ") +
                              join(and_group, ",\n          ") + "\n        ]");
        } else {
          all_items.push_back("        " + and_group[0]);
        }
        and_group.clear();
      }
    } else if (token.type == TokenType::VAR) {
      if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::NOT_POST) {
        and_group.push_back("[\"~\", \"" + string(1, token.value) + "\"]");
        i++;
      } else {
        and_group.push_back("\"" + string(1, token.value) + "\"");
      }
    }
  }

  // Handle any remaining tokens in the and_group
  if (!and_group.empty()) {
    if (and_group.size() > 1) {
      all_items.push_back("        [\"&\",\n" + string("          ") +
                          join(and_group, ",\n          ") + "\n        ]");
    } else {
      all_items.push_back("        " + and_group[0]);
    }
  }

  if (all_items.size() > 1) {
    json_output << "      [\"|\",\n";
    json_output << join(all_items, ",\n");
    json_output << "\n      ]\n";
  } else {
    json_output << all_items[0] << "\n";
  }

  json_output << "    ]\n";
  json_output << "  ]\n";
  json_output << "}\n";

  return json_output.str();
}


// ToDo: take the minimized expression


string SoPToVerilog(vector<Token> tokens) {
  ostringstream verilog_output;

  vector<string> all_items;
  vector<string> and_group;

  verilog_output << "module circuit(\n";

  vector<char> vars;
  for (size_t i = 0; i < tokens.size(); ++i) {
    Token token = tokens[i];
    if (token.type == TokenType::VAR) {
      if (find(vars.begin(), vars.end(), token.value) == vars.end()) {
        vars.push_back(token.value);
      }
    }
  }

  for (size_t i = 0; i < vars.size(); ++i) {
    verilog_output << "  input " << vars[i] << ",\n";
  }

  verilog_output << "  output out\n";
  verilog_output << ");\n";

  for (size_t i = 0; i < tokens.size(); ++i) {
    Token token = tokens[i];

    if (token.type == TokenType::OR) {
      if (!and_group.empty()) {
        if (and_group.size() > 1) {
          all_items.push_back("(" + join(and_group, " & ") + ")");
        } else {
          all_items.push_back(and_group[0]);
        }
        and_group.clear();
      }
    } else if (token.type == TokenType::VAR) {
      if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::NOT_POST) {
        and_group.push_back("~" + string(1, token.value));
        i++;
      } else {
        and_group.push_back(string(1, token.value));
      }
    }
  }

  // Handle any remaining tokens in the and_group
  if (!and_group.empty()) {
    if (and_group.size() > 1) {
      all_items.push_back("(" + join(and_group, " & ") + ")");
    } else {
      all_items.push_back(and_group[0]);
    }
  }

  verilog_output << "  assign out = ";
  if (all_items.size() > 1) {
    verilog_output << join(all_items, " | ");
  } else {
    verilog_output << all_items[0];
  }
  verilog_output << ";";

  verilog_output << "\nendmodule\n";

  return verilog_output.str();
}

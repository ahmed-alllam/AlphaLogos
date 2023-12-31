#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/logic_utils/circuit_drawer.h"
#include "../src/logic_utils/token.h"

using namespace std;

TEST_CASE("Test circuit drawer for ab+c") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'},
      {TokenType::VAR, 'b'},
      {TokenType::OR},
      {TokenType::VAR, 'c'},
  };

  string expected =
      "{\n"
      "  \"assign\": [\n"
      "    [\"out\",\n"
      "      [\"|\",\n"
      "        [\"&\",\n"
      "          \"a\",\n"
      "          \"b\"\n"
      "        ],\n"
      "        \"c\"\n"
      "      ]\n"
      "    ]\n"
      "  ]\n"
      "}\n";

  REQUIRE(SoPToWaveJSON(tokens) == expected);
}

TEST_CASE("Test circuit drawer for a+b+c") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'}, {TokenType::OR},       {TokenType::VAR, 'b'},
      {TokenType::OR},       {TokenType::VAR, 'c'},
  };

  string expected =
      "{\n"
      "  \"assign\": [\n"
      "    [\"out\",\n"
      "      [\"|\",\n"
      "        \"a\",\n"
      "        \"b\",\n"
      "        \"c\"\n"
      "      ]\n"
      "    ]\n"
      "  ]\n"
      "}\n";

  REQUIRE(SoPToWaveJSON(tokens) == expected);
}

TEST_CASE("Test circuit drawer for ab+c'+d") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}, {TokenType::OR},
      {TokenType::VAR, 'c'}, {TokenType::NOT_POST}, {TokenType::OR},
      {TokenType::VAR, 'd'},
  };

  string expected =
      "{\n"
      "  \"assign\": [\n"
      "    [\"out\",\n"
      "      [\"|\",\n"
      "        [\"&\",\n"
      "          \"a\",\n"
      "          \"b\"\n"
      "        ],\n"
      "        [\"~\", \"c\"],\n"
      "        \"d\"\n"
      "      ]\n"
      "    ]\n"
      "  ]\n"
      "}\n";

  REQUIRE(SoPToWaveJSON(tokens) == expected);
}

TEST_CASE("Test circuit drawer for ab'") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'},
      {TokenType::VAR, 'b'},
      {TokenType::NOT_POST},
  };

  string expected =
      "{\n"
      "  \"assign\": [\n"
      "    [\"out\",\n"
      "        [\"&\",\n"
      "          \"a\",\n"
      "          [\"~\", \"b\"]\n"
      "        ]\n"
      "    ]\n"
      "  ]\n"
      "}\n";

  REQUIRE(SoPToWaveJSON(tokens) == expected);
}

TEST_CASE("Test circuit drawer for a'b'") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'},
      {TokenType::NOT_POST},
      {TokenType::VAR, 'b'},
      {TokenType::NOT_POST},
  };

  string expected =
      "{\n"
      "  \"assign\": [\n"
      "    [\"out\",\n"
      "        [\"&\",\n"
      "          [\"~\", \"a\"],\n"
      "          [\"~\", \"b\"]\n"
      "        ]\n"
      "    ]\n"
      "  ]\n"
      "}\n";

  REQUIRE(SoPToWaveJSON(tokens) == expected);
}

TEST_CASE("Test circuit drawer for ab'cd+cd+acb'd+ac") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}, {TokenType::NOT_POST},
      {TokenType::VAR, 'c'}, {TokenType::VAR, 'd'}, {TokenType::OR},
      {TokenType::VAR, 'c'}, {TokenType::VAR, 'd'}, {TokenType::OR},
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'c'}, {TokenType::VAR, 'b'},
      {TokenType::NOT_POST}, {TokenType::VAR, 'd'}, {TokenType::OR},
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'c'}};

  string expected =
      "{\n"
      "  \"assign\": [\n"
      "    [\"out\",\n"
      "      [\"|\",\n"
      "        [\"&\",\n"
      "          \"a\",\n"
      "          [\"~\", \"b\"],\n"
      "          \"c\",\n"
      "          \"d\"\n"
      "        ],\n"
      "        [\"&\",\n"
      "          \"c\",\n"
      "          \"d\"\n"
      "        ],\n"
      "        [\"&\",\n"
      "          \"a\",\n"
      "          \"c\",\n"
      "          [\"~\", \"b\"],\n"
      "          \"d\"\n"
      "        ],\n"
      "        [\"&\",\n"
      "          \"a\",\n"
      "          \"c\"\n"
      "        ]\n"
      "      ]\n"
      "    ]\n"
      "  ]\n"
      "}\n";

  REQUIRE(SoPToWaveJSON(tokens) == expected);
}

// testing verilog output

TEST_CASE("Test verilog output for ab+c") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'},
      {TokenType::VAR, 'b'},
      {TokenType::OR},
      {TokenType::VAR, 'c'},
  };

  string expected =
      "module circuit(\n"
      "  input a,\n"
      "  input b,\n"
      "  input c,\n"
      "  output out\n"
      ");\n"
      "  assign out = (a & b) | c;\n"
      "endmodule\n";

  REQUIRE(SoPToVerilog(tokens) == expected);
}

TEST_CASE("Test verilog output for a+b+c") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'}, {TokenType::OR},       {TokenType::VAR, 'b'},
      {TokenType::OR},       {TokenType::VAR, 'c'},
  };

  string expected =
      "module circuit(\n"
      "  input a,\n"
      "  input b,\n"
      "  input c,\n"
      "  output out\n"
      ");\n"
      "  assign out = a | b | c;\n"
      "endmodule\n";

  REQUIRE(SoPToVerilog(tokens) == expected);
}

TEST_CASE("Test verilog output for ab+c'+d") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}, {TokenType::OR},
      {TokenType::VAR, 'c'}, {TokenType::NOT_POST}, {TokenType::OR},
      {TokenType::VAR, 'd'},
  };

  string expected =
      "module circuit(\n"
      "  input a,\n"
      "  input b,\n"
      "  input c,\n"
      "  input d,\n"
      "  output out\n"
      ");\n"
      "  assign out = (a & b) | ~c | d;\n"
      "endmodule\n";

  REQUIRE(SoPToVerilog(tokens) == expected);
}

TEST_CASE("Test verilog output for ab'") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'},
      {TokenType::VAR, 'b'},
      {TokenType::NOT_POST},
  };

  string expected =
      "module circuit(\n"
      "  input a,\n"
      "  input b,\n"
      "  output out\n"
      ");\n"
      "  assign out = (a & ~b);\n"
      "endmodule\n";

  REQUIRE(SoPToVerilog(tokens) == expected);
}

TEST_CASE("Test verilog output for a'b'") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'},
      {TokenType::NOT_POST},
      {TokenType::VAR, 'b'},
      {TokenType::NOT_POST},
  };

  string expected =
      "module circuit(\n"
      "  input a,\n"
      "  input b,\n"
      "  output out\n"
      ");\n"
      "  assign out = (~a & ~b);\n"
      "endmodule\n";

  REQUIRE(SoPToVerilog(tokens) == expected);
}

TEST_CASE("Test verilog output for ab'cd+cd+acb'd+ac") {
  vector<Token> tokens = {
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}, {TokenType::NOT_POST},
      {TokenType::VAR, 'c'}, {TokenType::VAR, 'd'}, {TokenType::OR},
      {TokenType::VAR, 'c'}, {TokenType::VAR, 'd'}, {TokenType::OR},
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'c'}, {TokenType::VAR, 'b'},
      {TokenType::NOT_POST}, {TokenType::VAR, 'd'}, {TokenType::OR},
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'c'}};

  string expected =
      "module circuit(\n"
      "  input a,\n"
      "  input b,\n"
      "  input c,\n"
      "  input d,\n"
      "  output out\n"
      ");\n"
      "  assign out = (a & ~b & c & d) | (c & d) | (a & c & ~b & d) | (a & "
      "c);\n"
      "endmodule\n";

  REQUIRE(SoPToVerilog(tokens) == expected);
}
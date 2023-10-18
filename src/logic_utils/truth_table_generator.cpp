#include <cassert>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void printTokens(deque<string> tokens) {
  // evaluate the first part, then recurse
  while (!tokens.empty()) {
    string temp = tokens.front();
    tokens.pop_front();
    cout << temp << endl;
  }
}

bool str2Bool(string toConvert) {
  if (toConvert == "true") {
    return true;
  } else if (toConvert == "false") {
    return false;
  } else {
    cout << "FAILED! Improper value passed to str2Bool. Asserting false..."
         << '\n';
    cout << "the value was " << toConvert << endl;
    assert(false);
    return false;
  }
}

string bool2Str(bool toConvert) {
  if (toConvert == true) {
    return "true";
  } else if (toConvert == false) {
    return "false";
  } else {
    cout << "FAILED! Improper value passed to bool2Str. Asserting true...";
    assert(false);
  }
  return "false";
}

string subString(string str, int index0, int index1) {
  string toReturn = "";
  if (index0 == index1)
    return toReturn;
  for (int i = index0; i <= index1 && i < str.length(); ++i) {
    toReturn += str[i];
  }
  // cout << "got str: " << str << endl;
  // cout << "I want to take from " << index0 << " to " << index1 << endl;
  // cout << "subString is returning " << toReturn << endl;
  return toReturn;
}

string evaluate(string var0, string var1, string lop,
                unordered_map<string, bool> valueMap) {
  string toPush;
  // cout << "evaluate sees: " << var0 << ' ' << var1 << ' ' << lop << endl;
  // cout << "valueMap[val0] " << valueMap[var0] << ' ' << "valueMap[val1] " <<
  // valueMap[var1] << endl;
  if (lop == "*") {
    toPush = bool2Str(valueMap[var0] and valueMap[var1]);
    // cout << "found lop as and, going to push " << toPush << endl;
  } else if (lop == "+") {
    // cout << "saw lop as or\n";
    // cout << (valueMap[var0] or valueMap[var1]) << endl;
    toPush = bool2Str(valueMap[var0] or valueMap[var1]);
  } else if (lop == "->") {
    toPush = bool2Str(!valueMap[var0] or valueMap[var1]);
  } else if (lop == "<->") {
    toPush = bool2Str(valueMap[var0] == valueMap[var1]);
  } else {
    cout << "ERROR! Invalid logical statement. Asserting true...";
    assert(false);
  }
  cout << "evaluate returned " << toPush
       << " and I'm returning this to be pushed onto deque\n";
  return toPush;
}

bool solveEquationDeque(deque<string> equationTokens,
                        unordered_map<string, bool> valueMap) {
  // solve equation without brackets
  string var0 = "", var1 = "", lop = "";
  while (!equationTokens.empty()) {
    if (var0.empty()) {
      var0 = equationTokens.front();
      // cout << "set var0 to " << var0 << endl;
      //  check for NOT
    } else if (lop.empty()) {
      lop = equationTokens.front();
      // cout << "set lop to " << lop << endl;
    } else {
      var1 = equationTokens.front();
      // cout << "set var1 to " << var1 << endl;
    }
    equationTokens.pop_front();
    if (!var0.empty() and !var1.empty() and !lop.empty()) {
      // cout << "evaluating...\n";
      equationTokens.push_front(evaluate(var0, var1, lop, valueMap));
      // printTokens(equationTokens);
      var0 = "";
      var1 = "";
      lop = "";
    }
  }
  if (var0 == "true" || var0 == "false") {
    return str2Bool(var0);
  }
  cout << "returning " << bool2Str(valueMap[var0]) << " from " << var0 << endl;
  return valueMap[var0];
}

deque<string>
tokenizeSpaces(string rawStr) { // delimiter only needs to be space
  // not very maintainable bc of this; can't add more delimiters in a very
  // efficient fashion
  deque<string> tokens;
  string token = "";
  for (char c : rawStr) {
    if (c != ' ') {
      token += c;
    } else {
      if (token != ""){
        tokens.push_back(token);
      }
      token = "";
    }
  }

  if (token != "") {
    tokens.push_back(token);
  }
  return tokens;
}

int getEndBracketPosition(string eqn, int firstBracketPosition) {
  int lastBracketPosition = -1;
  int bracketCount = 0;
  for (int i = firstBracketPosition; i < eqn.length(); ++i) {
    char c = eqn[i];
    if (c == '(')
      bracketCount++;
    if (c == ')') {
      bracketCount--;
      if (bracketCount == 0) {
        lastBracketPosition = i;
        break;
      }
    }
  }
  if (lastBracketPosition == -1) {
    cout << "cullBrackets couldn't find another bracket!\n"
         << "this was the equation: " << eqn << endl;
    assert(false);
  }
  // cout << endl << eqn << endl;
  // cout << "to\n";
  // cout << eqn.substr(firstBracketPosition+1, lastBracketPosition-1) << endl
  // << endl;
  return lastBracketPosition;
}

bool solveEquation(string eqn, unordered_map<string, bool> valueMap) {
  cout << "the equation I'm operating on is " << eqn << endl;
  if (eqn == "true")
    return true;
  if (eqn == "false")
    return false;
  bool toReverse = false;
  int firstBracketPosition = -1, lastBracketPosition = -1;
  for (int i = 0; i < eqn.length(); ++i) {
    char c = eqn[i];
    // cout << "c is " << c << endl;
    if (c == '~' && eqn[i + 1] == '(') {
      toReverse = true;
      // cout << "found tilde; changing eqn:\n";
      eqn = eqn.substr(0, eqn.find('~')) +
            eqn.substr(eqn.find('~') + 1, eqn.length() - 1);
      // cout << "changed eqn is " << eqn << endl;
      i = -1; // start going through from the beginning of the string again
    }
    if (c == '(') {
      firstBracketPosition = i;
      lastBracketPosition = getEndBracketPosition(eqn, i);
      int toPassFirst = firstBracketPosition, toPassLast = lastBracketPosition;
      if (toPassFirst == 0)
        toPassFirst = 1;
      if (toPassLast == eqn.length() - 1)
        toPassLast = eqn.length() - 2;
      // cout << "eqn is " << eqn << endl;
      // cout << "eqn.length() is " << eqn.length() << endl;
      // cout << "according to firstbracket and lastbracket, this part of the
      // equation is " <<
      // subString(eqn,firstBracketPosition+1,lastBracketPosition-1) << endl;
      // cout << "firstBracket and lastBracket positions are " <<
      // firstBracketPosition << ' ' << lastBracketPosition << endl; cout <<
      // subString(eqn,0,toPassFirst-1)+" ... "+
      // subString(eqn,lastBracketPosition+1,eqn.length()) << endl;
      if (!toReverse) {
        return solveEquation(
            subString(eqn, 0, toPassFirst - 1) +
                bool2Str(solveEquation(subString(eqn, firstBracketPosition + 1,
                                                 lastBracketPosition - 1),
                                       valueMap)) +
                subString(eqn, lastBracketPosition + 1, eqn.length()),
            valueMap);
      } else {
        return solveEquation(
            subString(eqn, 0, toPassFirst - 1) +
                bool2Str(!solveEquation(subString(eqn, firstBracketPosition + 1,
                                                  lastBracketPosition - 1),
                                        valueMap)) +
                subString(eqn, lastBracketPosition + 1, eqn.length()),
            valueMap);
      }
    }
    if (c == ')') {
      cout << "Something went wrong. I found an ending bracket with no "
              "beginning. Bye!\n"
           << "this was the equation:\n " << eqn;
      assert(false);
    }
  }
  // cout << "sending this to the deque function: " << eqn << endl;
  return solveEquationDeque(tokenizeSpaces(eqn), valueMap);
}

string extractVariables(const string &expression) {
  unordered_set<string> variables;
  istringstream iss(expression);
  string token = "";
  for (int i = 0; i < expression.size(); i++) {
    // Check if the token is a variable
    if (isalpha(expression[i])) {
      token = "";
      token.append(1, expression[i]);
      variables.insert(token);
    }
  }

  // Concatenate the variables into a string separated by spaces
  string result;
  for (const auto &variable : variables) {
    result += variable + " ";
  }
  return result;
}


string addSpaceAfterVariables(const std::string& expression) {
  std::string result;
  std::string::size_type i = 0;

  while (i < expression.length()) {
    result += expression[i];



        result += ' ';  // Add a space after the variable

    ++i;
  }

  return result;
}



bool truth_table_generator(string expression) {
  unordered_map<string, bool> valueMap;
  valueMap["true"] = true;
  valueMap["false"] = false;

  string vars, equation;

  cout << "Please enter your equation below.\n";
  getline(cin, equation);
  string cleanEquation = equation;

  vars = extractVariables(equation);

  equation = addSpaceAfterVariables(equation);
  deque<string> tmp = tokenizeSpaces(vars);

  int numVariations = 1, numBits = tmp.size();
  for (int i = 0; i < numBits; ++i) {
    numVariations *= 2;
  }

  bool sols[numVariations];
  for (int i = 0; i < numVariations; ++i) {
    // get bits and assign to valueMap appropriately
    for (int j = numBits - 1; j >= 0; --j) {
      if ((i & 1 << j) >> j) {
        // cout << '1';
        valueMap[tmp[(numBits - 1) - j]] = true;
        valueMap["~" + tmp[(numBits - 1) - j]] = false;
        // cout << tmp[(numBits-1)-j] << " is set to true for this run\n";
      } else {
        // cout << '0';
        valueMap[tmp[(numBits - 1) - j]] = false;
        valueMap["~" + tmp[(numBits - 1) - j]] = true;
        // cout << tmp[(numBits-1)-j] << " is set to false for this run\n";
      }
    }
    // sols[i] = solveEquation("(a -> b) and (a or c)",valueMap);
    sols[i] = solveEquation(equation, valueMap);
    cout << endl << endl;
    // cout << "sols[i] was set to " << bool2Str(sols[i]) << endl;
  }


  return sols;
}
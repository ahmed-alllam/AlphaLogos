#include "SoP_validator.h"

#include <cctype>
#include <iostream>

using namespace std;

bool isValidSoP(const std::string &expr) {
  int unmatchedParenCount = 0;
  bool lastWasAlpha = false;
  bool lastWasClosedParen = false;
  bool lastWasOperator = false;
  bool lastCharWasApostrophe = false;
  bool endedWithOperator = false;
  bool isParenthesisOpen = false;
  bool hadSummationInsideParen = false;

  for (size_t i = 0; i < expr.size(); i++) {
    char c = expr[i];

    if (c == ' ') continue;  // Ignore spaces

    if (c == '(') {
      isParenthesisOpen = true;
      hadSummationInsideParen = false;
      unmatchedParenCount++;
      endedWithOperator = false;
      lastWasClosedParen = false;
      continue;
    }

    if (c == ')') {
      if (lastWasOperator || !isParenthesisOpen) return false;
      if (hadSummationInsideParen) {
        size_t nextCharIndex = i + 1;
        while (nextCharIndex < expr.size() && expr[nextCharIndex] == ' ')
          nextCharIndex++;  // Skip spaces
        if (nextCharIndex == expr.size() ||
            (expr[nextCharIndex] != '+' && expr[nextCharIndex] != '\''))
          return false;
      }
      isParenthesisOpen = false;
      lastWasClosedParen = true;
      unmatchedParenCount--;
      continue;
    }

    if (c == '+') {
      if (!lastWasAlpha && !lastCharWasApostrophe) return false;
      if (isParenthesisOpen) hadSummationInsideParen = true;
      lastWasOperator = true;
      lastWasAlpha = false;
      lastCharWasApostrophe = false;
      endedWithOperator = true;
      lastWasClosedParen = false;
      continue;
    }

    if (c == '*') {
      if ((!lastWasAlpha && !lastCharWasApostrophe) || lastWasOperator)
        return false;
      lastWasOperator = true;
      lastWasAlpha = false;
      lastCharWasApostrophe = false;
      endedWithOperator = true;
      lastWasClosedParen = false;
      continue;
    }

    if (isalpha(c)) {
      lastWasAlpha = true;
      lastWasOperator = false;
      lastCharWasApostrophe = false;
      endedWithOperator = false;
      lastWasClosedParen = false;
      continue;
    }

    if (c == '\'') {
      if (!lastWasAlpha && !lastCharWasApostrophe && !lastWasClosedParen)
        return false;
      lastWasAlpha = false;
      lastCharWasApostrophe = true;
      lastWasOperator = false;
      endedWithOperator = false;
      lastWasClosedParen = false;
      continue;
    }

    // If we get here, it's an unexpected character
    return false;
  }

  return unmatchedParenCount == 0 && !endedWithOperator;
}

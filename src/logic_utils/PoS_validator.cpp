#include "PoS_validator.h"

#include <cctype>
#include <iostream>

using namespace std;

bool isValidPoS(const string& expr) {
  bool isParenthesisOpen = false;
  int charCountInParen = 0;
  bool lastWasClosedParen = false;
  bool lastCharWasApostrophe = false;
  int unmatchedParenCount = 0;  // To track unmatched parentheses

  for (size_t i = 0; i < expr.size(); i++) {
    char c = expr[i];

    if (isParenthesisOpen) {
      if (c == '(') return false;  // No nested parentheses

      if (c == ')') {
        if (charCountInParen == 0)
          return false;  // Invalid if no character before this
        isParenthesisOpen = false;
        charCountInParen = 0;
        lastCharWasApostrophe = false;
        lastWasClosedParen = true;
        unmatchedParenCount--;
      } else if (c == '+') {
        if (charCountInParen != 1)
          return false;  // A + should only come after a character (and optional
                         // apostrophe)
        charCountInParen = 0;
        lastCharWasApostrophe = false;
        lastWasClosedParen = false;
      } else if (isalpha(c)) {
        charCountInParen++;
        if (charCountInParen > 1) return false;  // No two characters in a row
        lastCharWasApostrophe = false;           // Resetting the flag
        lastWasClosedParen = false;
      } else if (c == '\'') {
        if (charCountInParen != 1 && !lastWasClosedParen)
          return false;  // Apostrophe should only come after a single character
        lastCharWasApostrophe = true;
        lastWasClosedParen = false;
      } else if (c == ' ') {
        // Spaces are allowed, but not immediately after an apostrophe
        if (lastCharWasApostrophe) return false;
      } else {
        return false;  // Invalid character inside parenthesis
      }
    } else {
      if (c == '(') {
        isParenthesisOpen = true;
        unmatchedParenCount++;
        lastWasClosedParen = false;
      } else if (c == ')') {
        return false;  // Closing parenthesis without an opening one
      } else if (c == '\'' &&
                 (lastWasClosedParen || lastCharWasApostrophe || isalpha(c))) {
        lastCharWasApostrophe = true;
        lastWasClosedParen = false;
        continue;  // Apostrophe outside parenthesis is allowed
      } else if (c != ' ' && c != '*' && !isalpha(c)) {
        return false;  // Invalid character outside parenthesis
      }

      lastWasClosedParen = false;
    }
  }

  return unmatchedParenCount == 0 &&
         !isParenthesisOpen;  // Return false if there's unmatched parentheses
}

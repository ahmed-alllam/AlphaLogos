#include "SoP_validator.h"


#include <iostream>
#include <cctype>

using namespace std;

bool isSoPExpression(const std::string& expr) {
    bool isOpen = false;
    bool lastWasAlpha = false;
    bool lastWasOperator = false; // To track consecutive operators
    int parenCount = 0;  // To track unmatched parentheses
    bool lastWasApostrophe = false;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == ' ') continue;  // Ignore spaces

        if (isOpen) {
            if (c == '(') return false;  // No nested parentheses

            if (c == ')') {
                isOpen = false;
                parenCount--;
            } else if (c == '*') {
                if (!lastWasAlpha) return false; // '*' should only come after a character
                lastWasOperator = true;
                lastWasAlpha = false;
            } else if (isalpha(c)) {
                if (lastWasAlpha) return false; // No two alphabets in a row
                lastWasAlpha = true;
                lastWasOperator = false;
                lastWasApostrophe = false;
            } else if (c == '\'') {
                if (!lastWasAlpha || lastWasApostrophe) return false;  // Apostrophe should only come after a character
                lastWasApostrophe = true;
            } else {
                return false;  // Invalid character inside parenthesis
            }
        } else {
            if (c == '(') {
                if (lastWasAlpha && !lastWasApostrophe) return false; // No '(' after an alphabet without apostrophe
                isOpen = true;
                parenCount++;
            } else if (c == '+') {
                if (!lastWasAlpha || lastWasOperator) return false;  // '+' should only come after a character
                lastWasOperator = true;
                lastWasAlpha = false;
            } else if (c == '*') {
                if (!lastWasAlpha) return false; // '*' should only come after a character
                lastWasOperator = true;
                lastWasAlpha = false;
            } else if (isalpha(c)) {
                if (lastWasAlpha) return false; // No two alphabets in a row
                lastWasAlpha = true;
                lastWasOperator = false;
                lastWasApostrophe = false;
            } else if (c == '\'') {
                if (!lastWasAlpha || lastWasApostrophe) return false;  // Apostrophe should only come after a character
                lastWasApostrophe = true;
            } else {
                return false;  // Invalid character
            }
        }
    }

    return parenCount == 0 && !isOpen;  // Return false if there's unmatched parentheses
}


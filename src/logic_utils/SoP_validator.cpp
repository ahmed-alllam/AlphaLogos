#include "SoP_validator.h"
#include <iostream>
#include <cctype>

using namespace std;


bool isSoPExpression(const std::string& expr) {
    int parenCount = 0;
    bool lastWasAlpha = false;
    bool lastWasOperator = false;
    bool lastWasApostrophe = false;
    bool endedWithOperator = false;
    bool withinParen = false;
    bool hadSummationInsideParen = false;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == ' ') continue;  // Ignore spaces

        if (c == '(') {
            withinParen = true;
            hadSummationInsideParen = false;
            parenCount++;
            endedWithOperator = false;
            continue;
        }

        if (c == ')') {
            if (lastWasOperator || !withinParen) return false;
            if (hadSummationInsideParen) {
                size_t nextCharIndex = i + 1;
                while (nextCharIndex < expr.size() && expr[nextCharIndex] == ' ') nextCharIndex++;  // Skip spaces
                if (nextCharIndex == expr.size() || expr[nextCharIndex] != '+') return false;
            }
            withinParen = false;
            parenCount--;
            continue;
        }

        if (c == '+') {
            if (!lastWasAlpha && !lastWasApostrophe) return false;
            if (withinParen) hadSummationInsideParen = true;
            lastWasOperator = true;
            lastWasAlpha = false;
            lastWasApostrophe = false;
            endedWithOperator = true;
            continue;
        }

        if (c == '*') {
            if ((!lastWasAlpha && !lastWasApostrophe) || lastWasOperator) return false;
            lastWasOperator = true;
            lastWasAlpha = false;
            lastWasApostrophe = false;
            endedWithOperator = true;
            continue;
        }

        if (isalpha(c)) {
            lastWasAlpha = true;
            lastWasOperator = false;
            lastWasApostrophe = false;
            endedWithOperator = false;
            continue;
        }

        if (c == '\'') {
            if (!lastWasAlpha) return false;
            lastWasAlpha = false;
            lastWasApostrophe = true;
            lastWasOperator = false;
            endedWithOperator = false;
            continue;
        }

        // If we get here, it's an unexpected character
        return false;
    }

    return parenCount == 0 && !endedWithOperator;
}

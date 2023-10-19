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
    bool withinSummation = false;
    bool withinProduct = false;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == ' ') continue;  // Ignore spaces

        if (c == '(') {
            withinParen = true;
            if (!lastWasOperator) withinProduct = true; // Start of a product term
            parenCount++;
            endedWithOperator = false;
            continue;
        }

        if (c == ')') {
            if (lastWasOperator || !withinParen) return false;
            if (withinSummation) {
                withinSummation = false;
            }
            withinParen = false;
            parenCount--;
            continue;
        }

        if (c == '+') {
            if (!lastWasAlpha && !lastWasApostrophe) return false;
            lastWasOperator = true;
            lastWasAlpha = false;
            lastWasApostrophe = false;
            endedWithOperator = true;
            withinProduct = false; // Reset product term
            continue;
        }

        if (c == '*') {
            if ((!lastWasAlpha && !lastWasApostrophe) || lastWasOperator) return false;
            if (withinSummation) return false;  // Multiplication is not allowed inside a summation
            withinProduct = true;  // Allow multiplication for product terms
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
            if (!withinParen && !lastWasApostrophe && !withinSummation) withinProduct = true; // Start of a product term
            continue;
        }

        if (c == '\'') {
            if (!lastWasAlpha) return false;
            lastWasAlpha = false;
            lastWasApostrophe = true;
            lastWasOperator = false;
            endedWithOperator = false;
            if (!withinParen && !lastWasAlpha && !withinSummation) withinProduct = true; // Start of a product term
            continue;
        }

        // If we get here, it's an unexpected character
        return false;
    }

    return parenCount == 0 && !endedWithOperator && !withinParen;
}

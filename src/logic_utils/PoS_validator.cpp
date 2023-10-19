#include <iostream>
#include <cctype>
#include "PoS_validator.h"

using namespace std;

bool isPoSExpression(const string& expr) {
    bool isOpen = false;
    int charCount = 0;
    bool lastWasApostrophe = false;
    int parenCount = 0;  // To track unmatched parentheses

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (isOpen) {
            if (c == '(') return false; // No nested parentheses

            if (c == ')') {
                if (charCount == 0) return false;  // Invalid if no character before this
                isOpen = false;
                charCount = 0;
                lastWasApostrophe = false;
                parenCount--;
            } else if (c == '+') {
                if (charCount != 1) return false;  // A + should only come after a character (and optional apostrophe)
                charCount = 0;
                lastWasApostrophe = false;
            } else if (isalpha(c)) {
                charCount++;
                if (charCount > 1) return false;  // No two characters in a row
                lastWasApostrophe = false;  // Resetting the flag
            } else if (c == '\'') {
                if (charCount != 1 || lastWasApostrophe) return false;  // Apostrophe should only come after a single character and not another apostrophe
                lastWasApostrophe = true;
            } else if (c == ' ') {
                // Spaces are allowed, but not immediately after an apostrophe
                if (lastWasApostrophe) return false;
            } else {
                return false;  // Invalid character inside parenthesis
            }
        } else {
            if (c == '(') {
                isOpen = true;
                parenCount++;
            } else if (c == ')') {
                return false;  // Closing parenthesis without an opening one
            } else if (c != ' ' && c != '*' && !isalpha(c)) {
                return false;  // Invalid character outside parenthesis
            }
        }
    }

    return parenCount == 0 && !isOpen;  // Return false if there's unmatched parentheses
}


//
// Created by Nikolas on 12/11/2024.
//
#include "imgProcessHelp.h"

void swap(int &a, int &b){ // three steps every time.
    int temp = b;
    b = a;
    a = temp;
}

string toHex(int num) {
    //TODO consider adding parameter to allow user to decide how long hex string should be.
    stringstream ss;
    string hex;
    ss << std::hex << num;
    hex = ss.str();
    if (hex[0] >= 48 && hex[0] <= 57 || hex[1] >= 48 && hex[1] <= 57) {
        return hex = hex + hex + hex;
    }
    else {
        hex[0] = (char)(hex[0] - 32);
        hex[1] = (char)(hex[1] - 32);
    }

    return hex = hex + hex + hex;
}
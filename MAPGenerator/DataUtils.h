#pragma once
#ifndef MAPGENERATOR_DATAUTILS_H
#define MAPGENERATOR_DATAUTILS_H

#include "sdk.h"

template <typename T>
std::string DecToHex(T val)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::hex << val;

    return stream.str();
}

char* SetTimeGMT(struct tm* gm);

#endif


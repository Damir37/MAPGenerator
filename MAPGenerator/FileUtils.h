#pragma once

#ifndef MAPGENERATOR_FILEUTILS_H
#define MAPGENERATOR_FILEUTILS_H

#include "sdk.h"

char* ReadFile(std::string path);

bool WriteMAPFile(std::string pathToWrite, char* binaryFile);

#endif

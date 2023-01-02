#pragma once

#ifndef MAPGENERATOR_PEUTILS_H
#define MAPGENERATOR_PEUTILS_H

#include "sdk.h"

time_t GetTimeStamp(PVOID hModule);

ULONG GetImageBase(PVOID hModule);

std::vector<std::string> GetSections(PVOID hModule);

DWORD GetEntryPoint(PVOID hModule);

#endif
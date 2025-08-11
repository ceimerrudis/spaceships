#pragma once
#define DEBUG true
#define DEBUG_SHADERS false
#define DEBUG_MEMORY false
#include "Logger.h"
#define LOG(...) Logger::Log(__FILE__, __LINE__, __func__); Logger::Log(__VA_ARGS__);Logger::Log()

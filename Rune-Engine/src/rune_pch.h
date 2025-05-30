#pragma once

#define RUNE_ENABLE_ASSERTS 1
#define RUNE_ENABLE_PROFILING 1

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Rune/Core/Log.h"
#include "Rune/Debug/Instrumentator.h"


#ifdef RUNE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

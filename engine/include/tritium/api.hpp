#pragma once

#if defined(_WIN32)
  #if defined(TRITIUM_BUILD_DLL)
    #define TRITIUM_API __declspec(dllexport)
  #else
    #define TRITIUM_API __declspec(dllimport)
  #endif
#else
  #define TRITIUM_API __attribute__((visibility("default")))
#endif
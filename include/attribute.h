#pragma once

#if defined(_MSC_VER)
#define attribute(X) __declspec(X)
#else
#if defined(__GNUC__)
#define attribute(X) __attribute__ ((X))
#endif

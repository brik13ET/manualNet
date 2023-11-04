#pragma once

#ifdef _MSC_VER
#define attribute(X) __declspec(X)
#elif defined (__GNUC__)
#define attribute(X) __attribute__ ((X))
#endif

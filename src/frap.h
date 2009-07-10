#pragma once
#ifndef frap_h__
#define frap_h__

#include "predicates.h"
#include "fraction.h"

#define FRAP_MAX_DENOMINATOR 1000000
#define FRAP_OPTIMIST true

fraction_t *frap(double);

#endif

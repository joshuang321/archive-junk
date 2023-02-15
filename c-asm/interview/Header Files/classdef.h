#pragma once
#ifndef CLASSDEF_H_INCLUDED
#define CLASSDEF_H_INCLUDED

#include <stdarg.h>

extern void* new(const void* (*ClassType) (va_list*), ...);
extern void* destroy(void*);
extern void* clone(const void*);

#endif
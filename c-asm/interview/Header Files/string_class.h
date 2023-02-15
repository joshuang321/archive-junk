#pragma once
#ifndef STRING_CLASS_H
#define STRING_CLASS_H

#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "class.h"

struct String{
	const Class m_Class;
    void* (*string_append) (void*, const void*);
    void* (*find_first_of) (const void*, const void*);
    void* (*find_last_of) (const void*, const void*);
    void (*print_string) (const void*);
	
	
    char* m_String;
};

typedef struct String String;

#endif
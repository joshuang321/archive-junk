#pragma once

#include "classdef.h"

#ifndef _STRING_H
#define _STRING_H

#define string_append(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->string_append))(CLASS_OBJ_1, CLASS_OBJ_2)
#define find_first_of(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->find_first_of))(CLASS_OBJ_1, CLASS_OBJ_2)
#define find_first_not_of(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->find_first_not_of))(CLASS_OBJ_1, CLASS_OBJ_2)
#define find_last_of(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->find_last_of))(CLASS_OBJ_1, CLASS_OBJ_2)
#define find_last_not_of(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->find_last_not_of))(CLASS_OBJ_1, CLASS_OBJ_2)
#define print_string(CLASS_OBJ) (*(CLASS_OBJ->print_string))(CLASS_OBJ)

struct String{
	const char m_Class[sizeof(struct{
		void* (*m_destructor) (void*);
		void* (*m_clone) (const void*);
	})];
    void* (*string_append) (void*, const void*);
    void* (*find_first_of) (const void*, const void*);
    void* (*find_last_of) (const void*, const void*);;
	void (*print_string) (const void*);
};

typedef struct String String;

extern const void* (*string) (va_list*);

#endif
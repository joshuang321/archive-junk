#pragma once

#include "classdef.h"

#ifndef _NODE_H
#define _NODE_H

#define push_front(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->push_front))(CLASS_OBJ_1, CLASS_OBJ_2)
#define push_back(CLASS_OBJ_1, CLASS_OBJ_2) (*(CLASS_OBJ_1->push_back))(CLASS_OBJ_1, CLASS_OBJ_2)
#define change_name(CLASS_OBJ, CLASS_OBJ_NAME) (*(CLASS_OBJ->change_name))(CLASS_OBJ, CLASS_OBJ_NAME)
#define change_item(CLASS_OBJ, CLASS_OBJ_ITEM) (*(CLASS_OBJ->change_item))(CLASS_OBJ, CLASS_OBJ_ITEM)
#define get_name(CLASS_OBJ) (*(CLASS_OBJ->get_name))(CLASS_OBJ)
#define get_item(CLASS_OBJ) (*(CLASS_OBJ->get_item))(CLASS_OBJ)
#define is_head(CLASS_OBJ) (*(CLASS_OBJ->is_head))(CLASS_OBJ)

struct Node{
	const char m_Class[sizeof(struct{
		void* (*m_destructor) (void*);
		void* (*m_clone) (const void*);
	})];
    void* (*push_front) (void*, const void*);
    void* (*push_back) (void*, const void*);
    void* (*change_name) (void*, const void*);
    void* (*change_item) (void*, const int);
	void* (*get_name) (const void*);
	int (*get_item) (const void*);
	_Bool (*is_head) (const void*);
};

typedef struct Node Node;

extern const void* (*node) (va_list*);

#endif
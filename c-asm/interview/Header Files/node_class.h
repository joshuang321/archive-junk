#pragma once
#ifndef NODE_CLASS_H
#define NODE_CLASS_H

#include <stdarg.h>
#include <malloc.h>
#include "class.h"

#define true 1
#define false 0

struct String{	
	const char m_supClass[sizeof(struct{
		const Class m_Class;
		void* (*string_append) (void*, const void*);
        void* (*find_first_of) (const void*, const void*);
        void* (*find_first_not_of) (const void*, const void*);
        void* (*find_last_of) (const void*, const void*);
        void* (*find_last_not_of) (const void*, const void*);
        void (*print_string) (const void*);
	
	
        char* m_String;
	})];
};

typedef struct String String;

struct Node{
	const Class m_Class;
    void* (*push_front) (void*, const void*);
    void* (*push_back) (void*, const void*);
    void* (*change_name) (void*, const void*);
    void* (*change_item) (void*, const int);
	void* (*get_name) (const void*);
	int (*get_item) (const void*);
	_Bool (*is_head) (const void*);
	
	
	String* m_Name;
    struct Node* m_Next;
	_Bool m_isHead;
    int m_item;
    
};

typedef struct Node Node;

#endif
#pragma once
#include <stdarg.h>
#include "Header Files/class.h"

void* new(const void* (*ClassType) (va_list*), ...){
	va_list list;
	va_start(list, ClassType);
	void* ptr = (void*)(*ClassType)(&list);
	va_end(list);
	return ptr;
}

void* destroy(void* ClassObj){
	Class* obj_class = (Class*) ClassObj;
	(*(obj_class->m_destructor))(ClassObj);
	
	return ClassObj;
}

void* clone(const void* ClassObj){
	Class* obj_class = (Class*)  ClassObj;
	Class* new_obj_class = (*(obj_class->m_clone))(ClassObj);
	
	return new_obj_class;
}
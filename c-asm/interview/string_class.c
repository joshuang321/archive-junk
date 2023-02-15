#pragma once

#include "Header Files/string_class.h"

static void* _string_constructor(va_list*);
static void* _string_destructor(void*);
static void* _string_clone(const void*);
static void* _string_append(void*, const void*);
static void* _find_first_of(const void*, const void*);
static void* _find_last_of(const void*, const void*);
static void _print_string(const void*);


static void* _string_constructor(va_list* list){
	String* string = calloc(1, sizeof(String));
	
	if (NULL == string)
		return NULL;
	
	string->m_String = va_arg(*list, char*);
	
	string->string_append = &_string_append;
	string->find_first_of = &_find_first_of;
	string->find_last_of = &_find_last_of;
	string->print_string = &_print_string;
	
	((Class*)string)->m_destructor = &_string_destructor;
	((Class*)string)->m_clone = &_string_clone;
	
	return string;
}

static void* _string_destructor(void* this){
	if(NULL == this)
		return NULL;
	
	String* string = (String*)this;	
	free(string);
	string = NULL;
	
	return this;
}

static void* _string_clone(const void* this){
	if (NULL == this)
		return NULL;
	
	String* cpystring = calloc(1, sizeof(String));
	*cpystring = *(String*)this;
	
	return cpystring;
}

static void* _string_append(void* this, const void* string){
	if (NULL == string || NULL == this)
		return NULL;
	
	String* _string_2 = (String*)this;
	
	const size_t string_size = strlen((char*) string);
	const size_t this_size =strlen((char*) _string_2->m_String);
	const size_t newsize = string_size + this_size +1;
	
	memcpy((char*)((_string_2->m_String) + this_size), (char*) string, newsize - this_size);
	
	return this;
}

static void* _find_first_of(const void* this, const void* string){
	if (NULL == string || NULL == this)
		return NULL;
	
	String* _string_2 = (String*)this;
	
	char* result;
	result = strstr(_string_2->m_String, string);
	result += strlen((const char*) string);
	
	  printf("[%s]\n", result);

	return result;
}

static void* _find_last_of(const void* this, const void* string){
	if (NULL == string || NULL == this)
		return NULL;
		
	String* _string = (String*)this;
	
    char* result;
    result = strstr(_string->m_String, string);
    result += strlen(string);
    if(NULL != strstr(_string->m_String, string)){
		result = strstr(_string->m_String, string);
	    result += strlen(string);
  }
  
  printf("[%s]", result);
  
  return result;
}

 static void _print_string(const void* this){
	String* string = (String*) this;
	printf("String: %s\n", string->m_String);
}

const void* (*string) (va_list*) = &_string_constructor;
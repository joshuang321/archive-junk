#pragma once
#include <stdio.h>
#include "Header Files/_string.h"
#include "Header Files/_node.h"

int main(void){
	String* obj = new(string, "test1 test2 test1");
	print_string(obj);
	string_append(obj, "yes");
	String* obj2 = clone(obj);
	
	Node* obj3 = new(node);
	Node* obj4 = clone(obj3);
	
	push_front(obj3, obj4);
	
	destroy(obj4);
	
	print_string(obj);
	printf("\n\n");

	char* str1 = find_first_of(obj, "test2");
	char* str2 = find_last_of(obj, "test2");
	
	
	printf("\n\n");
	print_string(obj2);
	printf("\n\n");
	
	str1 = find_first_of(obj2, "test2");
	str2 = find_last_of(obj2, "test2");
	
	destroy(obj);
	destroy(obj2);
	return 0;
}
	
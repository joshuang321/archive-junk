#pragma once

#include "Header Files/node_class.h"

static void* _node_constructor(va_list*);
static void* _node_destructor(void*);
static void* _node_clone(const void*);
static void* _push_front(void*, const void*);
static void* _push_back(void*, const void*);
static void* _change_name(void* this, const void*);
static void* _change_item(void*this, const int);
static void* _get_name(const void*);
static int _get_item(const void*);
static _Bool _is_head(const void*);

static void* _node_constructor(va_list* list){
	Node* node = calloc(1, sizeof(Node));
	
	if (NULL == node)
		return NULL;
	
	node->m_Name = va_arg(*list, String*);
	node->m_Next = va_arg(*list, Node*);
	node->m_isHead = true;
	node->m_item = va_arg(*list, int);
	
	node->get_item = &_get_item;
	node->is_head = &_is_head;
	node->push_front = &_push_front;
	node->push_back = &_push_back;
	node->change_name = &_change_name;
	node->change_item = &_change_item;
	node->get_name = &_get_name;
	node->get_item = &_get_item;
	node->is_head = &_is_head;
	
	((Class*)node)->m_destructor = &_node_destructor;
	((Class*)node)->m_clone = &_node_clone;
	
	return node;
}

static void* _node_destructor(void* this){
	if (NULL == this)
		return NULL;
	Node* node_iterator;
	Node* node_head = (Node*) this;
	while (NULL == node_head){
		node_iterator = node_head;
		node_head = node_head->m_Next;
		free(node_iterator);
		node_iterator = NULL;
	}
	
	return this;
}

static void* _node_clone(const void* this){
	if (NULL == this)
		return NULL;
	
	Node* cpynode = calloc(1, sizeof(Node));
	*cpynode = *(Node*)this;
	
	return cpynode;
}

static void* _push_front(void* this, const void* node){
	if (NULL == node || this == this)
		return NULL;
	
	Node* node_1 = (Node*)node;
	Node* node_2 = (Node*)this;
	
	node_1->m_Next = node_2;
	node_1->m_isHead = true;
	node_2->m_isHead = false;
	return (void*)node;
}
 
static void* _push_back(void* this, const void* node){
	if (NULL == node || NULL == this)
		return NULL;
	
	Node* node_1 = (Node*)node;
	Node* node_2 = (Node*)this;
	Node* node_iterator;
	
	while (NULL != node_2){
		node_iterator = node_2;
		node_2 = node_2->m_Next;
	}
	
	node_iterator->m_Next = node_1;
	node_1->m_isHead = false;
	return this;
}

static void* _change_name(void* this, const void* name){
	if (NULL == name || NULL == this)
		return NULL;
	
	Node* node = (Node*) this;
	
	node->m_Name = (String*)name;
	
	return this;
}

static void* _change_item(void*this, const int item){
	if (NULL == item || NULL == this)
		return NULL;
		
	Node* node = (Node*)this;
	node->m_item = item;
	
	return this;
}

static void* _get_name(const void* this){
	if (NULL == this)
		return NULL;
	Node* node = (Node*) this;
	return node->m_Name;
}

static int _get_item(const void* this){
	if (NULL == this)
		return (int)NULL;
	
	Node* node = (Node*) this;
	return node->m_item;
}

static _Bool _is_head(const void* this){
	if (NULL == this)
		return NULL;
	
	Node* node = (Node*) this;
	return node->m_isHead;
}

const void* (*node) (va_list*) = &_node_constructor;
#pragma once
#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

struct Class{
   void* (*m_destructor) (void*);
   void* (*m_clone) (const void*);
};

typedef struct Class Class;

#endif
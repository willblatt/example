#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "geomObj.hpp"

class LinkedList {
public:
   LinkedList();
   ~LinkedList();

   GeometricObject* begin(){ return mFirstPtr; }
   GeometricObject* end(){ return mLastPtr; }

   void push_back(GeometricObject* obj);
   void push_front(GeometricObject* obj);

   //! find the object with the given name and return it
   int find(std::string& name, GeometricObject*& obj);

   //! erase the given object from the list
   void erase(GeometricObject* obj);

   //! insert the object before or after the original object
   void insert(GeometricObject* obj, GeometricObject* orig, bool before);

private:
    GeometricObject *mFirstPtr, *mLastPtr;
};

#endif
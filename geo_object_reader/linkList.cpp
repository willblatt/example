#include <iostream>
#include <string>
#include "geomObj.hpp"
#include "linkList.hpp"

LinkedList::LinkedList() {
	mFirstPtr = mLastPtr = NULL;
}

LinkedList::~LinkedList() {
	GeometricObject *currentPtr = mFirstPtr;
	GeometricObject *tempPtr;

	while (currentPtr != NULL) {
		tempPtr=currentPtr;
		currentPtr = currentPtr->mNextPtr;
		delete tempPtr;
	}
}

void LinkedList::push_back(GeometricObject *obj) {
	// Special case where list is empty.
	if (mLastPtr == NULL) {
		mLastPtr = obj;
		mFirstPtr = mLastPtr;
		obj->mNextPtr = NULL;
		obj->mPrevPtr = NULL;
	} else {
		mLastPtr->mNextPtr = obj;
		obj->mPrevPtr = mLastPtr;
		obj->mNextPtr = NULL;
		mLastPtr = obj;
	}
}

void LinkedList::push_front(GeometricObject *obj) {
	// Special case where list is empty.
	if (mFirstPtr == NULL) {
		mFirstPtr = obj;
		mLastPtr = mFirstPtr;
		obj->mNextPtr = NULL;
		obj->mPrevPtr = NULL;
	} else {
		mFirstPtr->mPrevPtr = obj;
		obj->mNextPtr = mFirstPtr;
		obj->mPrevPtr = NULL;
		mFirstPtr = obj;
	}
}

int LinkedList::find(std::string& name, GeometricObject*& obj) {
	GeometricObject* CurrentObj = mFirstPtr;
	for(CurrentObj=mFirstPtr;CurrentObj=mLastPtr;CurrentObj=CurrentObj->mNextPtr) {
		string obj_name;
		CurrentObj->GetName(obj_name);
		if(!obj) {
			cout << "This item was not found, returning to main menu." << endl;
			return(1);
		}
		if (obj_name == name) {
			obj = CurrentObj;
			return(0);
		}
	}
	cout << "This item was not found." << endl;
	return(1);
}

void LinkedList::erase(GeometricObject* obj) {
	if (obj==mFirstPtr && obj==mLastPtr) {
		delete obj;
	} else if (obj==mFirstPtr) {
		mFirstPtr = obj->mNextPtr;
		obj->mNextPtr->mPrevPtr = NULL;
		delete obj;
	} else if (obj==mLastPtr) {
		mLastPtr = obj->mPrevPtr;
		obj->mPrevPtr->mNextPtr = NULL;
		delete obj;
	} else {
		obj->mPrevPtr->mNextPtr = obj->mNextPtr;
		obj->mNextPtr->mPrevPtr = obj->mPrevPtr;
		delete obj;
	}
}

void LinkedList::insert(GeometricObject* obj, GeometricObject* orig, bool before) {
	// If bool = before, insert before orig
	if (before==false) {
		obj->mPrevPtr = orig;
		if (mLastPtr == orig) {
			mLastPtr = obj;
			obj->mNextPtr = NULL;
		} else {
			orig->mNextPtr->mPrevPtr = obj;
			obj->mNextPtr = orig->mNextPtr;
		}
		orig->mNextPtr = obj;
	} else {
		obj->mNextPtr = orig;
		if (mFirstPtr == orig) {
			mFirstPtr = obj;
			obj->mPrevPtr = NULL;
		} else {
			orig->mPrevPtr->mNextPtr = obj;
			obj->mPrevPtr = orig->mPrevPtr;
		}
		orig->mPrevPtr = obj;
	}
}
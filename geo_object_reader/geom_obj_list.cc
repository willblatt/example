#include "geom_obj_list.h"

#include <iostream>
#include <string>

#include "tokenize.h"
#include "cone.h"

namespace geom {

GeomObjList::GeomObjList() {
	first_ = last_ = nullptr;
}
GeomObjList::~GeomObjList() {
	GeomObj *currPtr = first_;
	GeomObj*tempPtr;

	while (currPtr != nullptr) {
		tempPtr = currPtr;
		currPtr = currPtr->next_;
		delete tempPtr;
	}
}

int GeomObjList::Read(std::string fname) {
	std::ifstream ifile(fname.c_str());
	std::string line;

	//TODO: check if read in file was any good
	//std::cout << std::endl << ifile.good() << std::endl;

	std::vector<std::string> data;

	if (ifile.is_open()) {
		while (std::getline(ifile, line)) {
			tokenize(line, data, " ,\t");
		}
		ifile.close();
	} else {
		std::cout << "Unable to open file";
	}

	for (size_t i=0, ilen= data.size(); i<ilen; ++i) {
		if(data[i]=="CONE") {
			Cone* obj = new Cone();
			std::vector<std::string> cone_data(data.begin() + i, data.end());
			if (!(obj->Read(cone_data))) {
				PushBack(obj);
			}
		} else if(data[i]=="CYLINDER") {
	//		Cylinder* obj= new Cylinder();
	//		obj->readGeometricObject(i,tokens);
	//		cout << obj->GetType() << endl;
	//		geom_objs->push_back(obj);
		} else if(data[i]=="SPHERE") {
	//		Sphere* obj= new Sphere();
	//		obj->readGeometricObject(i,tokens);
	//		cout << obj->GetType() << endl;
	//		geom_objs->push_back(obj);
		} else if(data[i]=="BOX") {
	//		Box* obj= new Box();
	//		obj->Read(tokens, int(i));
	//		cout << obj->GetType() << endl;
	//		geom_objs->PushBack(obj);
		}
	}

	return 0;
}

GeomObj* GeomObjList::Begin() {
	return first_;
}
GeomObj* GeomObjList::End() {
	return last_;
}

void GeomObjList::PushBack(GeomObj *obj) {
	// When list is empty
	if (last_ == nullptr) {
		last_ = obj;
		first_ = last_;
		obj->next_ = nullptr;
		obj->prev_ = nullptr;
	} else {
		last_->next_ = obj;
		obj->prev_ = last_;
		obj->next_ = nullptr;
		last_ = obj;
	}
}
void GeomObjList::PushFront(GeomObj *obj) {
	// When list is empty.
	if (first_ == nullptr) {
		first_ = obj;
		last_ = first_;
		obj->next_ = nullptr;
		obj->prev_ = nullptr;
	} else {
		first_->prev_ = obj;
		obj->next_ = first_;
		obj->prev_ = nullptr;
		first_ = obj;
	}
}
GeomObj* GeomObjList::Find(const std::string name) {
	GeomObj* curr = first_;

	for (curr=first_; curr=last_; curr=curr->next_) {
		if (curr->GetName() == name) {
			return curr;
		}
	}

	std::cout << "No item found." << std::endl;
	return nullptr;
}
int GeomObjList::Remove(GeomObj* obj) {
	// Only obj in list
	if (obj == first_ && obj == last_) {
		delete obj;
		return 0;
	
	} else if (obj == first_) {
		first_ = obj->next_;
		obj->next_->prev_ = nullptr;
		delete obj;
		return 0;
	
	} else if (obj == last_) {
		last_ = obj->prev_;
		obj->prev_->next_ = nullptr;
		delete obj;
		return 0;

	} else {
		obj->prev_->next_ = obj->next_;
		obj->next_->prev_ = obj->prev_;
		delete obj;
		return 0;
	}

	return 1;
}
void GeomObjList::Insert(GeomObj* obj, GeomObj* orig, bool before) {
	if (before) {
		obj->next_ = orig;
		if (first_ == orig) {
			first_ = obj;
			obj->prev_ = nullptr;
		} else {
			orig->prev_->next_ = obj;
			obj->prev_ = orig->prev_;
		}
		orig->prev_ = obj;
	} else {
		obj->prev_ = orig;
		if (last_ == orig) {
			last_ = obj;
			obj->next_ = nullptr;
		} else {
			orig->next_->prev_ = obj;
			obj->next_ = orig->next_;
		}
		orig->next_ = obj;
	}
}

} // namespace geom
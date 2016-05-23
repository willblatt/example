#ifndef GEOM_LIST_H_
#define GEOM_LIST_H_

#include "geom_obj.h"

namespace geom {

class GeomObjList {

public:
	GeomObjList();
	~GeomObjList();

	int Read(std::string fname);

	GeomObj* Begin();
	GeomObj* End();

	void PushBack(GeomObj* obj);
	void PushFront(GeomObj* obj);

	GeomObj* Find(const std::string name);
	int Remove(GeomObj* obj);
	void Insert(GeomObj* obj, GeomObj* orig, bool before);

private:
	GeomObj *first_, *last_, *prev_, *next_;
};

} // namespace geom
#endif
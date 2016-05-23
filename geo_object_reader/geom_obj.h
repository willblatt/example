#ifndef GEOMOBJ_H
#define GEOMOBJ_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glut.h>

enum GeomType {
	UNKNOWN = 0,
	CONE,
	CYLINDER,
	BOX,
	POLYGON,
	SPHERE
};

static GLfloat vBLUE[] = { 0.0, 0.0, 1.0 };
static GLfloat vDKGREEN[] = { 0.0, 0.6, 0.0 };
static GLfloat vMAGENTA[] = { 1.0, 0.0, 1.0 };
static GLfloat vRED[] = { 1.0, 0.0, 0.0 };
static GLfloat vGRAY[] = { 0.6, 0.6, 0.6 };
static GLfloat vYELLOW[] = { 1.0, 1.0, 0.0 };
static GLfloat vWHITE[] = { 1.0, 1.0, 1.0 };
static GLfloat vGREEN[] = { 0.0, 1.0, 0.0 };
static GLfloat vCYAN[] = { 0.0, 1.0, 1.0 };
static GLfloat vBLACK[] = { 0.0, 0.0, 0.0 };

namespace geom {

class GeomObj {
	friend class GeomObjList;

public:
	GeomObj(void);
	~GeomObj(void) {};

	virtual int Write(std::ofstream& ofile) { return 0; }
	virtual int Read(const std::string data) { return 0; }
	virtual double GetVolume() { return 0.0; }
	virtual void DrawList() {}

	std::string GetName();
	void SetName(std::string name);
	std::string GetType();
	void SetType(std::string type);
	int GetId();
	void SetId(int id);
	void setDrawListID(GLuint counter);

	void DrawShapes();
	
	void GetTranslation(double &tx, double &ty, double &tz);
	void GetRotation(double &rx, double &ry, double &rz);
	void GetScale(double &sx, double &sy, double &sz);

	void SetTranslation(double tx, double ty, double tz);
	void SetRotation(double rx, double ry, double rz);
	void SetScale(double sx, double sy, double sz);

	GeomObj* GetPrev() { return prev_; }
	GeomObj* GetNext() { return next_; }

protected:
	GeomObj *next_;
	GeomObj *prev_;

	GLuint drawListId_;

	int id_;
	std::string name_, type_;
	double tx_, ty_, tz_;
	double rx_, ry_, rz_;
	double sx_, sy_, sz_;
};

} // namespace geom
#endif
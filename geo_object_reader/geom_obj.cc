#include "geom_obj.h"

namespace geom {

GeomObj::GeomObj(void) {
	tx_ = ty_ = tz_ = 0.0;
	rx_ = ry_ = rz_ = 0.0;
	sx_ = sy_ = sz_ = 1.0;

	next_ = prev_ = nullptr;
}
void GeomObj::SetName(std::string name) {
	name_ = name;
}
std::string GeomObj::GetName() {
	return name_;
}
void GeomObj::SetType(std::string type) {
	type_ = type;
}
std::string GeomObj::GetType() {
	return type_;
}
void GeomObj::SetId(int id) {
	id_ = id;
}
int GeomObj::GetId() {
	return id_;
}

void GeomObj::GetTranslation(double &x, double &y, double &z) {
	x = tx_;
	y = ty_;
	z = tz_;
}
void GeomObj::SetTranslation(double x, double y, double z) {
	tx_ = x;
	ty_ = y;
	tz_ = z;
}
void GeomObj::GetRotation(double &x, double &y, double &z) {
	x = rx_;
	y = ry_;
	z = rz_;
}
void GeomObj::SetRotation(double x, double y, double z) {
	rx_ = x;
	ry_ = y;
	rz_ = z;
}
void GeomObj::GetScale(double &x, double &y, double &z) {
	x = sx_;
	y = sy_;
	z = sz_;
}
void GeomObj::SetScale(double x, double y, double z) {
	if(x > 0 && y > 0 && z > 0) {
		sx_ = x;
		sy_ = y;
		sz_ = z;
	} else {
		std::cout << GetType() << " Error: scale must all be positive: (" << x << y << z << ")" << std::endl;
	}
}

void GeomObj::setDrawListID(GLuint counter) {
	drawListId_ = counter;
}

void GeomObj::DrawShapes() {
	glPushMatrix();

	//glColor4f(1,0.84,0.0, alpha);

	glRotatef((GLfloat)rx_, 1.0F, 0.0, 0.0);
	glRotatef((GLfloat)ry_, 0.0, 1.0F, 0.0);
	glRotatef((GLfloat)rz_, 0.0, 0.0, 1.0F);
	glScalef(1, 1, 1);
	glTranslatef(tx_, ty_, tz_);
	glCallList(drawListId_);

	glPopMatrix();
}

} // namespace geom

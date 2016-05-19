#include "GeomObj.hpp"

GeometricObject::GeometricObject(void) {

	mTx = 0.0;
	mTy = 0.0;
	mTz = 0.0;

	mRx = 0;
	mRy = 0;
	mRz = 0;

	mSx = 1.0;
	mSy = 1.0;
	mSz = 1.0;

	mNextPtr = mPrevPtr = NULL;
}

void GeometricObject::SetName(std::string name) {
	mName = name;
}

std::string GeometricObject::GetName() {
	return(mName);
}

void GeometricObject::SetType(std::string type) {
	mType = type;
}

std::string GeometricObject::GetType() {
	return(mType);
}

void GeometricObject::SetID(GeomType id) {
	mID = id;
}

GeomType GeometricObject::GetID() {
	return(mID);
}

void GeometricObject::GetTranslation(double &x, double &y, double &z) {
	x = mTx;
	y = mTy;
	z = mTz;

	return;
}
void GeometricObject::GetRotation(double &x, double &y, double &z) {
	x = mRx;
	y = mRy;
	z = mRz;

	return;
}
void GeometricObject::GetScale(double &x, double &y, double &z) {
	x = mSx;
	y = mSy;
	z = mSz;

	return;
}

void GeometricObject::SetTranslation(const double x, const double y,const double z) {
	mTx = x;
	mTy = y;
	mTz = z;

	return;
}
void GeometricObject::SetRotation(const double x, const double y, const double z) {
	mRx = x;
	mRy = y;
	mRz = z;

	return;
}
void GeometricObject::SetScale(const double x, const double y, const double z) {
	if(x > 0 && y > 0 && z > 0) {
		mSx = x;
		mSy = y;
		mSz = z;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Not Scaled Properly" << std::endl;
		exit(1);
	}

	return;
}

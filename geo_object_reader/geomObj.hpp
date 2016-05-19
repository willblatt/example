#ifndef GEOMETRIC_OBJECT_HPP
#define GEOMETRIC_OBJECT_HPP

#include <iostream>
#include <vector>
#include <qgl.h>
using namespace std;

class GeometricObject {
	friend class LinkedList;
public:
	GeometricObject(void);	// Constructor
	~GeometricObject(void){};	// Destructor

	virtual void print()=0;
	virtual void printToFile(ofstream& outFile, string outFilename)=0;
	virtual void read(const vector<string> tokens, int position)=0;
	virtual void readFromConsole(void)=0;
	virtual void create_draw_list(float alpha)=0;
	void drawShapes();

	void GetName(string &name);
	void SetName(string name);
	void setDrawListID(GLuint counter);
	GLuint getDrawListID(void) {return mDrawListID;};

	void GetTranslation(float &tx, float &ty, float &tz);
	void GetRotation(float &rx, float &ry, float &rz);
	void GetScale(float &sx, float &sy, float &sz);

	void SetTranslation(const float tx, const float ty, const float tz);
	void SetRotation(const float rx, const float ry, const float rz);
	void SetScale(const float sx, const float sy, const float sz);


	GeometricObject* Next(){return mNextPtr;}
	GeometricObject* Previous(){return mPrevPtr;}

protected:
	std::string mName;
	GLuint mDrawListID;
	float mTx, mTy, mTz;
	float mRx, mRy, mRz;
	float mSx, mSy, mSz;

private:
	GeometricObject* mNextPtr;
	GeometricObject* mPrevPtr;
};

#endif
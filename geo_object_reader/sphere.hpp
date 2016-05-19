#ifndef SPHERE_HPP
#define SPHERE_HPP

class Sphere : public GeometricObject {
public:
	Sphere(){};
	~Sphere(){};
	virtual void print();
	virtual void printToFile(ofstream& outFile, string outFilename);
	virtual void read(const vector<string> tokens, int position);
	virtual void readFromConsole(void);
	virtual void create_draw_list(float alpha);
	void SetDimensions(const float r);
	void GetDimensions(float &r);
	GLfloat GetRadius();

private:
	GLfloat mRadius;
};

void Sphere::print() {}

void Sphere::printToFile(ofstream& outFile, string outFilename) {}

void Sphere::read(const vector<string> tokens, int position) {
	//mName = tokens[++position];
	sscanf(tokens[++position].c_str(), "%f", &mTx);
	sscanf(tokens[++position].c_str(), "%f", &mTy);
	sscanf(tokens[++position].c_str(), "%f", &mTz);
	sscanf(tokens[++position].c_str(), "%f", &mRadius);
	//sscanf(tokens[++position].c_str(), "%f", &mRx);
	//sscanf(tokens[++position].c_str(), "%f", &mRy);
	//sscanf(tokens[++position].c_str(), "%f", &mRz);
	//sscanf(tokens[++position].c_str(), "%f", &mSx);
	//sscanf(tokens[++position].c_str(), "%f", &mSy);
	//sscanf(tokens[++position].c_str(), "%f", &mSz);
}

void Sphere::readFromConsole(void) {}

void Sphere::SetDimensions(const float r) {
	mRadius = r;
}

void Sphere::GetDimensions(float &r) {
	r = mRadius;
}

GLfloat Sphere::GetRadius() {
	return(mRadius);
}

void Sphere::create_draw_list(float alpha) {
	//GLfloat vMAGENTA[] = {1, 0.84, 0.0, alpha};
	glNewList(mDrawListID, GL_COMPILE);
	glColor4f(1,0.84,0.0, alpha);
    //glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vMAGENTA );
	GLUquadricObj *mySphereObj;
    mySphereObj = gluNewQuadric ();
    gluQuadricDrawStyle (mySphereObj, GLU_FILL);
    gluSphere (mySphereObj, mRadius, 80, 64);
	glEndList();
}

#endif
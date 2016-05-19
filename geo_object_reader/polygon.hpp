#ifndef MYPOLYGON_HPP
#define MYPOLYGON_HPP

class myPolygon : public GeometricObject {
public:
	myPolygon(void);
	~myPolygon(){};
	virtual void print();
	virtual void printToFile(ofstream& outFile, string outFilename);
	virtual void read(const vector<string> tokens, int position);
	virtual void readFromConsole(void);
	virtual void create_draw_list(void);
	void SetNumPts(int numPts);
	void GetNumPts(int &numPts);
	void SetPoint(const float x, const float y, const float z);
	void GetPoint(int point_number, float &x, float &y, float &z);

private:
	int mNumPts;
	vector<double> mx;
	vector<double> my;
	vector<double> mz;
};


void myPolygon::print() {
	int i;
	cout << endl;
	cout << "POLYGON " << mName << "\n";
	cout << mNumPts << "\n";

	for (i=0; i<mNumPts; i++) {
		cout << mx[i] << " " << my[i] << " " << mz[i] << endl;
	}

	cout << mTx << " " << mTy << " " << mTz << "\n";
	cout << mRx << " " << mRy << " " << mRz << "\n";
	cout << mSx << " " << mSy << " " << mSz << "\n";
	cout << "\n";
	return;
}

void myPolygon::printToFile(ofstream& outFile, string outFilename) {
	int i;
	outFile << "POLYGON " << mName << "\n";
	outFile << mNumPts << "\n";
	for (i=0; i<mNumPts; i++) {

		outFile << mx[i] << " " << my[i] << " " << mz[i] << endl;
	}
	outFile << mTx << " " << mTy << " " << mTz << "\n";
	outFile << mRx << " " << mRy << " " << mRz << "\n";
	outFile << mSx << " " << mSy << " " << mSz << "\n";
	outFile << "\n";
	cout << "Polygon printed to file \n";
}

void myPolygon::read(const vector<string> tokens, int position) {
	//define read statement here, line by line reading from file
	int i;
	mName = tokens[++position];
	sscanf(tokens[++position].c_str(), "%d", &mNumPts);
	for (i=0; i<mNumPts; i++) {
		mx.push_back(strtod(tokens[++position].c_str(), 0));
		my.push_back(strtod(tokens[++position].c_str(), 0));
		mz.push_back(strtod(tokens[++position].c_str(), 0));
	}
	sscanf(tokens[++position].c_str(), "%f", &mTx);
	sscanf(tokens[++position].c_str(), "%f", &mTy);
	sscanf(tokens[++position].c_str(), "%f", &mTz);

	sscanf(tokens[++position].c_str(), "%f", &mRx);
	sscanf(tokens[++position].c_str(), "%f", &mRy);
	sscanf(tokens[++position].c_str(), "%f", &mRz);

	sscanf(tokens[++position].c_str(), "%f", &mSx);
	sscanf(tokens[++position].c_str(), "%f", &mSy);
	sscanf(tokens[++position].c_str(), "%f", &mSz);
}

void myPolygon::readFromConsole(void) {
	cout << "Enter the name of the polygon" << endl;
	cin >> mName;
	cout << "Enter the number of points:" << endl;
	cin >> mNumPts;
	int i;
	for (i=0; i<mNumPts; i++) {
		cout << "Enter Point " << i+1 << endl;
		float x, y, z;
		cin >> x >> y >> z;
		mx.push_back(x);
		my.push_back(y);
		mz.push_back(z);
	}
	cout << "Enter the 3 translation parameters" << endl;
	cin >> mTx >> mTy >> mTz;
	cout << "Enter the 3 rotation parameters" << endl;
	cin >> mRx >> mRy >> mRz;
	cout << "Enter the 3 scale parameters" << endl;
	cin >> mSx >> mSy >> mSz;
}

myPolygon::myPolygon(void) {
	mNumPts = 1;
}

void myPolygon::SetNumPts(int numPts) {
	mNumPts = numPts;
}

void myPolygon::GetNumPts(int &numPts) {
	numPts = mNumPts;
}

void myPolygon::SetPoint(const float x, const float y, const float z) {
	mx.push_back(x);
	my.push_back(y);
	mz.push_back(z);
}

void myPolygon::GetPoint(int point_number, float &x, float &y, float &z) {
	x = mx[point_number];
	y = my[point_number];
	z = mz[point_number];
}

void myPolygon::create_draw_list(void) {
	GLfloat vBLUE[]    = {0.0, 0.0, 1.0};
	GLfloat vDKGREEN[] = {0.0, 0.6, 0.0};
	GLfloat vMAGENTA[] = {1.0, 0.0, 1.0};
	GLfloat vRED[]     = {1.0, 0.0, 0.0};
	GLfloat vGRAY[]    = {0.6, 0.6, 0.6};
	GLfloat vYELLOW[]  = {1.0, 1.0, 0.0};
	GLfloat vWHITE[]   = {1.0, 1.0, 1.0};
	GLfloat vGREEN[]   = {0.0, 1.0, 0.0};
	GLfloat vCYAN[]    = {0.0, 1.0, 1.0};
	GLfloat vBLACK[]   = {0.0, 0.0, 0.0};

	int i = 0;
	glNewList(mDrawListID, GL_COMPILE);
		glColor3fv(vCYAN);
		glBegin(GL_POLYGON);
			for (i=0; i<mNumPts; i++) {
				glVertex3f(mx[i],my[i],mz[i]);
			}
		glEnd();
	glEndList();
}

#endif
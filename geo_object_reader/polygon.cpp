#include "polygon.hpp"

Polygonal::Polygonal() {
	SetType("POLYGON");
	SetID(POLYGON);
	mNumOfPoints=0;
}

Polygonal::~Polygonal() {
	for(int i=0;i<mNumOfPoints;i++) {
		delete mL[i];
	}
	delete mL;
}

void Polygonal::set_numofpoints(int num) {
	if(num > 3){
		mNumOfPoints=num;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Number of points not suffiecient" << std::endl;
		exit(1);
	}
}

int Polygonal::get_numofpoints() {
	return(mNumOfPoints);
}

void Polygonal::readGeometricObject(const int start,const std::vector<std::string> tokens) {
	SetName(tokens[start+1]);

	//find number of points in POLYGON
	int ptscheck;
	if(!(std::istringstream(tokens[start+2]) >> ptscheck)){
		std::cout << "Error in TYPE " << GetType() << ": Nonnumeric value or file formatted incorrectly" << std::endl;
		exit(1);
	}
	set_numofpoints(ptscheck);

	int size=(12+3*mNumOfPoints); //Number of strings associated with POLYGON

	mL = new double* [mNumOfPoints];
	for(int i=0;i<mNumOfPoints;i++) {
		mL[i]= new double [3];
	}


	if(tokens.size()<(start+size)) {
		std::cout << "Error in TYPE " << GetType() << ": File is not formatted correctly" << std::endl;
		exit(1);
	}

	//convert object definitions from strings to doubles and store values
	std::vector<double> objval;
	for(i=(start+3);i<(start+size);i++) {
		double temp;
		if(!(std::istringstream(tokens[i]) >> temp)) {
			std::cout << "Error in TYPE " << GetType() << ": Nonnumeric value or file formatted incorrectly" << std::endl;
			exit(1);
		}
		objval.push_back(temp);
	}

	int k=0;
	for(i=0;i<mNumOfPoints;i++) {
		for(int j=0;j<3;j++) {
			mL[i][j]=objval[k];
			k++;
		}
	}

	SetTranslation(objval[k],objval[k+1],objval[k+2]);
	SetRotation(objval[k+3],objval[k+4],objval[k+5]);
	SetScale(objval[k+6],objval[k+7],objval[k+8]);
}

void Polygonal::printGeometricObject() {
	std::cout << "Type: " << GetType() << "\t" << "Name: " << GetName() << std::endl;
	std::cout << "Number of Points: " << get_numofpoints() << std::endl;
	std::cout << "Points: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;

	for(int i=0;i<mNumOfPoints;i++) {
		for(int j=0;j<3;j++) {
			std::cout << mL[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	//get translations
	std::cout << std::endl;
	std::cout << "Translations: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	std::cout << Tx << "\t" << Ty << "\t" << Tz << std::endl;

	//get rotations
	std::cout << std::endl;
	std::cout << "Rotations: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	std::cout << Rx << "\t" << Ry << "\t" << Rz << std::endl;

	//get scale
	std::cout << std::endl;
	std::cout << "Scale: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);
	std::cout << Sx << "\t" << Sy << "\t" << Sz << std::endl;
}

void Polygonal::writeGeometricObjectToFile(std::ofstream& outfile) {
	outfile << GetType() << " " << GetName() << std::endl;
	outfile << get_numofpoints() << std::endl;

	//print out points
	for(int i=0;i<mNumOfPoints;i++) {
		for(int j=0;j<3;j++) {
			outfile << mL[i][j] << ",";
		}
		outfile << std::endl;
	}

	//get translations
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	outfile << Tx << "," << Ty << "," << Tz << std::endl;

	//get rotations
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	outfile << Rx << "," << Ry << "," << Rz << std::endl;

	//get scale
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);
	outfile << Sx << "," << Sy << "," << Sz << std::endl;

	outfile << std::endl;
}

void Polygonal::DrawList() {
	//get translations
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	//get rotations
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	//get scale
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);

	glNewList(POLYGON, GL_COMPILE);
		glPushMatrix();
			//Rotations
			glRotatef ((GLfloat)Rx, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
			glRotatef ((GLfloat)Ry, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
			glRotatef ((GLfloat)Rz, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)1.0);
			//Scaling
			glScalef ((GLfloat)Sx,(GLfloat)Sy,(GLfloat)Sz);
			//Translations
			glTranslatef ((GLfloat)Tx, (GLfloat)Ty, (GLfloat)Tz);

			//Front Face
			glColor3fv(vWHITE);
			glBegin(GL_POLYGON);
			for(int i=0;i<mNumOfPoints;i++) {
				for(int j=0;j<3;j++) {
					glVertex3f(mL[i][0],mL[i][1],mL[i][2]);
				}
			}
			glEnd();
		glPopMatrix ();
	glEndList();
}
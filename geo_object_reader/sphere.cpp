#include "sphere.hpp"

Sphere::Sphere() {
	SetType("SPHERE");
	SetID(SPHERE);
	mRadius=0;
}

void Sphere::set_radius(double r) {
	if(r >= 0){
		mRadius=r;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Radius must be positive" << std::endl;
		exit(1);
	}
}

double Sphere::get_radius() {
	return(mRadius);
}

void Sphere::readGeometricObject(const int start,const std::vector<std::string> tokens) {
	int size=12;

	//Check to see if enough data has been written to completely define SPHERE
	if(tokens.size()<(start+size)) {
		std::cout << "Error in TYPE " << GetType() << ": File is not formatted correctly" << std::endl;
		exit(1);
	}

	SetName(tokens[start+1]);
	//convert object definitions from strings to doubles and store values
	std::vector<double> objval;
	for(int i=(start+2);i<(start+size);i++) {
		double temp;
		// converts the c-string to the type of variable listed and stores its value in the variable name
		if(!(std::istringstream(tokens[i]) >> temp)) {
			std::cout << "Error in TYPE " << GetType() << ": Nonnumeric value or file formatted incorrectly" << std::endl;
			exit(1);
		}
		objval.push_back(temp);
	}

	set_radius(objval[0]);

	SetTranslation(objval[1],objval[2],objval[3]);
	SetRotation(objval[4],objval[5],objval[6]);
	SetScale(objval[7],objval[8],objval[9]);
}

void Sphere::printGeometricObject() {
	std::cout << "Type: " << GetType() << "\t" << "Name: " << GetName() << std::endl;
	std::cout << "Radius: " << get_radius() << std::endl;

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

void Sphere::writeGeometricObjectToFile(std::ofstream& outfile) {
	outfile << GetType() << " " << GetName() << std::endl;
	outfile << get_radius() << std::endl;
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

void Sphere::DrawList() {
	GLUquadricObj *sphereObj;

	//get translations
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	//get rotations
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	//get scale
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);

	glNewList(SPHERE, GL_COMPILE);
		glColor3fv(vBLUE);
		//glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vBLUE );
		 glPushMatrix ();
			//Rotations
			glRotatef ((GLfloat)Rx, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
			glRotatef ((GLfloat)Ry, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
			glRotatef ((GLfloat)Rz, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)1.0);
			//Scaling
			glScalef ((GLfloat)Sx,(GLfloat)Sy,(GLfloat)Sz);
			//Translations
			glTranslatef ((GLfloat)Tx, (GLfloat)Ty, (GLfloat)Tz);
			sphereObj = gluNewQuadric ();
			gluQuadricDrawStyle (sphereObj, GLU_LINE);
			gluSphere (sphereObj, mRadius, 14, 20);
		glPopMatrix ();
	glEndList();
}
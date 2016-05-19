#include "cylinder.hpp"

Cylinder::Cylinder() {
	SetType("CYLINDER");
	SetID(CYLINDER);
	mHeight=0;
	mRadius=0;
}

void Cylinder::set_height(double h) {
	if(h >= 0){
		mHeight=h;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Height must be positive" << std::endl;
		exit(1);
	}
}

void Cylinder::set_radius(double r) {
	if(r >= 0){
		mRadius=r;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Radius must be positive" << std::endl;
		exit(1);
	}
}

double Cylinder::get_height() {
	return(mHeight);
}

double Cylinder::get_radius() {
	return(mRadius);
}

void Cylinder::readGeometricObject(const int start,const std::vector<std::string> tokens) {
	//Number of strings associated with CYLINDER
	int size=13;

	//Check to see if enough data has been written to completely define CYLINDER
	if(tokens.size()<(start+size)) {
		std::cout << "Error in TYPE " << GetType() << ": File is not formatted correctly" << std::endl;
	    exit(1);
	}
	//Store CONE name
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

	set_height(objval[0]);
    set_radius(objval[1]);

	SetTranslation(objval[2],objval[3],objval[4]);
	SetRotation(objval[5],objval[6],objval[7]);
	SetScale(objval[8],objval[9],objval[10]);
}

void Cylinder::printGeometricObject() {
	std::cout << "Type: " << GetType() << "\t" << "Name: " << GetName() << std::endl;
	std::cout << "Height: " << get_height() << "\t" << "Radius: " << get_radius() << std::endl;


	std::cout << std::endl;
	std::cout << "Translations: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	std::cout << Tx << "\t" << Ty << "\t" << Tz << std::endl;


	std::cout << std::endl;
	std::cout << "Rotations: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	std::cout << Rx << "\t" << Ry << "\t" << Rz << std::endl;


	std::cout << std::endl;
	std::cout << "Scale: " << std::endl;
	std::cout << "x\t" << "y\t" << "z\t" << std::endl;
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);
	std::cout << Sx << "\t" << Sy << "\t" << Sz << std::endl;
}

void Cylinder::writeGeometricObjectToFile(std::ofstream& outfile) {
	outfile << GetType() << " " << GetName() << std::endl;
	outfile << get_height() << "\t" << get_radius() << std::endl;

	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	outfile << Tx << "," << Ty << "," << Tz << std::endl;


	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	outfile << Rx << "," << Ry << "," << Rz << std::endl;

	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);
	outfile << Sx << "," << Sy << "," << Sz << std::endl;

	outfile << std::endl;
}

void Cylinder::DrawList() {
	GLUquadricObj *cylinderObj;

	//get translations
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	//get rotations
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	//get scale
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);

	glNewList(CYLINDER, GL_COMPILE);
	    glColor3fv(vBLUE);
        //glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vRED );
        glPushMatrix ();
		    //Rotations
            //glRotatef ((GLfloat)Rx, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
		    //glRotatef ((GLfloat)Ry, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
		    //glRotatef ((GLfloat)Rz, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)1.0);
		    //Scaling
		    //glScalef ((GLfloat)Sx,(GLfloat)Sy,(GLfloat)Sz);
		    //Translations
		    //glTranslatef ((GLfloat)Tx, (GLfloat)Ty, (GLfloat)Tz);
            cylinderObj = gluNewQuadric ();
            gluQuadricDrawStyle (cylinderObj, GLU_FILL);
            gluQuadricNormals (cylinderObj, GLU_SMOOTH);
            gluCylinder(cylinderObj, mRadius, mRadius, mHeight, 15, 10);
		glPopMatrix ();
    glEndList();
}
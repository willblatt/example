#include "box.hpp"

Box::Box() {
	SetType("BOX");
	SetID(BOX);
	mHeight=0;
	mWidth=0;
	mLength=0;
}

void Box::set_height(double h) {
	if(h >= 0) {
		mHeight=h;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Height must be positive" << std::endl;
		exit(1);
	}
}

void Box::set_width(double w) {
	if(w >= 0) {
		mWidth=w;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Width must be positive" << std::endl;
		exit(1);
	}
}

void Box::set_length(double l) {
	if(l >= 0) {
		mLength=l;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Length must be positive" << std::endl;
		exit(1);
	}
}

double Box::get_height() {
	return(mHeight);
}

double Box::get_width() {
	return(mWidth);
}

double Box::get_length() {
	return(mLength);
}

void Box::readGeometricObject(const int start,const std::vector<std::string> tokens) {
	int size=14; //Number of strings associated with BOX

	//Check to see if enough data has been written to completely define BOX
	if(tokens.size()<(start+size)) {
		std::cout << "Error in TYPE " << GetType() << ": File is not formatted correctly" << std::endl;
	    exit(1);
	}
	//Store BOX name
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
    set_width(objval[1]);
	set_length(objval[2]);

	SetTranslation(objval[3],objval[4],objval[5]);
	SetRotation(objval[6],objval[7],objval[8]);
	SetScale(objval[9],objval[10],objval[11]);
}

void Box::printGeometricObject() {
	std::cout << "Type: " << GetType() << "\t" << "Name: " << GetName() << std::endl;
	std::cout << "Height: " << get_height() << "\t" << "Width: " << get_width() << "\t" << "Length: " << get_length() << std::endl;


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

void Box::writeGeometricObjectToFile(std::ofstream& outfile) {
	outfile << GetType() << " " << GetName() << std::endl;
	outfile << get_height() << "\t" << get_width() << "\t" << get_length() << std::endl;

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

void Box::DrawList() {

	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);

	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);

	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);

	glNewList(BOX, GL_COMPILE);
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
			glColor3fv(vGREEN);
			glBegin(GL_POLYGON);
				glVertex3f(0,0,0);
				glVertex3f(mLength,0,0);
				glVertex3f(mLength,0,mHeight);
				glVertex3f(0,0,mHeight);
			glEnd();
			//Rear Face
			glColor3fv(vYELLOW);
			glBegin(GL_POLYGON);
				glVertex3f(0,mWidth,0);
				glVertex3f(mLength,mWidth,0);
				glVertex3f(mLength,mWidth,mHeight);
				glVertex3f(0,mWidth,mHeight);
			glEnd();
			//Right Face
			glColor3fv(vRED);
			glBegin(GL_POLYGON);
				glVertex3f(mLength,0,0);
				glVertex3f(mLength,mWidth,0);
				glVertex3f(mLength,mWidth,mHeight);
				glVertex3f(mLength,0,mHeight);
			glEnd();
			//Left Face
			glColor3fv(vBLUE);
			glBegin(GL_POLYGON);
				glVertex3f(0,0,0);
				glVertex3f(0,mWidth,0);
				glVertex3f(0,mWidth,mHeight);
				glVertex3f(0,0,mHeight);
			glEnd();
			//Top Face
			glColor3fv(vCYAN);
			glBegin(GL_POLYGON);
				glVertex3f(0,0,mHeight);
				glVertex3f(mLength,0,mHeight);
				glVertex3f(mLength,mWidth,mHeight);
				glVertex3f(0,mWidth,mHeight);
			glEnd();
			//Bottom Face
			glColor3fv(vMAGENTA);
			glBegin(GL_POLYGON);
				glVertex3f(0,0,0);
				glVertex3f(mLength,0,0);
				glVertex3f(mLength,mWidth,0);
				glVertex3f(0,mWidth,0);
			glEnd();
		glPopMatrix ();
	glEndList();
}
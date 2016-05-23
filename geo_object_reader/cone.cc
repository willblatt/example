#include "cone.h"

namespace geom {

Cone::Cone() {
	height_ = radius_ = 0;
}
void Cone::SetHeight(double height) {
	if (height >= 0) {
		height_ = height;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Height must be positive" << std::endl;
		exit(1);
	}
}
double Cone::GetHeight() {
	return height_;
}
double Cone::GetRadius() {
	return radius_;
}
void Cone::SetRadius(double radius) {
	if (radius >= 0) {
		radius_ = radius;
	} else {
		std::cout << "Error in TYPE " << GetType() << ": Radius must be positive" << std::endl;
		exit(1);
	}
}
double Cone::GetVolume() {
	double radius = GetRadius();
	double height = GetHeight();
	double pi = 3.14159265359;

	double volume = pi* pow(radius, 3) * height / 3.0;

	return 0.0;
}
int Cone::Read(const std::vector<std::string> data) {
	//Number of strings associated with CONE
	size_t size = 13;

	//Check to see if enough data has been written to completely define CONE
	if (data.size() < size) {
		std::cout << GetType() << " Error: File is not formatted correctly" << std::endl;

		return 1;
	}

	SetName(data[1]);

	std::vector<double> objvals;

	double temp;
	for (size_t i=2, ilen=size; i<ilen; ++i) {
		// converts the c-string to the type of variable listed and stores its value in the variable name
		if (!(std::stringstream(data[i]) >> temp)) {
			std::cout << "Error " << data[i] << std::endl;
			return 1;
		}
		objvals.push_back(temp);
	}

	SetHeight(objvals[0]);
	SetRadius(objvals[1]);

	SetTranslation(objvals[2], objvals[3], objvals[4]);
	SetRotation(objvals[5], objvals[6], objvals[7]);
	SetScale(objvals[8], objvals[9], objvals[10]);

	return 0;
}
int Cone::Write(std::ofstream& ofile) {
	ofile << GetType() << " " << GetName() << std::endl;
	ofile << GetHeight() << "\t" << GetRadius() << std::endl;
	//get translations
	double Tx, Ty, Tz;
	GetTranslation(Tx, Ty, Tz);
	ofile << Tx << "," << Ty << "," << Tz << std::endl;

	//get rotations
	double Rx, Ry, Rz;
	GetRotation(Rx, Ry, Rz);
	ofile << Rx << "," << Ry << "," << Rz << std::endl;

	//get scale
	double Sx, Sy, Sz;
	GetScale(Sx, Sy, Sz);
	ofile << Sx << "," << Sy << "," << Sz << std::endl;

	ofile << std::endl;

	return 0;
}
void Cone::DrawList() {

	GLUquadricObj *obj;

	//get translations
	double Tx,Ty,Tz;
	GetTranslation(Tx,Ty,Tz);
	//get rotations
	double Rx,Ry,Rz;
	GetRotation(Rx,Ry,Rz);
	//get scale
	double Sx,Sy,Sz;
	GetScale(Sx,Sy,Sz);

	glBegin(CONE); 
   
	glColor3fv(vRED);
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vRED );
    glPushMatrix (); 
		    
	//Rotations
    glRotatef ((GLfloat)Rx, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
	glRotatef ((GLfloat)Ry, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0); 
	glRotatef ((GLfloat)Rz, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)1.0); 
		    
	//Scaling
	glScalef ((GLfloat)Sx,(GLfloat)Sy,(GLfloat)Sz);

	//Translations
	glTranslatef ((GLfloat)Tx, (GLfloat)Ty, (GLfloat)Tz); 

	glTranslatef(-1.0f, -1.0f, -1.0f);

	obj = gluNewQuadric ();
    gluQuadricDrawStyle (obj, GLU_FILL);
    gluQuadricNormals (obj, GLU_SMOOTH);
    gluCylinder(obj, GetRadius(), 0.0, GetHeight(), 15, 10);
		
	glPopMatrix (); 
    
	glEnd();
}

} // namespace geom

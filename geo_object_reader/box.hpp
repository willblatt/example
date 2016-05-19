#ifndef BOX_HPP
#define BOX_HPP

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "geomObj.h"

class Box : public GeometricObject {
public:
	Box();
	~Box(){}

	void set_height(double h);
	void set_width(double r);
	void set_length(double r);

	double get_height(void);
	double get_width(void);
	double get_length(void);

	virtual void readGeometricObject(const int start,const std::vector<std::string> tokens);
	virtual void writeGeometricObjectToFile(std::ofstream& outfile);
	virtual void printGeometricObject(void);
	virtual void DrawList();

private:
	double mHeight;
	double mWidth;
	double mLength;
};

#endif
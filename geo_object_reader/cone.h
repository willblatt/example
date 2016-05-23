#ifndef CONE_H_
#define CONE_H_

#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "geom_obj.h"

namespace geom {

class Cone : public GeomObj{

public:
	Cone();		
	virtual int Write(std::ofstream& ofile);
	virtual int Read(const std::vector<std::string> data);
	virtual double GetVolume();
	virtual void DrawList();

	double Cone::GetHeight();
	void Cone::SetHeight(double height);
	double Cone::GetRadius();
	void Cone::SetRadius(double radius);


private:
	std::string name_;
	double height_;
	double radius_;
};

} // namespace geom
#endif
#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "GeomObj.hpp"


class Cylinder : public GeomObj {
	public:
		Cylinder( int& index, std::string* outPutFile );

		virtual void print();
		virtual void write();
		virtual std::string getName(){return name;};

		void read( const std::vector<std::string>& t, int& index );

	private:
		std::string name;
		float height;
		float radius;
		std::string* mOutPutFile;
		double *s;
};

#endif
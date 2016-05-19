#ifndef OBJFILEREADER_HPP
#define OBJFILEREADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "tokenize.hpp"
#include "geomObj.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "polygon.hpp"
#include "linkList.hpp"

#define GEOMETRICOBJINFILE "geoobjects.txt"

LinkedList* GeoObjReader();

#endif
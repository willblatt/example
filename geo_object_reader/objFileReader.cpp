#include "ObjFileReader.h"

LinkedList* GeoObjReader() {
	std::cout << "---Geometric Objects File Reader---" << std::endl;
	std::string filename;
	filename=GEOMOBJECTINFILE;
	std::ifstream infile (filename.c_str());
    if(infile==NULL || filename.length()==0) {
		std::cout << "Error: Geometric Object File not found" << std::endl;
		exit(1);
	}

    std::vector<std::string> tokens;
	std::string line;

	do {
        std::getline(infile, line, '\n');

		tokenize(line, tokens);
		if(infile.eof()==1) {
			std::cout << "Error: File is not formatted correctly or is empty" << std::endl;
            exit(1);
		}
	} while(tokens.size()<=0);


	while (std::getline(infile, line, '\n')) {
		tokenize(line, tokens);
	}

	delete infile;

	LinkedList* objlist = new LinkedList();
	std::cout << "Reading Objects ... " << std::endl;

	for(int i=0;i<tokens.size();i++) {
		if(tokens[i]=="CONE") {
			Cone* obj= new Cone();
			obj->readGeometricObject(i,tokens);
			std::cout << obj->GetType() << std::endl;
			objlist->push_back(obj);
		}
		if(tokens[i]=="CYLINDER") {
			Cylinder* obj= new Cylinder();
			obj->readGeometricObject(i,tokens);
			std::cout << obj->GetType() << std::endl;
			objlist->push_back(obj);
		}
		if(tokens[i]=="SPHERE") {
			Sphere* obj= new Sphere();
			obj->readGeometricObject(i,tokens);
			std::cout << obj->GetType() << std::endl;
			objlist->push_back(obj);
		}

		if(tokens[i]=="BOX") {
			Box* obj= new Box();
			obj->readGeometricObject(i,tokens);
			std::cout << obj->GetType() << std::endl;
			objlist->push_back(obj);
		}
		if(tokens[i]=="POLYGON") {
			Polygonal* obj= new Polygonal();
			obj->readGeometricObject(i,tokens);
			std::cout << obj->GetType() << std::endl;
			objlist->push_back(obj);
		}
	}

	std::cout << "Object file read successfully" << std::endl;

	return(objlist);
}
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

#include "geom_obj_list.h"
#include "tokenize.h"



void render(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 4.0, 0.0, 4.0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	geom::GeomObjList geom_objs;
	geom_objs.Read("geomobjects.txt");

	for (geom::GeomObj* curr = geom_objs.Begin(); curr == geom_objs.End(); curr = curr->GetNext()) {
		std::cout << curr->GetName() << " " << curr->GetVolume() << std::endl;
		curr->DrawList();
	}

	glutSwapBuffers();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My OpenGL program");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}
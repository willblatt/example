#include <fstream>
#include <strstream>
#include <iostream>

#include <afxdlgs.h>

#include <NXOpen/Session.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>

#include <uf.h>
#include <uf_ui.h>
#include <uf_exit.h>

using namespace NXOpen;
using namespace std;

int GetFname(char *prompt, char *fname){
    int res;
    char filter[UF_CFI_MAX_PATH_NAME_SIZE] = "*.txt";
    UF_UI_create_filebox(prompt,
    					 "Select point data file",
    					 filter,
    					 NULL,
    					 fname,
    					 &res);
    return res;
}

// User function entry point
extern DllExport void ufusr(char *parm, int *retCode, int rlen){
	// Initiate command prompt
	FILE *fp;
	fp = freopen("conout$", "w", stdout);

	UF_initialize();

	NXOpen::Session *session = NXOpen::Session::GetSession();
	NXOpen::Part *part = session->Parts()->Work();

	if(part == NULL) {
		part = session->Parts()->NewDisplay("file2Points", NXOpen::Part::UnitsMillimeters);
	}

	char fname[UF_CFI_MAX_PATH_NAME_SIZE];
	int res = GetFname("Select file that contains the point coordinate data", fname);

	if (res == UF_UI_OK) {
		ifstream file1;
		file1.open(fname);

		if (!file1.is_open()){
			cout<<"Could not open file\n";
		} else{
			double x,y,z;
			char c;

			while (!file1.eof()) {
				file1 >> x >> c >> y >> c >> z;

				if (!file1) {
					cout << "File format error:\n"
					cout << "The input file does not have the expected format\n";
					break;
				}

				NXOpen::Point3d point3d11(x,y,z);
				NXOpen::Point *point1;
				point1 = workPart->Points()->CreatePoint(point3d11);

				// The point is invisible when initially created
				point1->SetVisibility(NXOpen::SmartObject::VisibilityOptionVisible);
				file1 >> c;

				if (!file1.eof()) {
					file1.unget();
				}
			}

			file1.close();
			file1.clear();
		}

		UF_terminate();
	}
}

// Unload application
extern int ufusr_ask_unload(void){
    return UF_UNLOAD_IMMEDIATELY;
}
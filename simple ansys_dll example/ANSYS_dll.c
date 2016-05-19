#include "cAnsInterface.h"
#include "cAnsQuery.h"

int extfnc(char* uecmd){
	float max;
	float min;
    char strrtn[32];
    int i, itype;

	char* cmd = {"finish"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"/filname,$static_hot,1"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"/solution"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"ematwrite,yes"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"antype,static"};
	i = cAnsSendCommand(cmd);

	// Includes large-deflection effects in a static or full transient analysis
	char* cmd = {"nlgeom,on"};
	i = cAnsSendCommand(cmd);

	// activates stress stiffness effects in a nonlinear analysis,
	//   this used to be "pstres,on", but according to ANSYS help for v14
	//   you should use "sstif,on" instead for older elem types like
	//   SOLID45/95
	char* cmd = {"sstif,on"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"allsel"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"autots,on"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"lnsrch,on"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"neqit,25"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"nsub,1,3000,0"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"/nopr"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"solve"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"save"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"finish"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"allsel,all"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"/post1"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"nsort,s,eqv"};
	i = cAnsSendCommand(cmd);

	char* cmd = {"sort,,max"};
	i = cAnsGetValue(cmd,&max,strrtn,&itype);

	char* cmd = {"sort,,min"};
	i = cAnsGetValue(cmd,&min,strrtn,&itype);

	cAns_printf("Max seqv = %g\n",max);
	cAns_printf("Min seqv = %g\n",max);

	return(1);
}
#include <uf.h>
#include <uf_modl.h>
#include <uf_part.h>
#include <uf_obj.h>
#include <uf_sket.h>
#include <uf_curve.h>
#include <uf_sket_types.h>
#include <uf_ui.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#define WINDOW
#define NUM_PTS 5
#define UF_CALL(X) (report( __FILE__, __LINE__, #X, (X)))

static int report(char *file, int line, char *call, int irc){
	if (irc){
		char messg[133];
		printf("    %s, line %d:  %s\n", file, line, call);
		(UF_get_fail_message(irc, messg)) ?
			printf("   returned a %d\n", irc) :
		printf("        returned error %d:  %s\n", irc, messg);
	}
	return(irc);
}

struct sketch_info {
	char* sketch_name;
	double offset;
	double* s1_pts;//[3*NUM_PTS];
	double* s2_pts;//[3*NUM_PTS];
	double a1_2nd_pt[3];
	double a2_2nd_pt[3];
	tag_t s1_tag,s2_tag,a1_tag,a2_tag;
};

tag_t create_spline(sketch_info* mySketch_info, int side) {
	int s_deg = 3,s_per = 0,s_num_pts = NUM_PTS;
	UF_CURVE_pt_slope_crvatr_t s_pt_data[NUM_PTS];
	double s_params[NUM_PTS]={0.00,0.1,0.2,0.3,0.4};
	int s_save_def_data = 1;
	if(side == 1) {
		for(int i=0;i<NUM_PTS;i++) {
			s_pt_data[i].point[0] = mySketch_info->s1_pts[3*i];
			s_pt_data[i].point[1] = mySketch_info->s1_pts[3*i+1];
			s_pt_data[i].point[2] = mySketch_info->s1_pts[3*i+2];
			s_pt_data[i].slope_type = UF_CURVE_SLOPE_AUTO;
			s_pt_data[i].crvatr_type = UF_CURVE_CRVATR_NONE;
		}
	} else {
		for(int i=0;i<NUM_PTS;i++) {
			s_pt_data[i].point[0] = mySketch_info->s2_pts[3*i];
			s_pt_data[i].point[1] = mySketch_info->s2_pts[3*i+1];
			s_pt_data[i].point[2] = mySketch_info->s2_pts[3*i+2];
			s_pt_data[i].slope_type = UF_CURVE_SLOPE_AUTO;
			s_pt_data[i].crvatr_type = UF_CURVE_CRVATR_NONE;
		}
	}

	tag_t spline_tag = NULL_TAG;
	UF_CALL(UF_CURVE_create_spline_thru_pts(s_deg,s_per,s_num_pts,s_pt_data,s_params,s_save_def_data,&spline_tag));/* Create B-spline curve */
	return spline_tag;
}
tag_t create_arc(sketch_info* mySketch_info, int side) {
	tag_t arc_tag = NULL_TAG;
	if(side == 1){
		double a_first_point[3] = {
			mySketch_info->s1_pts[0],
			mySketch_info->s1_pts[1],
			mySketch_info->s1_pts[2]};

		double a_third_point[3] = {
			mySketch_info->s2_pts[0],
			mySketch_info->s2_pts[1],
			mySketch_info->s2_pts[2]};
			UF_CURVE_create_arc_thru_3pts(1,a_first_point,mySketch_info->a1_2nd_pt,a_third_point,&arc_tag);
	} else{
		double a_first_point[3]  = {
			mySketch_info->s1_pts[12],
			mySketch_info->s1_pts[13],
			mySketch_info->s1_pts[14]};
			double a_third_point[3] = {
				mySketch_info->s2_pts[12],
				mySketch_info->s2_pts[13],
				mySketch_info->s2_pts[14]};
			UF_CURVE_create_arc_thru_3pts(1,a_first_point,mySketch_info->a2_2nd_pt,a_third_point,&arc_tag);
	}
	return arc_tag;
}
tag_t create_constr(tag_t sketch_tag,int vertex_index1,int vertex_index2,double help_point[3],tag_t spline_tag,tag_t arc_tag) {
	tag_t con_geom_tag = NULL_TAG;
	UF_SKET_con_geom_t con_geoms[2];
	con_geoms[0].geom_tag = spline_tag;
	con_geoms[0].vertex_type = UF_SKET_start_vertex;
	con_geoms[0].vertex_index = vertex_index2;
	con_geoms[0].use_help = UF_SKET_use_help_pt;
	con_geoms[0].help_point[0]=help_point[0];
	con_geoms[0].help_point[1]=help_point[1];
	con_geoms[0].help_point[2]=help_point[2];
	con_geoms[1].geom_tag = arc_tag;
	con_geoms[1].vertex_type = UF_SKET_start_vertex;
	con_geoms[1].vertex_index = vertex_index1;
	con_geoms[1].use_help = UF_SKET_use_help_pt;
	con_geoms[1].help_point[0]=help_point[0];
	con_geoms[1].help_point[1]=help_point[1];
	con_geoms[1].help_point[2]=help_point[2];
	UF_SKET_create_geometric_constraint(sketch_tag,UF_SKET_tangent,2,con_geoms,&con_geom_tag);
	return con_geom_tag;
}
tag_t create_sketch(sketch_info* mySketch_info) {
	tag_t sketch_tag = NULL_TAG;
	double datum[9] = {1,0,0,0,1,0,0,0,mySketch_info->offset};
	UF_SKET_initialize_sketch(mySketch_info->sketch_name,&sketch_tag);
	UF_SKET_create_sketch(mySketch_info->sketch_name,2,datum,NULL,NULL,NULL,&sketch_tag);
	tag_t spline1_tag	= create_spline(mySketch_info,1);
	tag_t spline2_tag	= create_spline(mySketch_info,2);
	tag_t arc1_tag		= create_arc(mySketch_info,1);
	tag_t arc2_tag		= create_arc(mySketch_info,2);
	mySketch_info->a1_tag = arc1_tag;
	mySketch_info->a2_tag = arc2_tag;
	mySketch_info->s1_tag = spline1_tag;
	mySketch_info->s2_tag = spline2_tag;
	UF_SKET_add_objects(sketch_tag,1,&spline1_tag);
	UF_SKET_add_objects(sketch_tag,1,&spline2_tag);
	UF_SKET_add_objects(sketch_tag,1,&arc1_tag);
	UF_SKET_add_objects(sketch_tag,1,&arc2_tag);
	double help_point1[3] = {
		mySketch_info->s1_pts[0],
		mySketch_info->s1_pts[1],
		mySketch_info->s1_pts[2]};
	double help_point2[3] = {
		mySketch_info->s1_pts[12],
		mySketch_info->s1_pts[13],
		mySketch_info->s1_pts[14]};
	double help_point3[3] = {
		mySketch_info->s2_pts[12],
		mySketch_info->s2_pts[13],
		mySketch_info->s2_pts[14]};
	double help_point4[3] = {
		mySketch_info->s2_pts[0],
		mySketch_info->s2_pts[1],
		mySketch_info->s2_pts[2]};
	tag_t con_geom1 = create_constr(sketch_tag,1,1,help_point1,spline1_tag,arc1_tag);
	tag_t con_geom2 = create_constr(sketch_tag,1,5,help_point2,spline1_tag,arc2_tag);
	tag_t con_geom3 = create_constr(sketch_tag,3,5,help_point3,spline2_tag,arc2_tag);
	tag_t con_geom4 = create_constr(sketch_tag,3,1,help_point4,spline2_tag,arc1_tag);
	UF_SKET_update_sketch(sketch_tag);
	UF_SKET_terminate_sketch();
	return sketch_tag;
}

int do_ug_open() {
	UF_PART_close_all();
	char file_name[257];
	int response;
	strcpy(file_name,"default");
	int units=UF_PART_ENGLISH;
	UF_CALL(UF_UI_ask_create_part_filename(file_name, &units, &response));
	tag_t part_tag;
	UF_PART_new(file_name, units, &part_tag);
/*************************Sketch_1***************************/
	sketch_info sketch_1;
	sketch_1.sketch_name = "one";
	sketch_1.offset = 0;
	double s11_pts[3*NUM_PTS] = {
		-1.99816625669,  2.47948532707,  sketch_1.offset,
		-1.12252687144,  2.66045902344,  sketch_1.offset,
		0.16062296761,  2.37790040419,  sketch_1.offset,
		1.52474457117,  1.45706568342,  sketch_1.offset,
		2.70403410800, -0.10238241470,  sketch_1.offset};
	double s12_pts[3*NUM_PTS] = {
		-1.72606230823,  1.69737673782,  sketch_1.offset,
		-0.71233035458,  1.69004437308,  sketch_1.offset,
		0.37640502559,  1.43504786752,  sketch_1.offset,
		1.28083975886,  0.80805137449,  sketch_1.offset,
		2.39035661944, -0.32679861877,  sketch_1.offset};
	sketch_1.s1_pts = s11_pts;
	sketch_1.s2_pts = s12_pts;
	//sketch_1.s1_pts[0]    = -1.99816625669;
	//sketch_1.s1_pts[1]    = 2.47948532707;
	//sketch_1.s1_pts[2] 	  = sketch_1.offset;
	//sketch_1.s1_pts[3] 	  = -1.12252687144;
	//sketch_1.s1_pts[4] 	  = 2.66045902344;
	//sketch_1.s1_pts[5] 	  = sketch_1.offset;
	//sketch_1.s1_pts[6] 	  = 0.16062296761;
	//sketch_1.s1_pts[7] 	  = 2.37790040419;
	//sketch_1.s1_pts[8] 	  = sketch_1.offset;
	//sketch_1.s1_pts[9] 	  = 1.52474457117;
	//sketch_1.s1_pts[10]	  = 1.45706568342;
	//sketch_1.s1_pts[11]	  = sketch_1.offset;
	//sketch_1.s1_pts[12]	  = 2.70403410800;
	//sketch_1.s1_pts[13]	  = -0.10238241470;
	//sketch_1.s1_pts[14]	  = sketch_1.offset;
	//sketch_1.s2_pts[0] 	  = -1.72606230823;
	//sketch_1.s2_pts[1] 	  = 1.69737673782;
	//sketch_1.s2_pts[2] 	  = sketch_1.offset;
	//sketch_1.s2_pts[3] 	  =  -0.71233035458;
	//sketch_1.s2_pts[4] 	  = 1.69004437308;
	//sketch_1.s2_pts[5] 	  = sketch_1.offset;
	//sketch_1.s2_pts[6] 	  = 0.37640502559;
	//sketch_1.s2_pts[7] 	  = 1.43504786752;
	//sketch_1.s2_pts[8] 	  = sketch_1.offset;
	//sketch_1.s2_pts[9]	  = 1.28083975886;
	//sketch_1.s2_pts[10]	  = 0.80805137449;
	//sketch_1.s2_pts[11]   = sketch_1.offset;
	//sketch_1.s2_pts[12]   = 2.39035661944;
	//sketch_1.s2_pts[13]   = -0.32679861877;
	//sketch_1.s2_pts[14]   = sketch_1.offset;
	sketch_1.a1_2nd_pt[0] = -2.17664692145;
	sketch_1.a1_2nd_pt[1] = 1.97900176117;
	sketch_1.a1_2nd_pt[2] = sketch_1.offset;
	sketch_1.a2_2nd_pt[0] = 2.64906156685;
	sketch_1.a2_2nd_pt[1] = -0.35697388384;
	sketch_1.a2_2nd_pt[2] = sketch_1.offset;
	tag_t sketch1_tag	  = create_sketch(&sketch_1);
/*************************Sketch_2***************************/
	sketch_info sketch_2;
	sketch_2.sketch_name = "two";
	sketch_2.offset = 2;
	double s21_pts[3*NUM_PTS] = {
		-1.97073056221,  2.35229256058,  sketch_2.offset,
		-1.09531475222,  2.54390831549,  sketch_2.offset,
		0.18467049001,  2.25978372112,  sketch_2.offset,
		1.56455000479,  1.34645912635,  sketch_2.offset,
		2.54872769994, -0.11366285731,  sketch_2.offset};
	double s22_pts[3*NUM_PTS] = {
		-1.58057367785,  1.62896803083,  sketch_2.offset,
		-0.90741583482,  1.66148114889,  sketch_2.offset,
		0.29424816099,  1.39229848354,  sketch_2.offset,
		1.18029154755,  0.74734461301,  sketch_2.offset,
		2.22071541523, -0.32429985126,  sketch_2.offset};
	sketch_2.s1_pts = s21_pts;
	sketch_2.s2_pts = s22_pts;//sketch_2.s1_pts[0] = -1.97073056221;
	//sketch_2.s1_pts[1] = 2.35229256058;
	//sketch_2.s1_pts[2] = sketch_2.offset;
	//sketch_2.s1_pts[3] = -1.09531475222;
	//sketch_2.s1_pts[4] = 2.54390831549;
	//sketch_2.s1_pts[5] = sketch_2.offset;
	//sketch_2.s1_pts[6] = 0.18467049001;
	//sketch_2.s1_pts[7] = 2.25978372112;
	//sketch_2.s1_pts[8] = sketch_2.offset;
	//sketch_2.s1_pts[9] = 1.56455000479;
	//sketch_2.s1_pts[10] = 1.34645912635;
	//sketch_2.s1_pts[11] = sketch_2.offset;
	//sketch_2.s1_pts[12] = 2.54872769994;
	//sketch_2.s1_pts[13] = -0.11366285731;
	//sketch_2.s1_pts[14] = sketch_2.offset;
	//sketch_2.s2_pts[0] = -1.58057367785;
	//sketch_2.s2_pts[1] = 1.62896803083;
	//sketch_2.s2_pts[2] = sketch_2.offset;
	//sketch_2.s2_pts[3] = -0.90741583482;
	//sketch_2.s2_pts[4] = 1.66148114889;
	//sketch_2.s2_pts[5] = sketch_2.offset;
	//sketch_2.s2_pts[6] = 0.29424816099;
	//sketch_2.s2_pts[7] = 1.39229848354;
	//sketch_2.s2_pts[8] = sketch_2.offset;
	//sketch_2.s2_pts[9] = 1.18029154755;
	//sketch_2.s2_pts[10] = 0.74734461301;
	//sketch_2.s2_pts[11] = sketch_2.offset;
	//sketch_2.s2_pts[12] = 2.22071541523;
	//sketch_2.s2_pts[13] = -0.32429985126;
	//sketch_2.s2_pts[14] = sketch_2.offset;
	sketch_2.a1_2nd_pt[0] = -2.11174425458;
	sketch_2.a1_2nd_pt[1] = 1.80934422758;
	sketch_2.a1_2nd_pt[2] = sketch_2.offset;
	sketch_2.a2_2nd_pt[0] = 2.47577780250;
	sketch_2.a2_2nd_pt[1] = -0.36077775182;
	sketch_2.a2_2nd_pt[2] = sketch_2.offset;
	tag_t sketch2_tag = create_sketch(&sketch_2);
/*************************Sketch_3***************************/
	sketch_info sketch_3;
	sketch_3.sketch_name = "three";
	sketch_3.offset = 4;
	double s31_pts[3*NUM_PTS] = {
		-1.85389842079,  2.24246294126,  sketch_3.offset,
		-1.25003945626,  2.33094150826,  sketch_3.offset,
		-0.06659900596,  2.17148197127,  sketch_3.offset,
		1.17875567937,  1.47149616865,  sketch_3.offset,
		2.28664451632, 0.06699432596,  sketch_3.offset};
	double s32_pts[3*NUM_PTS] = {
		-1.55976416989,  1.51732034204,  sketch_3.offset,
		-0.74821811001,  1.52414160076,  sketch_3.offset,
		0.33969441882,  1.30517095861,  sketch_3.offset,
		1.22949144572,  0.63064194903,  sketch_3.offset,
		1.99351405244, -0.14233051957,  sketch_3.offset};
	sketch_3.s1_pts = s31_pts;
	sketch_3.s2_pts = s32_pts;

	//sketch_3.s1_pts[0] = -1.85389842079;
	//sketch_3.s1_pts[1] = 2.24246294126;
	//sketch_3.s1_pts[2] = sketch_3.offset;
	//sketch_3.s1_pts[3] = -1.25003945626;
	//sketch_3.s1_pts[4] = 2.33094150826;
	//sketch_3.s1_pts[5] = sketch_3.offset;
	//sketch_3.s1_pts[6] = -0.06659900596;
	//sketch_3.s1_pts[7] = 2.17148197127;
	//sketch_3.s1_pts[8] = sketch_3.offset;
	//sketch_3.s1_pts[9] = 1.17875567937;
	//sketch_3.s1_pts[10] = 1.47149616865;
	//sketch_3.s1_pts[11] = sketch_3.offset;
	//sketch_3.s1_pts[12] = 2.28664451632;
	//sketch_3.s1_pts[13] = 0.06699432596;
	//sketch_3.s1_pts[14] = sketch_3.offset;
	//sketch_3.s2_pts[0] = -1.55976416989;
	//sketch_3.s2_pts[1] = 1.51732034204;
	//sketch_3.s2_pts[2] = sketch_3.offset;
	//sketch_3.s2_pts[3] = -0.74821811001;
	//sketch_3.s2_pts[4] = 1.52414160076;
	//sketch_3.s2_pts[5] = sketch_3.offset;
	//sketch_3.s2_pts[6] = 0.33969441882;
	//sketch_3.s2_pts[7] = 1.30517095861;
	//sketch_3.s2_pts[8] = sketch_3.offset;
	//sketch_3.s2_pts[9] = 1.22949144572;
	//sketch_3.s2_pts[10] = 0.63064194903;
	//sketch_3.s2_pts[11] = sketch_3.offset;
	//sketch_3.s2_pts[12] = 1.99351405244;
	//sketch_3.s2_pts[13] = -0.14233051957;
	//sketch_3.s2_pts[14] = sketch_3.offset;
	sketch_3.a1_2nd_pt[0] = -2.00044981454;
	sketch_3.a1_2nd_pt[1] = 1.76079332459;
	sketch_3.a1_2nd_pt[2] = sketch_3.offset;
	sketch_3.a2_2nd_pt[0] = 2.23610984134;
	sketch_3.a2_2nd_pt[1] = -0.17214559582;
	sketch_3.a2_2nd_pt[2] = sketch_3.offset;
	tag_t sketch3_tag = create_sketch(&sketch_3);
/*************************Sketch_4***************************/
	sketch_info sketch_4;
	sketch_4.sketch_name = "four";
	sketch_4.offset = 6;
	double s41_pts[3*NUM_PTS] = {
		-1.76340175408,  1.94652442505,  sketch_4.offset,
		-1.13166297582,  2.18881332568,  sketch_4.offset,
		0.12608563158,  1.94290990106,  sketch_4.offset,
		1.16744210157,  1.19411503323,  sketch_4.offset,
		1.99331371687,  0.11077742105,  sketch_4.offset};
	double s42_pts[3*NUM_PTS] = {
		-1.44532304712,  1.41284156639,  sketch_4.offset,
		-0.69560300522,  1.39886082596,  sketch_4.offset,
		0.19653707120,  1.24230378988,  sketch_4.offset,
		0.86548954491,  0.77463529360,  sketch_4.offset,
		1.80839988015, -0.03765333922,  sketch_4.offset};
	sketch_4.s1_pts = s41_pts;
	sketch_4.s2_pts = s42_pts;

	//sketch_4.s1_pts[0] = -1.76340175408;
	//sketch_4.s1_pts[1] = 1.94652442505;
	//sketch_4.s1_pts[2] = sketch_4.offset;
	//sketch_4.s1_pts[3] = -1.13166297582;
	//sketch_4.s1_pts[4] = 2.18881332568;
	//sketch_4.s1_pts[5] = sketch_4.offset;
	//sketch_4.s1_pts[6] = 0.12608563158;
	//sketch_4.s1_pts[7] = 1.94290990106;
	//sketch_4.s1_pts[8] = sketch_4.offset;
	//sketch_4.s1_pts[9] = 1.16744210157;
	//sketch_4.s1_pts[10] = 1.19411503323;
	//sketch_4.s1_pts[11] = sketch_4.offset;
	//sketch_4.s1_pts[12] = 1.99331371687;
	//sketch_4.s1_pts[13] = 0.11077742105;
	//sketch_4.s1_pts[14] = sketch_4.offset;
	//sketch_4.s2_pts[0] = -1.44532304712;
	//sketch_4.s2_pts[1] = 1.41284156639;
	//sketch_4.s2_pts[2] = sketch_4.offset;
	//sketch_4.s2_pts[3] = -0.69560300522;
	//sketch_4.s2_pts[4] = 1.39886082596;
	//sketch_4.s2_pts[5] = sketch_4.offset;
	//sketch_4.s2_pts[6] = 0.19653707120;
	//sketch_4.s2_pts[7] = 1.24230378988;
	//sketch_4.s2_pts[8] = sketch_4.offset;
	//sketch_4.s2_pts[9] = 0.86548954491;
	//sketch_4.s2_pts[10] = 0.77463529360;
	//sketch_4.s2_pts[11] = sketch_4.offset;
	//sketch_4.s2_pts[12] = 1.80839988015;
	//sketch_4.s2_pts[13] = -0.03765333922;
	//sketch_4.s2_pts[14] = sketch_4.offset;
	sketch_4.a1_2nd_pt[0] = -1.77120879401;
	sketch_4.a1_2nd_pt[1] = 1.58024138126;
	sketch_4.a1_2nd_pt[2] = sketch_4.offset;
	sketch_4.a2_2nd_pt[0] = 1.96436756507;
	sketch_4.a2_2nd_pt[1] = -0.04255915672;
	sketch_4.a2_2nd_pt[2] = sketch_4.offset;
	tag_t sketch4_tag = create_sketch(&sketch_4);
/*************************thru_curves with arcs/splines***************************/
	UF_STRING_t thru_curves_list;
	UF_MODL_create_string_list(4,16,&thru_curves_list);			//4 - number of sections, 16, total number of items (4 sections x 4 curves/per section = 16
	thru_curves_list.num = 4;									// number of sections
	thru_curves_list.string[0] = 4;								// number of curves per section
	thru_curves_list.string[1] = 4;
	thru_curves_list.string[2] = 4;
	thru_curves_list.string[3] = 4;
	thru_curves_list.dir[0] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[1] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[2] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[3] = UF_MODL_CURVE_START_FROM_BEGIN;

	//list of all the tags to be used should be the size of the total from above
	tag_t thru_curves[16] = {
		sketch_1.s1_tag,sketch_1.s2_tag,sketch_1.a1_tag,sketch_1.a2_tag,
		sketch_2.s1_tag,sketch_2.s2_tag,sketch_2.a1_tag,sketch_2.a2_tag,
		sketch_3.s1_tag,sketch_3.s2_tag,sketch_3.a1_tag,sketch_3.a2_tag,
		sketch_4.s1_tag,sketch_4.s2_tag,sketch_4.a1_tag,sketch_4.a2_tag};
	thru_curves_list.id = thru_curves;
	UF_STRING_t s_spine;
	int patch =2;
	int alignment = 1;
	double value[6];
	int vdegree = 3;
	int vstatus =0;
	int body_type =1;
	UF_FEATURE_SIGN boolean = UF_NULLSIGN;
	double tol[3] = {0.01,0.01,0.01};
	tag_t c_face_id[2] = {NULL_TAG,NULL_TAG};
	int c_flag[2] = {0,0};
	tag_t thru_curves_tag;
	UF_MODL_create_thru_curves (&thru_curves_list,&s_spine,&patch,&alignment,value,&vdegree,&vstatus,&body_type,boolean,tol,c_face_id,c_flag,&thru_curves_tag);
/*************************thru_curves from sketches***************************/
/*	UF_STRING_t thru_curves_list;
	UF_MODL_create_string_list(4,4,&thru_curves_list);
	thru_curves_list.num = 4;
	thru_curves_list.string[0] = 1;
	thru_curves_list.string[1] = 1;
	thru_curves_list.string[2] = 1;
	thru_curves_list.string[3] = 1;
	thru_curves_list.dir[0] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[1] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[2] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[3] = UF_MODL_CURVE_START_FROM_BEGIN;
	tag_t thru_curves[4] = {sketch1_tag,sketch2_tag,sketch3_tag,sketch4_tag};
	thru_curves_list.id = thru_curves;
	UF_STRING_t s_spine;
	int patch =2;
	int alignment = 1;
	double value[6];
	int vdegree = 3;
	int vstatus =0;
	int body_type =1;
	UF_FEATURE_SIGN boolean = UF_NULLSIGN;
	double tol[3] = {0.01,0.01,0.01};
	tag_t c_face_id[2] = {NULL_TAG,NULL_TAG};
	int c_flag[ 2 ] = {0,0};
	tag_t thru_curves_tag;
	UF_MODL_create_thru_curves (&thru_curves_list,&s_spine,&patch,&alignment,value,&vdegree,&vstatus,&body_type,boolean,tol,c_face_id,c_flag,&thru_curves_tag);
/*************************thru_curves sheet***************************/
/*	UF_STRING_t thru_curves_list;
	UF_MODL_create_string_list(4,4,&thru_curves_list);
	thru_curves_list.num = 4;
	thru_curves_list.string[0] = 1;
	thru_curves_list.string[1] = 1;
	thru_curves_list.string[2] = 1;
	thru_curves_list.string[3] = 1;
	thru_curves_list.dir[0] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[1] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[2] = UF_MODL_CURVE_START_FROM_BEGIN;
	thru_curves_list.dir[3] = UF_MODL_CURVE_START_FROM_BEGIN;
	tag_t thru_curves[4] = {sketch_1.s1_tag,sketch_2.s1_tag,sketch_3.s1_tag,sketch_4.s1_tag};
	thru_curves_list.id = thru_curves;
	UF_STRING_t s_spine;
	int patch =2;
	int alignment = 1;
	double value[6];
	int vdegree = 3;
	int vstatus =0;
	int body_type =1;
	UF_FEATURE_SIGN boolean = UF_NULLSIGN;
	double tol[3] = {0.01,0.01,0.01};
	tag_t c_face_id[2] = {NULL_TAG,NULL_TAG};
	int c_flag[ 2 ] = {0,0};
	tag_t thru_curves_tag;
	UF_MODL_create_thru_curves (&thru_curves_list,&s_spine,&patch,&alignment,value,&vdegree,&vstatus,&body_type,boolean,tol,c_face_id,c_flag,&thru_curves_tag);
/*************************thru_curves sheet***************************/
/*	UF_STRING_t b_plane_list;
	UF_MODL_create_string_list(1,4,&b_plane_list);
	b_plane_list.num = 1;
	b_plane_list.string[0] = 4;
	b_plane_list.dir[0] = UF_MODL_CURVE_START_FROM_BEGIN;
	b_plane_list.dir[1] = UF_MODL_CURVE_START_FROM_BEGIN;
	b_plane_list.dir[2] = UF_MODL_CURVE_START_FROM_BEGIN;
	b_plane_list.dir[3] = UF_MODL_CURVE_START_FROM_BEGIN;
	tag_t b_plane[4] = {sketch_4.s1_tag,sketch_4.a2_tag,sketch_4.s2_tag,sketch_4.a1_tag};
	b_plane_list.id = b_plane;
	tag_t b_plane_tag;
	UF_CALL(UF_MODL_create_bplane (&b_plane_list,tol,&b_plane_tag));

	//UF_PART_save();
	return 0;
	*/
}
#include "menuUtils.h"
#define self GET_PLAYER_ACTOR(0)

bool ToggleSpoof13;
bool cutsceneRunning;
static int cutsceneIndex = 0;
char* OBJchar[] = { "Spawn", "Delete", "Move" };
char* OBJchar2[] = { "Name", "Reset" };
//"p_gen_marstonstree01x", "p_gen_powderkeg01x", "p_gen_powderkeg02x", "p_gen_stagecoach01x", "p_gen_statuereligious01x", "p_gen_statuereligious02x", "p_gen_streetclock01x", "p_gen_lampstreet03x", "p_gen_lamptelegraphpole01x", "p_gen_locatordummy02x", "p_gen_marker01x", "p_gen_marker02x",
char* ObjectChar[] = { "armoredcar01x", "p_gen_barrel01x", "p_gen_barricade01x", "p_gen_boatlarge01x", "p_gen_boatmedium01x", "p_gen_boatsmall01x", "p_gen_boatsmall02x", "p_gen_bodybin01x", "p_gen_bodypartarm01x", "p_gen_bodypartarm02x", "p_gen_bodyparthead01x", "p_gen_bodyparthead02x", "p_gen_boxcar0401x", "p_gen_butterbridge02x", "p_gen_campfire01x", "p_gen_campfire02x", "p_gen_campfirecombined01x", "p_gen_campfirecombinedng01x", "p_gen_cannon01x", "p_gen_cannon02x", "p_gen_car01cutscene01x", "p_gen_carblocked01x", "p_gen_cartmine01x", "p_gen_cavein02x", "p_gen_chuckwagon01x", "p_gen_chuckwagonbreak01x", "p_gen_chuckwagonburned01x", "p_gen_clock01x", "p_gen_clock02x", "p_gen_clocktable01x", "p_gen_cochinaygates_cs01x", "p_gen_cochinaygates_cs02x", "p_gen_cochinayplatform01x", "p_gen_cochinayrock_cs01x", "p_gen_cranedock01x", "p_gen_cranedockcutscene01x", "p_gen_crate01x", "p_gen_crate02x", "p_gen_crate03ax", "p_gen_crate03x", "p_gen_crate04x", "p_gen_cratecutscene01x", "p_gen_cratecutscene02x", "p_gen_crategatling01x", "p_gen_crategatling02x", "p_gen_cratemultiplayerammo01x", "p_gen_cratemultiplayerammofull01x", "p_gen_cratemultiplayeritem01x", "p_gen_cratemultiplayerweapon01x", "p_gen_cratesit01x", "p_gen_cratestack01x", "p_gen_cratestack02x", "p_gen_cratetnt01x", "p_gen_cratetnt02x", "p_gen_crateweapons01x", "p_gen_crateweapons02x", "p_gen_crateweapons03x", "p_gen_crateweapons04x", "p_gen_crateweaponsbreak01x", "p_gen_crateweaponsbreak02x", "p_gen_credenza02x", "p_gen_credenza03x", "p_gen_csplacementprop01x", "p_gen_dirtmound01x", "p_gen_divider01x", "p_gen_divider02x", "p_gen_doorcatacombs01x", "p_gen_dynamite01x", "p_gen_dynamite02x", "p_gen_dynamite03x", "p_gen_dynamite04x", "p_gen_dynamitecrate01x", "p_gen_elpresidiogates_cs01x", "p_gen_flatcar0102x", "p_gen_flatcar0103x", "p_gen_flatcar0104x", "p_gen_flatcar0105x", "p_gen_gatlinggun01x", "p_gen_gatlinggun02x", "p_gen_gatlingmaxim02x", "p_gen_gatlingmaximshield01x", "p_gen_gatlingmaximshield02x", "p_gen_glider01x", "p_gen_glider02x", "p_gen_glider_cs01x", "p_gen_glidercrash01x", "p_gen_gliderhidepile01x", "p_gen_graveeva01x", "p_gen_gravejohn01x", "p_gen_gravejohn02x", "p_gen_gravejohn03x", "p_gen_gravestone01x", "p_gen_gravestone02x", "p_gen_gravestone04x", "p_gen_gravestone05x", "p_gen_gravestoneclean01x", "p_gen_gravestoneclean02x", "p_gen_graveuncle01x", "p_gen_graveuncle02x", "p_gen_indianshrine01x", "p_gen_ladder01x", "p_gen_lamp01x", "p_gen_lamp02x", "p_gen_lamp03x", "p_gen_lamp04x", "p_gen_lamp05x", "p_gen_lampcandle01x", "p_gen_lampexterior01x", "p_gen_lampexterior02x", "p_gen_lampexterior03x", "p_gen_lampexterior04x", "p_gen_lampexterior05x", "p_gen_lampfactory01x", "p_gen_lampkerosene01x", "p_gen_lampstreet01x", "p_gen_marstonstree01x", "p_gen_powderkeg01x", "p_gen_statuereligious01x", "p_gen_statuereligious02x", "Defined Object"};
int PropObject[51];//object name for destroying
int CurrentObject = 0;//current index for objects (max of 50)
int TheCurrentSelectedObject = 0;//this is for manual delete and move of specified spawned object
int selectorz2 = 0;//the index to choose (spawn or delete prop)
int ObjectIndex = 119;//the left and right switch index id to pull the objectchar from the string array
int lastobject = -1;//last object spawned so the player knows which prop id was last spawned
int selectorz3 = 0;
int letternum = 0;
char cusobject[64];
static int object_index2;
char* Cscene[] =
{
"intro_sequence_1",//0
"intro_sequence_2",//1
"intro_sequence_3",//2
"intro_01",//3
"intro_b_seq",//4
"ranch_01",//5
"ranch_01_end",//6
"r3",//7
"ranch03_cs03",//8
"r2",//9
"ranch02_cs02",//10
"ranch02_end",//11
"r7",//12
"r7_end",//13
"r6",//14
"ranch_06_cs03",//15
"ranch06_cs05",//16
"r8",//17
"r4",//18
"ranch04_cs02",//19
"r4_end",//20
"m1",//21
"marshal01_cs02",//22
"marshal01_cs03",//23
"marshal01_cs04",//24
"m2",//25
"marshal02_end_seq",//26
"m4",//27
"marshal04_cs0a",//28
"marshal04_cs02_seq",//29
"marshal04_cs03",//30
"marshal04_cs05_seq",//31
"marshal04_cs06",//32
"m3",//33
"marshal03_cs02",//34
"marshal03_cs03_pt3",//35
"fort_01",//36
"ort01_warwagon_climb",//37
"fort_01_cs03_seq",//38
"fort01_cs06",//39
"fort01_cs0_seq7",//40
"anthro_01",//41
"anthro_03",//42
"anthro_04",//43
"anthro_04_cs04",//44
"anthro_04_cs06",//45
"anthro01_cs02",//46
"anthro01_end",//47
"anthro03_cs03",//48
"anthro04_climb_seq",//49
"anthro04_cs02",//50
"anthro04_cs02_seq",//51
"anthro04_end_scene_a",//52
"anthro04_end_scene_b",//53
"anthro04_end_scene_exec",//54
"fbi_01_cs03",//55
"fbi_01_end_scene",//56
"fbi_01_seq",//57
"fbi_02_seq",//58
"fbi_03_p1",//59
"fbi_04_intro_seq",//60
"fbi_05",//61
"fbi_05_cs03",//62
"fbi_05_cs04",//63
"fbi_05_cs05",//64
"fbi_05_cs05_b",//65
"fbi_05_end_scene",//66
"fbi_stairs_01",//67
"fbi_stairs_02",//68
"fbi01_cs04_exit_seq",//69
"fbi01_cs04_p1",//70
"fbi01_cs04_p2",//71
"fbi01_cs04_p3_alt",//72
"fbi04_cs02_seq",//73
"fbi04_cs03",//74
"fbi04_cs04_seq",//75
"fbi04_cs04_taunt_01",//76
"fbi04_cs04_taunt_02",//77
"fbi04_cs04_taunt_seq",//78
"fbi04_cs05_seq",//79
"fbi04_end",//80
"fort_02",//81
"fort_02_end",//82
"fort01_cs05_seq",//83
"grave_01",//84
"grave_02",//85
"grave_02_end",//86
"grave_03",//87
"grave01_cs02_seq",//88
"grave01_cs04_c_seq",//89
"grave01_cs04_f",//90
"grave01_cs04_seq",//91
"grave01_seq",//92
"grave03_cs03",//93
"gun_01",//94
"gun_01_cs02",//95
"gun_01_s",//96
"gun_02",//97
"gun_02_end_seq",//98
"gun_03",//99
"gun_03_end",//100
"gun_03_enter_train",//101
"gun_03_exit_train",//102
"gun_05_a",//103
"gun_05_b",//104
"gun_05_cs04",//105
"gun01_cs03",//106
"gun03_cs04",//107
"gun03_cs05",//108
"gun05_end",//109
"home_01",//110
"home_03",//111
"home_03_end_scene_a",//112
"home_03_end_scene_b",//113
"home01_cs02",//114
"home01_cs02_a",//115
"home01_cs02_c",//116
"home01_cs03",//117
"home02_end",//118
"home03_cs03",//119
"home03_cs04_c",//120
"home03_cs04_seq",//121
"intro01_cs02",//122
"jacks_beginning",//123
"marshal01_cs04_b",//124
"marshal03_cs03",//125
"marshal03_cs03_pt1",//126
"marshal03_cs03_pt2",//127
"marston_death_seq",//128
"merchant_01",//129
"merchant_01_a",//130
"merchant_02",//131
"merchant_03",//132
"merchant_04",//133
"merchant_05",//134
"merchant_05_end_scene",//135
"merchant01_cs03",//136
"merchant01_cs03_b",//137
"merchant02_cs02_seq",//138
"merchant02_cs03_a_f",//139
"merchant02_cs03_a_s",//140
"merchant02_cs03_b_f",//141
"merchant02_cs03_b_s",//142
"merchant02_cs03_c_p1",//143
"merchant02_end_seq",//144
"merchant03_cs02",//145
"merchant03_cs03",//146
"merchant04_end",//147
"mex_girl_01",//148
"mex_girl_01_end",//149
"mex_girl_02",//150
"mex_girl_03",//151
"mex_girl_03_cs02",//152
"mex_girl_03_end",//153
"mexarmy01_cs02",//154
"mexarmy01_cs03_b",//155
"mexarmy01_cs04",//156
"mexarmy02_cs02_a",//157
"mexarmy02_cs02_b",//158
"mexarmy02_cs02_seq",//159
"mexarmy02_cs02_train",//160
"mexarmy03_cs03",//161
"mexarmy03_cs06_p1",//162
"mexarmy04_cs03",//163
"mexarmy04_cs05_a",//164
"mexarmy05_cs02_b",//165
"mexarmy05_cs03",//166
"mexarmy05_cs03_p1",//167
"mexgirl01_cs02",//168
"mexgirl03_cs03",//169
"mexican_army_01",//170
"mexican_army_01_a",//171
"mexican_army_02",//172
"mexican_army_03",//173
"mexican_army_04",//174
"mexican_army_05",//175
"mexican_army_05_end",//176
"outlaw_01",//177
"outlaw_01_end",//178
"outlaw_02",//179
"outlaw_03",//180
"outlaw01_cs02",//181
"outlaw01_cs04",//182
"outlaw03_cs02",//183
"outlaw03_cs04",//184
"outlaw03_cs05_a",//185
"outlaw03_end",//186
"r6_seq",//187
"ranch01_cs02_p1",//188
"ranch01_cs02_p2",//189
"rcm_01_cs01",//190
"rcm_01_cs02",//191
"rcm_01_cs03",//192
"rcm_02_cs01",//193
"rcm_02_cs04",//194
"rcm_02_cs05",//195
"rcm_03_cs01",//196
"rcm_03_cs02",//197
"rcm_03_cs03_a",//198
"rcm_03_cs03_b",//199
"rcm_04_cs01",//200
"rcm_04_cs03_a",//201
"rcm_04_cs03_b",//202
"rcm_04_cs04",//203
"rcm_05_cs01",//204
"rcm_05_cs02",//205
"rcm_05_cs03",//206
"rcm_05_cs04",//207
"rcm_05_cs05",//208
"rcm_08_cs01",//209
"rcm_08_cs02",//210
"rcm_08_cs03",//211
"rcm_08_cs04",//212
"rcm_11_cs01_b",//213
"rcm_11_cs02",//214
"rcm_11_cs03",//215
"rcm_11_cs04_a",//216
"rcm_11_cs04_b",//217
"rcm_12_cs01",//218
"rcm_12_cs02",//219
"rcm_12_cs03",//220
"rcm_13_cs01",//221
"rcm_13_cs02",//222
"rcm_14_cs01",//223
"rcm_14_cs02",//224
"rcm_14_cs03",//225
"rcm_15_cs01",//226
"rcm_15_cs02_a",//227
"rcm_15_cs02_b",//228
"rcm_15_cs03_a",//229
"rcm_15_cs03_b",//230
"rcm_15_cs04",//231
"rcm_15_cs05",//232
"rcm_16_cs01",//233
"rcm_16_cs01_b",//234
"rcm_16_cs02",//235
"rcm_16_cs03",//236
"rcm_17_cs01",//237
"rcm_17_cs02",//238
"rcm_17_cs03",//239
"rcm_19_cs01",//240
"rcm_19_cs02",//241
"rcm_19_cs03",//242
"rcm_19_cs04",//243
"rcm_20_cs01",//244
"rcm_20_cs02",//245
"rcm_20_cs03",//246
"rcm_20_cs04",//247
"rcm_23_cs01",//248
"rcm_23_cs03",//249
"rcm_23_cs03",//250
"rcm_23_cs04",//251
"rcm_29_cs01",//252
"rcm_29_cs02",//253
"rcm_31_cs01",//254
"rcm_31_cs03",//255
"rcm_32_cs01",//256
"rcm_32_cs02",//257
"rcm_32_cs03",//258
"rcm_32_cs04",//259
"rcm32_cs04_end",//260
"rebel_02",//261
"rebel_04",//262
"rebel_05",//263
"rebel_06_alive_seq",//264
"rebel_06_dead_seq",//265
"rebel_leader_01",//266
"rebel_leader_05_a_2_seq",//267
"rebel_leader_05_a_seq",//268
"rebel_leader_05_b_seq",//269
"rebel_leader_05_cs03",//270
"rebel_leader_05_end",//271
"rebel_leader_06",//272
"rebel02_cs02",//273
"rebel02_cs03",//274
"rebel02_cs05",//275
"rebel03_cs03",//276
"rebel03_cs04",//277
"rebel03_cs06",//278
"rebel04_end",//279
"rebel05_cs06",//280
"rebel06_cs02",//281
"rebel06_cs02_b",//282
"rebel06_cs03",//283
"rebel06_cs04",//284
"rebel06_cs04_b",//285
"rebel06_cs06",//286
"rebel06_cs07",//287
"son_01",//288
"son_01_end",//289
"son_02",//290
"son_02_end",//291
"son_03",//292
"son03_cs02",//293
"son03_cs02_d",//294
"son03_cs02_seq",//295
"uncle_01",//296
"uncle_03",//297
"wife_02",//298
"wife_03",//299
"wife03_cs02",//300
"wife03_cs02_b",//301
"wife03_cs03",//302
"bonnie_rcm_1_pt_a_cs",//UNDEAD STARTS HERE 303
"bonnie_rcm_2_cs",
"bonnie_rcm_3_cs",
"cure_for_all_1_cs_seq",
"cure_for_all_1_pt_3",
"cure_for_all_1_pt_5_1_cs",
"cure_for_all_2_cs_seq",
"cure_for_all_3_pt_a_cs",
"escalera_1_cs_seq",
"escalera_1_pt_d_cs",
"escalera_2_pt_e_cs",
"escalera_2_pt_f_cs",
"false_ending",
"false_ending_intro",
"false_ending_intro_2",
"false_ending_intro_2_cs",
"fenway_1_cs",
"fenway_2_cs",
"fenway_3_pt_a_cs",
"fenway_cs_seq",
"landon_ricketts_1_cs_seq",
"landon_ricketts_2_cs_seq",
"marshal_rcm_1_cs_seq",
"marshal_rcm_2_cs_seq",
"marshal_rcm_3_cs",
"marshal_rcm_4_cs",
"marston_rises_again_cs",
"mckenna_1_pt_a_cs",
"mckenna_2_b_cs",
"mckenna_2_pt_a_cs",
"mexico_crossing_1_cs",
"mexico_crossing_2_cs",
"mexico_crossing_3_cs",
"mexico_crossing_4_pt_c_cs",
"mexico_crossing_4_pt_f",
"mexico_crossing_5_b_cs",
"mexico_crossing_5_cs",
"mexico_crossing_5_cs_seq",
"mexico_crossing_cs_seq",
"missing_persons_1_cs",
"missing_persons_2_cs",
"missing_persons_2_pt_b_cs",
"missing_persons_3_cs_seq",
"mother_superior_1_cs_seq",
"mother_superior_4_cs_seq",
"mother_superior_has_a_gun_2_pt_a_cs",
"mother_superior_has_a_gun_3_pt_a_cs",
"outbreak_1_pt_1_seq",
"outbreak_1_pt_1b_seq",
"outbreak_1_pt_2_seq",
"outbreak_3_cs_seq",
"outbreak_3_pt_1",
"outbreak_3_pt_2",
"outbreak_4_pt_a",
"outbreak_4_pt_a_cs",
"outbreak_4_pt_b",
"outbreak_4_pt_b_cs",
"pale_horse_cs_seq",
"sasquatch_1",
"sasquatch_1_cs",
"sasquatch_2",
"sasquatch_2_cs",
"seths_surprise_cs",
"the_dead_rise_again_1_cs_seq",
"the_dead_rise_again_2_pt_a_cs",
};

char* letternumber[] =
{
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"_",
};
bool RequestProp(const char* PropName)
{
	int iVar0;
	bool isLoaded = false;

	iVar0 = 0;
	int PropObjectID = GET_ASSET_ID(PropName, 0);
	for (int i = 0; i < 5; i++)
	{
		REQUEST_ASSET(PropName, 0);
		STREAMING_REQUEST_PROP(PropObjectID, 0);
		PropObjectID = GET_ASSET_ID(PropName, 0);
		if (STREAMING_IS_PROP_LOADED(PropObjectID)) {
			isLoaded = true;
		}
		WAIT(500);
	}
	return isLoaded;
}

void ObjectSpawnCam(Object object)
{
	//removing help screen so subtitles can print
	HUD_CLEAR_HELP();
	HUD_CLEAR_HELP_QUEUE();
	WAIT(500);//delay so it doesnt accept previous inputs and carry over to inputs here
	float camX = 0.0f, camY = 0.0f;
	vector3 camPos, camDirection, objPos, objPosFix, objOrient, objOrient2, objaxis;
	Camera cam = CREATE_CAMERA_IN_LAYOUT(GET_AMBIENT_LAYOUT(), "", 0);

	INIT_CAMERA_FROM_GAME_CAMERA(cam);
	SET_CURRENT_CAMERA_ON_CHANNEL(cam, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	GET_CAMERA_POSITION(cam, &camPos);

	while (!IS_BUTTON_PRESSED(0, BUTTON_Y, 1, 0))
	{
		print2("<y>Confirm Placement, <x>Move Object to Cam Position,\n<lb> + <dpadleft>/<dpadright> Rotate\n <red>THIS IS UNFINISHED ATM", 1000);
		SET_PLAYER_CONTROL(0, 0, 0, 0);

		float xStickLeft = GET_STICK_X(0, 0, 0);
		float yStickLeft = GET_STICK_Y(0, 0, 0);
		float xStickRight = GET_STICK_X(0, 1, 0);
		float yStickRight = GET_STICK_Y(0, 1, 0);

		GET_CAMERA_POSITION(cam, &camPos);
		GET_CAMERA_DIRECTION(cam, &camDirection);

		//Switch version has to be done this way... vectors assignment doesn't seems to work...
		float x = camPos.x;
		float y = camPos.y;
		float z = camPos.z;

		if (yStickLeft < -0.2f)
		{
			x += (camDirection.x * yStickLeft);
			y += (camDirection.y * yStickLeft);
			z += (camDirection.z * yStickLeft);
		}
		if (yStickLeft > 0.2f)
		{
			x += (camDirection.x * yStickLeft);
			y += (camDirection.y * yStickLeft);
			z += (camDirection.z * yStickLeft);
		}
		if (xStickLeft < -0.2f)
		{
			x += (COS_DEGREE(camY) * xStickLeft);
			z += (SIN_DEGREE((camY - 180.0f)) * xStickLeft);
		}
		if (xStickLeft > 0.2f)
		{
			x -= (COS_DEGREE((camY - 180.0f)) * xStickLeft);
			z -= (SIN_DEGREE(camY) * xStickLeft);
		}

		if ((yStickRight < -0.2f) || (yStickRight > 0.2f))
			if ((yStickRight > 0.2f && (camX > -50.0f)) || (yStickRight < -0.2f && (camX < 50.0f))) //Y Axis security
				camX += (yStickRight * -5.0f);
		if ((xStickRight > 0.2f) || (xStickRight < -0.2f))
			camY += (xStickRight * -5.0f);

		camPos.x = x;
		camPos.y = y;
		camPos.z = z;
		camDirection.x = camX;
		camDirection.y = camY;
		camDirection.z = 0.0f;

		SET_CAMERA_POSITION(cam, camPos);
		SET_CAMERA_ORIENTATION(cam, camDirection, 0);
		GET_OBJECT_ORIENTATION(object, &objOrient);
		//float objhead = GET_OBJECT_HEADING(object);
		float x1 = objOrient.x;
		float y1 = objOrient.y;
		float z1 = objOrient.z;
		if (GetButtonDown(BUTTON_LB))
		{
			if (GetButtonDown(DPAD_LEFT))
			{
				x1 = objOrient.x - 5.0f;
			}
			if (GetButtonDown(DPAD_RIGHT))
			{
				x1 = objOrient.x + 5.0f;
			}
		}
		SET_OBJECT_ORIENTATION(object, x1, y1, z1);

		if (IS_BUTTON_PRESSED(0, BUTTON_X, 1, 0))
		{
			SET_OBJECT_POSITION(object, camPos);//objects position
		}
		WAIT(0);
	}
	//clearing subtitles so help screen comes back normal right away
	HUD_CLEAR_OBJECTIVE();
	HUD_CLEAR_OBJECTIVE_QUEUE();
	WAIT(1000);//slight delay so it doesnt accidently carry over input wise to spawner menu
	REMOVE_CAMERA_FROM_CHANNEL(cam, 0);
	DESTROY_CAMERA(cam);
	CAMERA_RESET(0);
	SET_PLAYER_CONTROL(0, 1, 0, 0);
	SET_CAMERA_FOLLOW_ACTOR(self);
}

void SpawnObject(const char* fragname)
{
	//shitty hack to detect number of objects currently spawned
	int CurrentObjectsSpawned = 0;//reset it each time so we know the actual ammount spawned...
	for (int i = 0; i <= 49; i++)
	{
		if (IS_OBJECT_VALID(PropObject[i]))
		{
			CurrentObjectsSpawned++;
		}
	}
	if (CurrentObjectsSpawned == 49)print2("Max Props Spawned, Please Delete Some To Continue Spawning", 3000);
	if (CurrentObjectsSpawned != 49)
	{
		//here we are checking for available prop indexs in the case they were deleted, if so we find it and use it instead of adding onto the index and end up with less props.
		for (int i = 0; i <= 49; i++)
		{
			if (!IS_OBJECT_VALID(PropObject[i]))
			{
				CurrentObject = i;
				break;//should stop the for loop and continue with the function since we want to only detect available prop slots and use those
			}
		}
		//DESTROY_OBJECT(PropObject);
		vector3 herenow, rotobj;
		rotobj.x = 0.0f;
		rotobj.y = 0.0f;
		rotobj.z = 0.0f;
		const char* objecttospawn = strcatGlobal("$/fragments/", fragname);
		if (!RequestProp(objecttospawn))
		{
			print2("Couldn't Load Model", 2000);
			return;
		}
		GET_POSITION(self, &herenow);
		PropObject[CurrentObject] = CREATE_PROP_IN_LAYOUT(FIND_NAMED_LAYOUT("PlayerLayout"), "", objecttospawn, herenow, rotobj, 1);
		ObjectSpawnCam(PropObject[CurrentObject]);
		//lastobject = CurrentObject;
		//CurrentObject++;
	}
}

void TeleportActor2(Actor actor, vector3 position)
{
	float heading = GET_HEADING(actor);
	if (IS_ACTOR_RIDING(actor))
		TELEPORT_ACTOR(GET_MOUNT(actor), &position, 1, 1, 1);
	else if (IS_ACTOR_DRIVING_VEHICLE(actor))
		TELEPORT_ACTOR(GET_VEHICLE(actor), &position, 1, 1, 1);
	else
		TELEPORT_ACTOR_WITH_HEADING(actor, position, heading, 1, 1, 1);
}

void CheckToEndCutscene()
{
	if (IS_BUTTON_PRESSED(0, BUTTON_A, 0, 0) || CUTSCENE_MANAGER_IS_CUTSCENE_FINISHED())
	{
		CUTSCENE_MANAGER_STOP_CUTSCENE(1, 1);
		CUTSCENE_MANAGER_UNLOAD_CUTSCENE();
		STREAMING_SET_CUTSCENE_MODE(false);
		ENABLE_USE_CONTEXTS(true);
		CAMERA_RESET(0);
		UI_EXIT("LoadingScreen");
		UI_POP("FadeToBlack");
		HUD_FADE_IN(1.0f, 1065353216);
		HUD_CLEAR_OBJECTIVE_QUEUE();
		cutsceneRunning = false;
		WAIT(1000);//delay so inputs don't execute twice by accident
	}
}
void LoadCutscene(char* cutscene)
{
	if (DECOR_CHECK_EXIST(self, "globalcutloadscreen"))
	{
		DECOR_REMOVE(self, "globalcutloadscreen");
	}

	CUTSCENE_MANAGER_LOAD_CUTSCENE(cutscene, 0, 1, 1, 1, 2);
	STREAMING_SET_CUTSCENE_MODE(true);
	ENABLE_USE_CONTEXTS(false);
	CUTSCENE_MANAGER_PLAY_CUTSCENE();
	CUTSCENE_MANAGER_SET_SKIP_UI_STACK_POP(0);

	//FuncCleanUp(); //Close the menu so it doesn't run in the background
	cutsceneRunning = true;
}

void SetCutscene(int index)
{
	vector3 pos;
	char savedcut[255];
	stradd_s(savedcut, "$/cutscene/");
	stradd_s(savedcut, Cscene[index]);
	stradd_s(savedcut, "/");
	stradd_s(savedcut, Cscene[index]);
	GET_POSITION(self, &pos);
	if (!CUTSCENE_MANAGER_DOES_CUTSCENE_EXIST(savedcut))
	{
		print2("error", 2000);
		return;
	}
	WAIT(2000); //Giving time for the game
	LoadCutscene(savedcut);
	while (cutsceneRunning)
	{
		CheckToEndCutscene();
		WAIT(0);
	}
	WAIT(1500);
	TeleportActor2(self, pos);
}

void MainLRSwitches()
{
	if (ToggleSpoof13)
	{
		HUD_CLEAR_HELP_QUEUE();
		EnableThat = false;
		char modmsg[255];
		if (PedWepz == 100)
		{
			//while this is not the route I wanted to go it's the only way that seems to work best...
			//the new idea is to basically get all cutscenes mapped out then re-order them in the list
			//basically every cutscene part is now played individually per users selection instead of
			//grouping cutscene parts together to play back to back
			//i couldn't find a good way to group them together without the cutscenes playing odd aka no good way to clear the stored cutscene string names
			//and without a good way to do that the grouped cutscenes has chances of inf load screen and playing the wrong scene or outright not playing them.
			//so the new idea is re-order them once all mapped out then leave a txt doc saying this id through this id is this mission or event for this cutscene.
			//i will need some major help re-ordering these in the future.
			//while this is by no means great it's the best I have come up with
			//i would love to do the old way foxxyyy had but issues kept popping up and maybe it's something simple i'm missing but meh
			// this will do for now, just need to match cutscene parts to missions and of the such in the correct order
			//i would like to re-order these based on main missions first then side missions/stranger missions etc then special case events or something of that nature
			stradd_s(modmsg, "Cutscene Player\n<x>:Confirm\n<cancel>:Cancel\n<action>Cancel Cutscene\n<dpadleftright>:Cutscene:<orange> ");
			stradd_s(modmsg, Cscene[cutsceneIndex]);
			stradd_s(modmsg, "\n</orange>ID:<red> ");
			stradd_s(modmsg, INT_TO_STRING(cutsceneIndex));
		}
		if (PedWepz == 101)
		{
			stradd_s(modmsg, "Object Spawner\n<x>:Confirm\n<cancel>:Cancel\n<rb>:Action:<red> ");
			stradd_s(modmsg, OBJchar[selectorz2]);
			stradd_s(modmsg, "\n</red><dpadleftright>:<blue> ");
			if (selectorz2 == 0)stradd_s(modmsg, ObjectChar[ObjectIndex]);
			if (selectorz2 == 1 || selectorz2 == 2)stradd_s(modmsg, INT_TO_STRING(TheCurrentSelectedObject));
			stradd_s(modmsg, "\n</blue>Last Object Spawned: ");
			stradd_s(modmsg, INT_TO_STRING(CurrentObject));
		}
		if (PedWepz == 102)
		{
			//need to figure out backspace for this, it somewhat works but trips out
			//and at times it leaves 2/3 chars not erased when backspacing idk why
			stradd_s(modmsg, "Define Object\n<x>:Confirm\n<cancel>:Cancel\n<rb>:Action:<red> ");
			stradd_s(modmsg, OBJchar2[selectorz3]);
			if (selectorz3 == 0)
			{
				stradd_s(modmsg, "\n</red><dpadleftright>:<blue> ");
				stradd_s(modmsg, letternumber[letternum]);
			}
			stradd_s(modmsg, "\n");
			stradd_s(modmsg, cusobject);//might cause a crash on ryu and real hardware need to verify....
		}
		PRINT_HELP_B(modmsg, 500.0f, false, 1, 2, 1, "", "");
		if (GetButtonDown(DPAD_LEFT))
		{
			if (PedWepz == 100)
			{
				cutsceneIndex--;
				if (cutsceneIndex < 0) cutsceneIndex = 367;
			}
			if (PedWepz == 101)//for testing
			{
				if (selectorz2 == 0)
				{
					ObjectIndex--;
					if (ObjectIndex < 0) ObjectIndex = 119;
				}
				if (selectorz2 == 1 || selectorz2 == 2)//just gonna use the same index for delete and move as it's easier and just a lazy way around it lol.
				{
					TheCurrentSelectedObject--;
					if (TheCurrentSelectedObject < 0) TheCurrentSelectedObject = 49;
				}
			}
			if (PedWepz == 102)
			{
				if (selectorz3 == 0)
				{
					letternum--;
					if (letternum < 0) letternum = 36;
				}
			}
			WAIT(50);//so it's not very fast
		}
		if (GetButtonDown(DPAD_RIGHT))
		{
			if (PedWepz == 100)
			{
				cutsceneIndex++;
				if (cutsceneIndex > 367) cutsceneIndex = 0;
			}
			if (PedWepz == 101)
			{
				if (selectorz2 == 0)
				{
					ObjectIndex++;
					if (ObjectIndex > 119) ObjectIndex = 0;
				}
				if (selectorz2 == 1 || selectorz2 == 2)
				{
					TheCurrentSelectedObject++;
					if (TheCurrentSelectedObject > 49) TheCurrentSelectedObject = 0;
				}
			}
			if (PedWepz == 102)
			{
				if (selectorz3 == 0)
				{
					letternum++;
					if (letternum > 36) letternum = 0;
				}
			}
			WAIT(50);//so it's not very fast
		}
		if (GetButton(BUTTON_RB))
		{
			if (PedWepz == 101)
			{
				selectorz2++;
				if (selectorz2 > 2) selectorz2 = 0;
			}
			if (PedWepz == 102)
			{
				selectorz3++;
				if (selectorz3 > 1) selectorz3 = 0;
			}
		}
		if (GetButton(BUTTON_X))
		{
			if (PedWepz == 100)
			{
				SetCutscene(cutsceneIndex);
			}
			if (PedWepz == 101)
			{
				if (selectorz2 == 0)
				{
					if(ObjectIndex == 119)SpawnObject(cusobject);
					else
						SpawnObject(ObjectChar[ObjectIndex]);
				}
				if (selectorz2 == 1)
				{
					if (IS_OBJECT_VALID(PropObject[TheCurrentSelectedObject]))
					{
						DESTROY_OBJECT(PropObject[TheCurrentSelectedObject]);
					}
					else
						print2("Object not valid", 2000);
				}
				if (selectorz2 == 2)
				{
					if (IS_OBJECT_VALID(PropObject[TheCurrentSelectedObject]))
					{
						ObjectSpawnCam(PropObject[TheCurrentSelectedObject]);
					}
					else
						print2("Object not valid", 2000);
				}
			}
			if (PedWepz == 102)
			{
				if (selectorz3 == 0)
				{
					stradd_s(cusobject, letternumber[letternum]);
					object_index2++;
				}
				if (selectorz3 == 1)
				{
					memset(cusobject, 0, sizeof(cusobject));
					object_index2 = 0;
				}
			}
		}
		if (GetButton(BUTTON_B))
		{
			ToggleSpoof13 = false;
			EnableThat = true;
			HUD_CLEAR_HELP_QUEUE();
			DisplayMenu();
		}
	}
}
void Looped_Functions()
{
	MainLRSwitches();
}
int get_from_collection(char * code, Motif * result){
	Motif ms[16];

	size_t motif_0[MOTIF_MAX_BYTES] = {17,17,18,18,18,18,18,18,18,17,17,16,15,14,13,12,11,10,9,8,7,6,5,5,4,4,4,4,4,4,4,5};
	memcpy(ms[0].motif, &motif_0, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[0].code, "CNV_gain_L");
	ms[0].size = 32;
	ms[0].segments = 64;
	ms[0].alphabet = 24;
	ms[0].offset = 16.114755805477454;

	size_t motif_1[MOTIF_MAX_BYTES] = {4,4,3,3,3,3,3,3,3,4,5,5,6,8,9,10,11,13,14,15,16,17,18,19,19,19,20,20,19,19,19,18};
	memcpy(ms[1].motif, &motif_1, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[1].code, "CNV_gain_L");
	ms[1].size = 32;
	ms[1].segments = 64;
	ms[1].alphabet = 24;
	ms[1].offset = 16.682401347284074;

	size_t motif_2[MOTIF_MAX_BYTES] = {17,17,18,18,18,18,18,18,18,17,17,16,15,14,13,12,11,10,9,8,7,6,5,5,4,4,4,4,4,4,4,4};
	memcpy(ms[2].motif, &motif_2, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[2].code, "CNV_gain_R");
	ms[2].size = 32;
	ms[2].segments = 64;
	ms[2].alphabet = 24;
	ms[2].offset = 16.54849209033596;

	size_t motif_3[MOTIF_MAX_BYTES] = {14,15,15,16,17,17,17,17,17,17,16,16,15,14,13,12,11,10,8,7,6,6,5,5,4,4,4,4,5,5,6,7};
	memcpy(ms[3].motif, &motif_3, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[3].code, "CNV_gain_R");
	ms[3].size = 32;
	ms[3].segments = 64;
	ms[3].alphabet = 24;
	ms[3].offset = 14.962116131779233;

	size_t motif_4[MOTIF_MAX_BYTES] = {19,19,19,19,19,19,19,19,19,18,18,17,16,15,14,13,11,9,8,6,5,4,4,4,3,3,3,3,3,3,3,3};
	memcpy(ms[4].motif, &motif_4, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[4].code, "CNV_loss_L");
	ms[4].size = 32;
	ms[4].segments = 64;
	ms[4].alphabet = 24;
	ms[4].offset = 13.967678138859958;

	size_t motif_5[MOTIF_MAX_BYTES] = {4,3,3,3,3,3,3,3,4,4,5,6,7,9,10,12,14,16,17,18,19,20,20,21,21,21,21,21,21,21,21,20};
	memcpy(ms[5].motif, &motif_5, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[5].code, "CNV_loss_R");
	ms[5].size = 32;
	ms[5].segments = 64;
	ms[5].alphabet = 24;
	ms[5].offset = 22.330325334104923;

	size_t motif_6[MOTIF_MAX_BYTES] = {19,19,19,19,19,19,19,19,19,18,18,17,16,15,14,13,11,9,7,7,5,4,3,3,3,3,3,3,3,3,3,3};
	memcpy(ms[6].motif, &motif_6, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[6].code, "DEL_L");
	ms[6].size = 32;
	ms[6].segments = 64;
	ms[6].alphabet = 24;
	ms[6].offset = 14.440743843189814;

	size_t motif_7[MOTIF_MAX_BYTES] = {3,3,3,3,3,3,3,3,4,4,4,5,9,10,11,13,15,16,17,18,19,19,20,20,20,20,20,20,20,20,20,20};
	memcpy(ms[7].motif, &motif_7, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[7].code, "DEL_R");
	ms[7].size = 32;
	ms[7].segments = 64;
	ms[7].alphabet = 24;
	ms[7].offset = 20.102622950819672;

	size_t motif_8[MOTIF_MAX_BYTES] = {3,3,3,3,3,3,4,4,5,5,6,7,9,10,11,12,14,15,16,17,18,19,19,20,20,20,20,20,20,20,20,20};
	memcpy(ms[8].motif, &motif_8, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[8].code, "DUP_L");
	ms[8].size = 32;
	ms[8].segments = 64;
	ms[8].alphabet = 24;
	ms[8].offset = 20.281447443997703;

	size_t motif_9[MOTIF_MAX_BYTES] = {19,19,19,19,19,19,19,19,18,18,17,17,16,15,14,13,11,9,8,7,6,5,4,4,3,3,3,3,3,3,3,3};
	memcpy(ms[9].motif, &motif_9, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[9].code, "DUP_R");
	ms[9].size = 32;
	ms[9].segments = 64;
	ms[9].alphabet = 24;
	ms[9].offset = 15.202147044842338;

	size_t motif_10[MOTIF_MAX_BYTES] = {15,15,15,16,16,16,16,16,15,15,15,14,14,13,12,11,11,10,9,9,8,8,7,7,6,6,6,6,6,6,6,7};
	memcpy(ms[10].motif, &motif_10, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[10].code, "INS_C");
	ms[10].size = 32;
	ms[10].segments = 64;
	ms[10].alphabet = 24;
	ms[10].offset = 16.11181763120383;

	size_t motif_11[MOTIF_MAX_BYTES] = {6,6,5,5,5,5,5,5,5,6,6,7,8,8,9,10,11,12,13,14,15,15,16,17,17,17,17,17,17,17,17,16};
	memcpy(ms[11].motif, &motif_11, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[11].code, "INS_C");
	ms[11].size = 32;
	ms[11].segments = 64;
	ms[11].alphabet = 24;
	ms[11].offset = 15.941439031118408;

	size_t motif_12[MOTIF_MAX_BYTES] = {19,19,19,19,19,19,19,19,19,18,18,17,16,15,14,13,11,9,9,8,5,5,4,4,3,3,3,3,3,3,3,3};
	memcpy(ms[12].motif, &motif_12, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[12].code, "INV_L");
	ms[12].size = 32;
	ms[12].segments = 64;
	ms[12].alphabet = 24;
	ms[12].offset = 14.50280983284522;

	size_t motif_13[MOTIF_MAX_BYTES] = {15,15,16,16,16,17,17,17,17,17,16,16,15,14,13,12,10,9,8,7,6,5,4,4,3,3,3,3,3,4,5,5};
	memcpy(ms[13].motif, &motif_13, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[13].code, "INV_L");
	ms[13].size = 32;
	ms[13].segments = 64;
	ms[13].alphabet = 24;
	ms[13].offset = 11.114765381853005;

	size_t motif_14[MOTIF_MAX_BYTES] = {19,19,19,19,19,19,19,19,18,18,17,17,15,15,14,13,10,9,9,8,6,5,5,5,4,4,4,4,4,4,4,4};
	memcpy(ms[14].motif, &motif_14, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[14].code, "INV_R");
	ms[14].size = 32;
	ms[14].segments = 64;
	ms[14].alphabet = 24;
	ms[14].offset = 15.055598268117995;

	size_t motif_15[MOTIF_MAX_BYTES] = {15,16,17,17,18,18,18,18,18,18,17,17,15,15,14,13,10,9,8,7,6,5,5,4,4,4,4,4,4,5,6,6};
	memcpy(ms[15].motif, &motif_15, sizeof(size_t) * MOTIF_MAX_BYTES);
	strcpy(ms[15].code, "INV_R");
	ms[15].size = 32;
	ms[15].segments = 64;
	ms[15].alphabet = 24;
	ms[15].offset = 13.588002365125154;

	for (size_t i = 0; i < 16; i++) if (!strcmp(ms[i].code, code)) { * result = ms[i]; return 0; };
	return 1;
}

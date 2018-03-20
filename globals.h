#pragma once
#define MAX_PATCH_SIZE 15
#define MAX_SOURCE_IMAGES 3
#define MAX_PIXEL_PATCH MAX_SOURCE_IMAGES * (MAX_PATCH_SIZE * MAX_PATCH_SIZE) + 2
#define MAX_DIM 10
typedef unsigned char u08;
#define COLOR_GAMMA 0.5f
#define MAX_PYRAMID_LEVELS 30
#define MAX_NUM_THREADS 16
#define MAX_DIST 9999999999.f

#define GV_GRADIENT 3
#define GH_GRADIENT 4
//#define HAS_SEARCH_MASK 
//-SD
//#define HAS_3CHANNELS
//-SD
//#define TEST_BUG


extern float g_fW2;
typedef struct _myBox
{
	int isActive;
	float x1,x2,x3,x4,y1,y2,y3,y4;
} myBox;

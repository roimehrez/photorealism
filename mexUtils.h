#pragma once

#include "mex.h"
#include "Parameters.h"

void fillNNMap(const mxArray* x_pInput, SNNMap& xr_sMap);

bool readParameter(const mxArray *A, char* x_strFieldName , double x_dMin, double x_dMax, double& xr_dValue);


inline void readImage(const mxArray *A, char* x_strFieldName, ImageInput& x_rImage);
void readImage(const mxArray *val, ImageInput& x_rImage);

inline void readVoteWeight(const mxArray *A);

inline void readNNMAP(const mxArray *A, char* x_strName,SNNMap& x_sNNMap);



void fillNNMap(const mxArray* x_pInput, SNNMap& xr_sMap);

void fillInImage3D(ImageInput* x_psSrcImage,float***& x_rfDstImage);

void fillInImage2D(ImageInput* x_psSrcImage,float**& x_rfDstImage);
mxArray* fillOutImage3D(float*** x_pfSrImage, int x_nWidth, int x_nHeight, int x_nDim);

mxArray* fillOutImage2D(float** x_pfSrImage, int x_nWidth, int x_nHeight);

void readOptions(const mxArray *A);
int fillNNMapArray(const mxArray* x_pInput, SNNMap* x_psMap);
void readGainBias(const mxArray *A, int x_nIndex);
int readGainBiasArray(const mxArray *x_pInput);

float** create2DArray(int x_nWidth, int x_nHeight);
float*** create3DArray(int x_nWidth, int x_nHeight, int x_nDim);

void delete3DMatrixF(float***& xr_pfMatrix, int x_nWidth, int x_nHeight, int x_nDim);

void delete3DMatrixN(int***& xr_pnMatrix, int x_nWidth, int x_nHeight, int x_nDim);
void delete2DMatrixF(float**& xr_pfMatrix, int x_nWidth, int x_nHeight);

void delete3DMatrixN(int**& xr_pnMatrix, int x_nWidth, int x_nHeight);
void fillPyramid(const mxArray* x_pInput, SMipMapPyramid& xr_sPyramid);
int fillPyramidArray(const mxArray* x_pInput, SMipMapPyramid* x_psPyramid);
void delete4DMatrixF(float****& xr_pfMatrix, int x_nWidth, int x_nHeight, int x_nDim1, int x_nDim2);

// MATLAB interface, for PatchMatch + Generalized PatchMatch.

#include <stdio.h>
#include "mex.h"
#include "globals.h"
#include "Algorithm.h"
#include "mexUtils.h"
#include <omp.h>
#define EDGE_CONST 100





void calculateDX( float** x_pfInputIm, int x_nWidth, int x_nHeight, float** x_pfOutput)
{
	int _nW = x_nWidth - 1;
	int _nH = x_nHeight - 1;

	for(int i = 0; i < x_nWidth; i++)
	{
		for(int j = 0 ; j < x_nHeight ; j++)
		{
			x_pfOutput[i][j] = 0;
		}
	}
	for(int j = 0 ; j < x_nHeight ; j++)
	{
		for(int i = 0; i < x_nWidth; i++)
		{

			float _fC = x_pfInputIm[i][j];
			float _fN = (i < _nW) ? x_pfInputIm[ i + 1][j] : x_pfInputIm[i][j];
			float _fB = 0;
			float _fD = _fC - _fN;
			x_pfOutput[i][j] = _fD;
		}
	}

	for(int j = 0 ; j < x_nHeight ; j++)
	{
		for(int i = 1; i < _nW; i++)
		{

			float _fD = x_pfOutput[i][j];

			if(_fD < -EDGE_CONST || _fD > EDGE_CONST)
			{
				float _fC = x_pfInputIm[i][j];
				float _fTD = 0;
				float _fND = x_pfOutput[ i + 1][j];
				float _fBD = x_pfOutput[ i - 1][j];
				if(_fC < -EDGE_CONST || _fC > EDGE_CONST)
				{
					if(_fND > -EDGE_CONST && _fND < EDGE_CONST)
					{
						_fTD = _fND;
					}
					else if(_fBD > -EDGE_CONST && _fBD < EDGE_CONST)
					{
						_fTD = _fBD;
					}
					else
					{
						_fTD = 0;
					}
				}
				else
				{
					if(_fBD > -EDGE_CONST && _fBD < EDGE_CONST)
					{
						_fTD = _fBD;
					}	
					else if(_fND > -EDGE_CONST && _fND < EDGE_CONST)
					{
						_fTD = _fND;
					} 
					else
					{
						_fTD = 0;
					}

				}
				x_pfOutput[ i ][j] = _fTD;
			} 
		}

	}
}


void calculateDY( float** x_pfInputIm, int x_nWidth, int x_nHeight, float** x_pfOutput)
{
	int _nW = x_nWidth - 1;
	int _nH = x_nHeight - 1;

	for(int i = 0; i < x_nWidth; i++)
	{
		for(int j = 0 ; j < x_nHeight ; j++)
		{
			x_pfOutput[i][j] = 0;
		}
	}

	for(int i = 0; i < x_nWidth; i++)
	{
		for(int j = 0 ; j < x_nHeight ; j++)
		{


			float _fC = x_pfInputIm[i][j];
			float _fN = (j < _nH) ? x_pfInputIm[ i ][j + 1] : x_pfInputIm[i][j];
			float _fB = 0;
			float _fD = _fC - _fN;
			x_pfOutput[i][j] = _fD;
		}
	}

	//for(int k = 0 ; k < 10 ; k++)
	{

		for(int i = 0; i < x_nWidth; i++)
		{
			for(int j = 1 ; j < _nH ; j++)
			{
				//if(i == 23 && j == 11)
				// 	printf("here!\n");
				float _fD = x_pfOutput[i][j];
				if(_fD < -EDGE_CONST || _fD > EDGE_CONST)
				{
					float _fC = x_pfInputIm[i][j];
					float _fTD = 0;
					float _fND =  x_pfOutput[ i ][j + 1];
					float _fBD = x_pfOutput[ i ][j - 1];
					if(_fC < -EDGE_CONST || _fC > EDGE_CONST)
					{
						if(_fND > -EDGE_CONST && _fND < EDGE_CONST)
						{
							_fTD = _fND;
						}
						else if(_fBD > -EDGE_CONST && _fBD < EDGE_CONST)
						{
							_fTD = _fBD;
						}
						else
						{
							_fTD = 0;
						}
					}
					else
					{
						if(_fBD > -EDGE_CONST && _fBD < EDGE_CONST)
						{
							_fTD = _fBD;
						}	
						else if(_fND > -EDGE_CONST && _fND < EDGE_CONST)
						{
							_fTD = _fND;
						} 
						else
						{
							_fTD = 0;
						}

					}
					x_pfOutput[ i ][j] = _fTD;
				}

			}
		}
	}

	for(int j = 0 ; j < x_nHeight ; j++)
		{
			for(int i = 1; i < _nW; i++)
			{

				float _fD = x_pfOutput[i][j];
				if(_fD < -EDGE_CONST || _fD > EDGE_CONST)
				{
					printf("Error: at (%d,%d) gradient is big!\b", i , j);
				}

			}
		}
}



void mexFunction(int nout, mxArray *pout[], int nin, const mxArray *pin[]) {

  if (nin != 1) { mexErrMsgTxt("sDistMex called with != 1 input arguments"); }

  const mxArray *A = pin[0];
  if(mxGetNumberOfDimensions(A) != 2){ mexErrMsgTxt("Error: the input has to be gray scale image!"); }
  if(!mxIsSingle(A)){ mexErrMsgTxt("Error: the input has to be single!"); }
  ImageInput _sA;
  const mwSize* dimA = mxGetDimensions(A);
  _sA.m_pfData = (float*)mxGetData(A);
  _sA.m_nWidth = dimA[0];
  _sA.m_nHeight = dimA[1];
  _sA.m_bIsDefined = 1;
  float** _pfInputIm = 0;
  fillInImage2D(&_sA, _pfInputIm);
  
  float** _pf_DX = create2DArray(_sA.m_nWidth, _sA.m_nHeight);
  float** _pf_DY = create2DArray(_sA.m_nWidth, _sA.m_nHeight);
  calculateDX(_pfInputIm ,_sA.m_nWidth, _sA.m_nHeight, _pf_DX);
  calculateDY(_pfInputIm, _sA.m_nWidth, _sA.m_nHeight, _pf_DY);


  mxArray* DX = fillOutImage2D(_pf_DX, _sA.m_nWidth, _sA.m_nHeight);
  pout[1] = DX;

  mxArray* DY = fillOutImage2D(_pf_DY, _sA.m_nWidth, _sA.m_nHeight);
  pout[0] = DY;

  delete2DMatrixF(_pf_DX, _sA.m_nWidth, _sA.m_nHeight);
  delete2DMatrixF(_pf_DY, _sA.m_nWidth, _sA.m_nHeight);
}

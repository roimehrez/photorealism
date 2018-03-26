#pragma once
#include "globals.h"
#include "macros.h"
#include <string.h>
#include <time.h>

struct SNNMap
{
	int m_nWidth;
	int m_nHeight;
	bool m_bIsDefined;
	float*  m_pfData;
};

struct ImageInput
{
	int m_nWidth;
	int m_nHeight;
	int m_nDims;
	bool m_bIsDefined;
	float*  m_pfData;
	float** m_pf2DData;
	float*** m_pf3DData;
};

struct SMipMapPyramid
{
	int m_nLength;
	int m_nDim;
	int m_arrnWidth[MAX_PYRAMID_LEVELS];
	int m_arrnHeight[MAX_PYRAMID_LEVELS];
	float* m_arrpfData[MAX_PYRAMID_LEVELS];
	float m_arrfScales[MAX_PYRAMID_LEVELS];
	float global_scale;

};

class CParameters
{
public:
	int		m_nParallelIterations;
	int		m_nSequentialIterations;
	int		m_nPatchWidth;
	int		m_nRSMax;
	int		m_nRSMin;
	int     m_nNumberOfEMIterations;
	int		m_nDoMinNNF;
	int     m_nNumberOfThreads;
	int     m_nRandomSeed;
	float	m_fRSRatio;
	float	m_fRSIters;
	float	m_fMinScale;
	float	m_fMaxScale;
	float	m_fMinAngle;
	float	m_fMaxAngle;
	float	m_fNormalizeWeight;
	float   m_arrfVoteWeights[MAX_PATCH_SIZE][MAX_PATCH_SIZE];
	float  m_arrfVoteWeightOneD[MAX_PATCH_SIZE * MAX_PATCH_SIZE];
	float   m_arrfMinBias[MAX_DIM];
	float   m_arrfMaxBias[MAX_DIM];
	float   m_arrfMinGain[MAX_DIM];
	float   m_arrfMaxGain[MAX_DIM];
	float*  m_pfGainBias[MAX_SOURCE_IMAGES];
	int     m_nDimOfMinMax;
	float   m_fGradWeight;
	float   m_fMinRelScale;
	float   m_fMaxRelScale;
	float   m_fWindowSize;
	float   m_fCompletenessWeight;
	int m_nIsPixelInterpolation;
	int m_nIsRadnomInit;
	int m_nDoRandomSearch;
	int m_nIsReflection;
	float     m_fCoherencyWeight;
	ImageInput  m_sDstWeight;
	ImageInput  m_sMaskInput;
	ImageInput  m_sEMAlpha;
	ImageInput  m_sCurrentSRCIm;
	ImageInput m_sSearchSize;
	ImageInput m_sSrcSearchMask;
	ImageInput m_sTrgSegments;
	ImageInput m_sDstSearchMask;
	ImageInput m_sEpipolarConst;

	ImageInput  m_sSegments;
	SNNMap  m_sPrevMap;
	SNNMap  m_sPriorMap;
	SNNMap  m_sWindowSize;


	CParameters( int x_nPatchWidht = 8, int x_nParallelIterations = 0, int x_nSequentialIterations = 0, int x_nRSMax = 1000, int x_nRSMin = 1, float x_fRSRatio = 0.5, float x_fRSIters = 1.f , float x_fMaxScale = 2.f, float x_fMinScale = .5f, float x_fMinRelScale = 1.0f, float x_fMaxRelScale = 1.0f, float x_fMinAngle = 0.f, float x_fMaxAngle = 2 * M_PI, float x_fNormalizeWeight = 0
		, float x_fCoherencyWeight = 1.f,int x_nNumberOfEMIterations = 0, int x_nDoMinNNF = 0, int x_nNumberOfThreads = 1, int x_nIsPixelInterpolation = 0, float x_fGradWeight = 0)
	{
		m_nParallelIterations = x_nParallelIterations;
		m_nSequentialIterations = x_nSequentialIterations;
		m_nPatchWidth = x_nPatchWidht;
		m_nRSMax    = x_nRSMax;   
		m_nRSMin    = x_nRSMin ;  
		m_fRSRatio  = x_fRSRatio; 
		m_fRSIters  = x_fRSIters ;
		m_fMinScale = x_fMinScale;
		m_fMaxScale = x_fMaxScale;
		m_fMinRelScale = x_fMinRelScale;
		m_fMaxRelScale = x_fMaxRelScale;
		m_fMinAngle = x_fMinAngle;
		m_fMaxAngle = x_fMaxAngle;
		m_fCompletenessWeight = 0;
		for(int i = 0 ; i < MAX_DIM ; i++)
		{
			m_arrfMinBias[i] = 0;
			m_arrfMaxBias[i] = 0;
			m_arrfMinBias[i] = 1.f;
			m_arrfMaxBias[i]  = 1.f;
		}
		m_nDimOfMinMax = 0;
		m_nRandomSeed = ((unsigned)time ( NULL ) );
		m_nDoMinNNF  = x_nDoMinNNF;
		m_nIsPixelInterpolation = x_nIsPixelInterpolation;
		m_nNumberOfThreads = x_nNumberOfThreads;
		m_nNumberOfEMIterations = x_nNumberOfEMIterations;
		m_fCoherencyWeight = x_fCoherencyWeight;
		m_fGradWeight = x_fGradWeight;
		m_fNormalizeWeight = x_fNormalizeWeight;
		m_nIsRadnomInit = 1;
		m_nIsReflection = 1;
		m_nDoRandomSearch = 1;

		for(int i = 0 ; i < MAX_PATCH_SIZE ; i++)
		{
			for(int j = 0 ; j < MAX_PATCH_SIZE ; j++)
			{
				m_arrfVoteWeights[i][j] = 1.f;
			}
		}
		memset(m_pfGainBias, 0, sizeof(float) * MAX_SOURCE_IMAGES);
		m_sPrevMap.m_bIsDefined = 0;
		m_sWindowSize.m_bIsDefined = 0;
		m_sPriorMap.m_bIsDefined = 0;

		m_sSearchSize.m_bIsDefined = 0;
		m_sSearchSize.m_pf2DData = 0;
		m_sSearchSize.m_pf3DData = 0;
		m_fWindowSize = 0;

		m_sDstWeight.m_bIsDefined = 0;
		m_sDstWeight.m_pf2DData = 0;
		m_sDstWeight.m_pf3DData = 0;

		m_sSrcSearchMask.m_bIsDefined = 0;
		m_sSrcSearchMask.m_pf2DData = 0;
		m_sSrcSearchMask.m_pf3DData = 0;

		m_sDstSearchMask.m_bIsDefined = 0;
		m_sDstSearchMask.m_pf2DData = 0;
		m_sDstSearchMask.m_pf3DData = 0;

		m_sEpipolarConst.m_bIsDefined = 0;
		m_sEpipolarConst.m_pf2DData = 0;
		m_sEpipolarConst.m_pf3DData = 0;

		m_sMaskInput.m_bIsDefined = 0;
		m_sMaskInput.m_pf2DData = 0;
		m_sMaskInput.m_pf3DData = 0;

		m_sEMAlpha.m_bIsDefined = 0;
		m_sEMAlpha.m_pf2DData = 0;
		m_sEMAlpha.m_pf3DData = 0;

		m_sCurrentSRCIm.m_bIsDefined = 0;
		m_sCurrentSRCIm.m_pf2DData = 0;
		m_sCurrentSRCIm.m_pf3DData = 0;

		m_sSegments.m_bIsDefined = 0;
		m_sSegments.m_pf2DData = 0;
		m_sSegments.m_pf3DData = 0;

		m_sTrgSegments.m_bIsDefined = 0;
		m_sTrgSegments.m_pf2DData = 0;
		m_sTrgSegments.m_pf3DData = 0;
		
	};
	~CParameters(void);
};


extern CParameters* g_pParameter;

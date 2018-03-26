#pragma once
#include "ImageReader.h"
#include "SourceImage.h"
#include "CCorrespondanceMap.h"
#include "Patch.h"


class CAlgorithm
{
public:
	CSourceImage* m_pSource1;//first source
	CSourceImage* m_pSource2[MAX_SOURCE_IMAGES];//second source
	CPatch **m_pPathecs;
	float*** m_pfAccum;
	float**** m_pfAccumMed;
	CCorrespondanceMap* m_pCorrespondingMap[MAX_SOURCE_IMAGES];//Corresponding Map
	float** m_pfMask;
	float** m_pfSegments;
	float** m_pfEMAlpha;
	int m_nChannels;
	int m_nNumberOfSourceImages;
	void doVotingMed(float**** x_pfOutput, int x_nIndex);
	void doVotingInverse(float**** x_pfOutput, int x_nIndex);
	void voteForPatch(int x, int y, CPatch* x_pPatch, float x_fMaskValue, int x_nNumberOfChannels);

	float isCoherent(const int patchSize, int x_nIndex, float*** ann, int ax, int ay, float bx, float by, int dx, int dy, int _nAW, int _nAH, float x_fDist);
	int m_nDstImageSize;
	int m_nDstWidth;
	int m_nDstHeight;
	void correctDepthInfo();
	void unWeightCoherency(int x_nIndex);
	void createACC();
	void giveCoherencyWeight(float** x_pfCohWeight);
	void createACCMed(int x_nWidth, int x_nHeight);
	void mergeACCAndACCMED();
	CAlgorithm(CSourceImage* x_pSource1, CSourceImage* x_pSource2);
	CAlgorithm( char* x_strCorrespondingFileName);
	CAlgorithm( bool x_bIsSynthesize);
	CAlgorithm( SMipMapPyramid* x_pA, SMipMapPyramid* x_pB , bool x_bIsSynthesize);
	CAlgorithm( SMipMapPyramid* x_pA, SMipMapPyramid* x_pB , SNNMap* x_pNNMapForward, SNNMap* x_pNNMapBackward);
	CAlgorithm( SMipMapPyramid* x_pA, SMipMapPyramid* x_pB , SNNMap* x_pNNMap, int x_nDoVoting, int x_nNumberOfSources = 1, bool x_bDoGradientMedian = 0, int x_nScaledWidth = 0, int x_nScaledHeight = 0);
	int m_nPatchWidth;
	~CAlgorithm(void);
	void doVoting(float*** x_pfOutput, int x_nEmIndex, int x_nNormalized = 1, float x_fMaskValues = -1);

	void doVotingBid(float*** x_pfOutput, int x_nEmIndex, float x_fMaskValues = -1);
	//void voteForPatch(int x, int y, CPatch* x_pPatch);
	void initValues();
	void doEMIterations();
	void calculateACCFromACCMED();
	int getHeight(int x_nIndex){if(x_nIndex) return (*m_pSource2)->giveWidth(); return m_pSource1->giveWidth(); };
	int getWidth(int x_nIndex){if(x_nIndex) return (*m_pSource2)->giveHeight(); return m_pSource1->giveHeight(); };
	void addDataForMed(int x, int y, int x_nIndex, CPatch* x_pPatch2, CPatch* x_pPatch, int x_nNumberOfChannels);
	void addDataForInv(int x, int y, float x_fxR, float x_fyR, int x_nIndex, CPatch* x_pPatch, int x_nNumberOfChannels);
	float givePatchForVis(int x_nRX, int x_nRY,int x_nX, int x_nY,CPatch* x_pPatch);//This is for the visualizer and when I call it, it fills the x_pPatch with the values in the source image.
	void voteForPatchMed(int x, int y, int x_nNumberOfChannels);

};


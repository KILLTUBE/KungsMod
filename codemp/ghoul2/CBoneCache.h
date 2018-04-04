#pragma once

#include "../rd-rend2/tr_local.h"

class CTransformBone
{
public:
	int touch; // for minimal recalculation
	int touchRender;
	mdxaBone_t boneMatrix; //final matrix
	int parent; // only set once

	CTransformBone()
		: touch(0)
		, touchRender(0)
	{
	}

};

struct SBoneCalc
{
	int newFrame;
	int	currentFrame;
	float backlerp;
	float blendFrame;
	int blendOldFrame;
	bool blendMode;
	float blendLerp;
};

class CBoneCache
{
public:
	void AllocBoneCache();
	void GetBoneMatrix(float matrix[3][4], int bone_id, int frame_id);
	void EvalLow( int index );
	void SmoothLow( int index );
	bool hasUncompressedBones = false;
	mdxaBone_t *uncompressedBones = NULL; // R_Malloc(numFrames * numBones)
	int frameSize; 
	const mdxaHeader_t *header; 
	const model_t *mod; 
	// these are split for better cpu cache behavior
	std::vector<SBoneCalc> mBones;
	std::vector<CTransformBone> mFinalBones;
	std::vector<CTransformBone> mSmoothBones; // for render smoothing
	boneInfo_v *rootBoneList;
	mdxaBone_t rootMatrix;
	int incomingTime;
	int mCurrentTouch;
	int mCurrentTouchRender;
	int mLastTouch; 
	int mLastLastTouch;
	// for render smoothing
	bool mSmoothingActive;
	bool mUnsquash;
	float mSmoothFactor;
	CBoneCache( const model_t *amod, const mdxaHeader_t *aheader );
	SBoneCalc &Root();
	const mdxaBone_t &EvalUnsmooth( int index );
	const mdxaBone_t &Eval( int index );
	const mdxaBone_t &EvalRender( int index );
	bool WasRendered( int index );
	int GetParent( int index );
};
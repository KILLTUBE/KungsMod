#pragma once

// todo its just a copy from somewhere
// must be a power of two
#define MAX_G2_MODELS (1024)
#define G2_MODEL_BITS (10)
#define G2_INDEX_MASK (MAX_G2_MODELS-1)

class Ghoul2InfoArray : public IGhoul2InfoArray {
public:
	std::vector<CGhoul2Info>	mInfos[MAX_G2_MODELS];
	int					mIds[MAX_G2_MODELS];
	std::list<int>			mFreeIndecies;
	void DeleteLow(int idx);
	Ghoul2InfoArray();

	size_t GetSerializedSize() const;

	size_t Serialize ( char *buffer ) const;

	size_t Deserialize ( const char *buffer, size_t size );

#if G2API_DEBUG
	~Ghoul2InfoArray();
#endif
	int New();
	bool IsValid(int handle) const;
	void Delete(int handle);
	std::vector<CGhoul2Info> &Get(int handle);
	const std::vector<CGhoul2Info> &Get(int handle) const;

#if G2API_DEBUG
	vector<CGhoul2Info> &GetDebug(int handle);
	void TestAllAnims();

#endif
};
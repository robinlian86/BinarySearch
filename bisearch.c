#include <stdio.h>
#include <assert.h>
#define NAME_MAX_LEN    255

typedef struct
{
	int nId;
	char acName[NAME_MAX_LEN];
}T_IDNAME_MAP;

typedef int (*GetMidValFPtr)(const void *pArray, int nMid);

int bsearch(const int nDestVal, const void *pArray, int nNum, GetMidValFPtr pGetMidVal)
{
	int nLeft   = 0;
	int nRight  = 0;
	int nMid    = 0;
	int nTmpVal = 0;

	assert(pArray);
	assert(pGetMidVal);

	nRight = nNum - 1;
	while (nLeft <= nRight)
	{
		nMid = nLeft + ((nRight - nLeft) >> 1);
		nTmpVal = pGetMidVal(pArray, nMid);

		if (nDestVal > nTmpVal)
		{
			nLeft = nMid + 1;
		}
		else if (nDestVal < nTmpVal)
		{
			nRight = nMid -1;
		}
		else
		{
			return nMid;
		}
	}

	return -1;
}

int GetMidValue(const void *pArray, int nMid)
{
	T_IDNAME_MAP *ptMap = NULL;

	assert(pArray);

	ptMap = (T_IDNAME_MAP*)pArray;
	return ptMap[nMid].nId;
}

int main()
{
	int nId  = 0;
	int nMid = 0;
	T_IDNAME_MAP tMap[] = 
	{
		{2,   "xiaoer"},
		{38, "xiaoming"},
		{56, "xiaoli"},
		{250, "lese"},
	};
	for(;;)
	{
		printf("please input the info of ID\n");
		if (1 != scanf("%d", &nId))
		{
			return -1;
		}

		nMid = bsearch(nId, (void*)tMap, sizeof(tMap)/sizeof(T_IDNAME_MAP), GetMidValue);

		if (-1 == nMid)
		{
			printf("the ID:%d is not in the library\n", nId);
		}
		else
		{
			printf("the name of ID:%d is %s\n", nId, tMap[nMid].acName);
		}
	}

	return 0;
}
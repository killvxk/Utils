class CVMTHookManager
{
public:
	CVMTHookManager(void)
	{
		memset(this, 0, sizeof(CVMTHookManager));
	}

	CVMTHookManager(intptr_t** ppdwClassBase)
	{
		bInitialize(ppdwClassBase);
	}

	~CVMTHookManager(void)
	{
		UnHook();
	}
	bool bInitialize(intptr_t** ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT =  *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new intptr_t[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(intptr_t) * m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;
		return true;
	}
	bool bInitialize(intptr_t*** pppdwClassBase) // fix for pp
	{
		return bInitialize(*pppdwClassBase);
	}

	void UnHook(void)
	{
		dwHookMethod(oFunction, unhookindex);
	}

	void ReHook(void)
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}

	int iGetFuncCount(void)
	{
		return (int)m_dwVMTSize;
	}

	intptr_t dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
		{
			unhookindex = Index;
			oFunction = m_pdwOldVMT[Index];
			return m_pdwOldVMT[Index];
		}
		return NULL;
	}

	intptr_t* pdwGetOldVMT(void)
	{
		return m_pdwOldVMT;
	}

	intptr_t dwHookMethod(intptr_t dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return m_pdwOldVMT[iIndex];
		}

		return NULL;
	}

private:
	intptr_t**	m_ppdwClassBase;
	intptr_t*	m_pdwNewVMT;
	intptr_t*		m_pdwOldVMT;
	intptr_t	m_dwVMTSize, oFunction;
	int unhookindex;
	intptr_t dwGetVMTCount(intptr_t* pdwVMT)
	{
		intptr_t dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
			{
				break;
			}
		}
		return dwIndex;
	}
};

intptr_t dwGetVMTCount2(intptr_t* pdwVMT)
{
	intptr_t dwIndex = 0;

	for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
	{
		if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
		{
			break;
		}
	}
	return dwIndex;
}
void* HookVtblFunction(void* pClassInstance,void* dwHook, const int Index )
{
	void* pOrig;
	intptr_t *vtable = (intptr_t *)*(intptr_t *)pClassInstance;
	pOrig = (void*)(vtable[Index]);
	if (pOrig != dwHook) {
		intptr_t newVtableSize = dwGetVMTCount2(vtable);
	intptr_t* newVtable = new intptr_t[newVtableSize]; //leave some space
	memcpy(newVtable, vtable, newVtableSize * sizeof(intptr_t));
	newVtable[Index] = (intptr_t)dwHook;

	DWORD dwOld;

	VirtualProtect(pClassInstance, sizeof(intptr_t), PAGE_EXECUTE_READWRITE, &dwOld);

	*(intptr_t *)pClassInstance = (intptr_t)newVtable; //Replace Vtable

	VirtualProtect(pClassInstance, sizeof(intptr_t), dwOld, NULL);

}

	return pOrig;
}

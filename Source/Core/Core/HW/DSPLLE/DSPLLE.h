// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "Common/Thread.h"

#include "Core/DSPEmulator.h"
#include "Core/HW/DSPLLE/DSPLLEGlobals.h"

class DSPLLE : public DSPEmulator
{
public:
	DSPLLE();

	virtual bool Initialize(void *hWnd, bool bWii, bool bDSPThread) override;
	virtual void Shutdown() override;
	virtual bool IsLLE() override { return true; }

	virtual void DoState(PointerWrap &p) override;
	virtual void PauseAndLock(bool doLock, bool unpauseOnUnlock=true) override;

	virtual void DSP_WriteMailBoxHigh(bool _CPUMailbox, unsigned short) override;
	virtual void DSP_WriteMailBoxLow(bool _CPUMailbox, unsigned short) override;
	virtual unsigned short DSP_ReadMailBoxHigh(bool _CPUMailbox) override;
	virtual unsigned short DSP_ReadMailBoxLow(bool _CPUMailbox) override;
	virtual unsigned short DSP_ReadControlRegister() override;
	virtual unsigned short DSP_WriteControlRegister(unsigned short) override;
	virtual const short *DSP_PeekAIBuffer(unsigned int address, unsigned int num_samples);
	virtual void DSP_Update(int cycles) override;
	virtual void DSP_StopSoundStream() override;
	virtual u32 DSP_UpdateRate() override;

private:
	static void dsp_thread(DSPLLE* lpParameter);

	std::thread m_hDSPThread;
	std::mutex m_csDSPThreadActive;
	bool m_bWii;
	bool m_bDSPThread;
	bool m_bIsRunning;
	volatile u32 m_cycle_count;
};

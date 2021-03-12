//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once
#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes
#include <windows.h>

// Prototypes
class CClock
{
    public:
        CClock();
        ~CClock();

        bool Initialise();
        void Process();
        float GetDeltaTick();

    private:
        CClock(const CClock& _kr);
    protected:
         double m_fTimeElapsed;
         double m_fDeltaTime;
         double m_fLastTime;
         double m_fCurrentTime;
         double m_SecondsPerCount;
         int m_iFrameCount = 0;

    private:

};
#endif

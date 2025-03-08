#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "types.h"
#include "Graphics.h"
#include "Physics/Particle.h"
#include "Physics/Ball.h"

#define TARGET_FPS 60.0
#define TARGET_MS_PF (1000.0 / TARGET_FPS)

#define PIXELS_PER_METER 150

#ifdef _DEBUG // Defined when build mode is Debug
//#define _IN_DEBUGGER
#define _DEBUG_FPS
#endif // _DEBUG

#define METERS(m) ((uint32)(float32)m * (float32)PIXELS_PER_METER)

class Application {
    private:
        bool running = false;
        Particle *particle;
        Ball *ball;

        // FPS timer
        uint64 performanceFreq = 0;
        uint64 prevFrameTimestamp = 0;

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
        void FrameDelay(uint64 frameStartTimestamp, float64 targetMsPf);
        float64 getElapsedMsFromQPC(uint64 startTicks, uint64 endTicks);
};

#endif
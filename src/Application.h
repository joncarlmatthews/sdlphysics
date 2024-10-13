#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "types.h"
#include "Graphics.h"
#include "Physics/Particle.h"
#include "Physics/Ball.h"

#define CAP_FRAMERATE true

#if CAP_FRAMERATE
#define TARGET_FPS 30
#define TARGET_MS_PF (1000 / TARGET_FPS)
#endif

#define PIXELS_PER_METER 150

#ifdef _DEBUG
//#define _DEBUG_FPS true
#endif // _DEBUG

#define METERS(m) ((uint32)(float32)m * (float32)PIXELS_PER_METER)

class Application {
    private:
        bool running = false;
        Particle *particle;
        Ball *ball;
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
};

#endif
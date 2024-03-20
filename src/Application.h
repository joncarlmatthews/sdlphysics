#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "types.h"
#include "Graphics.h"
#include "Physics/Particle.h"

#define TARGET_FPS 60
#define TARGET_MS_PF (1000 / TARGET_FPS)

#ifdef _DEBUG
//#define _DEBUG_FPS true
#endif // _DEBUG


class Application {
    private:
        bool running = false;
        Particle *particle;
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
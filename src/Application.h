#ifndef APPLICATION_H
#define APPLICATION_H

#include "types.h"
#include "Graphics.h"
#include "Physics/Particle.h"

#define TARGET_FPS 60
#define TARGET_MS_PF (1000 / TARGET_FPS)

class Application {
    private:
        bool running = false;
        Particle *particle;
        uint32 timePreviousFrame = 0;

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
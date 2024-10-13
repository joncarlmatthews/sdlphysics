#include "Application.h"

bool Application::IsRunning() {
    return this->running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    this->running = Graphics::OpenWindow();
    this->prevFrameTimestamp = SDL_GetTicks64();

    // setup objects in the scene
    this->particle = new Particle(10.0f, 10.0f, 1.0f);
    this->ball = new Ball(0.0f, 0.0f, 1.0f, 20.0f);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {
    
    uint64 frameStartTimestamp = SDL_GetTicks64();

    // Delta time (in seconds) The time taken between this frame starting
    // and the program execution to make it all the way back around to here again.
    float32 deltaTime = ((frameStartTimestamp - this->prevFrameTimestamp) / 1000.0f);
    this->prevFrameTimestamp = SDL_GetTicks64(); // "Start the clock"

#ifdef _DEBUG_FPS
    static sizet frameIndex = 0;
    std::cout << "Frame " << frameIndex << std::endl;
    std::cout << "Delta time: " << deltaTime << std::endl;
#endif // _DEBUG_FPS
   
#ifdef _DEBUG
    // Clamp the framerate when in debugger
    if(deltaTime > 0.033){
        deltaTime = 0.033;
    }
#endif // DEBUG

#if true
    this->particle->acceleration = Vec2(0.0f, METERS(2.6)); // Acceleration == how much to increase the velocity by each frame
    
    // Integrate the acceleration and velocity to find the new position
    this->particle->velocity += (this->particle->acceleration * deltaTime);
    this->particle->position += (this->particle->velocity * deltaTime);
#endif

    if (this->particle->position.y > Graphics::windowHeight) {
        this->particle->position.y = (Graphics::windowHeight-4);
    }
    if (this->particle->position.x > Graphics::windowWidth) {
        this->particle->position.x = (Graphics::windowWidth-4);
    }

#if CAP_FRAMERATE
    uint64 frameProcessingTime = (SDL_GetTicks64() - frameStartTimestamp);

#ifdef _DEBUG_FPS
    std::cout << "Processing time: " << frameProcessingTime << "ms" << std::endl;
#endif // _DEBUG_FPS
    
    int64 msToSleep = (TARGET_MS_PF - frameProcessingTime);
    if(msToSleep > 0){
#ifdef _DEBUG_FPS
        std::cout << "Need to sleep for: " << msToSleep << "ms" << std::endl;
#endif // _DEBUG
        SDL_Delay(msToSleep);
    }

#ifdef _DEBUG_FPS
    std::cout << "Frame took: " << (SDL_GetTicks64() - frameStartTimestamp) << "ms. Target: " << TARGET_MS_PF << "ms" << std::endl << std::endl;
    frameIndex++;
#endif // _DEBUG_FPS

#endif // CAP_FRAMERATE

}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(this->particle->position.x, this->particle->position.y, 4, 0xFFFFFFFF);
    //this->ball->Draw();
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    // TODO: destroy all objects in the scene
    delete this->particle;
    delete this->ball;

    Graphics::CloseWindow();
}
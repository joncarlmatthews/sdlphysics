#include "Application.h"

bool Application::IsRunning() {
    return this->running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    SDL_Init(SDL_INIT_TIMER);
    this->running = Graphics::OpenWindow();

    this->performanceFreq = SDL_GetPerformanceFrequency();
    this->prevFrameTimestamp = SDL_GetPerformanceCounter();

    /*
    SDL_DisplayMode mode;
    if(SDL_GetCurrentDisplayMode(0, &mode) == 0){
        int refreshRate = mode.refresh_rate;
        std::cout << "Monitor Refresh Rate: " << refreshRate << " Hz" << std::endl;
    } else{
        std::cerr << "Failed to get display mode: " << SDL_GetError() << std::endl;
    }
    */

    // setup objects in the scene
    this->particle = new Particle(10.0f, 10.0f, 1.0f);
    this->ball = new Ball(25.0f, 25.0f, 1.0f, 20);
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
    
    uint64 frameStartTimestamp = SDL_GetPerformanceCounter();

    // Delta time (in seconds) The time taken between this frame starting
    // and the program execution to make it all the way back around to here again.
    float32 deltaTime = ((float32)(frameStartTimestamp - this->prevFrameTimestamp) / this->performanceFreq);

    // How long in ms has elapsed between this frame starting and the previous one ending?
    float64 msElapsed = this->getElapsedMsFromQPC(this->prevFrameTimestamp, frameStartTimestamp);

    this->prevFrameTimestamp = frameStartTimestamp;

    static sizet frameIndex = 0;

    std::cout << "Frame " << frameIndex << std::endl;
    std::cout << "Time elapsed since last frame " << msElapsed << std::endl;

#ifdef _DEBUG_FPS
    std::cout << "Delta time: " << deltaTime << std::endl;
#endif // _DEBUG_FPS
   
#ifdef _IN_DEBUGGER
    // Clamp the framerate when in debugger
    if(deltaTime > 0.016){
        deltaTime = 0.016;
    }
#endif // _IN_DEBUGGER

    this->ball->acceleration = Vec2(METERS(2.6), METERS(2.6)); // Acceleration == how much to increase the velocity by each frame
    //this->ball->acceleration = Vec2(0, 0);
    
    // Integrate the acceleration and velocity to find the new position
    this->ball->velocity += (this->ball->acceleration * deltaTime);
    this->ball->position += (this->ball->velocity * deltaTime);

    if (this->ball->position.y < this->ball->radius){
        this->ball->velocity.y = (this->ball->velocity.y * -1);
        this->ball->position.y = this->ball->radius;
    }else if (this->ball->position.y >= Graphics::windowHeight) {
        this->ball->velocity.y = (this->ball->velocity.y*-1);
        this->ball->position.y = (Graphics::windowHeight - this->ball->radius);
    }

    if(this->ball->position.x <= this->ball->radius){
        this->ball->velocity.x = (this->ball->velocity.x * -1);
        this->ball->position.x = this->ball->radius;
    }else if (this->ball->position.x >= Graphics::windowWidth) {
        this->ball->velocity.x = (this->ball->velocity.x * -1);
        this->ball->position.x = (Graphics::windowWidth - this->ball->radius);
    }

    FrameDelay(frameStartTimestamp, TARGET_MS_PF);

    frameIndex++;
}

void Application::FrameDelay(uint64 frameStartTimestamp, float64 targetMsPf){

    float64 frameProcessingTime = this->getElapsedMsFromQPC(frameStartTimestamp, SDL_GetPerformanceCounter());

#ifdef _DEBUG_FPS
    std::cout << "Processing time: " << frameProcessingTime << "ms" << std::endl;
#endif

    float64 targetMsToSleep = (targetMsPf - frameProcessingTime);

    if(targetMsToSleep > 0){

#ifdef _DEBUG_FPS
        std::cout << "Need to sleep for: " << targetMsToSleep << "ms" << std::endl;
#endif

        // Due to the unprecise nature of SDL_Delay, only use it for 10% of the required
        // sleep time. Spin lock for the rest...
        float64 sleepMs = (targetMsToSleep * 0.1);
        uint32 sdlSleepMs = (uint32)sleepMs;

        if(sdlSleepMs > 0){
#ifdef _DEBUG_FPS
            std::cout << "Delay sleeping for: " << sdlSleepMs << "ms" << std::endl;
#endif
            SDL_Delay(sdlSleepMs);
        }

#ifdef _DEBUG_FPS
        std::cout << "Spinning for anything remaining..." << std::endl;
#endif

        // Spin lock for last few ms for higher precision
        volatile uint64 *startCounter = &frameStartTimestamp;  // Prevents compiler optimization

        while(((double)(SDL_GetPerformanceCounter() - *startCounter) * 1000.0 / this->performanceFreq) < targetMsPf);
 
    }

#ifdef _DEBUG_FPS
    std::cout << "Frame took: " << this->getElapsedMsFromQPC(frameStartTimestamp, SDL_GetPerformanceCounter()) << "ms. Target: " << targetMsPf << "ms" << std::endl << std::endl;
#endif

    
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(this->particle->position.x, this->particle->position.y, 4, 0xFFFFFFFF);
    this->ball->Draw();
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

float64 Application::getElapsedMsFromQPC(uint64 startTicks, uint64 endTicks)
{
    return ( ((float64)(endTicks - startTicks)) * 1000.0 / this->performanceFreq);
}
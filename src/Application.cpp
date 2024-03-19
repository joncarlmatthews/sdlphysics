#include "Application.h"

bool Application::IsRunning() {
    return this->running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    this->running = Graphics::OpenWindow();

    // setup objects in the scene
    this->particle = new Particle(50.0f, 100.0f, 1.0f);
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
    // update all objects in the scene
    int32 msToSleep = (TARGET_MS_PF - (SDL_GetTicks() - this->timePreviousFrame));
    if(msToSleep > 0){
        SDL_Delay(msToSleep);
    }

    this->timePreviousFrame = SDL_GetTicks();

    // Constant velocity:
    this->particle->velocity = Vec2(5.0f, 0.0f);
    this->particle->position += this->particle->velocity;
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(this->particle->position.x, this->particle->position.y, 4, 0xFFFFFFFF);
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    // TODO: destroy all objects in the scene
    delete this->particle;

    Graphics::CloseWindow();
}
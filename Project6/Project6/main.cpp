/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/


#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "SDL_mixer.h"

#include "Util.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Scene.hpp"
#include "Level.hpp"
#include "Menu.hpp"

#include <vector>

SDL_Window* g_display_window;
bool g_game_is_running = true;

ShaderProgram g_shader_program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;
bool larry_won = false;
bool larry_lost = false;

Scene* curr_scene;
Scene* sceneList[2];

Mix_Music* music;
Mix_Chunk* bruh;
int lose_count = 0;

void UpdateScene(Scene* scene) {
    curr_scene = scene;
    curr_scene->initialise();
}

void initialise() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("DON'T TOUCH THE LAVA LARRY!",
                                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);

#ifdef _WINDOWS
    glewInit();
#endif
    glViewport(0, 0, 960, 720); //Change the view port to make the camera zoomed in.
    //glViewport(0, 0, 240, 180);

    g_shader_program.load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("start_game.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME/4);

    bruh = Mix_LoadWAV("bruh.wav");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    g_shader_program.set_projection_matrix(projectionMatrix);
    g_shader_program.set_view_matrix(viewMatrix);

    glUseProgram(g_shader_program.get_program_id());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sceneList[0] = new menu();
    sceneList[1] = new Level();
    UpdateScene(sceneList[0]);
}
void process_input() {

    curr_scene->state.player->movement = glm::vec3(0);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            g_game_is_running = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                // Move the player left
                break;

            case SDLK_RIGHT:
                // Move the player right
                break;

            case SDLK_SPACE:
                break;
            case SDLK_RETURN:
                if (curr_scene == sceneList[0] || larry_lost) {
                    UpdateScene(sceneList[1]);
                    music = Mix_LoadMUS("ninja.mp3");
                    Mix_PlayMusic(music, -1);
                    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
                    lose_count = 0;
                }
                break;
            }
            break; // SDL_KEYDOWN
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        curr_scene->state.player->movement.x = -1.0f;
        curr_scene->state.player->movement.y = 0.0f;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        curr_scene->state.player->movement.x = 1.0f;
        curr_scene->state.player->movement.y = 0.0f;
    }
    else if (keys[SDL_SCANCODE_UP]) {
        curr_scene->state.player->movement.y = 1.0f;
        curr_scene->state.player->movement.x = 0.0f;
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        curr_scene->state.player->movement.y = -1.0f;
        curr_scene->state.player->movement.x = 0.0f;
    }
    if (glm::length(curr_scene->state.player->movement) > 1.0f)
        curr_scene->state.player->movement = glm::normalize(curr_scene->state.player->movement);

}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP) {
        curr_scene->update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;
    }
    accumulator = deltaTime;

    viewMatrix = glm::mat4(1.0f);
    if (curr_scene->state.player->position.x > -100 &&
        curr_scene->state.player->position.x < 100) {
        viewMatrix = glm::translate
        
        (viewMatrix, glm::vec3(-curr_scene->state.player->position.x - 1.25,
            -curr_scene->state.player->position.y - 0.875, 0));
          
    }
}
  
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    g_shader_program.set_view_matrix(viewMatrix);
    if(!curr_scene->state.won && curr_scene->state.player->is_active)
        curr_scene->render(&g_shader_program);
    if(curr_scene->state.player->position.y < -42.5){
        larry_won = true;
        viewMatrix = glm::mat4(1.0f);
        g_shader_program.set_view_matrix(viewMatrix);
        Util::draw_text(&g_shader_program, Util::load_texture("font1.png"), "You Win!",
            0.5f, -0.2f, glm::vec3(-2.75f, -1.25f, 0));
    }
    else if (!(curr_scene->state.player->is_active)) {
        viewMatrix = glm::mat4(1.0f);
        g_shader_program.set_view_matrix(viewMatrix);
        if (lose_count == 0) {
            Mix_PlayChannel(-1, bruh, 0);
            lose_count += 1;
        }
        Util::draw_text(&g_shader_program, Util::load_texture("font1.png"), "You Lose!",
            0.5f, -0.2f, glm::vec3(-2.75f, -1.25f, 0));
        larry_lost = true;
    }
    SDL_GL_SwapWindow(g_display_window);
}


void shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    initialise();

    while (g_game_is_running) {
        process_input();
        update();
        if (curr_scene->state.nextScene > 0) UpdateScene(sceneList
            [curr_scene->state.nextScene]);
        render();
    }

    shutdown();
    return 0;
}

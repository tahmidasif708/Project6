/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Menu.hpp"
#define MENU_WIDTH 11
#define MENU_HEIGHT 8

unsigned int menu_data[] =
{
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void menu::initialise() {

    state.nextScene = 0;
    GLuint mapTextureID = Util::load_texture("lava.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 4, 1);
    // Initialize Game Objects
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(4, -2, 0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 3.5f;
    state.player->height = 0.8f;
    state.player->width = 0.7f;
    state.player->textureID = Util::load_texture("larry.png");
}

void menu::update(float deltaTime) {
    state.player->update(deltaTime, state.player, state.enemies, 0, state.map);
  
    if (state.player->position.x >= 12) state.nextScene = 1;
}
void menu::render(ShaderProgram* g_shader_program) {
    Util::draw_text(g_shader_program, Util::load_texture("font1.png"), "RUN",
        0.6f, 0.2f, glm::vec3(1.50f, -0.5f, 0));
    Util::draw_text(g_shader_program, Util::load_texture("font1.png"), "LARRY RUN!",
        0.4f, 0.1f, glm::vec3(2.0f, -1.0f, 0));
    Util::draw_text(g_shader_program, Util::load_texture("font1.png"),
        "Press Enter to Start!",
        0.25f, 0.0f, glm::vec3(1.0f, -4.0f, 0));
    state.map->render(g_shader_program);
    state.player->render(g_shader_program);
   
}

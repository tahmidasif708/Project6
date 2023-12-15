/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#pragma once
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

#include "Map.hpp"
#include "Util.hpp"

enum EntityType {PLAYER, PLATFORM, ENEMY};
enum AIType { FOLLOWER, GUARD, VERTICAL_WALKER, HORIZONTAL_WALKER};
enum AIState {IDLE, FOLLOW, PATROLX, PATROLY};

class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState;

    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 velocity;
    glm::vec3 load_in;

    float width = 1;
    float height = 1;

    bool is_jumping = false;
    float jumping_power = 6;

    float speed;

    GLuint textureID;

    glm::mat4 modelMatrix;

    int* animation_right = NULL;
    int* animation_left = NULL;
    int* animation_up = NULL;
    int* animation_down = NULL;

    int* animation_indices = NULL;
    int animation_frames = 0;
    int animation_index = 0;
    float animation_time = 0;
    int animation_cols = 0;
    int animation_rows = 0;

    bool is_active = true;

    bool collided_top = false;
    bool collided_bottom = false;
    bool collided_left = false;
    bool collided_right = false;

    bool hit = true; // Collision will hurt

    int lives;

    Entity();

    bool CheckCollision(Entity *other);
    void CheckCollisionsY(Entity* objects, int objectCount);
    void CheckCollisionsX(Entity* objects, int objectCount);
    void CheckCollisionsY(Map* map);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsXY(Map* map);

    void player_status(Entity* enemies, int enemyCount);
    void update(float deltaTime, Entity* player, Entity* objects, int objectCount, Map* map);
    void render(ShaderProgram* g_shader_program);
    void draw_sprite_from_texture_atlas(ShaderProgram* g_shader_program, GLuint textureID, int index);

    void AI(Entity *player);
    void AIWalker();
    void AIWaitAndGo(Entity *player);
    void AIWatch(Entity *player);
    void AIMove(Entity *player);
    void AIFollower(Entity* player);
    void AIGuard(Entity* player);
    void AIVerticalWalker(Entity* player);
    void AIHorizontalWalker(Entity* player);
};

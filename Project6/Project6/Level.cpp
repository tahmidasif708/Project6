/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Level.hpp"
#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 21

#define ENEMY_COUNT 42
unsigned int level_data[] =
{
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3,
 3, 0, 3, 0, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 3, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3,
 3, 0, 3, 3, 3, 0, 3, 0, 0, 3, 3, 0, 3, 0, 3, 3, 3, 3, 0, 3,
 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3,
 3, 0, 0, 3, 0, 0, 3, 0, 3, 0, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3,
 3, 0, 3, 3, 0, 3, 3, 0, 3, 0, 3, 3, 0, 0, 0, 3, 3, 3, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 3, 0, 0, 0, 0, 0, 3,
 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 0, 0, 3, 3, 3, 3, 3, 0, 3,
 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 3, 3, 0, 0, 3,
 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 0, 0, 3, 3, 0, 3, 3,
 3, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3,
 3, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 3, 3, 0, 3, 0, 0, 0, 3,
 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3,
 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 0, 3,
 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3,
 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 3, 3, 0, 3, 3, 3,
 3, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3
};

void Level::initialise() {

    //state.nextScene = -1;
    GLuint mapTextureID = Util::load_texture("lava.png");
    state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, level_data, mapTextureID, 2.0f, 4, 1);
    // Initialize Game Objects
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2, -3, 0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 9.0f;
    state.player->height = 0.8f;
    state.player->width = 0.7f;
    state.player->textureID = Util::load_texture("larry.png");

    
    state.enemies = new Entity[ENEMY_COUNT];
    GLuint bossTextureID = Util::load_texture("boss.png");
    GLuint alien1TextureID = Util::load_texture("alien1.png");
    GLuint alien2TextureID = Util::load_texture("alien2.png");
    GLuint alien3TextureID = Util::load_texture("alien3.png");

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;

    }
   
    state.enemies[0].textureID = bossTextureID;
    state.enemies[0].position = glm::vec3(2.0f, 3.0f, 0);
    state.enemies[0].speed = 2;
    state.enemies[0].aiType = FOLLOWER;
    state.enemies[0].aiState = FOLLOW;
    state.enemies[0].is_active = true;

    state.enemies[1].textureID = alien1TextureID;
    state.enemies[1].position = glm::vec3(2.0f, -7.0f, 0);
    state.enemies[1].load_in = glm::vec3(2.0f, -7.0f, 0);
    state.enemies[1].speed = 0.7;
    state.enemies[1].aiType = GUARD;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].is_active = true;

    state.enemies[2].textureID = alien2TextureID;
    state.enemies[2].position = glm::vec3(6.0f, -6.0f, 0);
    state.enemies[2].load_in = glm::vec3(6.0f, -6.0f, 0);
    state.enemies[2].speed = 0.8;
    state.enemies[2].aiType = VERTICAL_WALKER;
    state.enemies[2].aiState = PATROLY;
    state.enemies[2].is_active = true;

    state.enemies[3].textureID = alien2TextureID;
    state.enemies[3].position = glm::vec3(6.0f, -10.0f, 0);
    state.enemies[3].load_in = glm::vec3(6.0f, -10.0f, 0);
    state.enemies[3].speed = 0.8;
    state.enemies[3].aiType = HORIZONTAL_WALKER;
    state.enemies[3].aiState = PATROLX;
    state.enemies[3].is_active = true;

    state.enemies[4].textureID = alien3TextureID;
    state.enemies[4].position = glm::vec3(6.0f, -4.0f, 0);
    state.enemies[4].load_in = glm::vec3(6.0f, -4.0f, 0);
    state.enemies[4].speed = 0.8;
    state.enemies[4].aiType = HORIZONTAL_WALKER;
    state.enemies[4].aiState = PATROLX;
    state.enemies[4].is_active = true;

    state.enemies[5].textureID = alien3TextureID;
    state.enemies[5].position = glm::vec3(12.0f, -10.0f, 0);
    state.enemies[5].load_in = glm::vec3(12.0f, -10.0f, 0);
    state.enemies[5].speed = 1.9;
    state.enemies[5].aiType = VERTICAL_WALKER;
    state.enemies[5].aiState = PATROLY;
    state.enemies[5].is_active = true;

    state.enemies[6].textureID = alien1TextureID;
    state.enemies[6].position = glm::vec3(9.0f, -2.0f, 0);
    state.enemies[6].load_in = glm::vec3(9.0f, -2.0f, 0);
    state.enemies[6].speed = 0.8;
    state.enemies[6].aiType = GUARD;
    state.enemies[6].aiState = IDLE;
    state.enemies[6].is_active = true;

    state.enemies[7].textureID = alien1TextureID;
    state.enemies[7].position = glm::vec3(12.0f, -1.0f, 0);
    state.enemies[7].load_in = glm::vec3(12.0f, -1.0f, 0);
    state.enemies[7].speed = 0.8;
    state.enemies[7].aiType = GUARD;
    state.enemies[7].aiState = IDLE;
    state.enemies[7].is_active = true;

    state.enemies[8].textureID = alien2TextureID;
    state.enemies[8].position = glm::vec3(15.0f, -3.0f, 0);
    state.enemies[8].load_in = glm::vec3(15.0f, -3.0f, 0);
    state.enemies[8].speed = 0.8;
    state.enemies[8].aiType = HORIZONTAL_WALKER;
    state.enemies[8].aiState = PATROLX;
    state.enemies[8].is_active = true;

    state.enemies[9].textureID = alien1TextureID;
    state.enemies[9].position = glm::vec3(20.0f, -10.0f, 0);
    state.enemies[9].load_in = glm::vec3(20.0f, -10.0f, 0);
    state.enemies[9].speed = 0.8;
    state.enemies[9].aiType = GUARD;
    state.enemies[9].aiState = IDLE;
    state.enemies[9].is_active = true;

    state.enemies[10].textureID = alien2TextureID;
    state.enemies[10].position = glm::vec3(20.0f, -14.0f, 0);
    state.enemies[10].load_in = glm::vec3(20.0f, -14.0f, 0);
    state.enemies[10].speed = 0.8;
    state.enemies[10].aiType = VERTICAL_WALKER;
    state.enemies[10].aiState = PATROLY;
    state.enemies[10].is_active = true;

    state.enemies[11].textureID = alien2TextureID;
    state.enemies[11].position = glm::vec3(24.0f, -11.0f, 0);
    state.enemies[11].load_in = glm::vec3(24.0f, -11.0f, 0);
    state.enemies[11].speed = 0.8;
    state.enemies[11].aiType = VERTICAL_WALKER;
    state.enemies[11].aiState = PATROLY;
    state.enemies[11].is_active = true;

    state.enemies[12].textureID = alien2TextureID;
    state.enemies[12].position = glm::vec3(20, -3, 0);
    state.enemies[12].load_in = glm::vec3(20, -3, 0);
    state.enemies[12].speed = 0.8;
    state.enemies[12].aiType = HORIZONTAL_WALKER;
    state.enemies[12].aiState = PATROLX;
    state.enemies[12].is_active = true;

    state.enemies[13].textureID = alien2TextureID;
    state.enemies[13].position = glm::vec3(22, -1, 0);
    state.enemies[13].load_in = glm::vec3(22, -1, 0);
    state.enemies[13].speed = 3.0;
    state.enemies[13].aiType = VERTICAL_WALKER;
    state.enemies[13].aiState = PATROLY;
    state.enemies[13].is_active = true;

    state.enemies[14].textureID = alien3TextureID;
    state.enemies[14].position = glm::vec3(26, -1, 0);
    state.enemies[14].load_in = glm::vec3(26, -1, 0);
    state.enemies[14].speed = 3.0;
    state.enemies[14].aiType = VERTICAL_WALKER;
    state.enemies[14].aiState = PATROLY;
    state.enemies[14].is_active = true;

    state.enemies[16].textureID = alien2TextureID;
    state.enemies[16].position = glm::vec3(28, -2, 0);
    state.enemies[16].load_in = glm::vec3(28, -2, 0);
    state.enemies[16].speed = 3.0;
    state.enemies[16].aiType = VERTICAL_WALKER;
    state.enemies[16].aiState = PATROLY;
    state.enemies[16].is_active = true;

    state.enemies[17].textureID = alien3TextureID;
    state.enemies[17].position = glm::vec3(29.5, -3, 0);
    state.enemies[17].load_in = glm::vec3(29.5, -3, 0);
    state.enemies[17].speed = 1.5;
    state.enemies[17].aiType = VERTICAL_WALKER;
    state.enemies[17].aiState = PATROLY;
    state.enemies[17].is_active = true;

    state.enemies[18].textureID = alien2TextureID;
    state.enemies[18].position = glm::vec3(31, -2.5, 0);
    state.enemies[18].load_in = glm::vec3(31, -2.5, 0);
    state.enemies[18].speed = 3.0;
    state.enemies[18].aiType = VERTICAL_WALKER;
    state.enemies[18].aiState = PATROLY;
    state.enemies[18].is_active = true;

    state.enemies[19].textureID = alien1TextureID;
    state.enemies[19].position = glm::vec3(34, -4, 0);
    state.enemies[19].load_in = glm::vec3(34, -4, 0);
    state.enemies[19].speed = 1.0;
    state.enemies[19].aiType = GUARD;
    state.enemies[19].aiState = IDLE;
    state.enemies[19].is_active = true;

    state.enemies[20].textureID = alien1TextureID;
    state.enemies[20].position = glm::vec3(1, -13, 0);
    state.enemies[20].load_in = glm::vec3(1, -13, 0);
    state.enemies[20].speed = 1.0;
    state.enemies[20].aiType = GUARD;
    state.enemies[20].aiState = IDLE;
    state.enemies[20].is_active = true;

    state.enemies[21].textureID = alien1TextureID;
    state.enemies[21].position = glm::vec3(1, -20, 0);
    state.enemies[21].load_in = glm::vec3(1, -20, 0);
    state.enemies[21].speed = 0.5;
    state.enemies[21].aiType = GUARD;
    state.enemies[21].aiState = IDLE;
    state.enemies[21].is_active = true;

    state.enemies[22].textureID = alien1TextureID;
    state.enemies[22].position = glm::vec3(3, -22, 0);
    state.enemies[22].load_in = glm::vec3(3, -22, 0);
    state.enemies[22].speed = 0.5;
    state.enemies[22].aiType = GUARD;
    state.enemies[22].aiState = IDLE;
    state.enemies[22].is_active = true;

    state.enemies[23].textureID = alien1TextureID;
    state.enemies[23].position = glm::vec3(3.5, -26, 0);
    state.enemies[23].load_in = glm::vec3(3.5, -26, 0);
    state.enemies[23].speed = 1.0;
    state.enemies[23].aiType = GUARD;
    state.enemies[23].aiState = IDLE;
    state.enemies[23].is_active = true;

    state.enemies[24].textureID = alien1TextureID;
    state.enemies[24].position = glm::vec3(2, -29, 0);
    state.enemies[24].load_in = glm::vec3(2, -29, 0);
    state.enemies[24].speed = 1.0;
    state.enemies[24].aiType = GUARD;
    state.enemies[24].aiState = IDLE;
    state.enemies[24].is_active = true;

    state.enemies[24].textureID = alien1TextureID;
    state.enemies[24].position = glm::vec3(0, -33, 0);
    state.enemies[24].load_in = glm::vec3(0, -33, 0);
    state.enemies[24].speed = 0.9;
    state.enemies[24].aiType = GUARD;
    state.enemies[24].aiState = IDLE;
    state.enemies[24].is_active = true;

    state.enemies[25].textureID = alien1TextureID;
    state.enemies[25].position = glm::vec3(7, -34, 0);
    state.enemies[25].load_in = glm::vec3(7, -34, 0);
    state.enemies[25].speed = 0.5;
    state.enemies[25].aiType = GUARD;
    state.enemies[25].aiState = IDLE;
    state.enemies[25].is_active = true;

    state.enemies[26].textureID = alien2TextureID;
    state.enemies[26].position = glm::vec3(9, -30, 0);
    state.enemies[26].load_in = glm::vec3(9, -30, 0);
    state.enemies[26].speed = 0.9;
    state.enemies[26].aiType = HORIZONTAL_WALKER;
    state.enemies[26].aiState = PATROLY;
    state.enemies[26].is_active = true;

    state.enemies[27].textureID = alien2TextureID;
    state.enemies[27].position = glm::vec3(34, -10, 0);
    state.enemies[27].load_in = glm::vec3(34, -10, 0);
    state.enemies[27].speed = 0.9;
    state.enemies[27].aiType = VERTICAL_WALKER;
    state.enemies[27].aiState = PATROLY;
    state.enemies[27].is_active = true;

    state.enemies[28].textureID = alien2TextureID;
    state.enemies[28].position = glm::vec3(30, -15, 0);
    state.enemies[28].load_in = glm::vec3(30, -15, 0);
    state.enemies[28].speed = 0.9;
    state.enemies[28].aiType = HORIZONTAL_WALKER;
    state.enemies[28].aiState = PATROLX;
    state.enemies[28].is_active = true;

    state.enemies[29].textureID = alien2TextureID;
    state.enemies[29].position = glm::vec3(35, -20, 0);
    state.enemies[29].load_in = glm::vec3(35, -20, 0);
    state.enemies[29].speed = 0.9;
    state.enemies[29].aiType = VERTICAL_WALKER;
    state.enemies[29].aiState = PATROLY;
    state.enemies[29].is_active = true;

    state.enemies[30].textureID = alien1TextureID;
    state.enemies[30].position = glm::vec3(29, -20, 0);
    state.enemies[30].load_in = glm::vec3(29, -20, 0);
    state.enemies[30].speed = 0.9;
    state.enemies[30].aiType = GUARD;
    state.enemies[30].aiState = IDLE;
    state.enemies[30].is_active = true;

    state.enemies[31].textureID = alien3TextureID;
    state.enemies[31].position = glm::vec3(24, -20, 0);
    state.enemies[31].load_in = glm::vec3(24, -20, 0);
    state.enemies[31].speed = 0.9;
    state.enemies[31].aiType = HORIZONTAL_WALKER;
    state.enemies[31].aiState = PATROLX;
    state.enemies[31].is_active = true;

    state.enemies[32].textureID = alien3TextureID;
    state.enemies[32].position = glm::vec3(19, -20, 0);
    state.enemies[32].load_in = glm::vec3(19, -20, 0);
    state.enemies[32].speed = 0.9;
    state.enemies[32].aiType = HORIZONTAL_WALKER;
    state.enemies[32].aiState = PATROLX;
    state.enemies[32].is_active = true;

    state.enemies[33].textureID = alien3TextureID;
    state.enemies[33].position = glm::vec3(16, -24, 0);
    state.enemies[33].load_in = glm::vec3(16, -24, 0);
    state.enemies[33].speed = 0.9;
    state.enemies[33].aiType = VERTICAL_WALKER;
    state.enemies[33].aiState = PATROLY;
    state.enemies[33].is_active = true;

    state.enemies[34].textureID = alien3TextureID;
    state.enemies[34].position = glm::vec3(15, -30, 0);
    state.enemies[34].load_in = glm::vec3(15, -30, 0);
    state.enemies[34].speed = 0.9;
    state.enemies[34].aiType = HORIZONTAL_WALKER;
    state.enemies[34].aiState = PATROLX;
    state.enemies[34].is_active = true;

    state.enemies[35].textureID = alien1TextureID;
    state.enemies[35].position = glm::vec3(20, -37, 0);
    state.enemies[35].load_in = glm::vec3(20, -37, 0);
    state.enemies[35].speed = 0.3;
    state.enemies[35].aiType = GUARD;
    state.enemies[35].aiState = IDLE;
    state.enemies[35].is_active = true;

    state.enemies[36].textureID = alien1TextureID;
    state.enemies[36].position = glm::vec3(26, -37, 0);
    state.enemies[36].load_in = glm::vec3(26, -37, 0);
    state.enemies[36].speed = 0.5;
    state.enemies[36].aiType = GUARD;
    state.enemies[36].aiState = IDLE;
    state.enemies[36].is_active = true;

    state.enemies[37].textureID = alien1TextureID;
    state.enemies[37].position = glm::vec3(33, -34, 0);
    state.enemies[37].load_in = glm::vec3(26, -37, 0);
    state.enemies[37].speed = 0.5;
    state.enemies[37].aiType = GUARD;
    state.enemies[37].aiState = IDLE;
    state.enemies[37].is_active = true;

    state.enemies[38].textureID = alien3TextureID;
    state.enemies[38].position = glm::vec3(36, -34, 0);
    state.enemies[38].load_in = glm::vec3(36, -34, 0);
    state.enemies[38].speed = 1.0;
    state.enemies[38].aiType = VERTICAL_WALKER;
    state.enemies[38].aiState = PATROLY;
    state.enemies[38].is_active = true;

    state.enemies[39].textureID = alien3TextureID;
    state.enemies[39].position = glm::vec3(35, -36, 0);
    state.enemies[39].load_in = glm::vec3(35, -36, 0);
    state.enemies[39].speed = 1.0;
    state.enemies[39].aiType = VERTICAL_WALKER;
    state.enemies[39].aiState = PATROLY;
    state.enemies[39].is_active = true;

    state.enemies[40].textureID = alien1TextureID;
    state.enemies[40].position = glm::vec3(26, -25, 0);
    state.enemies[40].load_in = glm::vec3(26, -25, 0);
    state.enemies[40].speed = 1.0;
    state.enemies[40].aiType = GUARD;
    state.enemies[40].aiState = IDLE;
    state.enemies[40].is_active = true;

    state.enemies[41].textureID = alien3TextureID;
    state.enemies[41].position = glm::vec3(27, -31  , 0);
    state.enemies[41].load_in = glm::vec3(27, -31, 0);
    state.enemies[41].speed = 1.0;
    state.enemies[41].aiType = HORIZONTAL_WALKER;
    state.enemies[41].aiState = PATROLX;
    state.enemies[41].is_active = true;
}

void Level::update(float deltaTime) {
    state.player->update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    }
}
void Level::render(ShaderProgram* g_shader_program) {
    state.map->render(g_shader_program);
    for (int i = 0; i < ENEMY_COUNT; i++) state.enemies[i].render(g_shader_program);
    state.player->render(g_shader_program);
}

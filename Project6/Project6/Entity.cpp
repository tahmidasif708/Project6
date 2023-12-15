/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Entity.hpp"

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    velocity = glm::vec3(0);
    speed = 0;
    modelMatrix = glm::mat4(1.0f);
}

bool Entity::CheckCollision(Entity* other){
    if (is_active == false || other->is_active == false) return false;
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    if (xdist < 0 && ydist < 0) {
        //lastCollision = other->entityType;
        return true;
    }
    return false;
}

void Entity::CheckCollisionsY(Entity* objects, int objectCount){
    for (int i = 0; i < objectCount; i++){
        Entity* object = &objects[i];
        if (CheckCollision(object)){
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collided_top = true;
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collided_bottom = true;
            }
        }
    }
}


void Entity::CheckCollisionsY(Map* map) {
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->is_solid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collided_top = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collided_top = true;
    }
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collided_bottom = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collided_bottom = true;
    }
}

void Entity::CheckCollisionsX(Entity* objects, int objectCount){
    for (int i = 0; i < objectCount; i++){
        Entity* object = &objects[i];
        if (CheckCollision(object)){
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
            if (velocity.x > 0){
                position.x -= penetrationX;
                velocity.x = 0;
                collided_right = true;
            }
            else if (velocity.x < 0){
                position.x += penetrationX;
                velocity.x = 0;
                collided_left = true;
            }
        }
    }
}

void Entity::CheckCollisionsX(Map* map) {
    // Probes for tiles
    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);

    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

    float penetration_x = 0;
    float penetration_y = 0;
    if (map->is_solid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collided_left = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collided_left = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collided_left = true;
    }
    
    if (map->is_solid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collided_right = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collided_right = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collided_right = true;
    }
    
}

void Entity::player_status(Entity* enemies, int enemyCount) {
    for (int i = 0; i < enemyCount; i++) {
        Entity* enemy = &enemies[i];
        if (CheckCollision(enemy)) is_active = false;
    }
}

void Entity::AI(Entity* player) {
    switch (aiType) {
    case FOLLOWER:
        AIFollower(player);
        break;
    case GUARD:
        AIGuard(player);
        break;
    case HORIZONTAL_WALKER:
        AIHorizontalWalker(player);
    case VERTICAL_WALKER:
        AIVerticalWalker(player);
    }
}

void Entity::AIFollower(Entity* player) {
    switch (aiState) {
    case FOLLOW:
        if (player->position.x < position.x) movement.x = -1;
        else if (player->position.x > position.x) movement.x = 1;

        if (player->position.y < position.y) movement.y = -1;
        else if (player->position.y > position.y) movement.y = 1;
        break;
    }
}

void Entity::AIGuard(Entity* player) {
    switch (aiState) {
    case IDLE:
        if (glm::distance(position, player->position) < 2.5f) aiState = FOLLOW;
        else {
            if (position.y < load_in.y && movement.y <= 0) movement.y = 1;
            else if (position.y > load_in.y && movement.y >= 0) movement.y = -1;

            if (position.x < load_in.x && movement.x <= 0) movement.x = 1;
            else if (position.x > load_in.x && movement.x >= 0) movement.x = -1;
        }
        break;
    case FOLLOW:
        if (glm::distance(position, player->position) < 2.5f) {
            if (player->position.x < position.x) movement.x = -1;
            else if (player->position.x > position.x) movement.x = 1;

            if (player->position.y < position.y) movement.y = -1;
            else if (player->position.y > position.y) movement.y = 1;
        }
        else if (glm::distance(position, load_in) < 2.5f) {
            if (load_in.x < position.x) movement.x = -1;
            else if (load_in.x > position.x) movement.x = 1;

            if (load_in.y < position.y) movement.y = -1;
            else if (load_in.y > position.y) movement.y = 1;
        }
        if (glm::distance(position, load_in) == 0.0f) aiState = IDLE;
        break;
    }
}

void Entity::AIVerticalWalker(Entity* player) {
    switch (aiState) {
    case PATROLY:
        if (position == load_in) movement.y = -1;
        else if (position.y <= load_in.y - 1.5f && movement.y <= 0) movement.y = 1;
        else if (position.y >= load_in.y + 1.5f && movement.y >= 0) movement.y = -1;
    }
}

void Entity::AIHorizontalWalker(Entity* player) {
    switch (aiState) {
    case PATROLX:
        if (position == load_in) movement.x = -1;
        else if (position.x <= load_in.x - 1.5f && movement.x <= 0) movement.x = 1;
        else if (position.x >= load_in.x + 1.5f && movement.x >= 0) movement.x = -1;
    }
}
void Entity::update(float deltaTime, Entity* player, Entity* objects, int objectCount, Map* map)
{
    if (is_active == false) return;
    collided_top = false;
    collided_bottom = false;
    collided_left = false;
    collided_right = false;

    float original_x = position.x;
    float original_y = position.y;

    if (entityType == ENEMY) AI(player);
    else if (entityType == PLAYER) player_status(objects, objectCount);

    velocity.x = movement.x * speed;
    velocity.y = movement.y * speed;

    position.x += velocity.x * deltaTime; // Move on X

    position.y += velocity.y * deltaTime; // Move on Y

    if (entityType == PLAYER) {
        if (movement.x != 0.0f) CheckCollisionsX(map);
        else  if (movement.y != 0.0f) CheckCollisionsY(map);
        if (collided_bottom || collided_top) {
            movement.x = 0;
            position.x = original_x;
            is_active = false;
            
        }
        if (collided_right || collided_left) {
            movement.y = 0;
            position.y = original_y;
            is_active = false;
        }
    }
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram* g_shader_program, GLuint textureID, int index)
{
    float u = (float)(index % animation_cols) / (float)animation_cols;
    float v = (float)(index / animation_cols) / (float)animation_rows;

    float width = 1.0f / (float)animation_cols;
    float height = 1.0f / (float)animation_rows;

    float texture_coordinates[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v };

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };

    glBindTexture(GL_TEXTURE_2D, textureID);

    glVertexAttribPointer(g_shader_program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(g_shader_program->get_position_attribute());

    glVertexAttribPointer(g_shader_program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates);
    glEnableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(g_shader_program->get_position_attribute());
    glDisableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());
}

void Entity::render(ShaderProgram* g_shader_program) {
    if (is_active == false) return;
    g_shader_program->set_model_matrix(modelMatrix);

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texture_coordinates[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    glBindTexture(GL_TEXTURE_2D, textureID);

    glVertexAttribPointer(g_shader_program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(g_shader_program->get_position_attribute());

    glVertexAttribPointer(g_shader_program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates);
    glEnableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(g_shader_program->get_position_attribute());
    glDisableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());
}

/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Map.hpp"

Map::Map(int width, int height, unsigned int* level_data, GLuint textureID, float tile_size, int
    tile_count_x, int tile_count_y)
{
    this->width = width;
    this->height = height;
    this->level_data = level_data;
    this->textureID = textureID;
    this->tile_size = tile_size;
    this->tile_count_x = tile_count_x;
    this->tile_count_y = tile_count_y;

    this->build();
}

void Map::build()
{
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {

            int tile = level_data[y * width + x];
            if (tile == 0) continue;

            float u = (float)(tile % tile_count_x) / (float)tile_count_x;
            float v = (float)(tile / tile_count_x) / (float)tile_count_y;

            float tile_width = 1.0f / (float)tile_count_x;
            float tile_height = 1.0f / (float)tile_count_y;

            float x_offset = -(tile_size / 2); // From center of tile
            float y_offset = (tile_size / 2); // From center of tile

            vertices.insert(vertices.end(), {
                x_offset + (tile_size * x), y_offset + -tile_size * y,
                x_offset + (tile_size * x), y_offset + (-tile_size * y) - tile_size,
                x_offset + (tile_size * x) + tile_size, y_offset + (-tile_size * y) - tile_size,

                x_offset + (tile_size * x), y_offset + -tile_size * y,
                x_offset + (tile_size * x) + tile_size, y_offset + (-tile_size * y) - tile_size,
                x_offset + (tile_size * x) + tile_size, y_offset + -tile_size * y
            });
            texture_coordinates.insert(texture_coordinates.end(), {
             u, v,
             u, v + (tile_height),
             u + tile_width, v + (tile_height),

             u, v,
             u + tile_width, v + (tile_height),
             u + tile_width, v
                });
        }
    }

    left_bound = 0 - (tile_size / 2);
    right_bound = (tile_size * width) - (tile_size / 2);

    top_bound = 0 + (tile_size / 2);
    bottom_bound = -(tile_size * height) + (tile_size / 2);
}

void Map::render(ShaderProgram* g_shader_program)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    g_shader_program->set_model_matrix(modelMatrix);

    glUseProgram(g_shader_program->get_program_id());

    glVertexAttribPointer(g_shader_program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(g_shader_program->get_position_attribute());

    glVertexAttribPointer(g_shader_program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates.data());
    glEnableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());

    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size() / 2);

    glDisableVertexAttribArray(g_shader_program->get_position_attribute());
    glDisableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());
}

bool Map::is_solid(glm::vec3 position, float* penetration_x, float* penetration_y)
{
    *penetration_x = 0;
    *penetration_y = 0;

    if (position.x < left_bound || position.x > right_bound) return false;
    if (position.y > top_bound || position.y < bottom_bound) return false;

    int tile_x = floor((position.x + (tile_size / 2)) / tile_size);
    int tile_y = -(ceil(position.y - (tile_size / 2))) / tile_size; // Our array counts up as Y goes down.

    if (tile_x < 0 || tile_x >= width) return false;
    if (tile_y < 0 || tile_y >= height) return false;

    int tile = level_data[tile_y * width + tile_x];
    if (tile == 0) return false;

    float tile_center_x = (tile_x * tile_size);
    float tile_center_y = -(tile_y * tile_size);

    *penetration_x = (tile_size / 2) - fabs(position.x - tile_center_x);
    *penetration_y = (tile_size / 2) - fabs(position.y - tile_center_y);
    return true;
}

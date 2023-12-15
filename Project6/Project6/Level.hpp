/**
* Author: Tahmid Asif
* Assignment: Project 6
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Scene.hpp"
class Level : public Scene {

public:
    void initialise() override;
    void update(float deltaTime) override;
    void render(ShaderProgram* g_shader_program) override;
};

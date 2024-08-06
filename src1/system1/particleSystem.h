#ifndef _PARTICLESYSTEM_HPP_
#define _PARTICLESYSTEM_HPP_

#include"particle.h"
#include"vector"
using namespace std;
class ParSys{
    public:
    vector<Particle*> storage;
    GLuint shaderProgram;
    GLuint vbo, vao;
    glm::mat4 view_matrix;
    glm::mat4 ortho_matrix;
    glm::mat4 modelviewproject_matrix;
    GLuint uModelViewProjectMatrix;
    bool pau;
    void initShaderGL();
    void move();
    void initVBSHGL();
    void renderGL();
    void pause(int t);
};
#endif
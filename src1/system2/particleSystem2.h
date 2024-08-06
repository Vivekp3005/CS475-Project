#ifndef _PARTICLESYSTEM2_HPP_
#define _PARTICLESYSTEM2_HPP_

#include"particle2.h"
#include"vector"
using namespace std;
class ParSys2{
    public:
    vector<Particle2*> storage2;
    GLuint shaderProgram2;
    GLuint vbo2, vao2;
    bool pau2;
    glm::mat4 view_matrix;
    glm::mat4 ortho_matrix;
    glm::mat4 modelviewproject_matrix;
    GLuint uModelViewProjectMatrix;
    void initShaderGL2();
    void move2();
    void initVBSHGL2();
    void renderGL2();
    void pause2(int t);
};
#endif
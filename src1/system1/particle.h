#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_
// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "/home/viko/Downloads/CS475 Project/src1/glm/vec3.hpp"
#include "/home/viko/Downloads/CS475 Project/src1/glm/vec4.hpp"
#include "/home/viko/Downloads/CS475 Project/src1/glm/mat4x4.hpp"
#include "/home/viko/Downloads/CS475 Project/src1/glm/gtc/matrix_transform.hpp"
#include "/home/viko/Downloads/CS475 Project/src1/glm/gtc/type_ptr.hpp"
#include"/home/viko/Downloads/CS475 Project/src1/gl_framework.hpp"
#include"/home/viko/Downloads/CS475 Project/src1/shader_util.hpp"
#include<time.h>
class Particle{
    public:
    glm::vec2 position,velocity;
    int timeOrigin;
    int timeTotal = 3;
    int n = 200;
    Particle(float angle,int t);
};

#endif
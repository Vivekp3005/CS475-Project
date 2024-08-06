#include"particle.h"

Particle::Particle(float angle,int t){
    position = {0.0f,-2.0f};
    velocity = {(float)2.5*cos(angle),(float)2.5*sin(angle)};
    timeOrigin = t;
}
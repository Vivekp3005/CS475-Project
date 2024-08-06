/*
  A program which opens a window and draws full body in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the body move.

  Use the multiple keys to switch between different parts of body.
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 2.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;

//Shader program attribs
GLuint vPosition,vColor;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* currNode;
csX75::HNode* upperArmRight;
csX75::HNode* lowerArmRight;
csX75::HNode* handRight;
csX75::HNode* upperArmLeft;
csX75::HNode* lowerArmLeft;
csX75::HNode* handLeft;
csX75::HNode* torso;
csX75::HNode* hipLeft;
csX75::HNode* thighLeft;
csX75::HNode* legLeft;
csX75::HNode* hipRight;
csX75::HNode* thighRight;
csX75::HNode* legRight;
csX75::HNode* neck;
csX75::HNode* sar;

csX75::HNode* carUpper;
csX75::HNode* carUpperSideLeft;
csX75::HNode* carLower;
csX75::HNode* rightWheel;
csX75::HNode* leftWheel;
//-------------------------------------------------------------------------

#endif

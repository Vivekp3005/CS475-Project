#version 330

in vec3 vp;
uniform mat4 ModelViewProjectMatrix;

void main () 
{
  gl_Position = ModelViewProjectMatrix*vec4(vp,1.0);
}

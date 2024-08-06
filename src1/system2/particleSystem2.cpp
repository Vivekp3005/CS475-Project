#include"particleSystem2.h"

float steps = 100;
float radius = 1.0f;
float angle = 3.141*2.0f / steps;
float prevX = 0.0f;
float prevY = 0.0f - radius;

void ParSys2::move2(){
  for(int i=0;i<storage2.size();i++){
    Particle2* p = storage2[i];
    float h = (float)((float)p->timeTotal2/(float)p->n2);
    float x=(float)p->position2[0];
    float y=(float)p->position2[1];
    float r= pow(pow(x,2)+pow(y,2),0.5);
    if(r<1){
      p->velocity2[0]=0;
      p->velocity2[1]=0;
    }
    else{
      p->velocity2[0]=((pow(x,2)-pow(y,2)-1)*(pow(x,2)-pow(y,2)) + (4*x*x*y*y))/pow(r,4);
      p->velocity2[1]=-2*x*y/pow(r,4);
    }
    p->position2[0] += (p->velocity2[0]*h);
    p->position2[1] += (p->velocity2[1]*h);
  
  }
}

int getTime2(){
  time_t tim = time(0);
  tm *gottime = localtime(&tim);
  int sec = gottime->tm_sec;
  int min = gottime->tm_min;
  int hr = gottime->tm_hour;
  return (hr*60*60) + (min*60) + sec;
}

void ParSys2::initShaderGL2(){
  storage2.clear();
  std::string vertex_shader_file("/home/viko/Downloads/CS475 Project/src1/vshader.glsl");
  std::string fragment_shader_file("/home/viko/Downloads/CS475 Project/src1/fshader.glsl");
  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));
  shaderProgram2 = csX75::CreateProgramGL(shaderList);
  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo2);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo2);
  glGenVertexArrays (1, &vao2);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao2);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats 
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void ParSys2::initVBSHGL2()
{
  for(int i=1;i<=21;i++){
    Particle2* temp = new Particle2(getTime2(),i);
    storage2.push_back(temp);
  }
  float point[(storage2.size()+100)*9];
  int m = 0;
  for(int i=0;i<storage2.size();i++){
    float x = storage2[i]->position2[0];
    float y = storage2[i]->position2[1];
    point[m++] = (float)(x);
    point[m++] = (float)(y + (0.008/sqrt(3)));
    point[m++] = 0.0f;
    point[m++] = (float)(x+(float)(0.008/2));
    point[m++] = (float)(y-(float)(0.008/(2*sqrt(3))));
    point[m++] = 0.0f;
    point[m++] = (float)(x-(float)(0.008/2));
    point[m++] = (float)(y-(float)(0.008/(2*sqrt(3))));
    point[m++] = 0.0f;
  }
  for(int i=0;i<steps;i++){
    float newX = radius*sin(angle*i);
    float newY = radius*cos(angle*i);
    point[m++] = 0.0f;
    point[m++] = 0.0f;
    point[m++] = 0.0f;
    point[m++] = prevX;
    point[m++] = prevY;
    point[m++] = 0.0f;
    point[m++] = newX;
    point[m++] = newY;
    point[m++] = 0.0f;
    prevX = newX;
    prevY = newY;
  }
  glBufferData (GL_ARRAY_BUFFER, m*sizeof (float), point, GL_DYNAMIC_DRAW);
}

void ParSys2::renderGL2(void)
{
  if(!pau2){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    move2();
    initVBSHGL2();
    glUseProgram(shaderProgram2);

    glBindVertexArray (vao2);
    view_matrix = glm::lookAt(glm::vec3(0.0,0.0,2.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));

    ortho_matrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -20.0f, 20.0f);
    modelviewproject_matrix = ortho_matrix * view_matrix;

    glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));
  
    // Draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, (storage2.size() + steps)*3);
  }
  else{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram2);

    glBindVertexArray (vao2);

    view_matrix = glm::lookAt(glm::vec3(0.0,0.0,2.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));

    ortho_matrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -20.0f, 20.0f);
    modelviewproject_matrix = ortho_matrix * view_matrix;

    glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));
  
    // Draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, (storage2.size()+steps)*3);
  }
}

void ParSys2::pause2(int t){
  pau2 = 1;
  for(int i=0;i<storage2.size();i++){
    storage2[i]->timeOrigin2 = t;
  }
}




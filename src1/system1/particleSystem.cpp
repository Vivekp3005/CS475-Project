#include"particleSystem.h"

void ParSys::move(){
  for(int i=0;i<storage.size();i++){
    Particle* p = storage[i];
    float h= (float)p->timeTotal/(float)p->n;
    p->position[0]= p->position[0]+(p->velocity[0]*h);
    p->position[1]= p->position[1]+(h*p->velocity[1])-(h*h*0.49);
    p->velocity[1]= p->velocity[1]-(h*0.98);
  }
}

int getTime(){
  time_t tim = time(0);
  tm *gottime = localtime(&tim);
  int sec = gottime->tm_sec;
  int min = gottime->tm_min;
  int hr = gottime->tm_hour;
  return (hr*60*60) + (min*60) + sec;
}

void ParSys::initShaderGL(){
  storage.clear();
  std::string vertex_shader_file("/home/viko/Downloads/CS475 Project/src1/vshader.glsl");
  std::string fragment_shader_file("/home/viko/Downloads/CS475 Project/src1/fshader.glsl");
  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));
  shaderProgram = csX75::CreateProgramGL(shaderList);
  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats 
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void ParSys::initVBSHGL()
{
  Particle* temp1 = new Particle(1.39626,getTime());
  storage.push_back(temp1);
  Particle* temp2 = new Particle(1.48353,getTime());
  storage.push_back(temp2);
  Particle* temp3 = new Particle(1.65806,getTime());
  storage.push_back(temp3);
  Particle* temp4 = new Particle(1.74533,getTime());
  storage.push_back(temp4);
  Particle* temp5 = new Particle(1.439897,getTime());
  storage.push_back(temp5);
  Particle* temp6 = new Particle(1.701696,getTime());
  storage.push_back(temp6);
  Particle* temp7 = new Particle(1.57,getTime());
  storage.push_back(temp7);
  Particle* temp8 = new Particle(1.422443,getTime());
  storage.push_back(temp8);
  Particle* temp9 = new Particle(1.719149,getTime());
  storage.push_back(temp9);
  Particle* temp10 = new Particle(1.684243,getTime());
  storage.push_back(temp10);
  Particle* temp11 = new Particle(1.45735,getTime());
  storage.push_back(temp11);
  Particle* temp12 = new Particle(1.527163,getTime());
  storage.push_back(temp12);
  Particle* temp13 = new Particle(1.61443,getTime());
  storage.push_back(temp13);
  float point[storage.size()*9];
  int m = 0;
  for(int i=0;i<storage.size();i++){
    float x = storage[i]->position[0];
    float y = storage[i]->position[1];
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
  glBufferData (GL_ARRAY_BUFFER, storage.size()*9*sizeof (float), point, GL_DYNAMIC_DRAW);
}

void ParSys::renderGL(void)
{
  if(!pau){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    move();
    initVBSHGL();
    glUseProgram(shaderProgram);

    glBindVertexArray (vao);

    view_matrix = glm::lookAt(glm::vec3(0.0,0.0,-2.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));

    ortho_matrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -20.0f, 20.0f);
    modelviewproject_matrix = ortho_matrix * view_matrix;

    glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));

    // Draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, storage.size()*3);
  }
  else{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glBindVertexArray (vao);

    view_matrix = glm::lookAt(glm::vec3(0.0,0.0,-2.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));

    ortho_matrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -20.0f, 20.0f);
    modelviewproject_matrix = ortho_matrix * view_matrix;

    glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));

    // Draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, storage.size()*3);
  }
}

void ParSys::pause(int t){
  pau = 1;
  for(int i=0;i<storage.size();i++){
    storage[i]->timeOrigin = t;
  }
}




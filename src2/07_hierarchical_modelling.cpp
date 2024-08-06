#include "07_hierarchical_modelling.hpp"
#include<math.h>

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;


//-----------------------------------------------------------------

glm::vec4 positions[8];
void setPositions(double xmin, double xmax, double ymin, double ymax) {

  positions[0] = glm::vec4(xmin, ymin, 0.25, 1.0);
  positions[1] = glm::vec4(xmin, ymax, 0.25, 1.0);
  positions[2] = glm::vec4(xmax, ymax, 0.25, 1.0);
  positions[3] = glm::vec4(xmax, ymin, 0.25, 1.0);
  positions[4] = glm::vec4(xmin, ymin, -0.25, 1.0);
  positions[4] = glm::vec4(xmin, ymin, -0.25, 1.0);
  positions[5] = glm::vec4(xmin, ymax, -0.25, 1.0);
  positions[6] = glm::vec4(xmax, ymax, -0.25, 1.0);
  positions[7] = glm::vec4(xmax, ymin, -0.25, 1.0);
}

//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};

int tri_idx;
glm::vec4 v_positions_hands[num_vertices];
glm::vec4 v_colors_hands[num_vertices];
glm::vec4 v_positions_torso[num_vertices];
glm::vec4 v_colors_torso[num_vertices];
glm::vec4 v_positions_legs[num_vertices];
glm::vec4 v_colors_legs[num_vertices];
glm::vec4 v_positions_neck[num_vertices];
glm::vec4 v_colors_neck[num_vertices];
glm::vec4 v_positions_sar[num_vertices];
glm::vec4 v_colors_sar[num_vertices];
glm::vec4 v_positions_carUpperSide[num_vertices];
glm::vec4 v_colors_carUpperSide[num_vertices];
glm::vec4 v_positions_carUpper[num_vertices];
glm::vec4 v_colors_carUpper[num_vertices];
glm::vec4 v_positions_carLower[num_vertices];
glm::vec4 v_colors_carLower[num_vertices];
glm::vec4 v_positions_carWheel[num_vertices];
glm::vec4 v_colors_carWheel[num_vertices];

// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d, glm::vec4 v_positions[], glm::vec4 v_colors[])
{
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(double xmin, double xmax, double ymin, double ymax, std::string part)
{
  setPositions(xmin, xmax, ymin, ymax);
  tri_idx = 0;
  if (part == "hands") {
    quad( 1, 0, 3, 2, v_positions_hands, v_colors_hands );
    quad( 2, 3, 7, 6, v_positions_hands, v_colors_hands );
    quad( 3, 0, 4, 7, v_positions_hands, v_colors_hands );
    quad( 6, 5, 1, 2, v_positions_hands, v_colors_hands );
    quad( 4, 5, 6, 7, v_positions_hands, v_colors_hands );
    quad( 5, 4, 0, 1, v_positions_hands, v_colors_hands );
  }
  else if (part == "torso") {
    quad( 1, 0, 3, 2, v_positions_torso, v_colors_torso );
    quad( 2, 3, 7, 6, v_positions_torso, v_colors_torso );
    quad( 3, 0, 4, 7, v_positions_torso, v_colors_torso );
    quad( 6, 5, 1, 2, v_positions_torso, v_colors_torso );
    quad( 4, 5, 6, 7, v_positions_torso, v_colors_torso );
    quad( 5, 4, 0, 1, v_positions_torso, v_colors_torso );
  }
  else if (part == "legs") {
    quad( 1, 0, 3, 2, v_positions_legs, v_colors_legs );
    quad( 2, 3, 7, 6, v_positions_legs, v_colors_legs );
    quad( 3, 0, 4, 7, v_positions_legs, v_colors_legs );
    quad( 6, 5, 1, 2, v_positions_legs, v_colors_legs );
    quad( 4, 5, 6, 7, v_positions_legs, v_colors_legs );
    quad( 5, 4, 0, 1, v_positions_legs, v_colors_legs );
  }
  else if (part == "neck") {
    quad( 1, 0, 3, 2, v_positions_neck, v_colors_neck );
    quad( 2, 3, 7, 6, v_positions_neck, v_colors_neck );
    quad( 3, 0, 4, 7, v_positions_neck, v_colors_neck );
    quad( 6, 5, 1, 2, v_positions_neck, v_colors_neck );
    quad( 4, 5, 6, 7, v_positions_neck, v_colors_neck );
    quad( 5, 4, 0, 1, v_positions_neck, v_colors_neck );
  }
  else if (part == "sar") {
    quad( 1, 0, 3, 2, v_positions_sar, v_colors_sar );
    quad( 2, 3, 7, 6, v_positions_sar, v_colors_sar );
    quad( 3, 0, 4, 7, v_positions_sar, v_colors_sar );
    quad( 6, 5, 1, 2, v_positions_sar, v_colors_sar );
    quad( 4, 5, 6, 7, v_positions_sar, v_colors_sar );
    quad( 5, 4, 0, 1, v_positions_sar, v_colors_sar );
  }
  else if (part == "carUpper") {
    quad( 1, 0, 3, 2, v_positions_carUpper, v_colors_carUpper );
    quad( 2, 3, 7, 6, v_positions_carUpper, v_colors_carUpper );
    quad( 3, 0, 4, 7, v_positions_carUpper, v_colors_carUpper );
    quad( 6, 5, 1, 2, v_positions_carUpper, v_colors_carUpper );
    quad( 4, 5, 6, 7, v_positions_carUpper, v_colors_carUpper );
    quad( 5, 4, 0, 1, v_positions_carUpper, v_colors_carUpper );
  }
  else if (part == "carUpperSide") {
    quad( 1, 0, 3, 2, v_positions_carUpperSide, v_colors_carUpperSide );
    quad( 2, 3, 7, 6, v_positions_carUpperSide, v_colors_carUpperSide );
    quad( 3, 0, 4, 7, v_positions_carUpperSide, v_colors_carUpperSide );
    quad( 6, 5, 1, 2, v_positions_carUpperSide, v_colors_carUpperSide );
    quad( 4, 5, 6, 7, v_positions_carUpperSide, v_colors_carUpperSide );
    quad( 5, 4, 0, 1, v_positions_carUpperSide, v_colors_carUpperSide );
  }
  else if (part == "lowerCar") {
    quad( 1, 0, 3, 2, v_positions_carLower, v_colors_carLower );
    quad( 2, 3, 7, 6, v_positions_carLower, v_colors_carLower );
    quad( 3, 0, 4, 7, v_positions_carLower, v_colors_carLower );
    quad( 6, 5, 1, 2, v_positions_carLower, v_colors_carLower );
    quad( 4, 5, 6, 7, v_positions_carLower, v_colors_carLower );
    quad( 5, 4, 0, 1, v_positions_carLower, v_colors_carLower );
  }
  else if (part == "wheel") {
    quad( 1, 0, 3, 2, v_positions_carWheel, v_colors_carWheel );
    quad( 2, 3, 7, 6, v_positions_carWheel, v_colors_carWheel );
    quad( 3, 0, 4, 7, v_positions_carWheel, v_colors_carWheel );
    quad( 6, 5, 1, 2, v_positions_carWheel, v_colors_carWheel );
    quad( 4, 5, 6, 7, v_positions_carWheel, v_colors_carWheel );
    quad( 5, 4, 0, 1, v_positions_carWheel, v_colors_carWheel );
  }

}

void drawBody(void) {
  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  
  colorcube(0.0, 1.0, 3.0, 3.8, "neck");
  neck = new csX75::HNode(NULL, num_vertices,v_positions_neck,v_colors_neck,sizeof(v_positions_neck),sizeof(v_colors_neck));

  colorcube(-1.5, 2.5, -2.5, 3.0, "torso");
  torso = new csX75::HNode(NULL, num_vertices,v_positions_torso,v_colors_torso,sizeof(v_positions_torso),sizeof(v_colors_torso));

  colorcube(0.0, 2.0, 2.4, 3.0, "hands");
  upperArmLeft = new csX75::HNode(torso,num_vertices,v_positions_hands,v_colors_hands,sizeof(v_positions_hands),sizeof(v_colors_hands));
  upperArmLeft->change_parameters(0.2,1.7,0.0,0.0,0.0,-60.0);
  lowerArmLeft = new csX75::HNode(upperArmLeft,num_vertices,v_positions_hands,v_colors_hands,sizeof(v_positions_hands),sizeof(v_colors_hands));
  lowerArmLeft->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  handLeft = new csX75::HNode(lowerArmLeft,num_vertices,v_positions_hands,v_colors_hands,sizeof(v_positions_hands),sizeof(v_colors_hands));
  handLeft->change_parameters(1.0,0.0,0.0,0.0,0.0,0.0);
  currNode = handLeft;
  
  upperArmRight = new csX75::HNode(torso,num_vertices,v_positions_hands,v_colors_hands,sizeof(v_positions_hands),sizeof(v_colors_hands));
  upperArmRight->change_parameters(-4.0,4.5,0.0,0.0,0.0,240);
  lowerArmRight = new csX75::HNode(upperArmRight,num_vertices,v_positions_hands,v_colors_hands,sizeof(v_positions_hands),sizeof(v_colors_hands));
  lowerArmRight->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  handRight = new csX75::HNode(lowerArmRight,num_vertices,v_positions_hands,v_colors_hands,sizeof(v_positions_hands),sizeof(v_colors_hands));
  handRight->change_parameters(1.0,0.0,0.0,0.0,0.0,0.0);

  colorcube(-1.5, -0.5, -4.00, -2.5, "legs");
  hipLeft = new csX75::HNode(NULL,num_vertices,v_positions_legs,v_colors_legs,sizeof(v_positions_legs),sizeof(v_colors_legs));
  hipLeft->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  thighLeft = new csX75::HNode(hipLeft,num_vertices,v_positions_legs,v_colors_legs,sizeof(v_positions_legs),sizeof(v_colors_legs));
  thighLeft->change_parameters(0.0,-1.5,0.0,0.0,0.0,0.0);
  legLeft = new csX75::HNode(thighLeft,num_vertices,v_positions_legs,v_colors_legs,sizeof(v_positions_legs),sizeof(v_colors_legs));
  legLeft->change_parameters(0.0,-0.75,0.0,0.0,0.0,0.0);

  hipRight = new csX75::HNode(NULL,num_vertices,v_positions_legs,v_colors_legs,sizeof(v_positions_legs),sizeof(v_colors_legs));
  hipRight->change_parameters(3.0,0.0,0.0,0.0,0.0,0.0);
  thighRight = new csX75::HNode(hipRight,num_vertices,v_positions_legs,v_colors_legs,sizeof(v_positions_legs),sizeof(v_colors_legs));
  thighRight->change_parameters(0.0,-1.5,0.0,0.0,0.0,0.0);
  legRight = new csX75::HNode(thighRight,num_vertices,v_positions_legs,v_colors_legs,sizeof(v_positions_legs),sizeof(v_colors_legs));
  legRight->change_parameters(0.0,-0.75,0.0,0.0,0.0,0.0);

  colorcube(-0.7, 1.7, 3.8, 5.2, "sar");
  sar = new csX75::HNode(NULL,num_vertices,v_positions_sar,v_colors_sar,sizeof(v_positions_sar),sizeof(v_colors_sar));

}

void drawCar(void) {
  colorcube(-1.5, 3.1, -1.5, 1.47, "carUpper");
  carUpper = new csX75::HNode(NULL, num_vertices,v_positions_carUpper,v_colors_carUpper,sizeof(v_positions_carUpper),sizeof(v_colors_carUpper));

  colorcube(-2.8, -1.9, -2.4, 0.7, "carUpperSide");
  carUpperSideLeft = new csX75::HNode(NULL, num_vertices,v_positions_carUpperSide,v_colors_carUpperSide,sizeof(v_positions_carUpperSide),sizeof(v_colors_carUpperSide));
  carUpperSideLeft->change_parameters(1.0,0.0,0.0,0.0,0.0,-18);

  
  colorcube(-4.2, 4.2, -1.5, -4.0, "lowerCar");
  carLower = new csX75::HNode(NULL, num_vertices,v_positions_carLower,v_colors_carLower,sizeof(v_positions_carLower),sizeof(v_colors_carLower));

  colorcube(-3.2, -2.0, -3.7, -4.6, "wheel");
  leftWheel = new csX75::HNode(NULL, num_vertices,v_positions_carWheel,v_colors_carWheel,sizeof(v_positions_carWheel),sizeof(v_colors_carWheel));

  rightWheel = new csX75::HNode(NULL, num_vertices,v_positions_carWheel,v_colors_carWheel,sizeof(v_positions_carWheel),sizeof(v_colors_carWheel));
  rightWheel->change_parameters(5.0,0.0,0.0,0.0,0.0,0.0);
}
//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  drawCar();
  drawBody();

}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  if (csX75::isRobot) {
    torso->render_tree();
    hipLeft->render_tree();
    hipRight->render_tree();
    neck->render_tree();
    sar->render_tree();
  }
  else {
    carUpper->render_tree();
    carUpperSideLeft->render_tree();
    carLower->render_tree();
    leftWheel->render_tree();
    rightWheel->render_tree();
  }

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------


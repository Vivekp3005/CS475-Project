#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode *currNode, *upperArmRight, *lowerArmRight, *handRight, *upperArmLeft, *lowerArmLeft, *handLeft, *torso, *hipLeft, *thighLeft, *legLeft, *hipRight, *thighRight, *legRight, *neck, *sar;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
      csX75::isRobot = false;
    else if (key == GLFW_KEY_B && action == GLFW_PRESS)
      csX75::isRobot = true;
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      currNode = upperArmLeft;
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      currNode = lowerArmLeft; 
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      currNode = handLeft; 
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      currNode = upperArmRight;
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      currNode = lowerArmRight; 
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
      currNode = handRight; 
    else if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
      currNode = hipLeft;
    else if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
      currNode = thighLeft; 
    else if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
      currNode = legLeft;
    else if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
      currNode = hipRight;
    else if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
      currNode = thighRight; 
    else if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
      currNode = legRight;
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
      currNode = torso;
    else if (key == GLFW_KEY_N && action == GLFW_PRESS)
      currNode = neck;
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
      currNode = sar;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      currNode->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      currNode->inc_ry();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      currNode->dec_rx();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      currNode->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      currNode->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      currNode->inc_rz();
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zrot += 1.0;   
  }

  bool isRobot = true;
};  
  



//
//  main.cpp
//  VulkanTutorial
//
//  Created by null on 21/01/2021.
//

#define GLFW_INCLUDE_VULKAN
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class CoucouTriangleApplication {
public:
    
    void run(){
        initVulkan();
        mainLoop();
        cleanup();
    }
    
private:
    GLFWwindow* window;
    
    void initVulkan(){
        glfwInit();
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        window = glfwCreateWindow(WIDTH, HEIGHT, "Coucou Vulkan", nullptr, nullptr);
        
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        
        std::cout << extensionCount << " extensions supported\n";
    }
    
    void mainLoop(){
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            glm::mat4 matrix;
            glm::vec4 vec;
            glm::vec4 test = matrix * vec;
        }
    }
    
    void cleanup(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    CoucouTriangleApplication app;
    
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

//
//  main.cpp
//  VulkanTutorial
//
//  Created by null on 21/01/2021.
//


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class CoucouTriangleApplication {
public:
    
    void run(){
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
    
private:
    GLFWwindow* window;
    VkInstance instance;
    
    void initWindow(){
        glfwInit();
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Avoid GLFW creating OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Deactivate window resising for now
        
        window = glfwCreateWindow(WIDTH, HEIGHT, "Coucou Vulkan", nullptr, nullptr);
    }
    
    
    
    void initVulkan(){
        verifyExtensions();
        createInstance();
        
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
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    void createInstance(){
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Coucou Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;
        
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;
        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
            throw std::runtime_error("Failed to create instance!");
        }
    }
    
    void verifyExtensions() {
        uint32_t requiredExtensionCount = 0;
        auto requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionCount);
        std::cout << "Required extensions:\n";
        for(int i = 0; i < requiredExtensionCount; ++i) {
            std::cout << '\t' << requiredExtensions[i] << '\n';
        }
        
        uint32_t availableExtensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
        
        std::vector<VkExtensionProperties> extensions(availableExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, extensions.data());
        
        std::cout << "Available extensions:\n";
        for(const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
        
        for(int i = 0; i < requiredExtensionCount; ++i) {
            bool found = false;
            for(const auto& extension : extensions) {
                if(strcmp(requiredExtensions[i], extension.extensionName))
                {
                    found = true;
                }
            }
            if(!found){
                throw std::runtime_error("Missing required vulkan extension");
            }
        }
        std::cout << "All required extensions present" << std::endl;
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

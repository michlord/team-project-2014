#include "Window.h"

namespace Rendering {

    Window::Window() {
        window = nullptr;
    }

    Window::~Window() {
        close();
    }

    void Window::open(int width_, int height_, std::string title_) {
        if(isOpen() == false) {
            width  = width_;
            height = height_;
            title  = title_;

            window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        }
    }

    void Window::close() {
        if(isOpen()) {
            delete window;
            window = nullptr;
        }
    }

    void Window::clear() {
        if(isOpen()) {
            window->clear();
        }
    }

    void Window::display() {
        if(isOpen()) {
            window->display();
        }
    }

    bool Window::isOpen() {
        return (window != nullptr);
    }

    sf::RenderWindow& Window::getHandle() {
        return *window;
    }

    void Window::setSize(int width_, int height_) {
        width = width_;
        height = height_;
        
        if(isOpen())
            window->setSize(sf::Vector2u(width, height));
    }

    void Window::setTitle(std::string title_) {
        title = title_;

        if(isOpen())
            window->setTitle(title);
    }

    int Window::getWidth() {
        return width;
    }

    int Window::getHeight() {
        return height;
    }

    std::string Window::getTitle() {
        return title;
    }

}
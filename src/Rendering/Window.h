#ifndef RENDERING_WINDOW_H_INCLUDED
#define RENDERING_WINDOW_H_INCLUDED

#include "SFML/Graphics.hpp"
#include <string>

namespace Rendering {
    
    class Window {
        public:
            Window();
            ~Window();

            void open(int width_, int height_, std::string title_ = "");
            void close();
            void clear();
            void display();
            
            bool isOpen();
            sf::RenderWindow& getHandle();

            void setSize(int width_, int height_);

            int width;
            int height;
            std::string title;

        private:
            sf::RenderWindow* window;
    };

}

#endif
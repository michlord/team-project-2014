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

            void setSize(int width_, int height_);
            void setTitle(std::string title_);

            int  getWidth();
            int  getHeight();
            bool isOpen();
            std::string getTitle();
            sf::RenderWindow& getHandle();

        private:
            int width;
            int height;
            std::string title;

            sf::RenderWindow* window;
    };

}

#endif
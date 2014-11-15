#ifndef WINDOWCONTEXT_H_INCLUDED
#define WINDOWCONTEXT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class WindowContext {
    public:
        WindowContext();
        ~WindowContext();
        
        void open();
        void close();

        void update();
        void display();
        void clear();
        
        const sf::Vector2u& getSize() const;
        const sf::Vector2i& getPosition() const;
        int getPositionX() const;
        int getPositionY() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        const std::string& getTitle() const;
        const bool isOpened() const;
        const bool isVsyncEnabled() const;
        const sf::Time& getFrameTime() const;
        sf::RenderWindow& getHandle();

        void setSize(unsigned int width_, unsigned int height_);
        void setSize(const sf::Vector2u& size_);
        void setPosition(unsigned int posX_, unsigned int posY_);
        void setPosition(const sf::Vector2i& position_);
        void setTitle(const std::string& title_);
        void setVsync(bool flag);

    private:
        bool isVsync;
        std::string title;
        
        sf::Time frameTime;
        sf::Vector2i position;
        sf::Vector2u size;
        sf::RenderWindow* window;

};

#endif
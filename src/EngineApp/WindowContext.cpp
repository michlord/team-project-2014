#include <EngineApp/WindowContext.h>

WindowContext::WindowContext() {
    window = new sf::RenderWindow();

    // default settings
    title = "Title";
    size = sf::Vector2u(800, 600);
    position = sf::Vector2i(64, 64);
}

WindowContext::~WindowContext() {
    close();

    delete window;
}
        
void WindowContext::open() {
    if(isOpened() == false) {
        window->setPosition(getPosition());
        window->create(sf::VideoMode(getWidth(), getHeight()), getTitle());
        window->setVerticalSyncEnabled(isVsyncEnabled());
        window->setActive();
    }
}

void WindowContext::close() {
    if(isOpened() == true)
        window->close();
}

void WindowContext::update() {
    static sf::Clock clock;
    frameTime = clock.restart();
    
    display();
    clear();
}

void WindowContext::display() {
    if(isOpened())
        window->display();
}

void WindowContext::clear() {
    if(isOpened())
        window->clear();
}

const sf::Vector2u& WindowContext::getSize() const {
    return size;
}

const sf::Vector2i& WindowContext::getPosition() const {
    return position;
}

int WindowContext::getPositionX() const {
    return position.x;
}

int WindowContext::getPositionY() const {
    return position.y;
}

unsigned int WindowContext::getWidth() const {
    return size.x;
}

unsigned int WindowContext::getHeight() const {
    return size.y;
}

const std::string& WindowContext::getTitle() const {
    return title;
}

const bool WindowContext::isOpened() const {
    return window->isOpen();
}

const bool WindowContext::isVsyncEnabled() const {
    return isVsync;
}

const sf::Time& WindowContext::getFrameTime() const {
    return frameTime;
}

sf::RenderWindow& WindowContext::getHandle() {
    return *window;
}

void WindowContext::setSize(unsigned int width_, unsigned int height_) {
    size = sf::Vector2u(width_, height_);
    window->setSize(size);
}

void WindowContext::setSize(const sf::Vector2u& size_) {
    size = size_;
    window->setSize(size);
}

void WindowContext::setPosition(unsigned int posX_, unsigned int posY_) {
    position = sf::Vector2i(posX_, posY_);
    window->setPosition(position);
}

void WindowContext::setPosition(const sf::Vector2i& position_) {
    position = position_;
    window->setPosition(position);
}

void WindowContext::setTitle(const std::string& title_) {
    title = title_;
    window->setTitle(title);
}

void WindowContext::setVsync(bool flag) {
    isVsync = flag;

    if(isOpened())
        window->setVerticalSyncEnabled(isVsyncEnabled());
}
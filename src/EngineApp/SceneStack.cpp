#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <functional>
#include <memory>

namespace Core {

void SceneStack::pushScene(FrameListener* scene) {
    Change c;
    c.action = Action::Push;
    c.frameListener.reset(scene);
    pendingChanges.push_back(std::move(c));
}

void SceneStack::popScene() {
    Change c;
    c.action = Action::Pop;
    pendingChanges.push_back(std::move(c));
}

void SceneStack::clearScenes() {
    Change c;
    c.action = Action::Clear;
    pendingChanges.push_back(std::move(c));
}

void SceneStack::applyPendingChanges() {
    auto it = pendingChanges.begin();
    auto end = pendingChanges.end();
    while(it != end) {
        Change &c = *it;
        switch(c.action) {
        case Action::Push:
            stack.push_back(std::move(c.frameListener));
            break;
        case Action::Pop:
            stack.pop_back();
        case Action::Clear:
            stack.clear();
        default:
            break;
        }
        ++it;
    }
    pendingChanges.clear();
}

bool SceneStack::isEmpty() {
    return stack.empty();
}

namespace {
    void affect(std::vector< std::unique_ptr<FrameListener> > &stack, 
                std::function<bool(FrameListener*)> fun)
    {
        auto it = stack.rbegin();
        auto end = stack.rend();
        while(it != end) {
            FrameListener* scene = it->get();
            
            if(fun(scene)) {
                return;
            }
            ++it;
        }
    }
}

void SceneStack::render() {
    affect(stack, [](FrameListener* scene){return scene->render();});
}

void SceneStack::fixedUpdate() {
    Input::InputHandler *inputHandler = stack.back()->getInputHandler();
    if(inputHandler) {
        inputHandler->update();
    }

    affect(stack, [](FrameListener* scene){return scene->fixedUpdate();});
}

void SceneStack::handleEvent(const sf::Event &event) {
    Input::InputHandler *inputHandler = stack.back()->getInputHandler();
    if(!inputHandler) {
        return;
    }

    std::unique_ptr<Input::Input> input_p(Input::translateEvent(event));
    if(input_p) {
        inputHandler->handleInput(*input_p);
    }
}

}
#include <EngineApp/FrameContext.h>
#include <EngineApp/SceneStack.h>

namespace Core {

FrameContext::FrameContext()
 : window(nullptr), appWindow(nullptr), frameTime(0.0f), deltaTime(0.0f),
   sceneStack(new SceneStack), assetsManager(new Assets::AssetsManager)
{
}

FrameContext &FrameContext::getInstance() {
    static FrameContext instance;
    return instance;
}

FrameContext &frameContext = FrameContext::getInstance();

}

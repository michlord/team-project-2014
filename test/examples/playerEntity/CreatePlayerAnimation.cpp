#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

#include <stdexcept>

Video::Render::Animation createPlayerAnimation() {
    static sf::Texture texture;
    if(!texture.loadFromFile("assets/dummy_player_spritesheet.png")) {
        throw std::runtime_error("Error loading player animation texture");
    }

    Video::Render::AnimatedSprite idleSequence(texture);
    Video::Render::AnimatedSprite fallSequence(texture);
    Video::Render::AnimatedSprite slashSequence(texture);
    Video::Render::AnimatedSprite castSequence(texture);
    Video::Render::AnimatedSprite runSequence(texture);
    Video::Render::AnimatedSprite airSlashSequence(texture);
    Video::Render::AnimatedSprite hurtSequence(texture);
    Video::Render::AnimatedSprite jumpSequence(texture);
    
    Video::Render::Sprite::Frame frameBuffer[21];
    
    //idle
    frameBuffer[0].setTextureSegment(sf::IntRect(5, 7, 54, 69));
    frameBuffer[1].setTextureSegment(sf::IntRect(85, 7, 54, 69));
    frameBuffer[2].setTextureSegment(sf::IntRect(165, 7, 54, 69));
    frameBuffer[3].setTextureSegment(sf::IntRect(245, 7, 54, 69));
    
    //fall
    frameBuffer[4].setTextureSegment(sf::IntRect(344, 6, 48, 68));
    
    //slash
    frameBuffer[5].setTextureSegment(sf::IntRect(3, 100, 45, 67));
    frameBuffer[6].setTextureSegment(sf::IntRect(71, 100, 77, 67));
    
    //cast
    frameBuffer[7].setTextureSegment(sf::IntRect(175, 101, 78, 67));
    frameBuffer[8].setTextureSegment(sf::IntRect(256, 101, 76, 67));
    frameBuffer[9].setTextureSegment(sf::IntRect(336, 101, 76, 67));
    frameBuffer[10].setTextureSegment(sf::IntRect(416, 101, 76, 67));
    
    //run
    frameBuffer[11].setTextureSegment(sf::IntRect(1, 201, 67, 56));
    frameBuffer[12].setTextureSegment(sf::IntRect(77, 201, 67, 56));
    frameBuffer[13].setTextureSegment(sf::IntRect(156, 201, 67, 56));
    
    //air slash
    frameBuffer[14].setTextureSegment(sf::IntRect(257, 193, 73, 64));
    frameBuffer[15].setTextureSegment(sf::IntRect(331, 193, 79, 64));
    
    //hurt
    frameBuffer[16].setTextureSegment(sf::IntRect(5, 288, 51, 68));
    
    //jump
    frameBuffer[17].setTextureSegment(sf::IntRect(95, 299, 60, 58));
    frameBuffer[18].setTextureSegment(sf::IntRect(184, 299, 60, 58));
    frameBuffer[19].setTextureSegment(sf::IntRect(251, 280, 62, 77));
    frameBuffer[20].setTextureSegment(sf::IntRect(344, 280, 62, 75));
    
    for(int i = 0; i < 21; ++i) {
        frameBuffer[i].setDuration(sf::seconds(1.0f/15.0f));
    }
    
    int famt[] = {4, 1, 2, 4, 3, 2, 1, 4};
    Video::Render::AnimatedSprite *seq[] = {&idleSequence, &fallSequence, &slashSequence,
        &castSequence, &runSequence, &airSlashSequence, &hurtSequence, &jumpSequence};
        
    for(int i = 0, j = 0; i < 8; ++i) {
        for(int k = 0; k < famt[i]; ++k) {
            seq[i]->insertFrame(frameBuffer[j]);
            j += 1;
        }
    }
    
    Video::Render::Animation animation;
    animation.addSequence("idle", idleSequence, true);
    animation.addSequence("fall", fallSequence, true);
    animation.addSequence("slash", slashSequence, true);
    animation.addSequence("cast", castSequence, true);
    animation.addSequence("run", runSequence, true);
    animation.addSequence("air", airSlashSequence, true);
    animation.addSequence("hurt", hurtSequence, true);
    animation.addSequence("jump", jumpSequence, true);
    
    return animation;
}


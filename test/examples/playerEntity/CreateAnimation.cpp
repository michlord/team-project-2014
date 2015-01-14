#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

#include <stdexcept>

std::map<std::string, sf::IntRect> makePlayerAnimation(Video::Render::Animation &animation) {
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

    std::map<std::string, sf::IntRect> seq_solids;
    
    //everything was offset by 1px (5->6, 0->1, 55->54, 70->69...). why?
    //idle
    frameBuffer[0].setTextureSegment(sf::IntRect(5, 6, 55, 70));
    frameBuffer[1].setTextureSegment(sf::IntRect(85, 6, 55, 70));
    frameBuffer[2].setTextureSegment(sf::IntRect(165, 6, 55, 70));
    frameBuffer[3].setTextureSegment(sf::IntRect(245, 6, 55, 70));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("idle", sf::IntRect(10, 2, 30, 68)));
    
    //fall
    frameBuffer[4].setTextureSegment(sf::IntRect(343, 6, 48, 69));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("fall", sf::IntRect(13, 2, 30, 64)));
    
    //slash
    frameBuffer[5].setTextureSegment(sf::IntRect(3, 100, 79, 68));
    frameBuffer[6].setTextureSegment(sf::IntRect(82, 100, 79, 68));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("slash", sf::IntRect(12, 2, 30, 66)));
    
    //cast
    frameBuffer[7].setTextureSegment(sf::IntRect(188, 101, 78, 68));
    frameBuffer[8].setTextureSegment(sf::IntRect(268, 101, 78, 68));
    frameBuffer[9].setTextureSegment(sf::IntRect(348, 101, 78, 68));
    frameBuffer[10].setTextureSegment(sf::IntRect(428, 101, 78, 68));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("cast", sf::IntRect(10, 1, 30, 67)));
    
    //run
    frameBuffer[11].setTextureSegment(sf::IntRect(0, 202, 69, 55));
    frameBuffer[12].setTextureSegment(sf::IntRect(74, 202, 69, 55));
    frameBuffer[13].setTextureSegment(sf::IntRect(154, 202, 69, 55));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("run", sf::IntRect(19, 2, 40, 53)));
    
    //air slash
    frameBuffer[14].setTextureSegment(sf::IntRect(257, 193, 79, 63));
    frameBuffer[15].setTextureSegment(sf::IntRect(336, 193, 79, 63));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("air", sf::IntRect(19, 2, 30, 61)));
    
    //hurt
    frameBuffer[16].setTextureSegment(sf::IntRect(4, 288, 50, 67));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("hurt", sf::IntRect(8, 4, 40, 60)));
    
    //having one solid here is problematic, because first two frames are crouching, so shorter...
    //jump
    frameBuffer[17].setTextureSegment(sf::IntRect(96, 280, 67, 70));
    frameBuffer[18].setTextureSegment(sf::IntRect(174, 280, 67, 70));
    frameBuffer[19].setTextureSegment(sf::IntRect(250, 280, 67, 70));
    frameBuffer[20].setTextureSegment(sf::IntRect(341, 280, 67, 70));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("jump", sf::IntRect(19, 1, 30, 68)));
    
    for(int i = 0; i < 21; ++i) {
        frameBuffer[i].setDuration(sf::seconds(1.0f/15.0f));
    }
    
    // last one should be actually four but for now lets skip this frame
    int famt[] = {4, 1, 2, 4, 3, 2, 1, 3};
    Video::Render::AnimatedSprite *seq[] = {&idleSequence, &fallSequence, &slashSequence,
        &castSequence, &runSequence, &airSlashSequence, &hurtSequence, &jumpSequence};
        
    for(int i = 0, j = 0; i < 8; ++i) {
        for(int k = 0; k < famt[i]; ++k) {
            seq[i]->insertFrame(frameBuffer[j]);
            j += 1;
        }
    }
    
    animation.addSequence("idle", idleSequence, true);
    animation.addSequence("fall", fallSequence, true);
    animation.addSequence("slash", slashSequence, true);
    animation.addSequence("cast", castSequence, true);
    animation.addSequence("run", runSequence, true);
    animation.addSequence("air", airSlashSequence, true);
    animation.addSequence("hurt", hurtSequence, true);
    animation.addSequence("jump", jumpSequence, true);
    
    return seq_solids;
}

std::map<std::string, sf::IntRect> makeGuardAnimation(Video::Render::Animation &animation) {
    static sf::Texture texture;
    if(!texture.loadFromFile("assets/dummy_guard_spritesheet.png")) {
        throw std::runtime_error("Error loading guard animation texture");
    }

    Video::Render::AnimatedSprite idleSequence(texture);
    Video::Render::AnimatedSprite fallSequence(texture);
    Video::Render::AnimatedSprite slashSequence(texture);
    Video::Render::AnimatedSprite runSequence(texture);
    Video::Render::AnimatedSprite hurtSequence(texture);
    Video::Render::AnimatedSprite jumpSequence(texture);
    
    Video::Render::Sprite::Frame frameBuffer[15];

    std::map<std::string, sf::IntRect> seq_solids;
    
    //idle
    frameBuffer[0].setTextureSegment(sf::IntRect(9, 8, 67, 92));
    frameBuffer[1].setTextureSegment(sf::IntRect(89, 8, 67, 92));
    frameBuffer[2].setTextureSegment(sf::IntRect(169, 8, 67, 92));
    frameBuffer[3].setTextureSegment(sf::IntRect(249, 8, 67, 92));
    frameBuffer[4].setTextureSegment(sf::IntRect(329, 8, 67, 92));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("idle", sf::IntRect(12, 10, 40, 82)));
    
    //fall
    frameBuffer[5].setTextureSegment(sf::IntRect(17, 133, 64, 90));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("fall", sf::IntRect(2, 10, 40, 78)));
    
    //slash
    frameBuffer[6].setTextureSegment(sf::IntRect(123, 135, 100, 92));
    frameBuffer[7].setTextureSegment(sf::IntRect(220, 135, 100, 92));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("slash", sf::IntRect(25, 12, 40, 79)));
    
    //run
    frameBuffer[8].setTextureSegment(sf::IntRect(132, 271, 75, 92));
    frameBuffer[9].setTextureSegment(sf::IntRect(216, 271, 75, 92));
    frameBuffer[10].setTextureSegment(sf::IntRect(292, 271, 75, 92));
    frameBuffer[11].setTextureSegment(sf::IntRect(372, 271, 75, 92));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("run", sf::IntRect(20, 10, 40, 82)));
    
    //hurt
    frameBuffer[12].setTextureSegment(sf::IntRect(8, 281, 68, 89));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("hurt", sf::IntRect(16, 7, 40, 82)));
    
    //jump
    frameBuffer[13].setTextureSegment(sf::IntRect(22, 395, 56, 96));
    frameBuffer[14].setTextureSegment(sf::IntRect(107, 395, 56, 96));
    seq_solids.insert(std::pair<std::string, sf::IntRect>("jump", sf::IntRect(14, 8, 40, 85)));
    
    for(int i = 0; i < 15; ++i) {
        frameBuffer[i].setDuration(sf::seconds(1.0f/15.0f));
    }
    
    int famt[] = {5, 1, 2, 4, 1, 2};
    Video::Render::AnimatedSprite *seq[] = {&idleSequence, &fallSequence, &slashSequence,
        &runSequence, &hurtSequence, &jumpSequence};
        
    for(int i = 0, j = 0; i < 6; ++i) {
        for(int k = 0; k < famt[i]; ++k) {
            seq[i]->insertFrame(frameBuffer[j]);
            j += 1;
        }
    }
    
    animation.addSequence("idle", idleSequence, true);
    animation.addSequence("fall", fallSequence, true);
    animation.addSequence("slash", slashSequence, true);
    animation.addSequence("run", runSequence, true);
    animation.addSequence("hurt", hurtSequence, true);
    animation.addSequence("jump", jumpSequence, true);
    
    return seq_solids;
}




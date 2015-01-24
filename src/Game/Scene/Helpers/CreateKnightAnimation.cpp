#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

#include <stdexcept>

namespace Scene {
    namespace Helpers {

        std::map<std::string, sf::FloatRect> makeKnightAnimation(Video::Render::Animation &animation) {
            static sf::Texture texture;
            if(!texture.loadFromFile("assets/images/knight_character.png")) {
                throw std::runtime_error("Error loading knight animation texture");
            }

            Video::Render::AnimatedSprite idleSequence(texture);
            Video::Render::AnimatedSprite fallSequence(texture);
            Video::Render::AnimatedSprite slashSequence(texture);
            Video::Render::AnimatedSprite runSequence(texture);
            Video::Render::AnimatedSprite hurtSequence(texture);
            Video::Render::AnimatedSprite jumpSequence(texture);
    
            Video::Render::Sprite::Frame frameBuffer[15];

            std::map<std::string, sf::FloatRect> seq_solids;
    
            //idle
            frameBuffer[0].setTextureSegment(sf::IntRect(9, 8, 67, 92));
            frameBuffer[1].setTextureSegment(sf::IntRect(89, 8, 67, 92));
            frameBuffer[2].setTextureSegment(sf::IntRect(169, 8, 67, 92));
            frameBuffer[3].setTextureSegment(sf::IntRect(249, 8, 67, 92));
            frameBuffer[4].setTextureSegment(sf::IntRect(329, 8, 67, 92));
            seq_solids.insert(std::make_pair("idle", sf::FloatRect(12, 10, 40, 82)));
    
            //fall
            frameBuffer[5].setTextureSegment(sf::IntRect(17, 133, 64, 90));
            seq_solids.insert(std::make_pair("fall", sf::FloatRect(2, 10, 40, 78)));
    
            //slash
            frameBuffer[6].setTextureSegment(sf::IntRect(123, 135, 100, 92));
            frameBuffer[7].setTextureSegment(sf::IntRect(220, 135, 100, 92));
            seq_solids.insert(std::make_pair("slash", sf::FloatRect(25, 12, 40, 79)));
    
            //run
            frameBuffer[8].setTextureSegment(sf::IntRect(132, 271, 75, 92));
            frameBuffer[9].setTextureSegment(sf::IntRect(216, 271, 75, 92));
            frameBuffer[10].setTextureSegment(sf::IntRect(292, 271, 75, 92));
            frameBuffer[11].setTextureSegment(sf::IntRect(372, 271, 75, 92));
            seq_solids.insert(std::make_pair("run", sf::FloatRect(20, 10, 40, 82)));
    
            //hurt
            frameBuffer[12].setTextureSegment(sf::IntRect(8, 281, 68, 89));
            seq_solids.insert(std::make_pair("hurt", sf::FloatRect(16, 7, 40, 82)));
    
            //jump
            frameBuffer[13].setTextureSegment(sf::IntRect(22, 395, 56, 96));
            frameBuffer[14].setTextureSegment(sf::IntRect(107, 395, 56, 96));
            seq_solids.insert(std::make_pair("jump", sf::FloatRect(14, 8, 40, 85)));
    
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
    }
}

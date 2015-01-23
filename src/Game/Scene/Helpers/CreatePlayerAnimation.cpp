#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

#include <stdexcept>

namespace Scene {
    namespace Helpers {

        std::map<std::string, sf::FloatRect> makePlayerAnimation(Video::Render::Animation &animation) {
            static sf::Texture texture;
            if(!texture.loadFromFile("assets/images/player_character.png")) {
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

            std::map<std::string, sf::FloatRect> seq_solids;

            //idle
            frameBuffer[0].setTextureSegment(sf::IntRect(5, 6, 55, 70));
            frameBuffer[1].setTextureSegment(sf::IntRect(85, 6, 55, 70));
            frameBuffer[2].setTextureSegment(sf::IntRect(165, 6, 55, 70));
            frameBuffer[3].setTextureSegment(sf::IntRect(245, 6, 55, 70));
            seq_solids.insert(std::make_pair("idle", sf::FloatRect(10, 2, 30, 68)));

            //fall
            frameBuffer[4].setTextureSegment(sf::IntRect(343, 6, 48, 69));
            seq_solids.insert(std::make_pair("fall", sf::FloatRect(13, 2, 30, 64)));

            //slash
            frameBuffer[5].setTextureSegment(sf::IntRect(3, 100, 79, 68));
            frameBuffer[6].setTextureSegment(sf::IntRect(82, 100, 79, 68));
            seq_solids.insert(std::make_pair("slash", sf::FloatRect(12, 2, 30, 66)));

            //cast
            frameBuffer[7].setTextureSegment(sf::IntRect(188, 101, 78, 68));
            frameBuffer[8].setTextureSegment(sf::IntRect(268, 101, 78, 68));
            frameBuffer[9].setTextureSegment(sf::IntRect(348, 101, 78, 68));
            frameBuffer[10].setTextureSegment(sf::IntRect(428, 101, 78, 68));
            seq_solids.insert(std::make_pair("cast", sf::FloatRect(10, 1, 30, 67)));

            //run
            frameBuffer[11].setTextureSegment(sf::IntRect(0, 202, 69, 55));
            frameBuffer[12].setTextureSegment(sf::IntRect(74, 202, 69, 55));
            frameBuffer[13].setTextureSegment(sf::IntRect(154, 202, 69, 55));
            seq_solids.insert(std::make_pair("run", sf::FloatRect(19, 2, 40, 53)));

            //air slash
            frameBuffer[14].setTextureSegment(sf::IntRect(257, 193, 79, 63));
            frameBuffer[15].setTextureSegment(sf::IntRect(336, 193, 79, 63));
            seq_solids.insert(std::make_pair("air", sf::FloatRect(19, 2, 30, 61)));

            //hurt
            frameBuffer[16].setTextureSegment(sf::IntRect(4, 288, 50, 67));
            seq_solids.insert(std::make_pair("hurt", sf::FloatRect(8, 4, 40, 60)));

            //having one solid here is problematic, because first two frames are crouching, so shorter...
            //jump
            frameBuffer[17].setTextureSegment(sf::IntRect(96, 280, 67, 70));
            frameBuffer[18].setTextureSegment(sf::IntRect(174, 280, 67, 70));
            frameBuffer[19].setTextureSegment(sf::IntRect(250, 280, 67, 70));
            frameBuffer[20].setTextureSegment(sf::IntRect(341, 280, 67, 70));
            seq_solids.insert(std::make_pair("jump", sf::FloatRect(19, 1, 30, 68)));

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

    }

}

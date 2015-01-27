#include <Game/Entity/AnimationLoader.h>
#include <EngineSystem/Log/Log.h>

#include <fstream>

namespace Entity {

    Video::Render::Animation AnimationLoader::loadAnimation(const std::string& animationFilePath, const sf::Texture& texture) {
        Video::Render::Animation animation;
        Video::Render::AnimatedSprite sequence;
        std::ifstream animationFile;
        std::string currentName;
        std::string currentOperation;
        std::string currentBehaviour;
        std::string frameData[5];
        int fD[4];
        float duration;
        bool currentInitialized = false;


        animationFile.open(animationFilePath);


        if(animationFile.is_open() != true) {
            Log::get().write(Log::System::Game, "Unable to open animation file: %s", animationFilePath.c_str());
        

        } else {

            while(animationFile) {

                animationFile >> currentOperation;

                if(currentOperation == "sequence") {

                    if(currentInitialized) {
                        if(currentBehaviour == "true")
                            animation.addSequence(currentName, sequence, true);

                        else if(currentBehaviour == "false")
                            animation.addSequence(currentName, sequence, false);

                        else
                            animation.addSequence(currentName, sequence, currentBehaviour);
                    }

                    sequence = Video::Render::AnimatedSprite(texture);

                    animationFile >> currentName;
                    animationFile >> currentBehaviour;

                    currentInitialized = false;

                } else if(currentOperation == "frame") {
                    if(currentName != "") {

                        try {
                            animationFile >> frameData[0] >> frameData[1] >> frameData[2] >> frameData[3] >> frameData[4];

                            for(int i = 0; i < 4; ++i)
                                fD[i] = std::stoi(frameData[i]);
                        
                            duration = std::stof(frameData[4]);

                            sequence.insertFrame(
                                Video::Render::Sprite::Frame(
                                    sf::IntRect(
                                        fD[0], 
                                        fD[1], 
                                        fD[2], 
                                        fD[3]
                                    ), 
                                    sf::Time(
                                        sf::seconds(duration)
                                    )
                                )
                            );
                            
                            currentInitialized = true;

                        } catch(...) { }

                    }

                } else {
                    Log::get().write(Log::System::Game, "Unknown animation loader operation: %s", currentOperation.c_str());
                }
            }


            if(currentInitialized == true) {
                if(currentBehaviour == "true")
                    animation.addSequence(currentName, sequence, true);

                else if(currentBehaviour == "false")
                    animation.addSequence(currentName, sequence, false);

                else
                    animation.addSequence(currentName, sequence, currentBehaviour);
            }


            animationFile.close();
        }
        
        return animation;
    }

    std::map<std::string, sf::FloatRect> AnimationLoader::loadCollision(const std::string& collisionFilePath) {
        std::map<std::string, sf::FloatRect> collisions;
        std::ifstream collisionFile;
        std::string currentOperation;
        std::string currentName;
        std::string data[4];
        float rectData[4];
        

        collisionFile.open(collisionFilePath);


        if(collisionFile.is_open() != true) {
            Log::get().write(Log::System::Game, "Unable to open animation file: %s", collisionFilePath.c_str());
        

        } else {
            while(collisionFile) {
                collisionFile >> currentOperation;

                if(currentOperation == "rect") {
                    try {
                        collisionFile >> currentName;
                        collisionFile >> data[0] >> data[1] >> data[2] >> data[3];

                        for(int i = 0; i < 4; ++i)
                            rectData[i] = std::stof(data[i]);

                        collisions.insert(
                            std::make_pair(
                                currentName, 
                                sf::FloatRect(
                                    rectData[0],
                                    rectData[1],
                                    rectData[2],
                                    rectData[3]
                                )
                            )
                        );

                    } catch(...) { }

                } else {
                    Log::get().write(Log::System::Game, "Unknown animation collision operation: %s", currentOperation.c_str());
                }
            }


            collisionFile.close();
        }

        return collisions;
    }

}
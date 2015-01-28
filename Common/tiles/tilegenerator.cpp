#include "tilegenerator.h"

namespace Core {

    void TileGenerator::Tick(Engine *engine){

    }

    void TileGenerator::Loaded(Engine* engine){

    }

    double TileGenerator::GetGenerationPercentage(){
        return percentage;
    }

    void TileGenerator::SetGenerationPercentage(double percentage){
        this->percentage = percentage;
    }

    std::string TileGenerator::GetGenerationMessage(){
        return generationMessage;
    }

    bool TileGenerator::IsComplete(){
        return isComplete;
    }

    void TileGenerator::SetGenerationMessage(std::string message){
        this->generationMessage = message;
    }

    void TileGenerator::SetLevel(Level* level){
        this->level = level;
    }

    void TileGenerator::SetComplete(){
        this->isComplete = true;
    }

}

#include "SdlException.h"
#include <string>
#include <SDL2/SDL.h>

SdlException::SdlException(const char* description){
    sprintf(msg, "%s [%s]", description, SDL_GetError());
}

const char* SdlException::what() const noexcept{
    return msg;
}
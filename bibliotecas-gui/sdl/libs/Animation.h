/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>

#include "SdlException.h"

class SdlTexture;
class Area;

class Animation {
   public:
    Animation(const SdlTexture *texture);
    ~Animation();
    void update(float dt);
    void render(const Area& dst, const SDL_RendererFlip &flipType);
    void advanceFrame();

   private:
    /** SDL texture of the raw image. */
    const SdlTexture *texture;
    /** Current animation frame. */
    int currentFrame{0};
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed{0.0f};
    /** Frames per seconds (should this be elsewere?). */
    float frameRate{1.0f / 25.0f};
};

#endif  //__ANIMATION_H__

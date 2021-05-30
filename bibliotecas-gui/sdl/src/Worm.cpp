#include "Area.h"
#include "Worm.h"

Worm::Worm(SdlTexture &texture): an(&texture), facingLeft(false), moving(false), x(300), y(400) {}

Worm::~Worm() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Worm::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Worm::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    Area destArea(x, y, 60, 60);
    an.render(destArea, flip);
}

void Worm::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Worm::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Worm::stopMoving() {
    moving = false;
}

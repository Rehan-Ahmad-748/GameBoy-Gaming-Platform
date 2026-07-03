#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Window.hpp>

class InputSystem {
public:
    bool isKeyPressed(sf::Keyboard::Key key);  // Declaration (not definition)
};

#endif // INPUTSYSTEM_H

#include "InputButton.h"

InputButton::InputButton()
    : Button(), isActive(false)
{
}

InputButton::~InputButton()
{

}

InputButton::InputButton(const sf::String text, sf::Vector2f pos)
    : Button(text, pos),
      isActive(false)
{
}

InputButton::InputButton(const sf::String text, sf::Vector2f pos, sf::Color color)
    :Button(text, pos, color),
    isActive(false)
{
}

void InputButton::onEvent(sf::Event event)
{
    sf::FloatRect boxBound{ box.getGlobalBounds() };
	sf::Vector2f mousePos{ sf::Mouse::getPosition() };

    //check for click and toggle whether active.
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && boxBound.contains(mousePos)) {
			isActive = !isActive;
		}
	}

    //check if active and keypressed
    if (isActive && event.type == sf::Event::TextEntered) {
        sf::Uint32 key = event.text.unicode;
        bool changed = false;

        //backspace
        if (key == 8) {
            const sf::String& s = text.getString();
            int size = s.getSize();
            if (size > 0) {
                text.setString(s.substring(0, size - 1));
                changed = true;
            }
        }

        //ensure key is within range.
        if ( (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ) {
            char c = static_cast<char>(key);
            text.setString(text.getString() + c);
            changed = true;
        }

        //update space of box if characters modified.
        if (changed) {
            box.setSize(text.getLocalBounds().getSize());
        }
        
    }

}

InputButton::InputButton(InputButton&& other)
{
    text = std::move(other.text);
    box = std::move(other.box);
    onCallback = other.onCallback;
    color = other.color;
	font = other.font;
	text.setFont(*font);
	other.font = nullptr; //ensure other pointer invalided when it goes out of scope.
    other.onCallback = nullptr;
    isActive = other.isActive;
}

InputButton& InputButton::operator=(InputButton&& other) {
    if (this != &other) {
        text = std::move(other.text);
        box = std::move(other.box);
        onCallback = other.onCallback;
        color = other.color;
		font = other.font;
        text.setFont(*font);
		other.font = nullptr; //ensure other pointer invalided when it goes out of scope.
        setColor(color);
        other.onCallback = nullptr;
        isActive = other.isActive;
    }
    return *this;
}

//copy constructor (need to be careful)
InputButton::InputButton(const InputButton &other)
{
	if (this != &other) {

        this->text = other.text;
        this->box = other.box;
        this->onCallback = other.onCallback;
        this->color = other.color;
        setColor(color);
		font = other.font;
        isActive = other.isActive;

    }
}

//copy operator (need to be careful)
InputButton &InputButton::operator=(const InputButton &other)
{
    if (this != &other) {

        this->text = other.text;
        this->box = other.box;
        this->onCallback = other.onCallback;
        this->color = other.color;
        setColor(color);
		font = other.font;
        isActive = other.isActive;

    }
    return *this;
}

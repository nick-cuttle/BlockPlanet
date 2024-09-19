#include "InputButton.h"

InputButton::InputButton()
    : Button(), isActive(false)
{
}

InputButton::~InputButton()
{

}

InputButton::InputButton(const sf::String text, sf::Vector2f pos)
    : 
    Button(text, pos),
    isActive(false),
    label("", *font, 48)
{
}

InputButton::InputButton(const sf::String text, sf::Vector2f pos, sf::Color color, sf::String lab)
    :
    Button(text, pos, color),
    isActive(false),
    label(lab, *font, 48)
{

    label.setFont(*font);
    // Get the bounds for both the label and the text
    sf::FloatRect labelBounds = this->label.getLocalBounds();
    sf::FloatRect textBounds = this->text.getLocalBounds();

    // Calculate the total width and height to center both label and text as a group
    float totalWidth = labelBounds.width + textBounds.width;
    float totalHeight = std::max(labelBounds.height, textBounds.height);

    // Adjust position to center the entire label + text block
    sf::Vector2f centered{pos.x - totalWidth / 2, pos.y - totalHeight / 2};

    // Set the label position
    this->label.setPosition(centered);

    // Set the text position right after the label
    this->text.setPosition({centered.x + labelBounds.width, centered.y});

    // Update the bounding box to fit both the label and the text
    this->box = sf::RectangleShape({textBounds.width, totalHeight});

    // Set the position of the box to match the centered label's position
    this->box.setPosition(this->text.getPosition().x + textBounds.left, this->text.getPosition().y + textBounds.top);
    setColor(color);

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

            if (text.getString().isEmpty()) {
                box.setSize({10, box.getLocalBounds().height});
            }
            else {
                box.setSize(text.getLocalBounds().getSize());
            }
        }
        
    }

}

void InputButton::draw(sf::RenderWindow *window)
{
    window->draw(label);
    window->draw(box);
	window->draw(text);
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

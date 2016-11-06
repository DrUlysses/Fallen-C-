#include "GuiControl.hpp"

GuiControl::GuiControl(const int& index)
{
	this->index = index;
	focused = false;
	pressed = false;
}

void GuiControl::setFocused(const bool& focused)
{
	this->focused = focused;
}

void GuiControl::setPressed(const bool& pressed)
{
	this->pressed = pressed;
}

const bool& GuiControl::isFocused() const
{
	return focused;
}

const bool& GuiControl::isPressed() const
{
	return pressed;
}

const int& GuiControl::getIndex() const
{
	return index;
}
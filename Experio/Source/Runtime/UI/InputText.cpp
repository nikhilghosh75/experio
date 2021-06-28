#include "InputText.h"
#include "UIQueue.h"
#include "../Input/Input.h"

InputText::InputText()
{
}

InputText::InputText(GameObject* gameObject)
{
	this->gameObject = gameObject;

	enableAlpha = true;
	enableNumeric = true;
	enableLowercase = true;
	enableUppercase = true;
}

void InputText::Start()
{
	textComponent = gameObject->GetComponent<TextComponent>();
}

void InputText::Update()
{
	UIQueue::AddToQueue(this, gameObject->rectTransform.z, EUIComponentType::InputText);

	if (textComponent != nullptr)
	{
		textComponent->text = currentText;
	}

	if (isSelected)
		HandleKeyInput();
}

void InputText::HandleInput()
{
	if (Input::GetMouseButtonDown(EMouseButton::Left))
	{
		isSelected = !isSelected;
	}
}

void InputText::HandleKeyInput()
{
	if (!Input::AnyKeyDown())
		return;

	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		if (Input::GetKeyDown((EKeyCode)i))
		{
			if (i == (int)EKeyCode::Backspace)
			{
				if (!currentText.empty())
					currentText.pop_back();
			}
			else if (Input::IsAlpha((EKeyCode)i) && enableAlpha)
			{
				if (ConvertToUpper((EKeyCode)i))
				{
					char charToAdd = LString::ToUpper(Input::KeyCodeToChar((EKeyCode)i));
					currentText.push_back(charToAdd);
				}
				else if (enableLowercase)
				{
					char charToAdd = LString::ToLower(Input::KeyCodeToChar((EKeyCode)i));
					currentText.push_back(charToAdd);
				}
			}
			else if (Input::IsNumeric((EKeyCode)i) && enableNumeric)
			{
				currentText.push_back(Input::KeyCodeToChar((EKeyCode)i));
			}
		}
	}
}

bool InputText::ConvertToUpper(EKeyCode keyCode)
{
	if (!enableLowercase)
		return true;

	return (Input::GetKeyDown(EKeyCode::LeftShift) || Input::GetKeyDown(EKeyCode::RightShift))
		&& enableUppercase;
}

#include "UTextBlock.h"

UTextBlock::UTextBlock(const FString& _id, const FWidgetTransform& _transform, const FString& _str, const uInt& _size, const sf::Color& _color) : UWidget(_id)
{
	string = _str;
	size = _size;
	color = _color;

	font = sf::Font();
	text = new sf::Text();

	drawable = text;

	LoadText(_transform);
}

UTextBlock::~UTextBlock()
{
	delete text, drawable;
	text = nullptr;
	drawable = nullptr;
}

void UTextBlock::SetText(const FString& _text)
{
	string = _text;
	text->setString(string.GetText());
}

void UTextBlock::SetSize(const uInt& _size)
{
	size = _size;
	text->setCharacterSize(size);
}
void UTextBlock::SetStyle(const uInt& _style)
{
	text->setStyle(_style);
}
void UTextBlock::LoadFont(const FString& _fontName)
{
	std::string _path = FString::Format("../Content/Font/{}", _fontName.GetText()).GetText();
	if (!font.loadFromFile(_path))
	{
		std::cout << FString::Format("Font {} cannot be load in \"{}\"", _fontName.GetText(), _path).GetText() << std::endl;
	}
}
void UTextBlock::LoadText(const FWidgetTransform& _transform)
{	
	SetText(string);
	SetSize(size);
	SetFont("arial.ttf");
	SetColor(color);
	SetPosition(_transform);
}

void UTextBlock::SetColor(const sf::Color& _color)
{
	color = _color;
	text->setColor(color);
}
void UTextBlock::SetFont(const FString& _fontName)
{
	LoadFont(_fontName);
	text->setFont(font);
}

FVector2 UTextBlock::GetPosition() const
{
	sf::Vector2f _position = GetPositionSF();
	return FVector2(_position.x, _position.y);
}

void UTextBlock::SetPosition(const FWidgetTransform& _transform)
{
	UWidget::SetPosition(_transform);
	text->setPosition(_transform.posX, _transform.posY);
}

void UTextBlock::SetPosition(const uInt& _x, const uInt& _y)
{
	UWidget::SetPosition(_x, _y);
	text->setPosition(_x, _y);
}

sf::Vector2f UTextBlock::GetPositionSF() const
{
	return text->getPosition();
}

#pragma once
#include "../UWidget.h"

class UTextBlock: public UWidget
{
	FString string = "";
	uInt size = 15;
	sf::Color color = sf::Color::Red;
	sf::Text* text = nullptr;
	sf::Font font;



public:
	FORCEINLINE sf::Text* GetDrawable() const
	{ return text; }

public:
	UTextBlock(const FString& _id, const FWidgetTransform& _transform, const FString& _str, const uInt& _size = 15, const sf::Color& _color = sf::Color::White);
	virtual ~UTextBlock() override;



private:
	void LoadFont(const FString& _fontName);
	void LoadText(const FWidgetTransform& _transform);

public:
	void SetText(const FString& _text);
	void SetSize(const uInt& _size);
	void SetStyle(const uInt& _style);
	void SetFont(const FString& _fontName);
	void SetColor(const sf::Color& _color);


	virtual void SetPosition(const FWidgetTransform& _transform) override;
	virtual void SetPosition(const int& _x, const int& _y) override;
	virtual FVector2 GetPosition() const override;
	virtual sf::Vector2f GetPositionSF() const override;
};
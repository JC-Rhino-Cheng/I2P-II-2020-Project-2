#include <algorithm>
#include <string>

#include "Point.hpp"
#include "Slider.hpp"
#include "GameEngine.hpp"

Slider::Slider(float x, float y, float w, float h) :
	ImageButton("stage-select/slider.png", "stage-select/slider-blue.png", x, y),
	Bar("stage-select/bar.png", x, y, w, h),
	End1("stage-select/end.png", x, y + h / 2, 0, 0, 0.5, 0.5),
	End2("stage-select/end.png", x + w, y + h / 2, 0, 0, 0.5, 0.5){
	Position.x += w;
	Position.y += h / 2;
	Anchor = Engine::Point(0.5, 0.5);
}
//OK
// TODO 4 (0/6): Finish the 6 functions below and ensure it can control both BGM and SFX volume.
//               The slider shouldn't be dragged outside the bar, and you should also keep the mouse-in / mouse-out effect.
void Slider::Draw() const {
	//OK
	// TODO 4 (1/6): Draw all components.
	Bar.Draw();
	End1.Draw();//畫左側兩個
	End2.Draw();//畫右側兩個
	ImageButton::Draw();
}
void Slider::SetOnValueChangedCallback(std::function<void(float value)> onValueChangedCallback) {
	//OK
	// TODO 4 (2/6): Set the function pointer. Can imitate ImageButton's 'SetOnClickCallback'.
	OnValueChangedCallback = onValueChangedCallback;
}
void Slider::SetValue(float value) {
	//OK
	// TODO 4 (3/6): Call 'OnValueChangedCallback' when value changed. Can imitate ImageButton's 'OnClickCallback'.
	//               Also move the slider along the bar, to the corresponding position.
	if (value > Max || value < Min)return;
	if(this->value != value && Down){
		OnValueChangedCallback(value);
		Position.x = End1.Position.x + value * Bar.GetBitmapWidth();
	}
	
}
void Slider::OnMouseDown(int button, int mx, int my) {
	//OK
	// TODO 4 (4/6): Set 'Down' to true if mouse is in the slider.
	if (Position.x - GetBitmapWidth() / 2 <= mx && mx <= Position.x + GetBitmapWidth() / 2 && Position.y - GetBitmapHeight() / 2 <= my && my <= Position.y + GetBitmapHeight() / 2) {
		Down = true;
	}
}
void Slider::OnMouseUp(int button, int mx, int my) {
	//OK
	// TODO 4 (5/6): Set 'Down' to false.
	Down = false;
}
void Slider::OnMouseMove(int mx, int my) {
	//OK
	// TODO 4 (6/6): Clamp the coordinates and calculate the value. Call 'SetValue' when you're done.
	mouseIn = (Position.x - GetBitmapWidth() / 2 <= mx && mx <= Position.x + GetBitmapWidth() / 2 && Position.y - GetBitmapHeight() / 2 <= my && my <= Position.y + GetBitmapHeight() / 2) ? true : false;
	if (!mouseIn || !Enabled) bmp = imgOut;
	else bmp = imgIn;
	
	const auto  percentage = (mx - End1.Position.x) / (End2.Position.x - End1.Position.x);
	SetValue(percentage);
}

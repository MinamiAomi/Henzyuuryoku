#pragma once

#ifndef Easing_h_
#define Easing_h_

class Easing
{
public:

public:
	

	static float easeInSine(float x);
	static float easeOutSine(float x);
	static float easeInOutSine(float x);
	static float easeInQuad(float x);
	static float easeOutQuad(float x);
	static float easeInOutQuad(float x);
	static float easeInCubic(float x);
	static float easeOutCubic(float x);
	static float easeInOutCubic(float x);
	static float easeInQuart(float x);
	static float easeOutQuart(float x);
	static float easeInOutQuart(float x);
	static float easeInQuint(float x);
	static float easeOutQuint(float x);
	static float easeInOutQuint(float x);
	static float easeInExpo(float x);
	static float easeOutExpo(float x);
	static float easeInCirc(float x);
	static float easeOutCirc(float x);
	static float easeInOutCirc(float x);
	static float easeInBack(float x);
	static float easeOutBack(float x);
	static float easeInOutBack(float x);
	static float easeInElastic(float x);
	static float easeOutElastic(float x);
	static float easeInOutElastic(float x);
	static float easeInBounce(float x);
	static float easeOutBounce(float x);
	static float easeInOutBounce(float x);

private:
	Easing();
	~Easing();
};

#endif
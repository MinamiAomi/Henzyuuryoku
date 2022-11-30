#pragma once

class Debug
{
public:
	static constexpr unsigned int kHitColor = 0xFF000066;
	static constexpr unsigned int kNotHitColor = 0xFFFFFF66;

private:
	static int mPrintNum;

public:
	static void PrintNumReset();
	static void Print(const char* format, ...);
	static void Print(bool onoff, const char* format, ...);
	static void PrintNum();
};


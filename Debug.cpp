#include "Debug.h"
#include <Novice.h>

int Debug::mPrintNum = 0;

void Debug::PrintNumReset() {
	mPrintNum = 0;
}

void Debug::Print(const char* format, ...) {
	va_list args;
	va_start(args, format);
	Novice::ScreenPrintf(0, 20 * mPrintNum, format, args);
	va_end(args);
	mPrintNum++;
}

void Debug::Print(bool onoff, const char* format, ...) {
	if (onoff) {
		va_list args;
		va_start(args, format);
		Novice::ScreenPrintf(0, 20 * mPrintNum, format, args);
		va_end(args);
		mPrintNum++;
	}
}

void Debug::PrintNum() {
	Novice::ScreenPrintf(1240, 0, "%d", mPrintNum);
}
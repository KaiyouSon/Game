#include "FrameRate.h"
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

FrameRate::FrameRate() : frameRate(0)
{
}

void FrameRate::Init(const float& frameRate)
{
	reference = steady_clock::now();
	this->frameRate = frameRate;
}

void FrameRate::Update()
{
	// １/６０秒ぴったりの時間
	const microseconds minTime(uint64_t(1000000.0f / frameRate));

	// １/６０秒よりわずかに短い時間
	const microseconds minCheckTime(uint64_t(1000000.0f / (frameRate + 5)));

	// 現在の時間を取得
	steady_clock::time_point nowTime = steady_clock::now();

	// 前回の記録から経過時間を取得する
	microseconds elapsedTime = duration_cast<microseconds>(nowTime - reference);

	// １/６０秒経ってない場合
	if (elapsedTime < minCheckTime)
	{
		// １/６０秒経過するまで微小なスリープを繰り返す
		while (steady_clock::now() - reference < minTime)
		{
			sleep_for(microseconds(1));
		}
	}

	// 現在の時間を記録する
	reference = steady_clock::now();


}

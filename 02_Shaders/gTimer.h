#pragma once

/*
	Nanoszekundum pontoss�g� (*) GPU id�z�t�.

	Fontos: nem lehet egym�sba �gyazni a k�l�nb�z� timer-ek k�r�seit sem, am�g
	az OpenGL specifik�ci� nem enged�lyezi a nested glBegin/EndQuery-ket!

	(*): driver �s GPU f�gg�
*/

#include <GL/glew.h>
#include <chrono>
class GPU_Timer
{
public:
	GPU_Timer(void);
	~GPU_Timer(void);

	void Start();
	void Stop();
	double QuerryMillisecs();
	inline void Swap() { act = 1 - act; }

private:
	GLuint		queries[2];
	int			act = 0;
	GLuint64	last_delta;
};

class CPU_Timer
{
protected:
	std::chrono::high_resolution_clock::time_point start, finish;
public:
	inline void Start()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	inline void Finish()
	{
		finish = std::chrono::high_resolution_clock::now();
	}
	inline double GetSeconds()
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
	}
	inline double GetMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(finish - start).count();
	}
};

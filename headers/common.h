#ifndef INCLUDES_COMMON_H
#define INCLUDES_COMMON_H

// Try and autodetect the platform
#ifdef _WIN32
	#define PLATFORM_WINDOWS
#else
	#if defined(__GNUC__) && __GNUC__ >= 4
		#define PLATFORM_LINUX
	#endif
#endif

// 64 meters to the pixel
#define PIXELS_METER_RATIO 64

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#define DEG2RAD(deg) \
	(deg * (M_PI/180))

typedef double Timestep;

#endif /* INCLUDES_COMMON_H */


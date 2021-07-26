#include <hls_stream.h>
#include <ap_fixed.h>
#include <iostream>
using namespace std;

typedef ap_fixed<16, 5> data_type;
typedef ap_fixed<16, 5> weight_type;
typedef ap_fixed<40, 14> mid_data_type;


#ifndef AXIO
#define AXIO
struct AXI_datatype_O{
	float data;
	bool last;
};
#endif

#define M 		64	// middle channel number
#define K  		3	// kernel size
#define L 		12
#define IMGH	256
#define IMGW 	256

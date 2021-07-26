#include "types.h"
#include "load_img.h"
#include "MAC_I.h"
#include "MAC_DW.h"
#include "MAC_PW.h"
#include "MAC_O.h"
#include "reuse.h"
#include "reuseLUT.h"

// 由于模板函数在编译过程中不会生成obj，
// 因此需要将模板函数的实现包含在头文件中

void DnCNN(
	hls::stream<float>& input_img,
	hls::stream<AXI_datatype_O>& output_stream,
	hls::stream<float>& weight_stream,
	hls::stream<int>& control
);

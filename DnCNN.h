#include "types.h"
#include "load_img.h"
#include "MAC_I.h"
#include "MAC_DW.h"
#include "MAC_PW.h"
#include "MAC_O.h"
#include "reuse.h"
#include "reuseLUT.h"

// ����ģ�庯���ڱ�������в�������obj��
// �����Ҫ��ģ�庯����ʵ�ְ�����ͷ�ļ���

void DnCNN(
	hls::stream<float>& input_img,
	hls::stream<AXI_datatype_O>& output_stream,
	hls::stream<float>& weight_stream,
	hls::stream<int>& control
);

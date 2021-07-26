#include "types.h"

template<int TM, int ROW, int COL>	// TM for input channel tiling	ROW IMGW COL IMGH
void MAC_I(hls::stream<data_type>& input_data, hls::stream<data_type> output_data[TM], weight_type weights[M][3][3], int row, int col);

template<int TM, int ROW, int COL>	// TM for input channel tiling	ROW IMGW COL IMGH
void MAC_I(hls::stream<data_type>& input_data, hls::stream<data_type> output_data[TM], weight_type weights[M][3][3], int row, int col) {
	int m, i, j, tm;

	data_type input_data_t[3][3];

#pragma HLS ARRAY_PARTITION variable=weights cyclic factor=8 dim=1


	if ((row < ROW) & (col < COL)) {
		for (m = 0; m < M; m += TM) {
			mid_data_type output_data_tt[TM] = { (mid_data_type)0, (mid_data_type)0, (mid_data_type)0, (mid_data_type)0, (mid_data_type)0, (mid_data_type)0, (mid_data_type)0, (mid_data_type)0 };
#pragma HLS ARRAY_PARTITION variable=output_data_tt cyclic factor=8 dim=1
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
#pragma HLS PIPELINE
					if (m == 0) {
						input_data_t[i][j] = input_data.read();
						
					}
					for (tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
						// MAC
						output_data_tt[tm] += weights[m + tm][i][j] * input_data_t[i][j];

						// ReLU
						if ((i == 2) & (j == 2) & (output_data_tt[tm] < 0)) { 
							output_data_tt[tm] = (data_type)0;
						}


						if ((i == 2) & (j == 2)) {
							output_data[tm].write(output_data_tt[tm]);
						}
					}	// for tm
				}	// for j
			}	// for i
		}	// for i
	}	// if
}	// MAC_I

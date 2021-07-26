#include "types.h"

template<int TM, int ROWL, int ROWH, int COLL, int COLH>
void MAC_DW(hls::stream<data_type> input_data[TM], hls::stream<data_type> output_data[TM], weight_type weights[M][3][3], mid_data_type bias[M], int row, int col);

template<int TM, int ROWL, int ROWH, int COLL, int COLH>
void MAC_DW(hls::stream<data_type> input_data[TM], hls::stream<data_type> output_data[TM], weight_type weights[M][3][3], mid_data_type bias[M], int row, int col) {


#pragma HLS ARRAY_PARTITION variable=weights cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=bias cyclic factor=8 dim=1

	int m, i, j, tm;
	if ((row > ROWL) & (row < ROWH) & (col > COLL) & (col < COLH)) {
		for (m = 0; m < M; m += TM) {
			mid_data_type output_data_t[TM];
#pragma HLS ARRAY_PARTITION variable=output_data_t cyclic factor=8 dim=1
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
#pragma HLS PIPELINE
					for (tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
						// MAC
						if ((i == 0) & (j == 0)) {
							output_data_t[tm] = bias[m + tm];
						}
						output_data_t[tm] += mid_data_type(weights[m + tm][i][j] * input_data[tm].read());
						// ReLU
						if ((i == 2) & (j == 2) & (output_data_t[tm] < 0)) { 
							output_data_t[tm] = (data_type)0;
						}

						if ((i == 2) & (j == 2)) {
							output_data[tm].write(output_data_t[tm]);	
						}
					}
				}
			}
		}
	}
}

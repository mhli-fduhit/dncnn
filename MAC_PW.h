#include "types.h"

template<int TM, int TN, int ROWL, int ROWH, int COLL, int COLH>	// m for output; n for input;   weights[m][n]
void MAC_PW(hls::stream<data_type> input_data[TM], hls::stream<data_type> output_data[TM], weight_type weights[M][M], mid_data_type bias[M], int row, int col);

template<int TM, int TN, int ROWL, int ROWH, int COLL, int COLH>	// m for output; n for input;   weights[m][n]
void MAC_PW(hls::stream<data_type> input_data[TM], hls::stream<data_type> output_data[TM], weight_type weights[M][M], mid_data_type bias[M], int row, int col) {
	int m, n, tm, tn;

	data_type input_data_t[M];


#pragma HLS ARRAY_PARTITION variable=input_data_t cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=weights cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=weights cyclic factor=8 dim=2
#pragma HLS ARRAY_PARTITION variable=bias cyclic factor=8 dim=1

	if ((row > ROWL) & (row < ROWH) & (col > COLL) & (col < COLH)) {
		for (m = 0; m < M; m += TM) {
			mid_data_type output_data_t[TM];
#pragma HLS ARRAY_PARTITION variable=output_data_t cyclic factor=8 dim=1
			for (int ii = 0; ii < TM; ii++) {
#pragma HLS UNROLL
				output_data_t[ii] = bias[m + ii];
			}
			for (n = 0; n < M; n += TN) {
#pragma HLS PIPELINE
				for (tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL

					mid_data_type out_tt;

					if ((m == 0) & (tm == 0)) {
						input_data_t[n + 0] = input_data[0].read();
						input_data_t[n + 1] = input_data[1].read();
						input_data_t[n + 2] = input_data[2].read();
						input_data_t[n + 3] = input_data[3].read();
						input_data_t[n + 4] = input_data[4].read();
						input_data_t[n + 5] = input_data[5].read();
						input_data_t[n + 6] = input_data[6].read();
						input_data_t[n + 7] = input_data[7].read();
					}

					out_tt = mid_data_type(weights[m + tm][n + 0] * input_data_t[n + 0])
						+ mid_data_type(weights[m + tm][n + 1] * input_data_t[n + 1])
						+ mid_data_type(weights[m + tm][n + 2] * input_data_t[n + 2])
						+ mid_data_type(weights[m + tm][n + 3] * input_data_t[n + 3])
						+ mid_data_type(weights[m + tm][n + 4] * input_data_t[n + 4])
						+ mid_data_type(weights[m + tm][n + 5] * input_data_t[n + 5])
						+ mid_data_type(weights[m + tm][n + 6] * input_data_t[n + 6])
						+ mid_data_type(weights[m + tm][n + 7] * input_data_t[n + 7]);
					output_data_t[tm] += out_tt;


					// ReLU
					if (((n + TN) == M) & (output_data_t[tm] < 0)) {
						output_data_t[tm] = (data_type)0;
					}


					if ((n + TN) == M) { // ToDo: confirm index
						output_data[tm].write(output_data_t[tm]);
						
					}
				}
			}
		}
	}
}

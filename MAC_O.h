#include "types.h"

template<int TN, int ROWL, int ROWH, int COLL, int COLH>	// m for output; n for input;   weights[m][n]
void MAC_O(hls::stream<data_type> input_data[TN], hls::stream<AXI_datatype_O>& output_data, weight_type weights[M][3][3], int row, int col);

template<int TN, int ROWL, int ROWH, int COLL, int COLH>	// m for output; n for input;   weights[m][n]
void MAC_O(hls::stream<data_type> input_data[TN], hls::stream<AXI_datatype_O>& output_data, weight_type weights[M][3][3], int row, int col) {
	int n, i, j, tn;

	mid_data_type out_tmp = 0;

#pragma HLS ARRAY_PARTITION variable=input_data cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=weights cyclic factor=8 dim=1

	if ((row > ROWL) & (row < ROWH) & (col > COLL) & (col < COLH)) {
		for (n = 0; n < M; n += TN) {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
#pragma HLS PIPELINE

					mid_data_type out_tt;
					out_tt = mid_data_type(weights[n + 0][i][j] * input_data[0].read())
						+ mid_data_type(weights[n + 1][i][j] * input_data[1].read())
						+ mid_data_type(weights[n + 2][i][j] * input_data[2].read())
						+ mid_data_type(weights[n + 3][i][j] * input_data[3].read())
						+ mid_data_type(weights[n + 4][i][j] * input_data[4].read())
						+ mid_data_type(weights[n + 5][i][j] * input_data[5].read())
						+ mid_data_type(weights[n + 6][i][j] * input_data[6].read())
						+ mid_data_type(weights[n + 7][i][j] * input_data[7].read());

					out_tmp += out_tt;



					if ((i == 2) & (j == 2) & ((n + TN) == M)) {
						AXI_datatype_O tmp;
						tmp.data = (float)out_tmp;
						if ((row == (ROWH-1)) & (col == (COLH - 1))) {
							tmp.last = 1;
						}
						else {
							tmp.last = 0;
						}

						output_data.write(tmp);
					}
				}
			}
		}
	}
}

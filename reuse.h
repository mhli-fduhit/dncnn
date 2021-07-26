# include "types.h"

template<int SUBROW, int SUBCOL, int TM, int REUSEID>
void reuse(int row, int col, hls::stream<data_type> out_stream[TM], hls::stream<data_type> in_stream[TM]);


template<int SUBROW, int SUBCOL, int TM, int REUSEID>
void reuse(
	int row,
	int col,
	hls::stream<data_type> out_stream[TM],
	hls::stream<data_type> in_stream[TM]
)
{

	int layer_row = row - SUBROW;
	int layer_col = col - SUBCOL;

	static data_type input_BL[M][3][2];
	//#pragma HLS RESOURCE variable=input_BL core=RAM_1P_LUTRAM
	static data_type input_BT[M][2][IMGW + 2];
	//#pragma HLS RESOURCE variable=input_BT core=RAM_1P_LUTRAM
	//	static data_type output_data[M];		// in port: last layer output data
	static data_type input_data[M][3][3];	// out port: next layer output data
#pragma HLS ARRAY_PARTITION variable=input_data cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=input_BL cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=input_BT cyclic factor=8 dim=1

	if ((layer_row >= 0) & (layer_row <= IMGH) & (layer_col >= 0) & (layer_col <= IMGW)) {
		if ((layer_row == 0) & (layer_col == 0)) {
			for (int ch = 0; ch < M; ch += TM) {
				for (int ro = 0; ro < 2; ro++) {
					for (int co = 0; co < 2; co++) {
#pragma HLS PIPELINE
						for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
							if ((ro == 0) & (co == 1)) {

								input_BT[ch + tm][ro][co] = out_stream[tm].read();

							}
							else
							{
								input_BT[ch + tm][ro][co] = (data_type)0;
							}
						}
					}
				}
			}
		}
		else if ((layer_row == 0) & (layer_col > 0)) {
			for (int ch = 0; ch < M; ch += TM) {
#pragma HLS PIPELINE
				for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
					if (layer_col < IMGW) {
						input_BT[ch + tm][0][layer_col + 1] = out_stream[tm].read();
						input_BT[ch + tm][1][layer_col + 1] = (data_type)0;
					}
					else
					{
						input_BT[ch + tm][0][layer_col + 1] = (data_type)0;
						input_BT[ch + tm][1][layer_col + 1] = (data_type)0;

					}
				}
			}
		}
		else if ((layer_row > 0) & (layer_col == 0)) {
			//#pragma HLS DATAFLOW
			for (int ch = 0; ch < M; ch += TM) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 2; co++) {
#pragma HLS PIPELINE
						for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
							if (co == 1) {
								input_BL[ch + tm][ro][co] = (data_type)0;
							}
							else
							{
								if (ro < 2) {
									input_BL[ch + tm][ro][co] = input_BT[ch + tm][(layer_row + ro) % 2][1];
								}
								else
								{
									if (layer_row < IMGH) {
										input_BL[ch + tm][ro][co] = out_stream[tm].read();
									}
									else
									{
										input_BL[ch + tm][ro][co] = (data_type)0;
									}

								}
							}
						}
					}
				}
			}

			for (int ch = 0; ch < M; ch += TM) {
#pragma HLS PIPELINE
				for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
					input_BT[ch + tm][layer_row % 2][1] = input_BL[ch + tm][2][0]; //ToDo
				}
			}
		}
		else if ((layer_row > 0) & (layer_col > 0)) {
			//#pragma HLS DATAFLOW
			for (int ch = 0; ch < M; ch += TM) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 3; co++) {
#pragma HLS PIPELINE
						for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
							if (co < 2) {
								input_data[ch + tm][ro][co] = input_BL[ch + tm][ro][(layer_col + co) % 2];
								in_stream[tm].write(input_data[ch + tm][ro][co]);
							}
							else if (ro < 2) {
								input_data[ch + tm][ro][co] = input_BT[ch + tm][(layer_row + ro) % 2][layer_col + 1];
								in_stream[tm].write(input_data[ch + tm][ro][co]);
							}
							else {
								if ((layer_col < IMGW) & (layer_row < IMGH)) {
									input_data[ch + tm][ro][co] = out_stream[tm].read();
									in_stream[tm].write(input_data[ch + tm][ro][co]);
								}
								else
								{
									input_data[ch + tm][ro][co] = (data_type)0;
									in_stream[tm].write(input_data[ch + tm][ro][co]);
								}

							}
						}
					}
				}
			}

			for (int ch = 0; ch < M; ch += TM) {
#pragma HLS PIPELINE
				for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
					input_BT[ch + tm][layer_row % 2][layer_col + 1] = input_data[ch + tm][2][2];
				}
			}

			for (int ch = 0; ch < M; ch += TM) {
				for (int ro = 0; ro < 3; ro++) {
#pragma HLS PIPELINE
					for (int tm = 0; tm < TM; tm++) {
#pragma HLS UNROLL
						input_BL[ch + tm][ro][layer_col % 2] = input_data[ch + tm][ro][2];
					}
				}
			}
		}
	}
}
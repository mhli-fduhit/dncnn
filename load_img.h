#include "types.h"
template<int loadChannel>
void load_img(int row, int col, hls::stream<float>& input_img, hls::stream<data_type>& layer1_input_stream);

template<int loadChannel>
void load_img(
	int row,	// max IMGH - 1
	int col,	// max IMGW - 1
	hls::stream<float>& input_img,
	hls::stream<data_type>& layer1_input_stream
)
{
	static data_type layer1_input_data[loadChannel][3][3];
	static data_type layer1_input_BL[loadChannel][3][2];
	static data_type layer1_input_BT[loadChannel][2][IMGW + 2];

	if ((row < IMGW) & (col < IMGW)) {
		if ((row == 0) & (col == 0)) {
			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 3; co++) {
#pragma HLS PIPELINE
						if ((ro == 0) | (co == 0)) {
							layer1_input_data[ch][ro][co] = (data_type)0;
							layer1_input_stream.write(layer1_input_data[ch][ro][co]);
						}
						else {
							layer1_input_data[ch][ro][co] = (data_type)input_img.read();
							layer1_input_stream.write(layer1_input_data[ch][ro][co]);
						}
					}
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 2; co++) {
						layer1_input_BL[ch][ro][co] = layer1_input_data[ch][ro][co + 1];
					}
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 2; ro++) {
					for (int co = 0; co < 3; co++) {
						layer1_input_BT[ch][ro][co] = layer1_input_data[ch][ro + 1][co];
					}
				}
			}

		}
		else if ((row == 0) & (col > 0)) {
			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 3; co++) {
#pragma HLS PIPELINE
						if (co < 2) {
							layer1_input_data[ch][ro][co] = layer1_input_BL[ch][ro][(col + 1 + co) % 2];
							layer1_input_stream.write(layer1_input_data[ch][ro][co]);
						}
						else {
							if (ro != 0) {
								if (col < (IMGW - 1)) {
									layer1_input_data[ch][ro][co] = (data_type)input_img.read();  // ro - 1
									layer1_input_stream.write(layer1_input_data[ch][ro][co]);
								}
								else
								{
									layer1_input_data[ch][ro][co] = (data_type)0;
									layer1_input_stream.write(layer1_input_data[ch][ro][co]);
								}
							}
							else
							{
								layer1_input_data[ch][ro][co] = (data_type)0;
								layer1_input_stream.write(layer1_input_data[ch][ro][co]);
							}
						}
					}
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 2; ro++) {

					layer1_input_BT[ch][ro][col + 2] = layer1_input_data[ch][ro + 1][2];
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {

					layer1_input_BL[ch][ro][(col + 1) % 2] = layer1_input_data[ch][ro][2];

				}
			}
		}
		else if ((row > 0) & (col == 0)) {
			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 3; co++) {
#pragma HLS PIPELINE
						if (ro < 2) {
							layer1_input_data[ch][ro][co] = layer1_input_BT[ch][(row + 1 + ro) % 2][co];
							layer1_input_stream.write(layer1_input_data[ch][ro][co]);
						}
						else {
							if (co != 0) {
								if (row < (IMGH - 1)) {
									layer1_input_data[ch][ro][co] = (data_type)input_img.read();
									layer1_input_stream.write(layer1_input_data[ch][ro][co]);
								}
								else
								{
									layer1_input_data[ch][ro][co] = (data_type)0;
									layer1_input_stream.write(layer1_input_data[ch][ro][co]);
								}
							}
							else
							{
								layer1_input_data[ch][ro][co] = (data_type)0;
								layer1_input_stream.write(layer1_input_data[ch][ro][co]);
							}

						}
					}
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int co = 0; co < 3; co++) {

					layer1_input_BT[ch][(row + 1) % 2][co] = layer1_input_data[ch][2][co];
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 2; co++) {
						layer1_input_BL[ch][ro][co] = layer1_input_data[ch][ro][co + 1];
					}
				}
			}


		}
		else if ((row > 0) & (col > 0)) {
			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {
					for (int co = 0; co < 3; co++) {
#pragma HLS PIPELINE
						if (co < 2) {
							layer1_input_data[ch][ro][co] = layer1_input_BL[ch][ro][(col + 1 + co) % 2];
							layer1_input_stream.write(layer1_input_data[ch][ro][co]);
						}
						else if (ro < 2) {
							layer1_input_data[ch][ro][co] = layer1_input_BT[ch][(row + 1 + ro) % 2][col + 2];
							layer1_input_stream.write(layer1_input_data[ch][ro][co]);
						}
						else
						{
							if ((row < (IMGH - 1)) & (col < (IMGW - 1))) {
								layer1_input_data[ch][ro][co] = (data_type)input_img.read();
								layer1_input_stream.write(layer1_input_data[ch][ro][co]);
							}
							else
							{
								layer1_input_data[ch][ro][co] = (data_type)0;
								layer1_input_stream.write(layer1_input_data[ch][ro][co]);
							}
						}
					}
				}
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				layer1_input_BT[ch][(row + 1) % 2][col + 2] = layer1_input_data[ch][2][2];
			}

			for (int ch = 0; ch < loadChannel; ch++) {
				for (int ro = 0; ro < 3; ro++) {

					layer1_input_BL[ch][ro][(col + 1) % 2] = layer1_input_data[ch][ro][2];

				}
			}
		}
	}
}
#include "DnCNN.h"

void DnCNN(
	hls::stream<float>& input_img,
	hls::stream<AXI_datatype_O>& output_stream,
	hls::stream<float>& weight_stream,
	hls::stream<int>& control
)
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis register both port=output_stream
#pragma HLS INTERFACE axis register both port=input_img
#pragma HLS INTERFACE axis register both port=weight_stream
#pragma HLS INTERFACE axis register both port=control
	static weight_type layer1_weights[M][K][K];
	static weight_type layer2_weights_DW[M][K][K];
	static mid_data_type layer2_bais_DW[M];
	static weight_type layer2_weights_PW[M][M];
	static mid_data_type layer2_bais_PW[M];
	static weight_type layer3_weights_DW[M][K][K];
	static mid_data_type layer3_bais_DW[M];
	static weight_type layer3_weights_PW[M][M];
	static mid_data_type layer3_bais_PW[M];
	static weight_type layer4_weights_DW[M][K][K];
	static mid_data_type layer4_bais_DW[M];
	static weight_type layer4_weights_PW[M][M];
	static mid_data_type layer4_bais_PW[M];
	static weight_type layer5_weights_DW[M][K][K];
	static mid_data_type layer5_bais_DW[M];
	static weight_type layer5_weights_PW[M][M];
	static mid_data_type layer5_bais_PW[M];
	static weight_type layer6_weights_DW[M][K][K];
	static mid_data_type layer6_bais_DW[M];
	static weight_type layer6_weights_PW[M][M];
	static mid_data_type layer6_bais_PW[M];
	static weight_type layer7_weights_DW[M][K][K];
	static mid_data_type layer7_bais_DW[M];
	static weight_type layer7_weights_PW[M][M];
	static mid_data_type layer7_bais_PW[M];
	static weight_type layer8_weights_DW[M][K][K];
	static mid_data_type layer8_bais_DW[M];
	static weight_type layer8_weights_PW[M][M];
	static mid_data_type layer8_bais_PW[M];
	static weight_type layer9_weights_DW[M][K][K];
	static mid_data_type layer9_bais_DW[M];
	static weight_type layer9_weights_PW[M][M];
	static mid_data_type layer9_bais_PW[M];
	static weight_type layer10_weights_DW[M][K][K];
	static mid_data_type layer10_bais_DW[M];
	static weight_type layer10_weights_PW[M][M];
	static mid_data_type layer10_bais_PW[M];
	static weight_type layer11_weights_DW[M][K][K];
	static mid_data_type layer11_bais_DW[M];
	static weight_type layer11_weights_PW[M][M];
	static mid_data_type layer11_bais_PW[M];
	static weight_type layer12_weights[M][K][K];
#pragma HLS RESOURCE variable=layer1_weights           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer2_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer2_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer2_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer2_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer3_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer3_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer3_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer3_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer4_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer4_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer4_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer4_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer5_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer5_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer5_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer5_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer6_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer6_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer6_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer6_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer7_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer7_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer7_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer7_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer8_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer8_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer8_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer8_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer9_weights_DW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer9_bais_DW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer9_weights_PW        core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer9_bais_PW           core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer10_weights_DW       core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer10_bais_DW          core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer10_weights_PW       core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer10_bais_PW          core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer11_weights_DW       core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer11_bais_DW          core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer11_weights_PW       core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer11_bais_PW          core=RAM_1P_LUTRAM
#pragma HLS RESOURCE variable=layer12_weights          core=RAM_1P_LUTRAM

	int row, col;

	hls::stream<data_type> layer1_in;
	hls::stream<data_type> layer2_in_DW[8];
	hls::stream<data_type> layer3_in_DW[8];
	hls::stream<data_type> layer4_in_DW[8];
	hls::stream<data_type> layer5_in_DW[8];
	hls::stream<data_type> layer6_in_DW[8];
	hls::stream<data_type> layer7_in_DW[8];
	hls::stream<data_type> layer8_in_DW[8];
	hls::stream<data_type> layer9_in_DW[8];
	hls::stream<data_type> layer10_in_DW[8];
	hls::stream<data_type> layer11_in_DW[8];
	hls::stream<data_type> layer12_in_DW[8];
#pragma HLS STREAM variable=layer1_in       depth=2
#pragma HLS STREAM variable=layer2_in_DW    depth=2
#pragma HLS STREAM variable=layer3_in_DW    depth=2
#pragma HLS STREAM variable=layer4_in_DW    depth=2
#pragma HLS STREAM variable=layer5_in_DW    depth=2
#pragma HLS STREAM variable=layer6_in_DW    depth=2
#pragma HLS STREAM variable=layer7_in_DW    depth=2
#pragma HLS STREAM variable=layer8_in_DW    depth=2
#pragma HLS STREAM variable=layer9_in_DW    depth=2
#pragma HLS STREAM variable=layer10_in_DW   depth=2
#pragma HLS STREAM variable=layer11_in_DW   depth=2
#pragma HLS STREAM variable=layer12_in_DW   depth=2


	hls::stream<data_type> layer1_out[8];
	hls::stream<data_type> layer2_out_DW[8];
	hls::stream<data_type> layer2_out_PW[8];
	hls::stream<data_type> layer3_out_DW[8];
	hls::stream<data_type> layer3_out_PW[8];
	hls::stream<data_type> layer4_out_DW[8];
	hls::stream<data_type> layer4_out_PW[8];
	hls::stream<data_type> layer5_out_DW[8];
	hls::stream<data_type> layer5_out_PW[8];
	hls::stream<data_type> layer6_out_DW[8];
	hls::stream<data_type> layer6_out_PW[8];
	hls::stream<data_type> layer7_out_DW[8];
	hls::stream<data_type> layer7_out_PW[8];
	hls::stream<data_type> layer8_out_DW[8];
	hls::stream<data_type> layer8_out_PW[8];
	hls::stream<data_type> layer9_out_DW[8];
	hls::stream<data_type> layer9_out_PW[8];
	hls::stream<data_type> layer10_out_DW[8];
	hls::stream<data_type> layer10_out_PW[8];
	hls::stream<data_type> layer11_out_DW[8];
	hls::stream<data_type> layer11_out_PW[8];
#pragma HLS STREAM variable=layer1_out          depth=2
#pragma HLS STREAM variable=layer2_out_DW       depth=2
#pragma HLS STREAM variable=layer2_out_PW       depth=2
#pragma HLS STREAM variable=layer3_out_DW       depth=2
#pragma HLS STREAM variable=layer3_out_PW       depth=2
#pragma HLS STREAM variable=layer4_out_DW       depth=2
#pragma HLS STREAM variable=layer4_out_PW       depth=2
#pragma HLS STREAM variable=layer5_out_DW       depth=2
#pragma HLS STREAM variable=layer5_out_PW       depth=2
#pragma HLS STREAM variable=layer6_out_DW       depth=2
#pragma HLS STREAM variable=layer6_out_PW       depth=2
#pragma HLS STREAM variable=layer7_out_DW       depth=2
#pragma HLS STREAM variable=layer7_out_PW       depth=2
#pragma HLS STREAM variable=layer8_out_DW       depth=2
#pragma HLS STREAM variable=layer8_out_PW       depth=2
#pragma HLS STREAM variable=layer9_out_DW       depth=2
#pragma HLS STREAM variable=layer9_out_PW       depth=2
#pragma HLS STREAM variable=layer10_out_DW      depth=2
#pragma HLS STREAM variable=layer10_out_PW      depth=2
#pragma HLS STREAM variable=layer11_out_DW      depth=2
#pragma HLS STREAM variable=layer11_out_PW      depth=2


	if (control.read() == 1) {
		// load weights
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer1_weights[ii][i][j] = weight_stream.read();
				}
			}
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer2_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer2_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer2_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer2_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer3_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer3_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer3_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer3_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer4_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer4_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer4_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer4_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer5_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer5_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer5_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer5_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer6_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer6_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer6_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer6_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer7_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer7_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer7_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer7_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer8_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer8_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer8_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer8_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer9_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer9_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer9_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer9_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer10_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer10_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer10_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer10_bais_PW[ii] = weight_stream.read();
		}

		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer11_weights_DW[ii][i][j] = weight_stream.read();
				}
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer11_bais_DW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < M; i++) {
				layer11_weights_PW[ii][i] = weight_stream.read();
			}
		}
		for (int ii = 0; ii < M; ii++) {
			layer11_bais_PW[ii] = weight_stream.read();
		}
		for (int ii = 0; ii < M; ii++) {
			for (int i = 0; i < K; i++) {
				for (int j = 0; j < K; j++) {
					layer12_weights[ii][i][j] = weight_stream.read();
				}
			}
		}
	}


	for (row = 0; row < (IMGH + L - 1); row++) {
		for (col = 0; col < (IMGW + L - 1); col++) {
			cout << row << " " << col << endl;
#pragma HLS DATAFLOW
			load_region :
			load_img<1>(row, col, input_img, layer1_in);

		    layer1_region:
			MAC_I<8, IMGH, IMGW>(layer1_in, layer1_out, layer1_weights, row, col);
			layer1_reuse_region:
			reuse<0, 0, 8, 1>(row, col, layer1_out, layer2_in_DW);


			layer2_DW_region:
			MAC_DW<8, 0, IMGH + 1, 0, IMGW + 1>(layer2_in_DW, layer2_out_DW, layer2_weights_DW, layer2_bais_DW, row, col);
			layer2_PW_region:
			MAC_PW<8, 8, 0, IMGH + 1, 0, IMGW + 1>(layer2_out_DW, layer2_out_PW, layer2_weights_PW, layer2_bais_PW, row, col);
			layer2_reuse_region:
			reuse<1, 1, 8, 2>(row, col, layer2_out_PW, layer3_in_DW);


			layer3_DW_region:
			MAC_DW<8, 1, IMGH + 2, 1, IMGW + 2>(layer3_in_DW, layer3_out_DW, layer3_weights_DW, layer3_bais_DW, row, col);
			layer3_PW_region:
			MAC_PW<8, 8, 1, IMGH + 2, 1, IMGW + 2>(layer3_out_DW, layer3_out_PW, layer3_weights_PW, layer3_bais_PW, row, col);
			layer3_reuse_region:
			reuse<2, 2, 8, 3>(row, col, layer3_out_PW, layer4_in_DW);


			layer4_DW_region:
			MAC_DW<8, 2, IMGH + 3, 2, IMGW + 3>(layer4_in_DW, layer4_out_DW, layer4_weights_DW, layer4_bais_DW, row, col);
			layer4_PW_region:
			MAC_PW<8, 8, 2, IMGH + 3, 2, IMGW + 3>(layer4_out_DW, layer4_out_PW, layer4_weights_PW, layer4_bais_PW, row, col);
			layer4_reuse_region:
			reuse<3, 3, 8, 4>(row, col, layer4_out_PW, layer5_in_DW);


			layer5_DW_region:
			MAC_DW<8, 3, IMGH + 4, 3, IMGW + 4>(layer5_in_DW, layer5_out_DW, layer5_weights_DW, layer5_bais_DW, row, col);
			layer5_PW_region:
			MAC_PW<8, 8, 3, IMGH + 4, 3, IMGW + 4>(layer5_out_DW, layer5_out_PW, layer5_weights_PW, layer5_bais_PW, row, col);
			layer5_reuse_region:
			reuse<4, 4, 8, 5>(row, col, layer5_out_PW, layer6_in_DW);


			layer6_DW_region:
			MAC_DW<8, 4, IMGH + 5, 4, IMGW + 5>(layer6_in_DW, layer6_out_DW, layer6_weights_DW, layer6_bais_DW, row, col);
			layer6_PW_region:
			MAC_PW<8, 8, 4, IMGH + 5, 4, IMGW + 5>(layer6_out_DW, layer6_out_PW, layer6_weights_PW, layer6_bais_PW, row, col);
			layer6_reuse_region:
			reuse<5, 5, 8, 6>(row, col, layer6_out_PW, layer7_in_DW);


			layer7_DW_region:
			MAC_DW<8, 5, IMGH + 6, 5, IMGW + 6>(layer7_in_DW, layer7_out_DW, layer7_weights_DW, layer7_bais_DW, row, col);
			layer7_PW_region:
			MAC_PW<8, 8, 5, IMGH + 6, 5, IMGW + 6>(layer7_out_DW, layer7_out_PW, layer7_weights_PW, layer7_bais_PW, row, col);
			layer7_reuse_region:
			reuse<6, 6, 8, 7>(row, col, layer7_out_PW, layer8_in_DW);


			layer8_DW_region:
			MAC_DW<8, 6, IMGH + 7, 6, IMGW + 7>(layer8_in_DW, layer8_out_DW, layer8_weights_DW, layer8_bais_DW, row, col);
			layer8_PW_region:
			MAC_PW<8, 8, 6, IMGH + 7, 6, IMGW + 7>(layer8_out_DW, layer8_out_PW, layer8_weights_PW, layer8_bais_PW, row, col);
			layer8_reuse_region:
			reuseLUT<7, 7, 8, 8>(row, col, layer8_out_PW, layer9_in_DW);


			layer9_DW_region:
			MAC_DW<8, 7, IMGH + 8, 7, IMGW + 8>(layer9_in_DW, layer9_out_DW, layer9_weights_DW, layer9_bais_DW, row, col);
			layer9_PW_region:
			MAC_PW<8, 8, 7, IMGH + 8, 7, IMGW + 8>(layer9_out_DW, layer9_out_PW, layer9_weights_PW, layer9_bais_PW, row, col);
			layer9_reuse_region:
			reuseLUT<8, 8, 8, 9>(row, col, layer9_out_PW, layer10_in_DW);


			layer10_DW_region:
			MAC_DW<8, 8, IMGH + 9, 8, IMGW + 9>(layer10_in_DW, layer10_out_DW, layer10_weights_DW, layer10_bais_DW, row, col);
			layer10_PW_region:
			MAC_PW<8, 8, 8, IMGH + 9, 8, IMGW + 9>(layer10_out_DW, layer10_out_PW, layer10_weights_PW, layer10_bais_PW, row, col);
			layer10_reuse_region:
			reuseLUT<9, 9, 8, 10>(row, col, layer10_out_PW, layer11_in_DW);


			layer11_DW_region:
			MAC_DW<8, 9, IMGH + 10, 9, IMGW + 10>(layer11_in_DW, layer11_out_DW, layer11_weights_DW, layer11_bais_DW, row, col);
			layer11_PW_region:
			MAC_PW<8, 8, 9, IMGH + 10, 9, IMGW + 10>(layer11_out_DW, layer11_out_PW, layer11_weights_PW, layer11_bais_PW, row, col);
			layer11_reuse_region:
			reuseLUT<10, 10, 8, 11>(row, col, layer11_out_PW, layer12_in_DW);


			layer12_region:
			MAC_O<8, 10, IMGH + 11, 10, IMGW + 11>(layer12_in_DW, output_stream, layer12_weights, row, col);
		}
	}
}

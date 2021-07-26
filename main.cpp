#include <iostream>
#include <fstream>
#include "stdio.h"
#include "DnCNN.h"
#include "types.h"
using namespace std;

int main() {

	FILE* WEIGHTFP;
	FILE* INPUTFP;
	float tmp;
	if ((WEIGHTFP = fopen("G:\\dxy\\dncnn_fixed\\DnCNN_fixed\\DnCNN_fixed\\weights_layer12.txt", "r")) == NULL) {
		printf("cannot open weight file!");
		return 1;
	}

	if ((INPUTFP = fopen("G:\\dxy\\dncnn_fixed\\DnCNN_fixed\\DnCNN_fixed\\input_img.txt", "r")) == NULL) {
		printf("cannot open input file!");
		return 1;
	}


	static float img[IMGH][IMGW];

	hls::stream<float> input_img;
	hls::stream<AXI_datatype_O> output_stream;
	hls::stream<float> weight_stream;
	hls::stream<int> control;

	control.write(1);

	// load weights
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer1_weights[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer2_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer2_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer2_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer2_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer3_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer3_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer3_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer3_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer4_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer4_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer4_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer4_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer5_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer5_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer5_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer5_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer6_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer6_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer6_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer6_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer7_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer7_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer7_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer7_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer8_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer8_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer8_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer8_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer9_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer9_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer9_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer9_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer10_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer10_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer10_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer10_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}

	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer11_weights_DW[ii][i][j] = tmp;
				weight_stream.write(tmp);
			}
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer11_bais_DW[ii] = tmp;
		weight_stream.write(tmp);
	}
	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < M; i++) {
			fscanf(WEIGHTFP, "%f", &tmp);
			//layer11_weights_PW[ii][i] = tmp;
			weight_stream.write(tmp);
		}
	}
	for (int ii = 0; ii < M; ii++) {
		fscanf(WEIGHTFP, "%f", &tmp);
		//layer11_bais_PW[ii] = tmp;
		weight_stream.write(tmp);
	}


	for (int ii = 0; ii < M; ii++) {
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {
				fscanf(WEIGHTFP, "%f", &tmp);
				//layer12_weights[ii][i][j] = tmp;
//				if ((ii == M-1)&(i == K-1)&(j == K-1)) break;
				weight_stream.write(tmp);
			}
		}
	}

	//control.write(0);
	// load img
	for (int i = 0; i < IMGH; i++) {
		for (int j = 0; j < IMGW; j++) {
			fscanf(INPUTFP, "%f", &tmp);
			img[i][j] = tmp;
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			//cout << img[i][j] << endl;
			input_img.write(img[i][j]);
		}
	}

	for (int j = 2; j < IMGW; j++) {
		for (int i = 0; i < 2; i++) {
			//cout << img[i][j] << endl;
			input_img.write(img[i][j]);
		}
	}

	for (int i = 2; i < IMGH; i++) {
		for (int j = 0; j < IMGW; j++) {
			//cout << img[i][j] << endl;
			input_img.write(img[i][j]);
		}
	}

	fclose(WEIGHTFP);
	fclose(INPUTFP);

	DnCNN(
		input_img,
		output_stream,
		weight_stream,
		control
	);

	ofstream outfile;
	outfile.open("out_layer12.txt", ios::out);
	for (int iii = 0; iii < 65536; iii++) {
		outfile << output_stream.read().data << " ";
	}
	outfile.close();


}



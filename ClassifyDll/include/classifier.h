#pragma once

#include <string>
#include <fstream>
#include <utility>
#include <vector>


#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"


#include "tensorflow/core/public/session.h"
#define HYCOMMONWINAPI_EXPORTS
#ifdef _EXPORTDLL  
#define DllExport    __declspec(dllexport)  
#else  
#define DllExport    __declspec(dllimport)  
#endif  

namespace classifier
{
	struct Word
	{
		std::string word;
		float val;
	};

#define WIDTH 64
#define HEIGHT 64
#define CLASS 3820
	class DllExport Classifier
	{
	private:
		const std::string top_k_64 = "top_k_64";
		const std::string train_flag = "train_flag";
		const std::string image_batch = "image_batch";
		const std::string keep_prob = "keep_prob";
		const std::string output = "softmax";
		const std::string topK_index_output = "topK_out:0";
		const std::string topK_val_output = "topK_out:1";
		std::string labels[CLASS];
		tensorflow::Session* session;
		tensorflow::GraphDef graphdef;
	private:
		bool readLabel(std::string path);
		tensorflow::Status LoadGraph(std::string graphPath, tensorflow::GraphDef &graphdef);
		tensorflow::Status createGraph(tensorflow::Session *session, tensorflow::GraphDef &graphdef);
		void createInputsTensor(std::vector<std::pair<std::string, tensorflow::Tensor>>& input, cv::Mat& img, int topK, bool trainFlag, float keepProb);
		tensorflow::Status predict(tensorflow::Session *session, std::vector<std::pair<std::string, tensorflow::Tensor>>& inputs, std::vector<tensorflow::Tensor>& results);
	public:
		Classifier(std::string graphPath, std::string labelPath);
		bool classify(cv::Mat &img, std::vector<Word> &words, int topK = 3);
	};
}

#include "classifier.h"

namespace classifier
{

	Classifier::Classifier(const std::string& graphPath, const std::string& labelPath)
	{
		if (!readLabel(labelPath))
		{
		}
		else
		{
			tensorflow::SessionOptions options;

			tensorflow::Status graph_status = LoadGraph(graphPath, graphdef);
			if (!graph_status.ok())
			{
				throw graph_status.ToString();
			}
			else
			{
				//options.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.3);
				//options.config.mutable_gpu_options()->set_allow_growth(true);

				tensorflow::Status status = NewSession(options, &session);
				if (!status.ok())
				{
					throw status.ToString();
				}
				else
				{
					tensorflow::Status status_create = createGraph(session, graphdef);
					if (!status_create.ok())
					{
						throw status_create.ToString();
					}

				}
			}
		}


	}


	bool Classifier::classify(cv::Mat &img, std::vector<Word> &words, int topK)
	{
		std::vector<tensorflow::Tensor> results;
		std::vector<std::pair<std::string, tensorflow::Tensor>> inputs;

		createInputsTensor(inputs, img, 3, false, 1.0);

		tensorflow::Status predict_status = predict(session, inputs, results);
		if (!predict_status.ok())
		{
			//std::cout << "predict status: " << predict_status.ToString() << std::endl;
			throw predict_status.ToString();
		}
		else
		{
			tensorflow::TTypes<float>::Flat scores_flat = results[1].flat<float>();
			tensorflow::TTypes<tensorflow::int32>::Flat indices_flat = results[2].flat<tensorflow::int32>();

			for (int i = 0; i < topK; ++i)
			{
				//std::cout << labels[indices_flat(i)] << " " << scores_flat(i) << "==" << std::endl;
				words.push_back(Word{ labels[indices_flat(i)],scores_flat(i) });
			}

		}
	}

	bool Classifier::readLabel(const std::string& path)
	{
		std::ifstream infile(path);
		std::string buffer;
		int i = 0;
		if (!infile.is_open())
			return false;
		while (getline(infile, buffer))
		{
			labels[i] = buffer;
			//std::cout << i << std::endl;
			++i;
		}
		infile.close();
		return true;
	}

	tensorflow::Status Classifier::LoadGraph(const std::string& graphPath, tensorflow::GraphDef & graphdef)
	{
		using namespace tensorflow;
		SessionOptions options;

		Status status_load = ReadBinaryProto(Env::Default(), graphPath, &graphdef);

		if (!status_load.ok())
		{
			//std::cout << "ERROR: load graph" << status_load.ToString() << "\n";
		}
		return status_load;
	}

	tensorflow::Status Classifier::createGraph(tensorflow::Session * session, tensorflow::GraphDef & graphdef)
	{
		tensorflow::Status status_create = session->Create(graphdef);
		if (!status_create.ok())
		{
			//std::cout << "ERROR: create graph" << status_create.ToString() << "\n";
		}
		return status_create;
	}

	void Classifier::createInputsTensor(std::vector<std::pair<std::string, tensorflow::Tensor>>& input, cv::Mat & img, int topK, bool trainFlag, float keepProb)
	{
		using namespace tensorflow;
		Tensor isTraining(DT_BOOL, TensorShape());
		isTraining.scalar<bool>()() = trainFlag;

		Tensor keep_prob_vaule(DT_FLOAT, TensorShape());
		keep_prob_vaule.scalar<float>()() = keepProb;

		Tensor top_k(DT_INT64, TensorShape());
		top_k.scalar<long long>()() = topK;

		resize(img, img, cv::Size(WIDTH, HEIGHT));
		Tensor img_tensor(DT_FLOAT, TensorShape({ 1,WIDTH,HEIGHT,1 }));
		auto img_tensor_map = img_tensor.tensor<float, 4>();
		for (int i = 0; i < HEIGHT; ++i)
		{
			uchar* values = img.ptr<uchar>(i);
			for (int j = 0; j < WIDTH; ++j)
			{
				img_tensor_map(0, i, j, 0) = 1.0f*values[j] / 255.0;
			}
		}

		std::vector<std::pair<string, Tensor>> inputs = {
			{ top_k_64 ,top_k },
		{ image_batch ,img_tensor },
		{ train_flag ,isTraining },
		{ keep_prob,keep_prob_vaule }
		};
		input = inputs;
	}

	tensorflow::Status Classifier::predict(tensorflow::Session * session, std::vector<std::pair<std::string, tensorflow::Tensor>>& inputs, std::vector<tensorflow::Tensor>& results)
	{
		return session->Run(inputs, { output,topK_index_output,topK_val_output }, {}, &results);
	}

}
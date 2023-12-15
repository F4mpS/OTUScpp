#include "../headers/AccuracyFinder.h"

AccuracyFinder::AccuracyFinder(std::size_t input_dim, std::size_t hidden_dim, std::size_t output_dim) :
    input_dim(input_dim), hidden_dim(hidden_dim), output_dim(output_dim), clf() {}

void AccuracyFinder::SetupClassifier(const std::filesystem::path& modelPath)
{
    auto l1 = read_mat_from_file(input_dim, hidden_dim, (modelPath / "w1.txt"));
    auto l2 = read_mat_from_file(hidden_dim, output_dim, (modelPath / "w2.txt"));

    clf = new MlpClassifier{l1.transpose(), l2.transpose()};
}

float AccuracyFinder::GetAccuracy(const std::filesystem::path& csvPath)
{

    auto features = MlpClassifier::features_t{};

    auto file = read_csv(csvPath);
    float all = file.size();
    float right = 0;

    for (auto &fileString : file)
    {
        std::size_t expected = std::stoi(fileString.front());
        fileString.erase(fileString.begin());

        read_features(fileString, features);
        auto pred = clf->predict(features);

        if (expected = pred)
            right++;
    }

    float accuracy = right / all;
    
    return accuracy;
}
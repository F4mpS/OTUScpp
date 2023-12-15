#pragma once

#include <filesystem>

#include "helpers.h"
#include "mlp_classifier.h"

using namespace mnist;

class AccuracyFinder
{
public:
    AccuracyFinder(std::size_t, std::size_t, std::size_t);
    ~AccuracyFinder() = default;

    void SetupClassifier(const std::filesystem::path&);

    float GetAccuracy(const std::filesystem::path&);
private:
    std::size_t input_dim;
    std::size_t hidden_dim;
    std::size_t output_dim;
    MlpClassifier* clf = nullptr;
};

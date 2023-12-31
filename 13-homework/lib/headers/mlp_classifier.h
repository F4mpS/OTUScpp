#pragma once

#include <Eigen/Dense>

#include "../interfaces/classifier.h"

namespace mnist
{

    class MlpClassifier : public Classifier
    {
    public:
        MlpClassifier(const Eigen::MatrixXf &, const Eigen::MatrixXf &);

        size_t num_classes() const override;

        size_t predict(const features_t &) const override;

        probas_t predict_proba(const features_t &) const override;

    private:
        Eigen::MatrixXf w1_, w2_;
    };

}
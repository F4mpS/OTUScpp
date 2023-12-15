#include "../headers/helpers.h"

namespace mnist
{

    Eigen::MatrixXf read_mat_from_file(std::size_t rows, std::size_t cols, const std::filesystem::path &matPath)
    {
        std::ifstream matFile(matPath.native());
        Eigen::MatrixXf matRes(rows, cols);

        for (std::size_t i = 0; i < rows; ++i)
        {
            for (std::size_t j = 0; j < cols; ++j)
            {
                std::string tmp;
                matFile >> tmp;
                double val = std::stod(tmp);
                matRes(i, j) = val;
            }
        }

        return matRes;
    }

    void read_features(std::vector<std::string> &pixels, Classifier::features_t &features)
    {
        features.clear();
        for (const auto &pixel : pixels)
        {
            features.push_back(std::stof(pixel));
        }
    }

    std::vector<std::vector<std::string>> read_csv(const std::filesystem::path &csvPath)
    {
        std::vector<std::vector<std::string>> result;
        std::fstream csv(csvPath);

        for (std::string line; std::getline(csv, line);)
        {
            result.push_back(utilities::Split(line, ','));
        }

        return result;
    }

}

namespace utilities
{
    std::vector<std::string> Split(const std::string &str, char d)
    {
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }
}
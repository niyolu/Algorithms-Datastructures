#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iomanip>

double smoothstep(double edge0, double edge1, double x) {
    if (x < edge0)
        return 0;

    if (x >= edge1)
        return 1;

    x = (x - edge0) / (edge1 - edge0);

    return x * x * (3 - 2 * x);
}

template<typename T, unsigned int dim>
std::vector<T> random_vector(unsigned int MIN, unsigned int MAX, long unsigned int seed = 421337) {
    std::mt19937 mersenne_engine(seed);
    std::uniform_real_distribution<T> dist(MIN, MAX);

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    std::vector<T> vec(dim);
    generate(begin(vec), end(vec), gen);
    return vec;
}

std::vector<double> random_2vector(unsigned int MIN, unsigned int MAX, long unsigned int seed = 421337) {
    return random_vector<double, 2>(MIN, MAX, seed);
}

template<typename T>
T dot_product(const std::vector<T> &v1, const std::vector<T> &v2) {
    T sum{};
    const auto n = v1.size();
    for (int i = 0; i < n; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

template<typename T>
std::vector<T> vecor_subtract(const std::vector<T> &v1, const std::vector<T> &v2) {
    const auto n = v1.size();
    std::vector<T> difference(n);
    for (int i = 0; i < n; i++) {
        difference[i] = v1[i] - v2[i];
    }
    return difference;
}

template<typename T>
std::vector<T> vector_normalize(std::vector<T> vector) {
    const auto n = vector.size();
    double sum = dot_product(vector, vector);
    double mag = std::sqrt(sum);
    if (mag == 0)
        return std::vector<T>(n, 0.0);
    for (auto &x : vector)
        x /= mag;
    return vector;
}

double interpolate(double x1, double x2, double alpha) {
    return x1 * alpha + x2 * (1 - alpha);
}

struct PerlinNoise2DGenerator {
    using real_vector_collection = std::vector<std::vector<double>>;
    using discrete_vector_collection = std::vector<std::vector<long>>;

    // should be static
    const unsigned int dim = 2;
    const unsigned int num_corners = std::pow(2, dim);
    double grid_size = 10;

    explicit PerlinNoise2DGenerator(double grid_size) : grid_size(grid_size) {};

    double generate(double x, double y) const { return generate({x, y}); }

    double generate(const std::vector<double> &point) const {
        double x = point[0], y = point[1];
        // find grid top-left coordinates
        auto grid_i = static_cast<int>(x / grid_size);
        auto grid_j = static_cast<int>(y / grid_size);
        auto grid_x = static_cast<int>(x / grid_size) * grid_size;
        auto grid_y = static_cast<int>(y / grid_size) * grid_size;
        discrete_vector_collection corner_indices = {
                {grid_i,     grid_j},
                {grid_i + 1, grid_j},
                {grid_i,     grid_j + 1},
                {grid_i + 1, grid_j + 1},
        };
        real_vector_collection corners = {
                {grid_x,             grid_y},
                {grid_x + grid_size, grid_y},
                {grid_x,             grid_y + grid_size},
                {grid_x + grid_size, grid_y + grid_size},
        };
        std::vector<double> products;
        // std::vector<std::vector<double>> grid_vectors;
        constexpr auto seed_length = sizeof(long unsigned int) / 2;

        auto weight_x = (x - grid_x) / grid_size;
        auto weight_y = (y - grid_y) / grid_size;

        for (int i = 0; i < num_corners; i++) {
            auto corner_idx = corner_indices[i];
            auto corner = corners[i];
            long unsigned int seed = (corner_idx[0] << seed_length) | (corner_idx[1] & seed_length);
            std::cout << std::endl << "seed" << seed << std::endl;
            auto random_edge_vector = random_2vector(0.0, 1.0, seed);
            auto offset_vector = vector_normalize(vecor_subtract(corner, point));
            products.emplace_back(dot_product(offset_vector, random_edge_vector));
        }

        double interpolant = smoothstep(
                smoothstep(products[0], products[1], weight_x),
                smoothstep(products[2], products[3], weight_x),
                weight_y
        );

        return interpolant;
    }

};

//int main() {
//    auto vec = random_2vector(0.0, 1.0);
//    for (auto x : vec) {
//        std::cout << x << " ";
//    }
//    return 0;
//}

//int main() {
//    double x = 3.5, y = 0.7, grid_size = 0.5;
//    auto grid_x = static_cast<int>(x / grid_size) * grid_size;
//    auto grid_y = static_cast<int>(y / grid_size) * grid_size;
//    std::cout << grid_x << ";" << grid_y << std::endl;
//    std::cout << grid_x + grid_size << ";" << grid_y << std::endl;
//    std::cout << grid_x << ";" << grid_y + grid_size << std::endl;
//    std::cout << grid_x + grid_size << ";" << grid_y + grid_size << std::endl;
//    return 0;
//}

//int main() {
//    std::vector<double> v = {1, 1, 1};
//    for (auto x : vector_normalize(v))
//        std::cout <<x<<" ";
//    return 0;

//}

void test_perlin_noise(double x_start, double x_end,
                       double y_start, double y_end,
                       double step) {
    PerlinNoise2DGenerator pn(0.3);
    std::vector<std::vector<double>> noise;
    int i = 0, j = 0;
    std::cout << std::setprecision(2);
    for (double y = y_start; y < y_end; y += step, j++) {
        for (double x = x_start; x < x_end; x += step, i++) {
            std::cout << pn.generate(x, y);
            if (x + step >= x_end)
                std::cout << ",";
        }
        if (y + step >= y_end)
            std::cout << ";";
    }
}

int main() {
    test_perlin_noise(0.0, 10.0, 0.0, 10.0, 0.4);
    return 0;
}
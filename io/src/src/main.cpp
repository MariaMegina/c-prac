#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <ostream>
#include <system_error>
#include "classes.h"
#include "generate.h"

std::vector<unsigned> read_csv(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<unsigned> res;
    unsigned works_num;
    file >> works_num;
    res.reserve(works_num);
    for (int i = 0; i < works_num; ++i) {
        unsigned len;
        file >> len;
        res.push_back(len);
    }
    return res;
}

int main() {
    int num_proc = 2;
    srand(time(NULL));
    auto works = read_csv("out.csv");
    Solution* start_sol = new Solution(num_proc, works);
    std::cout << "start score: " << start_sol->score() << std::endl;
    Mutator mutator(3);
    std::vector<std::shared_ptr<ITemperatureDecrease>> temp_decr_arr = {std::make_shared<BoltzmannTemperatureDecrease>()};
    for (const auto& temp_decr : temp_decr_arr) {
        int sum_secs = 0;
        unsigned sum_res = 0;
        int iter_num = 1;
        for (int i = 0; i < iter_num; ++i) {
            auto start = std::chrono::system_clock::now();
            auto best_sol = MainCycle(start_sol, 100, &mutator, temp_decr.get()).process();
            sum_secs += std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count();
            std::vector<std::string> sum_works;
            for (int j = 0; j < num_proc; ++j) {
                sum_works.push_back("");
            }
            for (const auto& [work, proc] : ((Solution*)best_sol)->get_timetable()) {
                sum_works[proc] = std::to_string(works[work]) + " " + sum_works[proc];
            }
            i = 0;
            for (const auto& summm : sum_works) {
                std::cout << "proc_num "<<i<<": "<<summm << std::endl;
                ++i;
            }
            sum_res += best_sol->score();
            delete best_sol;
        }
        std::cout << "average score: " << (double)sum_res / iter_num << std::endl;
        std::cout << (double)sum_secs / iter_num << " secs" << std::endl;
    }
    delete start_sol;
    return 0;
}

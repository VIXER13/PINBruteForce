#include <omp.h>
#include "PINBruteForce.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Please input MD5" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        MD5Utils::MD5Array inputMD5(std::string{argv[1]}, MD5Utils::MD5Array::COMPRESS);
        std::cout << "hash: " << inputMD5 << std::endl;

        double time = omp_get_wtime();
        auto pin = MD5Utils::PINBruteForcer<8>::force(inputMD5);
        time = omp_get_wtime() - time;

        std::cout << "PIN: ";
        for(size_t i = 0; i < pin.size(); ++i) {
            std::cout << pin[i];
        }
        std::cout << std::endl;

        std::cout << "time: " << time << std::endl;
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
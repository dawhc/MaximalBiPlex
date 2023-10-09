#include "biplex.h"
#include "bigraph.hpp"
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <vector>

#define RESULT_MAXNUM 0xFFFFFFFFFFFFFFFF

void usage() {
	std::cout << "Usage: run <dataset> <q> <k>" << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		usage();
		return 0;
	}

	BiGraph G(argv[1]);

	biplex::Result result = biplex::enumeration(
		G, 
		atoi(argv[2]), 
		atoi(argv[3]),
		argc == 4 ? RESULT_MAXNUM : atoi(argv[4])
	);

	biplex::printResult(result);

	return 0;
}

#include <iostream>
#include <vector>
#include <optional>
#include <dlib/clustering.h>
#include <dlib/rand.h>

using namespace std;
using namespace dlib;


using sample_type = matrix<double, 2, 1>;

auto parse_input(std::string input) {
	sample_type sample;
	try {
		auto iter = std::find(input.cbegin(), input.cend(), ';');
		double s1 = std::stod(std::string{ input.cbegin(),iter });
		double s2 = std::stod(std::string{ iter + 1,input.cend() });
		sample(0) = s1;
		sample(1) = s2;
		return std::optional<sample_type>{sample};
	}
	catch (...) {
		return	std::optional<sample_type>{};
	}
}

int main()
{
	typedef radial_basis_kernel<sample_type> kernel_type;

	kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);

	kkmeans<kernel_type> test(kc);

	std::vector<sample_type> samples;
	std::vector<sample_type> initial_centers;

	int num_clusters = 3;

	std::string input;
	while (true) {
		std::getline(std::cin, input);
		if (std::cin.eof()) {
			break;
		}
		auto s_opt = parse_input(input);
		if (s_opt.has_value()) {
			samples.push_back(s_opt.value());
		}
	}
	// tell the kkmeans object we made that we want to run k-means with k set to 3. 
	// (i.e. we want 3 clusters)
	test.set_number_of_centers(num_clusters);

	// You need to pick some initial centers for the k-means algorithm.  So here
	// we will use the dlib::pick_initial_centers() function which tries to find
	// n points that are far apart (basically).  
	pick_initial_centers(num_clusters, initial_centers, samples, test.get_kernel());

	// now run the k-means algorithm on our set of samples.  
	test.train(samples, initial_centers);

	// now loop over all our samples and print out their predicted class.  In this example
	// all points are correctly identified.
	for (const auto& sample : samples){
		cout << sample(0) << ";"
			 << sample(1) << ";" 
			 << test(sample) << "\n";
	}
}
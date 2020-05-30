#include <iostream>
#include <vector>

#include <dlib/clustering.h>
#include <dlib/rand.h>

using namespace std;
using namespace dlib;

using sample_type = matrix<double, 2, 1>;

sample_type gen_sample_in_radius(double radius, dlib::rand& rnd) {
	sample_type m;
	double sign = 1;
	if (rnd.get_random_double() < 0.5)
		sign = -1;
	m(0) = 2 * radius*rnd.get_random_double() - radius;
	m(1) = sign * sqrt(radius*radius - m(0)*m(0));
	return m;
}

std::vector<sample_type> generate_simple() {
	std::vector<sample_type> samples;

	sample_type m;

	dlib::rand rnd;

	// we will make 50 points from each class
	const long num = 50;

	// make some samples near the origin
	double radius = 0.5;
	for (long i = 0; i < num; ++i)
	{
		m = gen_sample_in_radius(radius,rnd); 
		samples.push_back(m);
	}

	// make some samples in a circle around the origin but far away
	radius = 10.0;
	for (long i = 0; i < num; ++i)
	{
		m = gen_sample_in_radius(radius, rnd);
		samples.push_back(m);
	}

	// make some samples in a circle around the point (25,25) 
	radius = 4.0;
	for (long i = 0; i < num; ++i)
	{
		m = gen_sample_in_radius(radius, rnd);
		// translate this point away from the origin
		m(0) += 25;
		m(1) += 25; 
		samples.push_back(m);
	}
	return samples;
}

int main()
{
	std::vector<sample_type> samples = generate_simple();
	
	for (const auto& sample : samples) {
		std::cout << sample(0) << ";" << sample(1) << "\n";
	}
}
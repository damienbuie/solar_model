#include <modelling.h>

#include <iostream>

int main(int, char**){
	

	modelling::Sunpos<double> pos;
		pos.generate();

	modelling::Spectral<double> spec;
		spec.generate(pos);

	modelling::Spatial<double> spat;
		spat.generate();
		spat.rotate(pos);

	modelling::Vector4<double> vec;
	double weight;

	for (size_t i = spat.size(); i--; ) {
		spat.get(vec,weight,i);
//		std::cout<<vec<<" "<<weight<<std::endl;
	}

	std::cout<<std::endl;
	std::cout<<pos<<std::endl;
	std::cout<<spat<<std::endl;
	std::cout<<spec<<std::endl;

	return 0;

}



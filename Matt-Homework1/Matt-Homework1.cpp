#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class car {
	friend std::ostream & operator<<(std::ostream & os, const car & c);
public:
	car(std::string_view brand) : brand(brand) {}
private:
	std::string brand;
};

std::ostream & operator<<(std::ostream & os, const car & c) {
	return os << c.brand;
}

int main() {
	std::vector<std::unique_ptr<car>> street; // initially empty
	std::vector<std::unique_ptr<car>> garage; // initially empty

											  // create a standalone car
	std::unique_ptr<car> car_ptr = std::make_unique<car>("brand_a");
	// `car_ptr` is a pointer to our car

	// create another car on the street
	street.push_back(std::make_unique<car>("brand_b"));
	// `street[0]` is a pointer to our car

	std::cout << "car_ptr points to: " << *car_ptr << '\n';
	std::cout << "street[0] points to: " << *street[0] << '\n';

	// print out the contents of `street`
	std::cout << "street contains pointers to: ";
	for (auto & street_car_ptr : street) std::cout << '[' << *street_car_ptr << ']';
	std::cout << '\n';

	// move standalone car to the garage:
	garage.push_back(std::move(car_ptr)); // transferring ownership
										  // `car_ptr` pointer does NOT own our "brand_a" car anymore
										  // now, `garage[0]` is a unique pointer to our car
										  // note this "unique ownership semantics" 
										  // - it prevents us from the lack of clarity ("who owns what") we had with raw pointers
	std::cout << "garage[0] points to: " << *garage[0] << '\n';

	// print out the contents of `garage`
	std::cout << "garage contains pointers to: ";
	for (auto & garage_car_ptr : garage) std::cout << '[' << *garage_car_ptr << ']';
	std::cout << '\n';

	// exercise: understand the following: moving the (only) "brand_a" car from `garage` to `street`
	std::cout << "moving from `garage` to `street`:\n";
	auto car_ptr_iterator = begin(garage); // obtain and hold on to an iterator to pointer `garage[0]` 
	street.push_back(std::move(*car_ptr_iterator)); // transfer ownership from pointer `garage[0]` to a (newly created) unique pointer in `street`
	garage.erase(car_ptr_iterator); // erase (now useless -- no longer owning) pointer `garage[0]`

									// print out the contents of `street`

	// print out the contents of `garage`
	std::cout << "garage contains pointers to: ";
	for (auto & garage_car_ptr : garage) std::cout << '[' << *garage_car_ptr << ']';
	std::cout << std::endl;

	//print out the contetns of `street`
	std::cout << "street contains pointers to: ";
	//for (auto & street_car_ptr : street) std::cout << '[' << *street_car_ptr << ']' << std::endl;

	// exercise: now, use `std::move` from `<algorithm>` to move all cars from `street` to `garage`
	// see: http://en.cppreference.com/w/cpp/algorithm/move#Example
	// afterward, make sure to `clear` container `street` (since the pointers will become useless)
	// see: http://en.cppreference.com/w/cpp/container/vector/clear

	//Homework
	//moving cars from street to garage
	int streetSize = street.size();
	for (size_t i = 0; i < streetSize; i++)
	{
		auto street_ptr_iterator = begin(street); // obtaining an hold on to an iterator to pointer `street[0]`
		garage.push_back(std::move(*street_ptr_iterator)); // transfer ownership from pointer
		street.erase(street_ptr_iterator);
	}
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "garage contains pointers to: ";
	for (auto & garage_car_ptr : garage) std::cout << '[' << *garage_car_ptr << ']' << std::endl;

	//print out the contetns of `street`
	std::cout << "street contains pointers to: ";
	for (auto & street_car_ptr : street) std::cout << '[' << *street_car_ptr << ']' << std::endl;

	system("pause");
	return 0;
}
#include <nlohmann/json.hpp>
#include <iostream>
void test_json(){
    using json = nlohmann::json;
    using nlohmann::literals::operator""_json;
    json ex2 = R"(
	  {
	    "pi": 3.141,
	    "happy": true
	  }
	)"_json;
    std::cout << "pi:" 
		<< ex2["pi"].template get<float>() << std::endl;
}
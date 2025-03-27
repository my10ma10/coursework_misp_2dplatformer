#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <tuple>

using namespace sf;

//std::tuple <std::string, std::vector <Vector2i> > fileExecuter(std::string filePath) {
//    std::vector <Vector2i> res;
//    std::string object_name;
//    unsigned int x_coord, y_coord;
//    std::ifstream file(filePath);
//    if (file.is_open()) {
//        std::getline(file, object_name);
//        std::cout << object_name << std::endl;
//        while (file >> x_coord >> y_coord) {
//            res.push_back(Vector2i(x_coord, y_coord));
//        }
//        file.close();
//    }
//    else {
//        std::cout << "File Executer doesn't open a file" << std::endl;
//    }
//    return std::make_tuple(object_name, res);
//}
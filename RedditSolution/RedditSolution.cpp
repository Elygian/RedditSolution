#include <string>
#include <sstream>
#include <vector>

//Random comment
struct Person {
	std::string name, surname, telephone, email;
};

std::ostream& operator<<(std::ostream &out, const Person &p) {
	out << p.name << ' ' << p.surname << ": " << p.telephone << " " << p.email;
	return out;
}

int main() {
	std::stringstream ss{ "<person S Smith N Tom >\n<person S Smith N Dick T +49.921.1434 >\n<person S Smith N Harry E hsmith@gmail.com >\n<person S Smith N Mary T +39.921.1434 E msmith@gmail.com >\n<person S John N John T +33.921.1434 E jjohn@gmail.com >" };
	std::string tmp;
	std::vector<Person> people;

	while (ss >> tmp) {
		if (tmp == "<person") {
			ss >> tmp;
			Person p;
			while (tmp != ">") {
				if (tmp == "S") {
					ss >> p.surname;
				}
				else if (tmp == "N") {
					ss >> p.name;
				}
				else if (tmp == "T") {
					ss >> p.telephone;
				}
				else if (tmp == "E") {
					ss >> p.email;
				}
				else {
					std::cerr << "Unknown token: " << tmp << "\n";
				}
				ss >> tmp;
			}
			people.push_back(p);
		}
		else {
			std::cerr << "Bad starting sequence: " << tmp << std::endl;
		}
	}

	for (auto &p : people) {
		std::cout << p << "\n";
	}
}
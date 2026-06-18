#include <iostream>
#include <fstream>
#include <string>

static std::ofstream out("output.txt");

void removeLastUTF8Char(std::string &str)
{
    if (str.empty())
        return;
    size_t pos = str.size() - 1;

    while (pos > 0 && (str[pos] & 0xC0) == 0x80)
    {
        --pos;
    }
    str.erase(pos);
}

void func(int length, std::string &name, const std::string &file)
{
    if (length > 0)
    {
        std::ifstream in(file);
        std::string line;
        while (std::getline(in, line))
        {
            name += line;
            func(length - 1, name, file);
            removeLastUTF8Char(name);
        }
    }

    out << name << "\n";
    std::cout << name << std::endl;
}

int main()
{
    int length;
    std::cout << "你认为小葱的名字最多为多少位呢:" << std::endl;
    std::cin >> length;

    std::string name;

    func(length, name, "text.txt");
}
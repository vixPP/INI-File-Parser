#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

class IniParser
{
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;

public:
    IniParser(const std::string& path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::runtime_error("Не удалось открыть файл INI: " + path);
        }

        std::string line;
        std::string section;
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }
            else if (line[0] == '[')
            {
                section = line.substr(1, line.size() - 2);
            }
            else
            {
                size_t pos = line.find('=');
                if (pos == std::string::npos)
                {
                    throw std::runtime_error("Некорректный формат INI-файла: " + line);
                }

                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                data[section][key] = value;
            }
        }

        file.close();
    }

    std::string get_value(const std::string& section, const std::string& key)
    {
        if (data.find(section) == data.end())
        {
            throw std::runtime_error("Раздел не найден: " + section);
        }

        if (data[section].find(key) == data[section].end())
        {
            throw std::runtime_error("Ключ не найден: " + key);
        }

        return data[section][key];
    }

    std::vector<std::string> get_sections()
    {
        std::vector<std::string> sections;
        for (const auto& section : data)
        {
            sections.push_back(section.first);
        }

        return sections;
    }

    std::unordered_map<std::string, std::string> get_all_values(const std::string& section)
    {
        if (data.find(section) == data.end())
        {
            throw std::runtime_error("Раздел не найден: " + section);
        }

        return data[section];
    }
};

int main()
{
    try
    {
        IniParser parser("config.ini");
        std::string name = parser.get_value("general", "name");
        std::cout << "Имя: " << name << std::endl;

        std::string mail = parser.get_value("general","mail");
        std::cout << "Электронная почта: " << mail << std::endl << std::endl; 


        std::string dolars = parser.get_value("Wallet", "dolars");
        std::cout << "Доларов: " << dolars << std::endl;

        std::string rubles = parser.get_value("Wallet", "rubles");
        std::cout << "Рублей: " << rubles << std::endl << std::endl;


        std::string city = parser.get_value("Adress", "city");
        std::cout << "Город: " << city << std::endl;

        std::string street = parser.get_value("Adress", "street");
        std::cout << "Улица: " << street << std::endl;

        std::string Nhouse = parser.get_value("Adress", "Nhouse");
        std::cout << "Номер дома: " << Nhouse << std::endl << std::endl;

    }
    catch (const std::exception& ex)
    {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
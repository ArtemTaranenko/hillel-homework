#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <memory>
#include <functional>
#include <regex>
#include <cassert>
#include <string_view>

class INumberReader
{
	public:
	virtual std::vector<int> read (const std::string& filename) = 0;
	virtual ~INumberReader() = default;
};

class NumberReader: public INumberReader
{
	public:
	std::vector<int> read (const std::string& filename) override
	{
		std::vector<int> numbers;
		std::ifstream file (filename);
		if (!file.is_open()){
			std::cout << "Cannot open file " << std::endl;
			return numbers;
			}
		int number;
		while (file >> number){
			numbers.push_back(number);
			}
		return numbers;
	}
	~NumberReader() = default;
};

class INumberFilter
{
	public:
	virtual bool keep (int a) = 0;
	virtual ~INumberFilter () {}
};

class EvenFilter: public INumberFilter
{
	public:
	bool keep (int a) override
	{
		return a % 2 == 0;
	}
};

class OddFilter: public INumberFilter
{
	public:
	bool keep (int a) override
	{
		return a % 2 != 0;
	}
};

class GreaterFilter: public INumberFilter
{
	int number = 0;
	public:
	GreaterFilter(int Number): number(Number) {}
	bool keep (int a) override
	{
		return a > number;
	}
};

class INumberObserver
{
	public:
	virtual void on_number(int a) = 0;
	virtual void on_finished() = 0;
};

class PrintObserver: public INumberObserver
{
	public:
	void on_number(int a) override
	{
		std::cout << a << std::endl;
	}
	
	void on_finished() override
	{
		std::cout << "====== FINISHED ======" << std::endl;
	}
};

class CountObserver: public INumberObserver
{
	uint32_t counter = 0;
	
	public:
	void on_number (int a) override
	{
		counter++;
	}
	
	void on_finished() override
	{
		std::cout << "Numbers Count = " << counter << std::endl;
	}
};

struct IRegistry
{
	virtual std::unique_ptr<INumberFilter> create (const std::string& input) = 0;
};

class FilterFactory: public IRegistry
{
	using Factory = std::function<std::unique_ptr<INumberFilter> (const std::string& input)>;
	std::map<std::string, Factory> registry;
	
	FilterFactory() = default;
	FilterFactory (const FilterFactory& f) = delete;
	FilterFactory& operator = (const FilterFactory& f) = delete;
	
	public:
	static FilterFactory& instance()
	{
		static FilterFactory reg;
		return reg;
	}
	
	void register_factory (const std::string& filter_type, Factory f)
	{
		this->registry[filter_type] = f;
	}
	std::unique_ptr<INumberFilter> create( const std::string& input)
    {
        for (const auto& [type, factory] : registry) {
            if (input.starts_with(type)) {
                return factory(input);
            }
        }
        
        std::cerr << "No matching filter type found for: " << input << std::endl;
        return nullptr;
    }
};

class NumberProcessor
{
	INumberReader& reader;
	INumberFilter& filter;
	std::vector<std::reference_wrapper<INumberObserver>> observer;
	public:
	NumberProcessor(INumberReader& reader, INumberFilter& filter, std::vector<std::reference_wrapper<INumberObserver>> observer): reader(reader), filter(filter), observer(observer){}
	void run(const std::string& filename)
	{
		std::vector<int> numbers = reader.read(filename);
		for (auto obs : observer){
			for (auto elem : numbers){
				if (filter.keep(elem)){
					obs.get().on_number(elem);
				}			
			}
			obs.get().on_finished();
		}		
	}
};

int main(int argc, char** argv)
{
	if (argc != 3){
		std::cerr << "Right usage: <program> <filter (EVEN, ODD, GT<n>)> <filename>" << std::endl;
		return -1;
		}
	if ( !std::regex_match(argv[1], std::regex ("^even$", std::regex_constants::icase)) 
	&& !std::regex_match(argv[1], std::regex ("^odd$", std::regex_constants::icase))
	&&  !std::regex_match(argv[1],std::regex ("^gt\\d+$", std::regex_constants::icase))){
		std::cerr << "Invalid input type of filter" << std::endl;
		return -1;
	}
	std::string f = argv[1];
	std::transform(f.begin(), f.end(), f.begin(), [](unsigned char c){ return std::toupper(c); });
	FilterFactory& registry = FilterFactory::instance();
	registry.register_factory("EVEN", [](const std::string fil){
		return std::make_unique<EvenFilter>();
		});
	registry.register_factory("ODD", [](const std::string fil){
		return std::make_unique<OddFilter>();
		});
	registry.register_factory("GT", [](const std::string fil){
		int n = std::stoi(fil.substr(2));
		return std::make_unique<GreaterFilter>(n);
		});
	std::unique_ptr<INumberFilter> filter = registry.create(f);
	CountObserver count;
	PrintObserver print;
	std::vector<std::reference_wrapper<INumberObserver>> observers = {count,print};
	NumberReader reader;
	NumberProcessor proc(reader, *filter, observers);
	proc.run(argv[2]);
	return 0;
}

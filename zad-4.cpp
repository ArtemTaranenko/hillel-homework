#include <iostream>
#include <fstream>
#include <memory> 
#include <cctype>
#include <algorithm>

using namespace std;

struct LogSink {
  virtual void write(const std::string& msg) = 0;
  virtual ~LogSink() = default;
};

struct ConsoleSink: LogSink
{
	virtual void write(const std::string& msg) override
	{
		cout << msg << endl;
	}
};

struct FileSink: LogSink
{
	ofstream file;
	FileSink(): file("app.log", ios::app){
		if (!(file.is_open())){
			cerr << "Error with opening file" << endl;
			}
		}
	virtual void write(const std::string& msg) override
	{
		file << msg << endl;
	}
};

struct NoneSink: LogSink
{
	virtual void write(const std::string& msg) override {}
};

enum class SinkType { CONSOLE, FILE, NONE };

class Logger {
public:
  static Logger& instance()
  {
	  static Logger instance;
	  return instance;
  }
  void set_sink(SinkType type)
  {
	  switch (type){
		  case SinkType::CONSOLE:
			sink_ = make_unique<ConsoleSink>();
			break;
		  case SinkType::FILE:
			sink_ = make_unique<FileSink>();
			break;
		  case SinkType::NONE:
			sink_ = make_unique<NoneSink>();
			break;
		}
		  
  }
  void log(const std::string& msg)
  {
	  sink_->write(msg);
  }
private:
  unique_ptr<LogSink> sink_;
  Logger() = default;
  Logger (const Logger& other) = delete;
  Logger& operator = (const Logger& other) = delete;
};

string to_lower(const string& input)
{
	string output = input;
	transform(output.begin(), output.end(), output.begin(), [] (unsigned char c) { return tolower(c); });
	return output;
}

int main(int argc, char** argv)
{
	if (argc >2){
		cout << "Usage: <program name>, <type of sink: console, file or none>" << endl;
		return 1;
		}
	SinkType type;
	if (argc <2){
		cout << "No type of sink was provided, console sink will be used as default " << endl;
		type = SinkType::CONSOLE;
		}
	else{
	string sink = to_lower(argv[1]);
	if (sink == "console"){
			type = SinkType::CONSOLE;
		}
	else if (sink =="file"){
			type = SinkType::FILE;
		}
	else if (sink =="none"){
			type = SinkType::NONE;
		}
	else {
			cerr << "Wrong type of sink" << endl;
			return 1;
		}
	}
	Logger::instance().set_sink(type);
	Logger::instance().log("Test message");
	Logger::instance().log("Test message");
	Logger::instance().log("Test message");
	Logger::instance().log("Test message");
	return 0;
}

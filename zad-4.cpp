#include <iostream>
#include <fstream>
#include <memory> 

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
	string filename = "app.log";
	virtual void write(const std::string& msg) override
	{
		ofstream file(filename, ios::app);
		if (file.is_open()){
		file << msg << endl;
		}
		else {
			cerr << "Error with opening file" << endl;
		}
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


int main(int argc, char** argv)
{
	if (argc !=2){
		cout << "Usage: <program name>, <type of sink: console, file or none>" << endl;
		return 1;
		}
	string sink = argv[1];
	SinkType type;
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
	if (sink == "file") {
		ofstream clear("app.log", ios::trunc); 
		clear.close();
	}

	Logger::instance().set_sink(type);
	Logger::instance().log("Test message");
	Logger::instance().log("Test message");
	Logger::instance().log("Test message");
	return 0;
}

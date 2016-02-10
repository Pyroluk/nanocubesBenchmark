#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

#include "stopwatch.hh"
#include "tclap/CmdLine.h"
#include "tiny-process-library/process.hpp"

struct Options {

	Options(std::vector<std::string>& args);

	TCLAP::CmdLine cmd_line{ "Nanocube Benchmark", ' ', "1.0" };

	// -s or --schema
	/*TCLAP::ValueArg<std::string> schema{
		"s",              // flag
		"schema",         // name
		"Nanocube schema file (if not coming from stdin)", // description
		false,            // required
		"",               // value
		"schema-filename" // type description
	};*/

	// -d or --data
	TCLAP::ValueArg<std::string> data{
		"d",              // flag
		"data",         // name
		"Initial data from a file", // description
		true,            // required
		"",               // value
		"data" // type description
	};

	/* -o or --save ... just create a nanocube file from input data. do not start server.
	TCLAP::ValueArg<std::string> save{
		"o",              // flag
		"save",         // name
		"Store nanocube into a file", // description
		false,            // required
		"",               // value
		"filename" // type description
	};

	TCLAP::ValueArg<std::string> load{
		"l",                       // flag
		"load",                    // name
		"Load from nanocube file", // description
		false,                     // required
		"",                        // value
		"filename"                 // type description
	};*/

	TCLAP::ValueArg<int> query_port{
		"q",                     // flag
		"query_port",            // name
		"Port for querying",     // description
		false,                   // required
		29512,                       // value
		"query-port"             // type description
	};

	/*TCLAP::ValueArg<int> insert_port{
		"i",                     // flag
		"insert_port",           // name
		"Port for inserting records via tcp",     // description
		false,                                    // required
		0,                                        // value
		"insert-port"                             // type description
	};*/

	TCLAP::ValueArg<int> no_mongoose_threads{
		"t",              // flag
		"threads",        // name
		"Number of threads for querying (mongoose; default=100)",     // description
		false,                                 // required
		100,                                   // value
		"threads"                         // type description
	};

	// should be std::size_t
	TCLAP::ValueArg<int> max_points{
		"m",              // flag
		"max_points",        // name
		"Insert only max-points",     // description
		false,                                 // required
		0,                                   // value
		"max-points"                         // type description
	};

	// should be std::size_t
	TCLAP::ValueArg<int> report_frequency{
		"f",              // flag
		"report_frequency",        // name
		"Report import status every x seconds",     // description
		false,                                 // required
		5,                                   // value
		"report-frequency in seconds"                         // type description
	};

	// should be std::size_t
	TCLAP::ValueArg<int> batch_size{
		"b",              // flag
		"batch_size",        // name
		"",     // description
		false,                                 // required
		1000,                                   // value
		"batch-size"                         // type description
	};

	/* should be std::size_t
	TCLAP::ValueArg<int> sleep_for_ns{
		"y",              // flag
		"sleep",        // name
		"",     // description
		false,                                 // required
		100,                                   // value
		"sleep"                         // type description
	};*/

	TCLAP::ValueArg<std::string> nanocube_parts{
		"p",              // flag
		"nanocube_parts",        // name
		"Number of nanocubes that are going to be created in parallel or a list of splitpoints that describe the distribution of points to a specific nanocube part",     // description
		true,                                 // required
		"1",                                   // value
		"number of nanocubes/threads e.g. 4 or spilt points in quadtree address format e.g. 2120000130332122230113231"                         // type description
	};

	TCLAP::ValueArg<int> training_size{
		"x",              // flag
		"training-size",         // name
		"training size", // description
		false,            // required
		10000,               // value
		"number" // type description
	};

	/*TCLAP::ValueArg<std::string> alias{
		"a",                      // flag
		"alias",              // name
		"Try registering this server into the registries on NANOCUBE_REGISTRY env. variable",  // description
		false,                // required
		"",                   // value
		"name" // type description
	};*/

	TCLAP::ValueArg<std::string> compression{
		"c",                      // flag
		"compression",              // name
		"Set or disables the compression algorithm for storing",  // description
		false,                // required
		"gzip",                   // value
		"gzip, bzip2 or none" // type description
	};

	TCLAP::ValueArg<std::string> nanocubeFilePath{
		"n",                      // flag
		"nanocubeFilePath",              // name
		"Filepath of the nanocube executable",  // description
		false,                // required
		"allocator.exe",                   // value
		"Filepath" // type description
	};

	TCLAP::ValueArg<std::string> queriesFilePath{
		"u",                      // flag
		"queriesFilePath",              // name
		"File path of the file holding the queries to be executed",  // description
		true,                // required
		"",                   // value
		"File path" // type description
	};

#ifdef _WIN64
	TCLAP::ValueArg<std::string> temp_path{
		"w",                      // flag
		"temp_path",              // name
		"Path to the folder to hold the temporary memory files",  // description
		false,                // required
		"",                   // value
		"dictionary path" // type description
	};
	TCLAP::ValueArg<std::uint64_t> max_nanocube_size{
		"g",                      // flag
		"max_nanocube_size",              // name
		"Defines the sizes of the temporary memory files, and therefore the maximum nanocube size in GB",  // description
		false,                // required
		32,                   // value
		"size in GB" // type description
	};
#endif // _WIN64
};

Options::Options(std::vector<std::string>& args)
{
	//cmd_line.add(schema); // add command option
	cmd_line.add(data);
	//cmd_line.add(load);
	cmd_line.add(query_port);
	//cmd_line.add(insert_port);
	cmd_line.add(no_mongoose_threads);
	cmd_line.add(max_points);
	//cmd_line.add(save); // add command option
	cmd_line.add(report_frequency);
	cmd_line.add(batch_size);
	//cmd_line.add(sleep_for_ns);
	cmd_line.add(nanocube_parts);
	cmd_line.add(training_size);
	//cmd_line.add(alias);
	cmd_line.add(compression);
	cmd_line.add(nanocubeFilePath);
	cmd_line.add(queriesFilePath);
#ifdef _WIN64
	cmd_line.add(temp_path);
	cmd_line.add(max_nanocube_size);
#endif
	cmd_line.parse(args);
}

bool startsWith(std::string s, std::string prefix)
{
	return s.compare(0, prefix.size(), prefix) == 0;
}

inline bool endsWith(std::string const & value, std::string const & ending)
{
	if (ending.size() > value.size())
		return false;

	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

#ifdef _WIN64
#pragma warning(disable : 4996)
#endif
std::string urlDecode(std::string str) {
	std::string ret;
	char ch;
	int i, ii, len = str.length();

	for (i = 0; i < len; i++) {
		if (str[i] != '%') {
			if (str[i] == '+')
				ret += ' ';
			else
				ret += str[i];
		}
		else {
			sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
			ch = static_cast<char>(ii);
			ret += ch;
			i = i + 2;
		}
	}
	return ret;
}

std::vector<std::string> getQueries(std::string filePath)
{
	std::ifstream fileStream(filePath);
	std::vector<std::string> queries;

	std::string line;
	while (std::getline(fileStream, line))
		if (endsWith(filePath, ".harp") || endsWith(filePath, ".har"))//firebug network export files,  net.logLimit = 0 -> no limit
		{
			auto tmp = trim(line);
			if (startsWith(tmp, "\"url\":") && !endsWith(tmp, ".png\","))
			{
				tmp = tmp.substr(tmp.find_last_of('/') + 1);//"url": "http://lukas-pc.fritz.box:29512/count.r(%22time%22,mt_interval_sequence(0,65,8192))",
				tmp = urlDecode(tmp.substr(0, tmp.length() - 2));//count.r(%22time%22,mt_interval_sequence(0,65,8192))",
				queries.push_back(tmp);//count.r(%22time%22,mt_interval_sequence(0,65,8192))
			}
		}
		else
			queries.push_back(line); //count.r(% 22time % 22, mt_interval_sequence(0, 65, 8192))

	return queries;
}

void report(std::string s, std::ofstream& fileStream)
{
	std::cout << s;
	fileStream << s;
}

using boost::asio::ip::tcp;
bool runQuereys(Options& options, std::vector<std::string> queries, std::ofstream& fileStream)
{
	try
	{
		auto querySucceeded = 0;

		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query resolverquery("localhost", std::to_string(options.query_port.getValue()));
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(resolverquery);

		// Try each endpoint until we successfully establish a connection.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		for (auto& query : queries)
		{
			//socket.set_option(tcp::no_delay(true));//disable Nagle algorithm
			boost::asio::streambuf request;
			std::ostream request_stream(&request);
			request_stream << "GET /" << query << " HTTP/1.1\r\n";
			request_stream << "Host: " << "localhost:" << options.query_port.getValue() << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "\r\n\r\n";

			// Send the request.
			boost::asio::write(socket, request);

			// Read the response status line. The response streambuf will automatically
			// grow to accommodate the entire line. The growth may be limited by passing
			// a maximum size to the streambuf constructor.
			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");

			// Check that response is OK.
			std::istream response_stream(&response);
			std::string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			std::string status_message;
			std::getline(response_stream, status_message);
			/*if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
				report("(HTTP) Invalid response on query: " + query + "\n", fileStream);
				querysFailed++;
			}*/
			if (status_code != 200)
				report("(HTTP) Response returned with status code " + std::to_string(status_code) + " on query: " + query + "\n", fileStream);
			else
				querySucceeded++;

			// Read the response headers, which are terminated by a blank line.
			/*boost::asio::read_until(socket, response, "\r\n\r\n");

			/* Process the response headers.
			std::string header;
			std::size_t contentLength = 0;
			while (std::getline(response_stream, header) && header != "\r")
				if (startsWith(header, "Content-Length: "))//"Content-Length: 75\r"
					contentLength = std::stoi(header.substr(16));

			//optional TODO: Check if response corresponds to the on inside the harp/har file

			/* Write whatever content we already have to output.
			if (response.size() > 0)
				std::cout << &response;*/

			/* Read until EOF, writing data to output as we go.
			boost::system::error_code error;
			while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
				;//std::cout << &response;
			if (error != boost::asio::error::eof)
				throw boost::system::system_error(error);*/
		}

		report(std::to_string(querySucceeded) + "/" + std::to_string(queries.size()) + " queries succeeded\n", fileStream);

		return true;
	}
	catch (std::exception& e)
	{
		report("Exception: " + std::string(e.what()) + "\n", fileStream);
		return false;
	}
}

int main(int argc, char *args[])
{
	std::vector<std::string> params(args, args + argc);
	Options options(params);

	std::vector<std::string> queries = getQueries(options.queriesFilePath.getValue());

	auto numNanocubes = 1;

	if (startsWith(options.nanocube_parts.getValue(), "qtpart("))
	{
		std::string split_points = options.nanocube_parts.getValue().substr(7, options.nanocube_parts.getValue().length() - 8);
		std::vector<std::string> splitPoints = split(options.nanocube_parts.getValue(), ',');
		numNanocubes = splitPoints.size() + 1;
		if (numNanocubes < 1)
		{
			std::cerr << "[Error] parsing of split points failed" << std::endl;
			return -1;
		}
	}
	else if (startsWith(options.nanocube_parts.getValue(), "auto"))
	{
		if (options.nanocube_parts.getValue() == "auto")
			numNanocubes = std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 1;
		else
			numNanocubes = std::stoi(options.nanocube_parts.getValue().substr(4));
	}
	else
		numNanocubes = std::stoi(options.nanocube_parts.getValue());

	//possible tests
	//for now:
	//- always build cube with dmp file, mesure time needed
	//- query cube with wide range of queryes TODO: figure out how many, and which

	//-p 8, means tests cubes starting with 1 part up to 8 parts, no clever splitt
	//-p auto8, means tests cubes starting with 1 part up to 8 parts, with auto splitt function

	//logfile
	std::ofstream logFileStream("testlog.txt");

	bool useAutoPartFunc = startsWith(options.nanocube_parts.getValue(), "auto");

	//loop through 1 - x nanocube settings and compaire build and query speed
	for (auto i = 1; i <= numNanocubes; i++)
	{
		//build commandline
		std::string arguments = " -d \"" + options.data.getValue() + "\"";
		arguments += " -q " + std::to_string(options.query_port.getValue());
		arguments += " -t " + std::to_string(options.no_mongoose_threads.getValue());
		if (options.max_points.isSet())
			arguments += " -m " + std::to_string(options.max_points.getValue());
		arguments += " -f " + std::to_string(options.report_frequency.getValue());
		arguments += " -b " + std::to_string(options.batch_size.getValue());
		arguments += " -x " + std::to_string(options.training_size.getValue());
		arguments += " -c " + options.compression.getValue();
		if (options.temp_path.isSet())
			arguments += " -w " + options.temp_path.getValue();
		arguments += " -g " + std::to_string(options.max_nanocube_size.getValue());
		arguments += " -p " + (useAutoPartFunc ? "auto" + std::to_string(i) : std::to_string(i));

		std::string commandLine = "\"" + options.nanocubeFilePath.getValue() + "\"" + arguments + "\n\n";

		report(commandLine, logFileStream);

		//start timer
		stopwatch::Stopwatch sw;
		sw.start();

		bool finishedInsert = false;
		Process process1(commandLine, "", [&logFileStream, &finishedInsert, i](const char *bytes, size_t n) {

			std::string s = std::string(bytes, n);

			finishedInsert = s.find("(stdin:done)") != std::string::npos;

			report(s, logFileStream);
		});

		//TODO: Set Priority on Linux and Mac too
#ifdef _WIN32
		SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); //REALTIME_PRIORITY_CLASS
		SetPriorityClass(OpenProcess(PROCESS_ALL_ACCESS, TRUE, process1.get_id()), HIGH_PRIORITY_CLASS); //REALTIME_PRIORITY_CLASS
#endif

		while (!finishedInsert)
			std::this_thread::sleep_for(std::chrono::seconds(1));

		report("\ntestrun build #" + std::to_string(i) + "\n time: " + std::to_string(sw.time()) + "ms\n\n", logFileStream);

		sw.stop();

		report("Start querying...\n", logFileStream);
		//start timer
		stopwatch::Stopwatch sw2;
		sw2.start();

		//start querey benchmark
		if (!runQuereys(options, queries, logFileStream))
			report("queries failed!\n", logFileStream);
		else
			report("finished after " + std::to_string(sw2.time()) + " ms\n", logFileStream);

		sw2.stop();

		process1.kill(true);
	}

	logFileStream.close();

	return 0;
}
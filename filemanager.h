#ifndef H_FILEMANAGER
#define H_FILEMANAGER

#include <fstream>
#include <string>

struct filemanager
{
	ifstream infile;
	ofstream logger;
	ofstream output_file;
	std::string data;
	std::vector<string> datafile;
	bool opened;
	int lines_processed;

	filemanager()
	{
		lines_processed = 0;
		opened = false;
	};

	bool create(std::string filename)
	{
		output_file.open( filename.c_str(),ios::trunc );
		//output_file.seekp(0, ios::end);
		return true;
	};

	bool write_this(std::string data)
	{
		if( output_file.is_open() )
		{
			output_file << data.c_str() << endl;
			return true;
		}
		return false;
	};

	void close()
	{
		if(output_file.is_open())
		{
			output_file.clear();
			output_file.close();
		}
	};

	std::vector<string> open(std::string filename)
	{
		lines_processed = 0;
		datafile.clear();
		infile.open(filename.c_str());
		infile.seekg(0,ifstream::end);
		long size = infile.tellg();
		infile.seekg(0);
		while(!infile.eof())
		{
			getline(infile,data);
			datafile.push_back(data);
			lines_processed++;
		}
		infile.clear();
		infile.close();
		return datafile;
	};

	void open_log()
	{
		if(!logger.is_open())
		{
			logger.open("error.log");
			opened = true;
		}
		else
		{
			opened = false;
		}
	};

	void write_log(std::string error)
	{
		if(opened == true)
		{
			if(logger.is_open())
			{
				logger << error.c_str() << endl;
			}
		}
	};

	void close_log()
	{
		if(logger.is_open())
		{
			logger.clear();
			logger.close();
			opened = false;
		}
	};

	~filemanager()
	{
		if(output_file.is_open())
		{
			output_file.clear();
			output_file.close();
		}
		if(logger.is_open())
		{
			logger.clear();
			logger.close();
		}
		if(infile.is_open())
		{
			infile.clear();
			infile.close();
		}
	};
};

#endif
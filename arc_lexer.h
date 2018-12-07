#ifndef ARC_LEXER
#define ARC_LEXER
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <iterator>

namespace Lexer
{
	enum Token {file_path, archivate, dearchivate, exit, nothing, eos, def,
		rle, lzw, lz77, lz78
	};

	class Token_hash
	{
	    public:
	    std::size_t operator()(Token t) { return static_cast<std::size_t>(t); }
	};

	class Lexer_analysater
	{
	public:
		Lexer_analysater(std::istream *inputptr = &std::cin);
		Token get_token();
		Token check_next();
		void miss();
		std::string get_value();
		~Lexer_analysater();
	private:
		void init_tokens();
		bool first_call();

		std::istream *_inputptr;
		std::string _value;
		std::unordered_map<std::string, std::size_t> _tokens;
		std::istringstream *_iss_ptr;
		std::istream_iterator<std::string> *_str_it_ptr;
		std::istream_iterator<std::string> _eos;
	};

}

#endif

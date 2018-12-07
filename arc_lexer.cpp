#include "arc_lexer.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <new>

namespace Lexer
{

	Lexer_analysater::Lexer_analysater(std::istream *inputptr)
	{
		_inputptr = inputptr;
		_str_it_ptr = new std::istream_iterator<std::string>();
		_iss_ptr = new std::istringstream();

		init_tokens();
	}

	Token Lexer_analysater::get_token()
	{
        std::string str;
        char c;

        std::cin.get(c);

        if(c == '\n')
        {
            std::cin.putback(c);
            return Token::eos;
        }

        std::cin.putback(c);
        std::cin >> str;

		if (_tokens.find(_value) != _tokens.end())
			return static_cast<Token>(_tokens[_value]);

		return Token::file_path;
	}

	Token Lexer_analysater::check_next()
	{
		_value = **_str_it_ptr;

		if (_tokens.find(_value) != _tokens.end())
			return static_cast<Token>(_tokens[_value]);

		return Token::file_path;
	}

	void Lexer_analysater::miss()
	{
		if (*_str_it_ptr == _eos)
		{
			std::string str;

			getline(*_inputptr, str);

			_iss_ptr = new (_iss_ptr) std::istringstream(str);
			_str_it_ptr = new (_str_it_ptr) std::istream_iterator<std::string>(*_iss_ptr);
		}

		_value = **_str_it_ptr;
		(*_str_it_ptr)++;
	}

	std::string Lexer_analysater::get_value() { return _value; }

	Lexer_analysater::~Lexer_analysater()
	{
		delete _str_it_ptr;
		delete _iss_ptr;
	}

	void Lexer_analysater::init_tokens()
	{
		_tokens["archivate"] = static_cast<std::size_t>(Token::archivate);
		_tokens["dearchivate"] = static_cast<std::size_t>(Token::dearchivate);
		_tokens["exit"] = static_cast<std::size_t>(Token::exit);
		_tokens[""] = static_cast<std::size_t>(Token::nothing);
		_tokens["-def"] = static_cast<std::size_t>(Token::def);
		_tokens["-rle"] = static_cast<std::size_t>(Token::rle);
		_tokens["-lzw"] = static_cast<std::size_t>(Token::lzw);
		_tokens["-lz77"] = static_cast<std::size_t>(Token::lz77);
		_tokens["-lz78"] = static_cast<std::size_t>(Token::lz78);
	}

	bool Lexer_analysater::first_call() { return _value == ""; }

}

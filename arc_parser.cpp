#include "arc_parser.h"

namespace Parser
{

	//Syntax analysater's function definitions

	Command_Objects::Command_Objects(Lexer_analysater *laptr)
		: arc(laptr), dearc(laptr), nothing(laptr), exit(laptr)
	{}

	Syntax_analysater::Syntax_analysater(Lexer_analysater *laptr)
		: c_objs(laptr)
	{
		_laptr = laptr;

		_commands[Lexer::Token::archivate] = &c_objs.arc;
		_commands[Lexer::Token::dearchivate] = &c_objs.dearc;
		_commands[Lexer::Token::exit] = &c_objs.exit;
		_commands[Lexer::Token::nothing] = &c_objs.nothing;
	}

	void Syntax_analysater::execute()
	{
		Lexer::Token token = _laptr->get_token();

		if (_commands.find(token) == _commands.end())
			throw IncorrectCommand(_laptr->get_value());

		_commands[token]->execute();
	}

	// Command functions definitions

	Command::Command(Lexer_analysater *laptr)
	{
		_laptr = laptr;
	}

	Command::~Command() {}

	// Arc_Objects function definitions

	Arc_Objects::Arc_Objects(Lexer_analysater *laptr)
		: def(laptr), rle(laptr), lzw(laptr), lz77(laptr), lz78(laptr)
	{ }

	// Option function definitions

	Option::Option(Lexer_analysater *laptr)
	{
		_laptr = laptr;
	}

	Option::~Option() {}

	Def_op::Def_op(Lexer_analysater *laptr) : Option(laptr)
	{}

	void Def_op::execute()
	{}

	Def_op::~Def_op()
	{}

	Lzw_op::Lzw_op(Lexer_analysater *laptr) : Option(laptr)
	{
		combine();
		compact();
	}

	void Lzw_op::combine()
	{

	}

	void Lzw_op::compact()
	{

	}

	void Lzw_op::execute()
	{}

	Lzw_op::~Lzw_op()
	{}

	Rle_op::Rle_op(Lexer_analysater *laptr) : Option(laptr)
	{}

	void Rle_op::execute()
	{}

	Rle_op::~Rle_op()
	{}

	Lz77_op::Lz77_op(Lexer_analysater *laptr) : Option(laptr)
	{}

	void Lz77_op::execute()
	{}

	Lz77_op::~Lz77_op()
	{}

	Lz78_op::Lz78_op(Lexer_analysater *laptr) : Option(laptr)
	{}

	void Lz78_op::execute()
	{}

	Lz78_op::~Lz78_op() {}

	//  Archivate function definitions

	Archivate::Archivate(Lexer_analysater *laptr) : Command(laptr), arc_objs(laptr)
	{
		options[static_cast<std::size_t>(Lexer::Token::def)] = &arc_objs.def;
		options[static_cast<std::size_t>(Lexer::Token::lzw)] = &arc_objs.lzw;
		options[static_cast<std::size_t>(Lexer::Token::rle)] = &arc_objs.rle;
		options[static_cast<std::size_t>(Lexer::Token::lz77)] = &arc_objs.lz77;
		options[static_cast<std::size_t>(Lexer::Token::lz78)] = &arc_objs.lz78;
	}

	void Archivate::execute()
	{
		Lexer::Token tok = _laptr->check_next();

		if (options.find(tok) == options.end())
		{
			options[Lexer::Token::def]->execute();
		}
		else
		{
			_laptr->miss();
			options[static_cast<std::size_t>(tok)]->execute();
		}
	}

	Archivate::~Archivate() {}

	// Dearchivate functions definitions

	Dearchivate::Dearchivate(Lexer_analysater *laptr) : Command(laptr)
	{}

	void Dearchivate::execute()
	{}

	Dearchivate::~Dearchivate() {}

	// Exit functions definitions

	Exit::Exit(Lexer_analysater *laptr) : Command(laptr)
	{}

	void Exit::execute()
	{}

	Exit::~Exit() {}

	// Nothing functions definitions

	Nothing::Nothing(Lexer_analysater *laptr) : Command(laptr)
	{}

	void Nothing::execute()
	{}

	Nothing::~Nothing() {}

	//Exceptions

	IncorrectCommand::IncorrectCommand(const std::string &not_command)
	{
		value = not_command;
	}

	std::string IncorrectCommand::get_value() { return value; }
}

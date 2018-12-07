#ifndef ARC_PARSER
#define ARC_PARSER
#include "arc_lexer.h"
#include <unordered_map>

namespace Parser
{
	using Lexer::Lexer_analysater;

	class Option
	{
	public:
		Option(Lexer_analysater *laptr);
		virtual void execute() = 0;
		virtual ~Option();
	protected:
		Lexer_analysater * _laptr;
	};

	class Def_op : public Option
	{
	public:
		Def_op(Lexer_analysater *laptr);
		virtual void execute();
		~Def_op();
	};

	class Lzw_op : public Option
	{
	public:
		Lzw_op(Lexer_analysater *laptr);
		virtual void execute();
		~Lzw_op();
	private:
		void combine();
		void compact();
	};

	class Rle_op : public Option
	{
	public:
		Rle_op(Lexer_analysater *laptr);
		virtual void execute();
		~Rle_op();
	};

	class Lz77_op : public Option
	{
	public:
		Lz77_op(Lexer_analysater *laptr);
		virtual void execute();
		~Lz77_op();
	};

	class Lz78_op : public Option
	{
	public:
		Lz78_op(Lexer_analysater *laptr);
		virtual void execute();
		~Lz78_op();
	};

	struct Arc_Objects
	{
		Arc_Objects(Lexer_analysater *laptr);

		Def_op def;
		Lzw_op lzw;
		Rle_op rle;
		Lz77_op lz77;
		Lz78_op lz78;
	};

	class Command
	{
	public:
		Command(Lexer_analysater *laptr);
		virtual void execute() = 0;
		virtual ~Command();
	protected:
		Lexer_analysater * _laptr;
	};

	class Archivate : public Command
	{
	public:
		Archivate(Lexer_analysater *laptr);
		virtual void execute();
		~Archivate();
	private:
		Arc_Objects arc_objs;
		std::unordered_map<std::size_t, Option *> options;
	};

	class Dearchivate : public Command
	{
	public:
		Dearchivate(Lexer_analysater *laptr);
		virtual void execute();
		~Dearchivate();
	};

	class Exit : public Command
	{
	public:
		Exit(Lexer_analysater *laptr);
		virtual void execute();
		~Exit();
	};

	class Nothing : public Command
	{
	public:
		Nothing(Lexer_analysater *laptr);
		virtual void execute();
		~Nothing();
	};

	struct Command_Objects
	{
		Command_Objects(Lexer_analysater *laptr);

		Archivate arc;
		Dearchivate dearc;
		Nothing nothing;
		Exit exit;
	};

	class Syntax_analysater
	{
	public:
		Syntax_analysater(Lexer_analysater *laptr);
		void execute();

		//class IncorrectCommand;
	private:
		Lexer_analysater *_laptr;
		std::unordered_map<std::size_t, Command *> _commands;
		Command_Objects c_objs;
	};

	class IncorrectCommand
	{
	public:
		IncorrectCommand(const std::string &not_command);
		std::string get_value();
	private:
		std::string value;
	};


}

#endif

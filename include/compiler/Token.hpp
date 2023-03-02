#pragma once

#include "pch.hpp"
#include "Maybe.hpp"
#include "compiler/ast/AST.hpp"
#include "compiler/ast/parsers/Parser.hpp"
#include "compiler/ast/parsers/ImportParser.hpp"
#include "compiler/TokenIterator.hpp"

namespace ion::compiler
{
	class Token;

	class Token
	{
	private:
		static inline std::vector<std::string> typeNames_ = {};

		template<typename T>
		static inline std::size_t registerType()
		{
			const std::size_t id = typeNames_.size();
			typeNames_.emplace_back(typeid(T).name());
			return id;
		}

	public:
		static inline const std::string& nameFromID(std::size_t id)
		{
			assert(id < typeNames_.size());
			return typeNames_.at(id);
		}

		static inline std::size_t typeCount()
		{
			return typeNames_.size();
		}

	public:
		template<typename T, typename Value>
		struct Type
		{
		private:
			static inline std::vector<T> types_ = {};

		public:
			static inline const std::size_t ID = registerType<T>();

			static Maybe<T&> fromId(const std::size_t id)
			{
				if (id < types_.size())
					return types_.at(id);
				return {};
			}

			static Maybe<T&> fromValue(const Value& val)
			{
				for (T& type : types_)
					if (type.match(val))
						return type;
				return {};
			}

			template<typename ...Args>
			static T& create(Args&& ...args)
			{
				return types_.emplace_back(types_.size(), std::forward<Args>(args)...);
			}

			template<typename ...Args>
			static const std::vector<T>& types(Args&& ...args)
			{
				return types_;
			}


		protected:
			explicit Type(const std::size_t id, const Value& value, ast::Parser parser = ast::defaultParser):
				id(id),
				value(value),
				parser(parser)
			{ }

			explicit Type(const std::size_t id, Value&& value, ast::Parser parser = ast::defaultParser):
				id(id),
				value(value),
				parser(parser)
			{ }

			Type(const Type& other) = default;
			Type(Type&& other) = default;
			virtual ~Type() { }

			virtual bool match(const Value& other) const = 0;

		public:
			std::size_t id;
			Value value;
			ast::Parser parser;
		};

		template<typename T, typename Value>
		struct Type<T, Value*>
		{
		private:
			static inline std::vector<T> types_ = {};

		public:
			static inline const std::size_t ID = registerType<T>();

			static const Maybe<T&> fromId(const std::size_t id)
			{
				if (id < types_.size())
					return types_.at(id);
				return {};
			}

			static const Maybe<T&> fromValue(const Value* val)
			{
				for (T& type : types_)
					if (type.match(val))
						return type;
				return {};
			}

			template<typename ...Args>
			static T& create(Args&& ...args)
			{
				return types_.emplace_back(types_.size(), std::forward<Args>(args)...);
			}

			template<typename ...Args>
			static const std::vector<T>& types(Args&& ...args)
			{
				return types_;
			}

			Type& operator=(const Type& other) = default;

		protected:
			explicit Type(const std::size_t id, const Value* value, ast::Parser parser = ast::defaultParser):
				id(id),
				value(value),
				parser(parser)
			{ }

			Type(const Type& other) = default;
			Type(Type&& other) = default;
			virtual ~Type() { }

			virtual bool match(const Value* other) const = 0;

		public:
			std::size_t id;
			Value* value;
			ast::Parser parser;
		};

	public:
		struct Identifier: public Type<Identifier, std::pair<char, bool>>
		{
			explicit Identifier(const std::size_t id, char value, bool ignore = false, ast::Parser parser = ast::defaultParser): Type(id, { value, ignore }, parser) { }

			virtual bool match(const std::pair<char, bool>& c) const override { return value.first == c.first; }

			Identifier& operator=(const Identifier& other)
			{
				id = other.id;
				value = other.value;
				parser = other.parser;
				return *this;
			}

			bool operator==(const Identifier& other) const
			{
				const bool sameID = id == other.id;
				const bool sameChar = value.first == other.value.first;
				const bool sameBool = value.second == other.value.second;
				return sameID && sameChar && sameBool;
			}

			char getChar() const { return value.first; }
			char ignore() const { return value.second; }
		};

		struct Keyword: public Type<Keyword, std::string>
		{
			template<typename ...Args>
			explicit Keyword(Args&&... args): Type(std::forward<Args>(args)...) { }

			Keyword& operator=(const Keyword& other)
			{
				id = other.id;
				value = other.value;
				parser = other.parser;
				return *this;
			}

			bool operator==(const Keyword& other) const
			{
				const bool sameID = id == other.id;
				const bool sameVal = value.compare(other.value) == 0;
				return sameID && sameVal;
			}

			virtual bool match(const std::string& str) const override { return str.compare(value) == 0; }
		};

		struct Name: public Type<Name, std::string>
		{
			template<typename ...Args>
			explicit Name(Args&&... args): Type(std::forward<Args>(args)...) { }

			Name& operator=(const Name& other)
			{
				id = other.id;
				value = other.value;
				parser = other.parser;
				return *this;
			}

			bool operator==(const Name& other) const
			{
				const bool sameID = id == other.id;
				const bool sameVal = value.compare(other.value) == 0;
				return sameID && sameVal;
			}

			virtual bool match(const std::string& str) const override { return str.compare(value) == 0; }
		};

		struct Unknown: public Type<Unknown, std::string>
		{
			template<typename ...Args>
			explicit Unknown(Args&&... args): Type(std::forward<Args>(args)...) { }

			Unknown& operator=(const Unknown& other)
			{
				id = other.id;
				value = other.value;
				parser = other.parser;
				return *this;
			}

			bool operator==(const Unknown& other) const
			{
				const bool sameID = id == other.id;
				const bool sameVal = value.compare(other.value) == 0;
				return sameID && sameVal;
			}

			virtual bool match(const std::string& str) const override { return str.compare(value) == 0; }
		};

		struct Tokens
		{
			const Keyword KEYWORD_NONE = Keyword::create("\0");
			const Keyword EXPORT = Keyword::create("export");
			const Keyword IMPORT = Keyword::create("import", ast::importParser);
			const Keyword RETURN = Keyword::create("return");
			const Keyword LET = Keyword::create("let");
			const Keyword PUB = Keyword::create("pub");
			const Keyword FN = Keyword::create("fn");
			const Keyword STRUCT = Keyword::create("struct");
			const Keyword TRAIT = Keyword::create("trait");
			const Keyword TYPE = Keyword::create("type");
			const Keyword USING = Keyword::create("using");
			const Keyword INTERFACE = Keyword::create("interface");
			const Keyword IF = Keyword::create("if");
			const Keyword ELSEIF = Keyword::create("else if");
			const Keyword ELSE = Keyword::create("else");
			const Keyword FOR = Keyword::create("for");
			const Keyword WHILE = Keyword::create("while");
			const Keyword MATCH = Keyword::create("match");
			const Keyword CONST = Keyword::create("const");
			const Keyword MUT = Keyword::create("mut");
			const Keyword THIS = Keyword::create("this");
			const Keyword AS = Keyword::create("as");

			const Identifier IDENT_NONE = Identifier::create('\0', true);
			const Identifier NEW_LINE = Identifier::create('\n', true);
			const Identifier CARIAGE_RETURN = Identifier::create('\r', true);
			const Identifier TAB = Identifier::create('\t', true);
			const Identifier SPACE = Identifier::create(' ', true);

			const Identifier END_STMT = Identifier::create(';');
			const Identifier SCOPE_START = Identifier::create('{');
			const Identifier SCOPE_END = Identifier::create('}');
			const Identifier BRACKET_START = Identifier::create('(');
			const Identifier BRACKET_END = Identifier::create(')');
			const Identifier GENERIC_START = Identifier::create('<');
			const Identifier GENERIC_END = Identifier::create('>');
			const Identifier SQ_BRACKET_START = Identifier::create('[');
			const Identifier SQ_BRACKET_END = Identifier::create(']');
			const Identifier SEP = Identifier::create(',');
			const Identifier ADD = Identifier::create('+');
			const Identifier SUBTRACT = Identifier::create('-');
			const Identifier DIVIDE = Identifier::create('/');
			const Identifier MULTPLY = Identifier::create('*');
			const Identifier ATTRIBUTE = Identifier::create('#');
			const Identifier COLON = Identifier::create(':');
			const Identifier DOT = Identifier::create('.');
			const Identifier REF = Identifier::create('&');
			const Identifier TILDE = Identifier::create('~');
			const Identifier PIPE = Identifier::create('|');
			const Identifier NOT = Identifier::create('!');

			const Unknown UNKNOWN = Unknown::create("");

		private:
			explicit Tokens() { }

			friend class Token;
		};

		static Tokens tokens;

		struct TokenType
		{
		public:
			template<typename T>
			TokenType(const T& tokenType):
				typeID(T::ID),
				type_(tokenType)
			{ }

			template<typename T>
			inline T type() const { return std::get<T>(type_); }

			inline std::string name() const
			{
				if (typeID == Identifier::ID)
					return std::string({ type<Identifier>().value.first });
				else if (typeID == Keyword::ID)
					return type<Keyword>().value;
				else if (typeID == Name::ID)
					return type<Name>().value;
				else if (typeID == Unknown::ID)
					return type<Unknown>().value;

				return "";
			}

			inline std::string typeName() const
			{
				return Token::nameFromID(typeID);
			}

			template<typename T>
			inline bool match(const T& value) const
			{
				if (typeID == Identifier::ID)
					return type<Identifier>().match(value);
				else if (typeID == Keyword::ID)
					return type<Keyword>();
				else if (typeID == Name::ID)
					return type<Name>().match(value);
				else if (typeID == Unknown::ID)
					return type<Unknown>().match(value);

				return false;
			}

			inline ast::Parser parser() const
			{
				if (typeID == Identifier::ID)
					return type<Identifier>().parser;
				else if (typeID == Keyword::ID)
					return type<Keyword>().parser;
				else if (typeID == Name::ID)
					return type<Name>().parser;
				else if (typeID == Unknown::ID)
					return type<Unknown>().parser;

				return ast::defaultParser;
			}

			bool operator==(const TokenType& other) const
			{
				return other.typeID == typeID && other.type_ == type_;
			}

			std::size_t typeID;

		private:
			std::variant<Identifier, Keyword, Name, Unknown> type_;
		};

	public:
		template<typename T>
		Token(std::size_t line, std::size_t column, T type, const std::string& text):
			line(line),
			column(column),
			text(text),
			type(type)
		{ }

		Token():
			line(0),
			column(0),
			text(""),
			type(tokens.UNKNOWN)
		{ }

		std::string toString() const;

		template<typename T>
		inline bool is() const
		{
			return type.typeID == T::ID;
		}

		template<typename T>
		bool match(const T& value) const
		{
			return type.match(value);
		}

		Token& operator=(const Token& other)
		{
			line = other.line;
			column = other.column;
			text = other.text;
			type = other.type;
			return *this;
		}

		bool operator==(const Token& other) const
		{
			if (other.line != line)
				return false;

			if (other.column != column)
				return false;

			if (other.type != type)
				return false;

			return false;
		}

		std::size_t line;
		std::size_t column;
		std::string text;
		TokenType type;

	};
}
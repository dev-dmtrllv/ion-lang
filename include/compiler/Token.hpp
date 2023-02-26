#pragma once

#include "pch.hpp"
#include "Maybe.hpp"

namespace ion::compiler
{
	struct Token
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

	public:

		template<typename T, typename Value>
		struct Type
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

			static const Maybe<T&> fromValue(const Value& val)
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
			explicit Type(const std::size_t id, const Value& value):
				id(id),
				value(value)
			{ }

			explicit Type(const std::size_t id, Value&& value):
				id(id),
				value(value)
			{ }

			Type(const Type& other) = default;
			Type(Type&& other) = default;
			virtual ~Type() { }

			virtual bool match(const Value& other) const = 0;

		public:
			std::size_t id;
			Value value;
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
			explicit Type(const std::size_t id, const Value* value):
				id(id),
				value(value)
			{ }

			Type(const Type& other) = default;
			Type(Type&& other) = default;
			virtual ~Type() { }

			virtual bool match(const Value* other) const = 0;

		public:
			std::size_t id;
			Value* value;
		};

	public:
		struct Identifier: public Type<Identifier, std::pair<char, bool>>
		{
			explicit Identifier(const std::size_t id, char value, bool ignore = false): Type(id, { value, ignore }) { }

			virtual bool match(const std::pair<char, bool>& c) const override { return value.first == c.first; }

			Identifier& operator=(const Identifier& other)
			{
				id = other.id;
				value = other.value;
				return *this;
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
				return *this;
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
				return *this;
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
				return *this;
			}

			virtual bool match(const std::string& str) const override { return str.compare(value) == 0; }
		};

		static Keyword KEYWORD_NONE;
		static Keyword EXPORT;
		static Keyword IMPORT;
		static Keyword RETURN;
		static Keyword LET;
		static Keyword PUB;
		static Keyword FN;
		static Keyword STRUCT;
		static Keyword TRAIT;
		static Keyword TYPE;
		static Keyword USING;
		static Keyword INTERFACE;
		static Keyword IF;
		static Keyword ELSEIF;
		static Keyword ELSE;
		static Keyword FOR;
		static Keyword WHILE;
		static Keyword MATCH;
		static Keyword CONST;
		static Keyword MUT;
		static Keyword THIS;

		static Identifier IDENT_NONE;
		static Identifier NEW_LINE;
		static Identifier CARIAGE_RETURN;
		static Identifier TAB;
		static Identifier SPACE;

		static Identifier END_STMT;
		static Identifier SCOPE_START;
		static Identifier SCOPE_END;
		static Identifier BRACKET_START;
		static Identifier BRACKET_END;
		static Identifier GENERIC_START;
		static Identifier GENERIC_END;
		static Identifier SQ_BRACKET_START;
		static Identifier SQ_BRACKET_END;
		static Identifier SEP;
		static Identifier ADD;
		static Identifier SUBTRACT;
		static Identifier DIVIDE;
		static Identifier MULTPLY;
		static Identifier ATTRIBUTE;
		static Identifier COLON;
		static Identifier DOT;
		static Identifier REF;
		static Identifier TILDE;
		static Identifier PIPE;
		static Identifier NOT;

	public:
		template<typename T>
		Token(std::size_t line, std::size_t column, T type, const std::string& text):
			line(line),
			column(column),
			typeID(T::ID),
			text(text),
			type_(type)
		{ }

		std::string toString() const;

		std::size_t line;
		std::size_t column;
		std::size_t typeID;
		std::string text;

		template<typename T>
		inline T type() { return std::get<T>(type_); }

	private:
		std::variant<Identifier, Keyword, Name, Unknown> type_;
	};
}
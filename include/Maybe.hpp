#pragma once

namespace ion
{
	template<typename T>
	struct Maybe
	{
		Maybe():
			hasValue_(false),
			buffer_{  }
		{ }

		Maybe(const T& value): Maybe()
		{
			set(value);
		}

		Maybe(T&& value): Maybe()
		{
			set(value);
		}

		template<typename ...Args>
		Maybe(Args&& ...args) : Maybe()
		{
			set(std::forward<Args>(args)...);
		}

		~Maybe()
		{
			if (hasValue_)
				ptr()->~T();
		}

		void set(const T& value)
		{
			if(hasValue_)
				destruct();
			new (ptr()) T(value);
			hasValue_ = true;
		}

		void set(T&& value)
		{
			if(hasValue_)
				destruct();
			new (ptr()) T(value);
			hasValue_ = true;
		}

		template<typename ...Args>
		void set(Args&& ...args)
		{
			if(hasValue_)
				destruct();
			new (ptr()) T(std::forward<Args>(args)...);
			hasValue_ = true;
		}

		bool hasValue() const { return hasValue_; }
		bool isEmpty() const { return !hasValue_; }

		T& value() const { assert(hasValue()); return *ptr(); }

		T& operator->() { return value(); };

		Maybe<T>& operator=(const Maybe<T>& other)
		{
			*ptr() = other;
			return *this;
		}

		template<typename Arg>
		Maybe<T>& operator=(const Arg& other)
		{
			*ptr() = other;
			return *this;
		}

		template<typename Arg>
		Maybe<T>& operator=(Arg&& other)
		{
			*ptr() = other;
			return *this;
		}

		void reset()
		{
			hasValue_ = false;
			destruct();
			buffer_ = { 0 };
		}

		T unwrap() const
		{
			return *value();
		}

		auto unwrap(auto callback) const
		{
			return callback(*this);
		}

	private:
		T* ptr() { return reinterpret_cast<T*>(&buffer_[0]); }
		
		inline void destruct() { ptr()->~T(); }

	private:
		char buffer_[sizeof(T) / sizeof(char)];
		bool hasValue_;
	};

	template<typename T>
	struct Maybe<T*>
	{
		Maybe(T* value = nullptr): value_(value) {}

		~Maybe() {}

		void set(T* value)
		{
			value_ = value;
		}

		bool hasValue() const { return value_ != nullptr; }
		bool isEmpty() const { return value_ == nullptr; }

		T& value() const { assert(hasValue()); return *value_; }
		
		T& operator->() { return value(); };

		Maybe<T>& operator=(const Maybe<T>& other)
		{
			set(other.value());
			return *this;
		}

		Maybe<T>& operator=(T* value)
		{
			set(value);
			return *this;
		}

		void reset()
		{
			value_ = nullptr;
		}

		T unwrap() const
		{
			return *value_;
		}

		auto unwrap(auto callback) const
		{
			return callback(*this);
		}

	private:
		T* value_;
	};

	template<typename T>
	struct Maybe<T&>
	{
		Maybe(): value_(nullptr) {}

		Maybe(T* value): value_(value) {}

		Maybe(T& value): value_(std::addressof(value)) {}

		~Maybe() {}

		void set(T* value)
		{
			value_ = value;
		}

		void set(T& value)
		{
			value_ = std::addressof(value);
		}

		bool hasValue() const { return value_ != nullptr; }
		bool isEmpty() const { return value_ == nullptr; }

		T& value() const { assert(hasValue()); return *value_; }

		T& operator->() { return value(); };

		void reset()
		{
			value_ = nullptr;
		}

		bool unwrap(T& value) const
		{
			if(!hasValue())
				return false;
			value = *value_;
			return true;
		}

		// T unwrap(T&& value) const
		// {
		// 	if(!hasValue())
		// 		return value;
		// 	return *value_;
		// }

		// auto unwrap(auto callback) const
		// {
		// 	return callback(*this);
		// }

	private:
		T* value_;
	};
}
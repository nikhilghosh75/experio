#pragma once
#include <stdint.h>
#include <string>

enum class EAssertionStatus : uint8_t
{
	Success,
	Failure
};

struct FAssertionOutcome
{
	EAssertionStatus status;
	std::string statement;
	std::string filepath;
	unsigned int lineNumber;

	FAssertionOutcome(EAssertionStatus status, std::string statement, std::string filepath, unsigned int lineNumber)
	{
		this->status = status;
		this->statement = statement;
		this->filepath = filepath;
		this->lineNumber = lineNumber;
	}
};

#define ASSERT_TRUE(x) if(!(x))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_TRUE(x, statement) if(!(x))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_FALSE(x) if(x)\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_FALSE(x, statement) if(x)\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_EQUAL(x, y) if(!(x == y))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_EQUAL(x, y, statement) if(!(x == y))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_NOT_EQUAL(x, y) if(x == y)\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_NOT_EQUAL(x, y, statement) if(x == y)\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_GREATER_THAN(x, y) if(!(x > y))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_GREATER_THAN(x, y, statement) if(!(x > y))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_LESS_THAN(x, y) if(!(x < y))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_LESS_THAN(x, y, statement) if(!(x < y))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_NULL(x) if(!(x == nullptr))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_NULL(x, statement) if(!(x == nullptr))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_NOT_NULL(x) if(!(x != nullptr))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_NOT_NULL(x, statement) if(!(x != nullptr))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_ZERO(x) if(!(x == 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_ZERO(x, statement) if(!(x == 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_NOT_ZERO(x) if(!(x != 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_NOT_ZERO(x, statement) if(!(x != 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_POSITIVE(x) if(!(x > 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_POSITIVE(x, statement) if(!(x > 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_NEGATIVE(x) if(!(x < 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, "", __FILE__, __LINE__);\
}

#define ASSERT_NEGATIVE(x, statement) if(!(x < 0))\
{\
	return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);\
}

#define ASSERT_PASS()

#define ASSERT_PASS(statement)

#define ASSERT_FAIL()

#define ASSERT_FAIL(statement) return FAssertionOutcome(EAssertionStatus::Failure, statement, __FILE__, __LINE__);
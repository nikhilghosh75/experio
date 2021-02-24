#pragma once
#include <string>
#include <vector>

struct TerminalOption
{
	char shortOption;
	std::string longOption;
};

class TerminalParser
{
	const std::vector<std::string>* args;
	std::vector<TerminalOption> options;
public:

	TerminalParser(const std::vector<std::string>& args, std::vector<TerminalOption> options)
	{
		this->args = &args;
		this->options = options;
	}

	class Iterator
	{
		TerminalParser* parser;

		size_t index;
	public:
		size_t currentOption;
		std::string arg;

		Iterator(TerminalParser* parser, size_t index)
		{
			this->parser = parser;
			this->index = index;
			if (this->parser != nullptr)
			{
				++(*this);
			}
		}

		Iterator& operator*()
		{
			return *this;
		}

		Iterator& operator++()
		{
			index++;
			if (index >= parser->args->size())
			{
				this->parser = nullptr;
				return *this;
			}
			if ((*parser->args)[index][0] != '-')
			{
				index++;
			}

			if (index != parser->args->size() - 1)
			{
				if ((*parser->args)[index + 1][0] != '-')
				{
					arg = parser->args[index + 1][0];
				}
				else
				{
					arg = "";
				}
			}
			else
			{
				arg = "";
			}

			if ((*parser->args)[index][1] == '-')
			{
				for (size_t i = 0; i < parser->options.size(); i++)
				{
					if ((*parser->args)[index].find(parser->options[i].longOption) != std::string::npos)
					{
						currentOption = i;
						break;
					}
				}
			}
			else
			{
				for (size_t i = 0; i < parser->options.size(); i++)
				{
					if (parser->options[i].shortOption == 0)
						continue;

					if ((*parser->args)[index][1] == parser->options[i].shortOption)
					{
						currentOption = i;
						break;
					}
				}
			}

			return *this;
		}

		bool operator==(const Iterator& other) const
		{
			if (parser == nullptr && other.parser == nullptr)
				return true;
			else if (parser == nullptr || other.parser == nullptr)
				return false;

			return this->index == other.index;
		}

		bool operator!=(const Iterator& other) const
		{
			if (parser == nullptr && other.parser == nullptr)
				return false;
			else if (parser == nullptr || other.parser == nullptr)
				return true;

			return this->index != other.index;
		}
	};

	Iterator begin()
	{
		return Iterator(this, 0);
	}

	Iterator end()
	{
		return Iterator(nullptr, 0);
	}
};
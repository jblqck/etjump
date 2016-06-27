#include <gtest/gtest.h>
#include "../game/etj_commands_parser.h"

using namespace ETJump;

class CommandsParserTests : public testing::Test
{
public:
	void SetUp() override {
		parser = CommandsParser();
	}

	void TearDown() override {
	}

	CommandsParser parser;
};

bool OptionExists(const CommandsParser::ParsedCommand& command, const std::string& option)
{
	return command.options.find(option) != end(command.options);
}

TEST_F(CommandsParserTests, TestRegularCommandWithNoOptions)
{
	struct CommandsParser::ParseOptions options;

	std::vector<std::string> args = {
		"!throw",
		"player",
		"far"
	};
	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_EQ(parsedCommand.arguments.size(), 2);
	ASSERT_EQ(parsedCommand.arguments[0], "player");
	ASSERT_EQ(parsedCommand.arguments[1], "far");
	ASSERT_EQ(parsedCommand.options.size(), 0);
}

TEST_F(CommandsParserTests, TestCommandWithJustOptions)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("player", CommandsParser::OptionDefinition::Type::Token, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("tester", CommandsParser::OptionDefinition::Type::Token, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("player", CommandsParser::OptionDefinition::Type::Boolean, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"-player",
		"thisIsAPlayer",
		"-tester",
		"ATester",
		"-thingIsActive"
	};

	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "throw");
	ASSERT_EQ(parsedCommand.arguments.size(), 0);
	ASSERT_TRUE(OptionExists(parsedCommand, "player"));
	ASSERT_EQ(parsedCommand.options["player"].text, "thisIsAPlayer");
	ASSERT_TRUE(OptionExists(parsedCommand, "tester"));
	ASSERT_EQ(parsedCommand.options["tester"].text, "ATester");
	ASSERT_TRUE(OptionExists(parsedCommand, "thingIsActive"));
	ASSERT_EQ(parsedCommand.options["thingIsActive"].type, CommandsParser::OptionDefinition::Type::Boolean);
	ASSERT_TRUE(parsedCommand.options["thingIsActive"].active);
}

TEST_F(CommandsParserTests, TestCommandWithOptionsAndArgs)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("player", CommandsParser::OptionDefinition::Type::Token, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("tester", CommandsParser::OptionDefinition::Type::Token, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("player", CommandsParser::OptionDefinition::Type::Boolean, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"-player",
		"thisIsAPlayer",
		"-tester",
		"ATester",
		"-thingIsActive",
		"arguments",
		"are",
		"here"
	};

	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "throw");
	ASSERT_EQ(parsedCommand.arguments.size(), 3);
	ASSERT_EQ(parsedCommand.arguments[0], "arguments");
	ASSERT_EQ(parsedCommand.arguments[1], "are");
	ASSERT_EQ(parsedCommand.arguments[2], "here");
	ASSERT_TRUE(OptionExists(parsedCommand, "player"));
	ASSERT_EQ(parsedCommand.options["player"].text, "thisIsAPlayer");
	ASSERT_TRUE(OptionExists(parsedCommand, "tester"));
	ASSERT_EQ(parsedCommand.options["tester"].text, "ATester");
	ASSERT_TRUE(OptionExists(parsedCommand, "thingIsActive"));
	ASSERT_EQ(parsedCommand.options["thingIsActive"].type, CommandsParser::OptionDefinition::Type::Boolean);
	ASSERT_TRUE(parsedCommand.options["thingIsActive"].active);
}

TEST_F(CommandsParserTests, TestCommandWithMixedOptionsAndArgs)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("player", CommandsParser::OptionDefinition::Type::Token, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("tester", CommandsParser::OptionDefinition::Type::Token, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("player", CommandsParser::OptionDefinition::Type::Boolean, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"so",
		"it",
		"begins",
		"-player",
		"thisIsAPlayer",
		"-tester",
		"ATester",
		"-thingIsActive",
		"arguments",
		"are",
		"here"
	};

	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "throw");
	ASSERT_EQ(parsedCommand.arguments.size(), 6);
	ASSERT_EQ(parsedCommand.arguments[0], "so");
	ASSERT_EQ(parsedCommand.arguments[1], "it");
	ASSERT_EQ(parsedCommand.arguments[2], "begins");
	ASSERT_EQ(parsedCommand.arguments[3], "arguments");
	ASSERT_EQ(parsedCommand.arguments[4], "are");
	ASSERT_EQ(parsedCommand.arguments[5], "here");
	ASSERT_TRUE(OptionExists(parsedCommand, "player"));
	ASSERT_EQ(parsedCommand.options["player"].text, "thisIsAPlayer");
	ASSERT_TRUE(OptionExists(parsedCommand, "tester"));
	ASSERT_EQ(parsedCommand.options["tester"].text, "ATester");
	ASSERT_TRUE(OptionExists(parsedCommand, "thingIsActive"));
	ASSERT_EQ(parsedCommand.options["thingIsActive"].type, CommandsParser::OptionDefinition::Type::Boolean);
	ASSERT_TRUE(parsedCommand.options["thingIsActive"].active);
}

TEST_F(CommandsParserTests, TestMultiToken)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("message", CommandsParser::OptionDefinition::Type::MultiToken, "A description"));

	std::vector<std::string> args = {
		"!print",
		"-message",
		"a",
		"long",
		"message"
	};

	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "print");
	ASSERT_EQ(parsedCommand.arguments.size(), 0);
	ASSERT_TRUE(OptionExists(parsedCommand, "message"));
	ASSERT_EQ(parsedCommand.options["message"].text, "a long message");
}

TEST_F(CommandsParserTests, TestToken)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("message", CommandsParser::OptionDefinition::Type::Token, "A description"));

	std::vector<std::string> args = {
		"!print",
		"random",
		"-token",
		"token",
		"text"
	};

	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "print");
	ASSERT_EQ(parsedCommand.arguments.size(), 2);
	ASSERT_TRUE(OptionExists(parsedCommand, "token"));
	ASSERT_EQ(parsedCommand.options["token"].text, "token");
}

TEST_F(CommandsParserTests, TestDuration)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("duration", CommandsParser::OptionDefinition::Type::Duration, "A description"));

	std::vector<std::string> args = {
		"!displayDuration",
		"-duration",
		"37s",
	};

	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 37 * 1000);

	args[2] = "3min";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 3 * 60 * 1000);


	args[2] = "5h";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 5 * 60 * 60 * 1000);

	args[2] = "7d";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 7 * 24 * 60 * 60 * 1000);

	args[2] = "9w";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 9 * 7 * 24 * 60 * 60 * 1000);

	args[2] = "11mon";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 11 * 30 * 24 * 60 * 60 * 1000);

	args[2] = "13y";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_TRUE(OptionExists(parsedCommand, "duration"));
	ASSERT_EQ(parsedCommand.options["duration"].duration, 13 * 12 * 30 * 24 * 60 * 60 * 1000);
}

TEST_F(CommandsParserTests, TestInteger)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("integer", CommandsParser::OptionDefinition::Type::Integer, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"-integer",
		"1000"
	};
	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_EQ(parsedCommand.options["integer"].integer, 1000);

	args[2] = "-1000";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_EQ(parsedCommand.options["integer"].integer, -1000);

	args[2] = "a string";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_GT(parsedCommand.options["integer"].errorMessage.length(), 0);

}

TEST_F(CommandsParserTests, TestPositiveInteger)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("integer", CommandsParser::OptionDefinition::Type::Integer, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"-integer",
		"1000"
	};
	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_EQ(parsedCommand.options["integer"].integer, 1000);

	args[2] = "-1000";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_GT(parsedCommand.options["integer"].errorMessage.length(), 0);

	args[2] = "a string";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_GT(parsedCommand.options["integer"].errorMessage.length(), 0);
}

TEST_F(CommandsParserTests, TestNegativeInteger)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("integer", CommandsParser::OptionDefinition::Type::Integer, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"-integer",
		"1000"
	};
	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_GT(parsedCommand.options["integer"].errorMessage.length(), 0);

	args[2] = "-1000";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_EQ(parsedCommand.options["integer"].integer, -1000);

	args[2] = "a string";
	parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "integer"));
	ASSERT_GT(parsedCommand.options["integer"].errorMessage.length(), 0);
}

TEST_F(CommandsParserTests, TestBoolean)
{
	struct CommandsParser::ParseOptions options;
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("boolean", CommandsParser::OptionDefinition::Type::Boolean, "A description"));
	options.optionDefinitions.push_back(CommandsParser::OptionDefinition("boolean2", CommandsParser::OptionDefinition::Type::Boolean, "A description"));

	std::vector<std::string> args = {
		"!throw",
		"-boolean"
	};
	auto parsedCommand = CommandsParser::parse(args, options);
	ASSERT_EQ(parsedCommand.command, "!throw");
	ASSERT_TRUE(OptionExists(parsedCommand, "boolean"));
	ASSERT_TRUE(parsedCommand.options["boolean"].active);
	ASSERT_TRUE(OptionExists(parsedCommand, "boolean2"));
	ASSERT_FALSE(parsedCommand.options["boolean2"].active);
}



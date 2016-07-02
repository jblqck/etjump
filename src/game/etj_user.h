#pragma once
#include <string>
#include <vector>
#include <boost/functional/hash.hpp>

namespace ETJump
{
	// A persistent user that stays across multiple sessions / server restarts etc.
	class User
	{
	public:
		User(int64_t id, const std::string& guid);

		User(int64_t id, 
			const std::string& guid, 
			int level, 
			int64_t lastSeen, 
			const std::string& name, 
			const std::string& title, 
			const std::string& commands, 
			const std::string& greeting, 
			const std::vector<std::string>& hardwareIds)
			: _id(id),
			  _guid(guid),
			  _level(level),
			  _lastSeen(lastSeen),
			  _name(name),
			  _title(title),
			  _commands(commands),
			  _greeting(greeting),
			  hardwareIds(hardwareIds)
		{
		}

		User();
		~User();

		friend std::ostream& operator<<(std::ostream& os, const User& obj)
		{
			return os
				<< "_id: " << obj._id
				<< " _guid: " << obj._guid
				<< " _level: " << obj._level
				<< " _lastSeen: " << obj._lastSeen
				<< " _name: " << obj._name
				<< " _title: " << obj._title
				<< " _commands: " << obj._commands
				<< " _greeting: " << obj._greeting;
		}


		int64_t id() const
		{
			return _id;
		}

		std::string guid() const
		{
			return _guid;
		}

		int level() const
		{
			return _level;
		}

		int64_t lastSeen() const
		{
			return _lastSeen;
		}

		std::string name() const
		{
			return _name;
		}

		std::string title() const
		{
			return _title;
		}

		std::string commands() const
		{
			return _commands;
		}

		std::string greeting() const
		{
			return _greeting;
		}

		std::vector<std::string> hardwareIds1() const
		{
			return hardwareIds;
		}

	private:
		int64_t _id;
		std::string _guid;
		int _level;
		int64_t _lastSeen;
		std::string _name;
		std::string _title;
		std::string _commands;
		std::string _greeting;
		std::vector<std::string> hardwareIds;
	};
}




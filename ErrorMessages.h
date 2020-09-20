#pragma once
#include <vector>
#include <string>
class Response {

private:
	std::vector<std::string>messageError;
	int success;
public:
	Response() {
		this->success = 0;
	}

	Response(const Response& message) {
		this->messageError = message.messageError;
		this->success = message.success;
	}

	void append(std::string str) {
		this->messageError.push_back(str);
	}

	std::vector<std::string> getAll() {
		return this->messageError;
	}

	int size() {
		return this->messageError.size();
	}

	int isSuccess() {

		return success;
	}

	void setSuccess(int status) {
		this->success = status;
	}
};
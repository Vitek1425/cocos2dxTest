#include "apiclient.h"

#include <vector>
#include <fstream>

#include "cocos2d.h"
#include "network\HttpClient.h"
#include "network\HttpRequest.h"

//#include "Libs\json.hpp"
#include "Libs\picojson.h"

#define SERVER_API_URL "https://puzzle-english.com/api"
#define API_METHOD_URL "https://puzzle-english.com/api/test.php"
#define LOCAL_VIDEO_NAME "localVideo.mp4"

USING_NS_CC;

ApiClient * ApiClient::getInstance()
{
	static ApiClient client;
	return &client;
}

void ApiClient::checkConnection(std::function<void(bool)> checkConnectionCallback)
{
	auto request = new (std::nothrow) network::HttpRequest();
	request->setUrl(SERVER_API_URL);
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback([checkConnectionCallback](network::HttpClient* sender, network::HttpResponse* response) {
		if (!response)
		{
			checkConnectionCallback(false);
			return;
		}
		//если удалось соединиться с SERVER_API_URL, значит есть соединение с интернетом
		checkConnectionCallback(response->getResponseCode() != -1);
	});
	network::HttpClient::getInstance()->sendImmediate(request);
	request->release();
}

void ApiClient::requestVideoUrl(std::function<void(const std::string&)> requestVideoUrlCallback)
{
	auto request = new (std::nothrow) network::HttpRequest();
	request->setUrl(API_METHOD_URL);
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback([requestVideoUrlCallback](network::HttpClient* sender, network::HttpResponse* response) {
		if (!response)
		{
			requestVideoUrlCallback(std::string());
			return;
		}

		std::string videoUrl;

		//чтение ответа в формате json
		try {
			std::vector<char>* buffer = response->getResponseData();
			if (buffer->empty())
			{
				requestVideoUrlCallback(std::string());
				return;
			}
			std::string jsonString(buffer->data());
			picojson::value jsonValue;
			std::string err = picojson::parse(jsonValue, jsonString);
			if (!err.empty()) {
				requestVideoUrlCallback(std::string());
				return;
			}
			videoUrl = jsonValue.get<picojson::object>()["url"].get<std::string>();
		}
		catch (...)
		{

		}
		requestVideoUrlCallback(videoUrl);
		
	});
	network::HttpClient::getInstance()->sendImmediate(request);
	request->release();
}

std::string ApiClient::localVideoCopyPath() const
{
	return FileUtils::getInstance()->getWritablePath() + std::string(LOCAL_VIDEO_NAME);
}

bool ApiClient::isLocalVideoCopyExist() const
{
	return FileUtils::getInstance()->isFileExist(localVideoCopyPath());
}

void ApiClient::loadVideo(const std::string &url, std::function<void()> loadVideoCallback)
{
	auto request = new (std::nothrow) network::HttpRequest();
	request->setUrl(url);
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback([&,loadVideoCallback](network::HttpClient* sender, network::HttpResponse* response) {
		if (!response)
		{
			loadVideoCallback();
			return;
		}
		std::vector<char>* buffer = response->getResponseData();
		if (!buffer->empty() && response->getResponseCode() == 200)
		{
			//запись видео в локальный файл
			std::ofstream videoFile(localVideoCopyPath().c_str(), std::ofstream::binary);
			videoFile.write(response->getResponseData()->data(), response->getResponseData()->size());
			videoFile.close();
		}

		loadVideoCallback();
	});
	network::HttpClient::getInstance()->sendImmediate(request);
	request->release();
}
#ifndef APICLIENT_H
#define APICLIENT_H

#include <functional>
#include <string>

//класс для выполнения запросов к api
class ApiClient
{
public:
	static ApiClient* getInstance();

	ApiClient(const ApiClient&) = delete;
	ApiClient& operator=(const ApiClient&) = delete;

	//проверка соединения с сервисом, проверка выполняется асинхронно, результат заносится в checkConnectionCallback
	void checkConnection(std::function<void(bool)> checkConnectionCallback);

	//получение url видео, выполняется асинхронно, результат заносится в requestVideoUrlCallback
	void requestVideoUrl(std::function<void(const std::string&)> requestVideoUrlCallback);

	//получение пути к локальной копии видео
	std::string localVideoCopyPath() const;

	//существует ли локальная копия
	bool isLocalVideoCopyExist() const;

	//загрузка видео, выполняется асинхронно, при завершении вызывается loadVideoCallback
	void loadVideo(const std::string &url, std::function<void()> loadVideoCallback);
private:
	ApiClient() = default;
	~ApiClient() = default;
};

#endif // APICLIENT_H
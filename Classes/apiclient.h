#ifndef APICLIENT_H
#define APICLIENT_H

#include <functional>
#include <string>

//����� ��� ���������� �������� � api
class ApiClient
{
public:
	static ApiClient* getInstance();

	ApiClient(const ApiClient&) = delete;
	ApiClient& operator=(const ApiClient&) = delete;

	//�������� ���������� � ��������, �������� ����������� ����������, ��������� ��������� � checkConnectionCallback
	void checkConnection(std::function<void(bool)> checkConnectionCallback);

	//��������� url �����, ����������� ����������, ��������� ��������� � requestVideoUrlCallback
	void requestVideoUrl(std::function<void(const std::string&)> requestVideoUrlCallback);

	//��������� ���� � ��������� ����� �����
	std::string localVideoCopyPath() const;

	//���������� �� ��������� �����
	bool isLocalVideoCopyExist() const;

	//�������� �����, ����������� ����������, ��� ���������� ���������� loadVideoCallback
	void loadVideo(const std::string &url, std::function<void()> loadVideoCallback);
private:
	ApiClient() = default;
	~ApiClient() = default;
};

#endif // APICLIENT_H
#pragma once
using namespace System;
using namespace System::Text;
using namespace Net;
using namespace Sockets;
using namespace Threading;
using namespace Collections::Generic;

delegate void LoginHandler(bool data);//делегат хранит сссылку на метод
delegate void MessageHandler( String^ msg);
ref class Client
{
	String^ serverHost;
	int port = 5555;
	Socket^ socket;//подключение
	bool active = false;
	void SendData(String^dat);
	void Communicate();//обзение
	bool Enter = false;
	void ParseCommand(String^ req);//разютраем строку
	String^ ReceiveData();//получаем из байтов строку
public:
	event MessageHandler^ OnMessageReceived;//событие получения сообщения
	event LoginHandler^ OnEnterResult;//событие результат входа
	Client(String^ serverHost);//конструктор
	void Enters(String^Number, String^Pin);//попытка входа с данным логином и паролем
	void Remove(String^s);//снимает со счета
	void Insert(String^s);//пополняем счет
	void SendMessage(String^ message);
	void Transfer(String^NumberCard, String^Money);
	void Balance();//отпраялем запрос на получение информации о балансе
	void Stop();

	virtual ~Client();
};


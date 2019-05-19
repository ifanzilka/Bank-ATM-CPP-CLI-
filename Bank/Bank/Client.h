#pragma once
using namespace System;
using namespace System::Text;
using namespace Net;
using namespace Sockets;
using namespace Threading;
using namespace Collections::Generic;

delegate void LoginHandler(bool data);//������� ������ ������� �� �����
delegate void MessageHandler( String^ msg);
ref class Client
{
	String^ serverHost;
	int port = 5555;
	Socket^ socket;//�����������
	bool active = false;
	void SendData(String^dat);
	void Communicate();//�������
	bool Enter = false;
	void ParseCommand(String^ req);//��������� ������
	String^ ReceiveData();//�������� �� ������ ������
public:
	event MessageHandler^ OnMessageReceived;//������� ��������� ���������
	event LoginHandler^ OnEnterResult;//������� ��������� �����
	Client(String^ serverHost);//�����������
	void Enters(String^Number, String^Pin);//������� ����� � ������ ������� � �������
	void Remove(String^s);//������� �� �����
	void Insert(String^s);//��������� ����
	void SendMessage(String^ message);
	void Transfer(String^NumberCard, String^Money);
	void Balance();//��������� ������ �� ��������� ���������� � �������
	void Stop();

	virtual ~Client();
};


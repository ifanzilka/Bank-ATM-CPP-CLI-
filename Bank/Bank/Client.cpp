#include "Client.h"

void Client::SendData(String ^ data)
{
	if (!socket) return;//���� ���� �����������
	try {
		if (!data || data->Trim()->Equals("")) data = "\0";
		array<Byte>^ b = Encoding::UTF8->GetBytes(data);//������ ��������� � �����
		Console::WriteLine("Sending: {0}", data);
		socket->Send(b);//���������� �����
		Console::WriteLine("Sent");
	}
	catch (...)
	{
		active = false;
	}
}

void Client::Communicate()
{
	if (!socket) return;
	Console::WriteLine("Starting communication");
	while (active) {
		Console::WriteLine("Receiving response...");//��������� ������
		auto req = ReceiveData();//��������� ���������
		ParseCommand(req);
	}
}

void Client::ParseCommand(String ^ req)
{
	if (!req || req->Trim()->Equals("")) return;
	array<String^>^ sep = { ":" };
	array<String^>^ parts = req->Split(sep, 2, StringSplitOptions::None);//��������� ���������� ������ �� ��� ������ � ���������� � ������ (��������� � ':')
	if (parts[0]->ToUpper()->Equals("ENTERS"))//���� ������ ������� ����� 
	{
		OnEnterResult(parts[1]->Contains("OK"));
	}
	else if (parts[0]->ToUpper()->Equals("BALANCE"))//���� ������ ������� ���������
	{
		
			OnMessageReceived("������� �������:"+parts[1]);
		
	}
	else if (parts[0]->ToUpper()->Equals("MESSAGE"))
	{
		OnMessageReceived( parts[1]);
	}
}

String ^ Client::ReceiveData()
{
	if (!socket) return "";
	String^ res = "";
	try {
		auto b = gcnew array<Byte>(65536);//������������� ���������� ���
		int bc = socket->Receive(b, 0, 65535, SocketFlags::None);
		res = Encoding::UTF8->GetString(b, 0, bc);
		Console::WriteLine("Response: {0}", res);
		return res;
	}
	catch (...) {
		active = false;
		return nullptr;
	}
}

Client::Client(String ^ serverHost)
{
	socket = gcnew Socket(
		SocketType::Stream,
		ProtocolType::Tcp
	);
	this->serverHost = serverHost;
	socket->Connect(this->serverHost, port);
	ThreadStart^ th = gcnew ThreadStart(this, &Client::Communicate);//�������� �����
	Thread^ t = gcnew Thread(th);
	active = true;
	t->Start();//��������� �����
	if (!socket->Connected)//���� �� �����������
	{
		socket = nullptr;
		throw gcnew Exception("Error Connect");
	}
}

void Client::Enters(String ^ Number, String ^ Pin)
{
	SendData("ENTER:" + Number + ":" + Pin);
}

void Client::Remove(String ^ s)
{
	SendData("REMOVE:" + s);
}

void Client::Insert(String ^ s)
{
	SendData("INSERT:" + s);
}

void Client::SendMessage(String ^ message)
{
	SendData("Message:" + message);
}

void Client::Transfer(String ^ NumberCard, String ^ Money)
{
	SendData("TRANSFER:"+NumberCard+":"+Money);
}

void Client::Balance()
{
	SendData("BALANCE:1");
}

void Client::Stop()
{
	try
	{

		SendData("SHUTDOWN:1");
		active = false;
		if (socket)
		{
			socket->Shutdown(SocketShutdown::Both);//��������� ����������
			socket->Disconnect(false);
			socket->Close();
		}
	}catch(...)
	{

	}
}

Client::~Client()
{
	
}

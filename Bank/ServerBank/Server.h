#pragma once
using namespace System;
using namespace Net;
using namespace Sockets;
using namespace Text;
using namespace Threading;
using namespace Collections::Generic;
#using<system.dll>
using namespace System;
using namespace System::IO;

ref struct BankClient
{
	String^ Name;
	Double Balance;
	String^ NumberCard;
	String^ PinCode;
	bool on_off = false;
};
ref class ClientModel
{
	Socket^ socket;//���� �����������
	List<BankClient^>^Accounts;
	List<ClientModel^>^ Clients;//c����� ��������
	BankClient^YourAccount;
	bool Find = false;
	bool active = false;

	
public:
	ClientModel(Socket^ s, List<ClientModel^>^ clients, List<BankClient^>^Account);//����������� ������� ��������
private:
	void Rewrite();
	void ParseData(String^ req);//��������� ������
	void SendMessage(String^ msg);
	void SendData(String^ data);//���������� ������
	void Communicate();
	void FindClient(String^Number, String^Pin);
	void ShutDownClient(String^ data);//�������� ����������
	void TransferMoney(String^Card, Double coin);

	String^ ReceiveData();//�������� ������ �� ���������� ������

	void Stop();

public:
	

};

 

ref class ServerBank
{
private:
	int port = 5555;
	String^host= "127.0.0.1";

	List<BankClient^>^ Accounts;
	List<ClientModel^>^ Clients = gcnew List<ClientModel^>();//������ ��������
public:
	
	void Parse(String^s);
	void Rewrite();
	ServerBank();
	virtual ~ServerBank();

};




















/*
	property String^ name
	{
		String^ get()
		{
			return Name;
		}
		void set(String^nm)
		{
			Name = nm;
		}
	}
	property String^numberCard
	{
		String^get()
		{
			return NumberCard;
		}
		void set(String^numc)
		{
			NumberCard = numc;
		}
	}
	property String^pinCode
	{
		String^get()
		{
			return PinCode;
		}
		void set(String^pin)
		{
			PinCode = pin;
		}
	}
	property Double balance
	{
		Double get()
		{
			return Balance;
		}
		void set (Double a) {

			Balance = a;
		}

	}

*/
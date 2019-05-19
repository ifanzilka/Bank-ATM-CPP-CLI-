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

ref struct BankClient//что хранят клиенты
{
	String^ Name;
	Double Balance;
	String^ NumberCard;
	String^ PinCode;
	bool on_off = false;
};
ref class ClientModel
{
	Socket^ socket;//само подключение
	List<BankClient^>^Accounts;
	List<ClientModel^>^ Clients;//cписок клиентов
	BankClient^YourAccount;
	bool Find = false;
	bool active = false;

	
public:
	ClientModel(Socket^ s, List<ClientModel^>^ clients, List<BankClient^>^Account);//конструктор моделей коиентов
private:
	void Rewrite();
	void ParseData(String^ req);//разбираем строку
	void SendMessage(String^ msg);
	void SendData(String^ data);//отправляем строку
	void Communicate();
	void FindClient(String^Number, String^Pin);
	void ShutDownClient(String^ data);//обрываем соединение
	void TransferMoney(String^Card, Double coin);

	String^ ReceiveData();//получаям строку из полученных байтов

	void Stop();

public:
	

};

 

ref class ServerBank
{
private:
	int port = 5555;
	String^host= "127.0.0.1";

	List<BankClient^>^ Accounts;
	List<ClientModel^>^ Clients = gcnew List<ClientModel^>();//список клинетов
public:
	
	void Parse(String^s);//разбор строки с txt
	void Rewrite()
	{
		String^ fileName = "ServerBank.txt";
		StreamWriter^ sw = gcnew StreamWriter(fileName);


		for each(BankClient^ var in Accounts) {

			sw->WriteLine(var->Name + ":" + Convert::ToString(var->Balance) + ":" + var->NumberCard + ":" + var->PinCode);
		}

	}
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
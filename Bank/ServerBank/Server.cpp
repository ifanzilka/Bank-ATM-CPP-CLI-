#include"Server.h"


void ServerBank::Parse(String ^ str)
{
	
		array<String^>^ sep = { ":" };
		array<String^>^ parts = str->Split(sep, 4, StringSplitOptions::None);//разбираем полученную строку на две строки и закидываем в массив (разделяем с ':')hh
		
		BankClient^ client = gcnew BankClient;
		client->Name = parts[0];
		client->Balance = (Convert::ToDouble(parts[1]));
		client->NumberCard = parts[2];
		client->PinCode = parts[3];
	
		Accounts->Add(client);

		/*for each (BankClient ^var in Clients)
		{
			Console::WriteLine(var->Name);
			Console::WriteLine(var->Balance);
		}*/
		

		

}

void ServerBank::Rewrite()
{
	String^ fileName = "ServerBank.txt";
	StreamWriter^ sw = gcnew StreamWriter(fileName);
	

	for each(BankClient^ var in Accounts) {

		sw->WriteLine(var->Name + ":" + Convert::ToString(var->Balance) + ":" + var->NumberCard + ":" + var->PinCode);
	}
	
}

ServerBank::ServerBank()
{
	Socket^ sSocket = gcnew Socket(

		SocketType::Stream,
		ProtocolType::Tcp//протокол соединения
	);
	try
	{	
		//SortedList<String^, BankClient^>^NumberCard = gcnew SortedList<String^, BankClient^>;
		 Accounts = gcnew List<BankClient^>;
		String^ fileName = "ServerBank.txt";
		Console::WriteLine("Считываем данные клиентов с {0}...", fileName);
		StreamReader^ din = File::OpenText(fileName);

		String^ str;
		int count = 0;
		while ((str = din->ReadLine()) != nullptr)
		{
			count++;

			Console::WriteLine("line {0}: {1}", count, str);
			Parse(str);


		}
		din->Close();

		
		this->Clients = Clients;
		sSocket->Bind(
			gcnew IPEndPoint(
				Dns::GetHostEntry(host)->AddressList[0],//первый ip
				port
			));
		Console::WriteLine("Starting server");
		sSocket->Listen(10);//максимум одновременных подключений
		Console::WriteLine("Waiting for connection...");
		while (true)
		{

			Socket^cSocket = sSocket->Accept();//ждем полкючения и возвращаем клиентский сокет
			gcnew ClientModel(cSocket,Clients,Accounts);
			Console::WriteLine("There is a connection!!!");


		}

	}
	catch (Exception^ ex) 
	{
		Console::WriteLine("Что-то пошло не так... " + ex->Message);
		Console::ReadLine();
	}
	
	Console::ReadLine();
}

ServerBank::~ServerBank()
{

	//Rewrite();
};



ClientModel::ClientModel(Socket ^ s, List<ClientModel^>^ Clients, List<BankClient^>^Accounts)
{
	socket = s;
	this->Accounts = Accounts;
	this->Clients = Clients;
	Clients->Add(this);
	ThreadStart^ ts = gcnew ThreadStart(this, &ClientModel::Communicate);//выделяем поток для общения
	Thread^ t = gcnew Thread(ts);
	active = true;
	t->Start();
}

void ClientModel::Rewrite()
{
	String^ fileName = "ServerBank.txt";
	String^mas = "";

	for each(BankClient^ var in Accounts) {

		mas+=(var->Name + ":" + Convert::ToString(var->Balance) + ":" + var->NumberCard + ":" + var->PinCode+"\n");
	}

	System::IO::File::WriteAllText(fileName, mas);
}

void ClientModel::ParseData(String ^ req)
{
	if (!req || req->Trim()->Equals("")) return;
	array<String^>^ sep = { ":" };
	array<String^>^ parts = req->Split(sep, 2, StringSplitOptions::None);
	if (parts[0]->ToUpper()->Equals("ENTER"))
	{	
		array<String^>^NumberAndPin = parts[1]->Split(sep, 2, StringSplitOptions::None);
		FindClient(NumberAndPin[0], NumberAndPin[1]);
		
	}
	else if (parts[0]->ToUpper()->Equals("BALANCE"))
	{
		if(Find)
		{
			SendData("BALANCE:" +Convert::ToString (YourAccount->Balance));
		
		}
	}

	else if (parts[0]->ToUpper()->Equals("REMOVE"))
	{
		Double coin = Convert::ToDouble(parts[1]);
		if (coin <= YourAccount->Balance) 
		{
			YourAccount->Balance -= coin;
			
			SendData("MESSAGE:" + "Операция успешно выполнена!\n Текущий остаток:"+Convert::ToString(YourAccount->Balance));
		}
		else
		{
			SendData("MESSAGE:" + "Недостаточно средств на счете!\r\n");
		}
	}
	else if (parts[0]->ToUpper()->Equals("INSERT"))
	{
		Double coin = Convert::ToDouble(parts[1]);
		YourAccount->Balance += coin;
		SendData("MESSAGE:" + "Операция успешно выполнена!\n Текущий остаток:" + Convert::ToString(YourAccount->Balance)+"\r\n");
	}
	else if (parts[0]->ToUpper()->Equals("SHUTDOWN"))
	{
		ShutDownClient("");
	}
	else if(parts[0]->ToUpper()->Equals("TRANSFER"))
	{
		try {
			array<String^>^CardAndMoney = parts[1]->Split(sep, 2, StringSplitOptions::None);
			Double coin = Convert::ToDouble(CardAndMoney[1]);
			if (coin < YourAccount->Balance)
			{
				TransferMoney(CardAndMoney[0], coin);
			}
			else
			{
				SendData("MESSAGE:" + "Недостаточно средств на счете!\r\n");
			}
		}catch(Exception^ex)
		{
			Console::WriteLine(ex->Message);
		}

	}
}

void ClientModel::SendMessage(String ^ msg)
{

	for each(ClientModel^ c in Clients)//отправлям всем сокетам из списка
	{
		c->SendData("Message:" + msg);
	}

}

void ClientModel::SendData(String ^ data)
{
	try {
		if (!socket || !socket->Connected) throw gcnew Exception();//проверяем подключен ли клиент
		if (!data || data->Trim()->Equals("")) data = "\0";//проверям пустая строка или нет
		array<Byte>^ b = Encoding::UTF8->GetBytes(data);//строку в байты
		Console::WriteLine("Sending: {0}", data);
		socket->Send(b);//отпраыляем этому сокету
		Console::WriteLine("Sent");
	}
	catch (Exception^ ex)
	{
		active = false;
		Clients->Remove(this);
	}
}


void ClientModel::Communicate()
{
	if (!socket) return;
	Console::WriteLine("Starting communication");//начали общение с клиентом
	while (active) {
		Console::WriteLine("Receiving request...");//ждем команды от клиента
		auto req = ReceiveData();
		Console::WriteLine(req);
		ParseData(req);
	}
}

void ClientModel::FindClient(String ^ Number, String ^ Pin)
{

	bool find = false;
	for each (BankClient^ var in Accounts )
	{
		if(var->NumberCard==Number&&var->PinCode==Pin)
		{
			find = true;
			if (!var->on_off) {
				var->on_off = true;
				this->YourAccount = var;
				Find = true;
				Console::WriteLine("USER {0} Connected in account", var->Name);
				SendData("ENTERS:OK");
				SendData("MESSAGE:" + "Здравствуйте, " + var->Name + "\n");
				break;
				
			}
			else
			{ 
				Console::WriteLine("This account is already connected"); 
				SendData("MESSAGE:Под данынм аккаунтом уже вошли!");
				break;
			}
		}
	}
	if (!find) {
		SendData("ENTERS:NO");
	}
}

void ClientModel::ShutDownClient(String ^ data)
{
	
	try
	{
		if(this->YourAccount)this->YourAccount->on_off = false;
		
		active = false;
		Rewrite();
		if (socket)
		{
			socket->Shutdown(SocketShutdown::Both);
			socket->Disconnect(false);
			socket->Close();
			Clients->Remove(this);
		}
	}
	catch (...) {}
}

void ClientModel::TransferMoney(String ^ Card, Double coin)
{
	bool Find = false;
	for each (BankClient^ var in Accounts)
	{
		
		if (var->NumberCard == Card) {
			Find = true;
			var->Balance += coin;
			YourAccount->Balance -= coin;

			for each (ClientModel^ var in Clients)
			{
				if(var->YourAccount->NumberCard==Card)
				{
					var->SendData("MESSAGE:Получено:" + Convert::ToString(coin) + " от "+YourAccount->Name);
				}
			}
			SendData("MESSAGE:Перевод успешно выполнен!");
		}
		
	}
	if (!Find) 
	{
		SendData("MESSAGE:Перевод не выполнен (возможно неверно введена карта)");
	}

}

String ^ ClientModel::ReceiveData()
{
	
	String^ res = "";
	try {
		if (!socket || !socket->Connected) throw gcnew Exception();
		auto b = gcnew array<Byte>(65536);

		int bc = socket->Receive(b, 0, 65535, SocketFlags::None);//байты в переменную b
		res = Encoding::UTF8->GetString(b, 0, bc);//переводим строку в байты
		Console::WriteLine("Request: {0}", res);//пишем полученное сообщение в командной строке
		return res;
	}
	catch (Exception^ ex) {
		active = false;
		Clients->Remove(this);
		return "";
	}
}

void ClientModel::Stop()
{
	
}
void main()
{
	gcnew ServerBank();

}

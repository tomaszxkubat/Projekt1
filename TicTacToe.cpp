///////////////////////////////
//        Tic-Tac-Toe        //
///////////////////////////////
// Tomasz Kubat       218551 //
///////////////////////////////

#include <iostream>

using namespace std;

int Win=0;		// Czy wygrana?
int Draw=0;		// Czy remis?
int End = 0;    // Wartoœæ 1 koñczy rozgrywke 
int InLine = 3; // Iloœæ znaków w rzêdzie

void ViewBoard(char Fields[], int Size)
{
	for (int i = 1; i <= Size*Size; i++)
	{
		cout << " " << Fields[i] << " ";
		if (i % Size)       cout << "|";
		else if (i != Size*Size)
		{
			cout << endl;
			for (int i = 1; i < Size; i++)
				cout << "---+";
			cout <<"---"<< endl;
		}
		else            cout << endl;
	}
}

void IfWinner(char Fields[], char Player, int Key, int Size)
{
	Win=0;  
	int i;
	int Timer=0; // do zliczania iloœci równych sobie znaków w okreœlonej lini

	//Wiersze
	for (i = 1; i <= (Size*Size - (Size - 1)); i += Size)
	{
		for (int j = i; j <= i + Size - InLine + 1; j++)
		{
			Timer = 0;
			for (int k = 0; k < InLine; k++)
			{
				if (Fields[j+k] == Player)
					Timer++;
			}
			if (Timer == InLine)
				Win = 1;
		}
	}

	// Kolumny
	for (int j = 1; j <= (Size*(Size - InLine+1)); j += Size)
	{
		for (i = j; i < (j + Size - 1); i++)
		{
			Timer = 0;
			for (int k = 0; k < InLine; k++)
			{
				if (Fields[i + k*Size] == Player)
					Timer++;
			}
			if (Timer == InLine)
				Win = 1;
		}
	}

	// ->
	for (int j = 1; j <= (Size*(Size - InLine)+1); j += Size) //
	{
		for (i = j; i < j + Size - InLine + 1; i++)
		{
			Timer = 0;
			for (int k = 0; k < InLine; k++)
			{
				if (Fields[i + k*Size + k]==Player)
					Timer++;
			}
			if (Timer == InLine)
				Win = 1;
		}
	}

	// <-
	for (int j = Size; j <= Size*(Size - InLine+1); j += Size)
	{
		for (i = j; i >= j - Size + InLine; i--)
		{
			Timer = 0;
			for (int k = 0; k < InLine; k++)
			{
				if (Fields[i + k*Size - k] == Player)
					Timer++;
			}
			if (Timer == InLine)
				Win = 1;
		}
	}
	if (Win)
	{
		if (!Key)
		{
			ViewBoard(Fields, Size);
			cout << "\nPlayer " << Player << " WINS!\n\n";
			End = 1;
		}
	}
}

void IfDraw(char Fields[], int Key, int Size)
{
	Draw = 1;
	for (int i = 1; i <= Size*Size; i++)
		if (Fields[i] == ' ')
			Draw = 0;

	if (Draw)
		if (!Key)
	{
		ViewBoard(Fields, Size);
		cout << "\n DRAW! \n\n";
	}

}

int Minimax(char Fields[], char Player, int Size)
{
	
	int M, Mmx; // Zmienne pomocnicze funkcji Minimax
	Win = 0;
	IfWinner(Fields, Player, 1, Size);
	if (Win == 1)
		if (Player == 'X')
			return 1;
		else
			return -1;

	Draw = 0;
		IfDraw(Fields,1, Size);
		if (Draw==1)
		return 0;

		if (Player == 'X')
			Player = 'O';
		else
			Player = 'X';

		if (Player == 'O')
			Mmx = 10;
		else
			Mmx = -10;

	for (int i = 1; i <= Size*Size; i++)
		if (Fields[i] == ' ')
		{
			Fields[i] = Player;
			M = Minimax(Fields, Player, Size);
			Fields[i] = ' ';
			if (((Player == 'O') && (M < Mmx)) || ((Player == 'X') && (M > Mmx)))
				Mmx = M;
		}
	return Mmx;
}

int Computer(char Fields[], int Size)
{
	int Move, i, M, Mmx;

	Mmx = -10;
	for (i = 1; i <= Size*Size; i++)
	{
		if (Fields[i] == ' ')
		{
			Fields[i] = 'X';
			M = Minimax(Fields, 'X', Size);
			Fields[i] = ' ';
			if (M > Mmx)
			{
				Mmx = M; Move = i;
			}
		}
	}
	return Move;
}

void Move(char Fields[], char &Player,int Size)
{
	int r;
	ViewBoard(Fields,Size);
	if (Player == 'O')
	{
		cout << "\nHUMAN CHOICE : ";
		cin >> r;
		if ((r >= 1) && (r <= Size*Size) && (Fields[r] == ' '))
		{
			Fields[r] = Player;
		}
		Player = 'X';
	}
	else
	{
		r = Computer(Fields,Size);
		cout << "\nCOMPUTER CHOICE : " << r << endl;
		if ((r >= 1) && (r <= Size*Size) && (Fields[r] == ' '))
		{
			Fields[r] = Player;
		}
		Player = 'O';
	}
	cout << "---------------------------\n\n";
	
}
int main()
{
	char Player; // Który gracz?
	char Choice; // Zmienna obs³uguj¹ca pêtle
	do
	{
		int Size; //rozmiar tablicy(szerokoœæ lub wysokoœæ)
		cout << "=================\n"
			"=  TIC-TAC-TOE  =\n"
			"=================\n\n"
		"PODAJ ROZMIAR: ";
		cin >> Size;
		cout << endl;
		cout << "ILE W LINI?: ";
		cin >> InLine;
		cout << endl;


		char *Fields = new char[Size*Size + 1]; //Tablica dynamiczna typu char w której znajduj¹ siê elementy pól planszy
		
		for (int i = 1; i <= Size*Size; i++) Fields[i] = ' ';
		Player = 'O';


		while (Win==0 && Draw==0) 
		{
			system("cls");
			cout << "=================\n"
					"=  TIC-TAC-TOE  =\n"
				    "=================\n\n";
			Move(Fields, Player,Size);
			IfWinner(Fields, 'X',0,Size);
			IfWinner(Fields, 'O',0,Size);
			IfDraw(Fields,0,Size);
			if (End) 
				break;
		}
		Win = Draw = End= 0;

		cout << "TRY AGAIN? (Y/N) : ";
		cin >> Choice;
		cout << "\n\n\n";

		delete[] Fields;

	} while ((Choice == 'Y') || (Choice == 'y'));

	return 0;
}

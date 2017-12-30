#include <iostream>
using namespace std;
char symbol(int x)
{
	switch(x){
		case 1 : // 1 refers to computer
			return 'O';
		case 0 :
			return ' ';
		case -1 : // -1 refers to player
			return 'X';		

	}
}
void draw(int board[],int n)
{
	cout<<" "<<symbol(board[0])<<" | "<<symbol(board[1])<<" | "<<symbol(board[2])<<endl;
	cout<<"-----------"<<endl;
	cout<<" "<<symbol(board[3])<<" | "<<symbol(board[4])<<" | "<<symbol(board[5])<<endl;
	cout<<"-----------"<<endl;
	cout<<" "<<symbol(board[6])<<" | "<<symbol(board[7])<<" | "<<symbol(board[8])<<endl;

}
int win(int board[],int n)
{
	int checker[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
	for(int i=0;i<8;i++)
	{
		if(board[checker[i][0]] != 0 && board[checker[i][0]]==board[checker[i][1]] && board[checker[i][0]]==board[checker[i][2]])
			return board[checker[i][2]];
	}
	return 0;
}
int minimax(int board[], int n, int human_player_symbol_digit )
{
	if(win(board,9))
		return (win(board,9)*human_player_symbol_digit);//-1 is multiplied because it is imitaing human
	//the above condition is base condition of recursion
	int move=-1;
	int score=-2;
	int computedscore;
	for(int i=0;i<9;i++)
	{
		if(board[i]==0)
		{
			board[i]=human_player_symbol_digit;//now computer sets its value what human would have done
			//in next step again as computer its checking 
			//this recursion goes deep until a favourable state is found
			computedscore=-minimax(board,n,human_player_symbol_digit*-1);
			if(computedscore>score)
			{
				score=computedscore;
				move=i;
			}
			board[i]=0;
		}
	}
	if(move==-1)
		return 0;
	else
		return score;
}

void computermove(int board[],int n)
{
	int move=-1; // this decides where computer is placing X if it is a human
	int score=-2;// computer will give as -ve as because it is playing as human but for itself max +ve
	int computedscore;
	for(int i=0;i<9;i++)
	{
		if(board[i]==0)
		{
			board[i]=1;//1 means computer fixed its posn and then checking in next step as next move of human
			computedscore= - minimax(board,9,-1);//-1 is passed because it is playing as human and for human check symbol 
			//there is minus sign in minimax because it return score of -2 always
			board[i]=0;
			if(computedscore > score)
			{
				score=computedscore;
				move=i;
			}
			

		}
	}
	board[move]=1;//1 because it is 
}
void humanmove (int board[],int n)
{
	cout<<"please choose the only the empty spaces"<<endl;
	
	cout<<"enter move number";
	int move=0;
	do{
		start :
	cout<<"input move [0...8]"<<endl;
	cin>>move;
	if(board[move] != 0)
	{
		cout<<"already occupied"<<endl;
		goto start;
	}
    }while(move>=9 || move<0 && board[move]==0);

board[move]=-1;// -1 bcoz human is playing check symbol
}
int main()
{
	int board[9]={0,0,0,0,0,0,0,0,0};
	cout<<"Computer is O and You are X"<<endl;
	cout<<"for first chance Press 1 and for second press 2 "<<endl;
	int chance=0;
	cin>>chance;
	for(int i=0;i<9 && win(board,9)==0;i++)
	{
		if((chance+i)%2==0)
			computermove(board,9);
		else
		{
			draw(board,9);
			humanmove(board,9);
		}
	}
	switch(win(board,9))
	{
		case -1 :
			cout<<"you win"<<endl;
			break;
		case 1 :
			draw(board,9);cout<<endl;
			cout<<"you lose"<<endl;
			break;
		case 0 :
			cout<<"Match is draw"<<endl;
			break;		
	}
}

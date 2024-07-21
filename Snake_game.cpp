#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
bool GameOver;
const int height=20;
const int width = 20;
int x,y,eggX,eggY,score;
int tailX[100],tailY[100];
int ntail;
enum direction {STOP=0,LEFT,RIGHT,UP,DOWN};
direction dir;

void Setup(){
  GameOver=false;
  dir=STOP;
  x=width/2;
  y=height/2;
  eggX = rand() % width;
  eggY = rand() % height;
  score=0;
}
void Draw(){
   //system("cls");  //(clears screen and outputs fresh)
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0}); //(rewrites on same console) (decreases flickering)
  for(int i=0;i<width+2;i++)  cout<<"#";
  cout<<endl;

  for(int i=0;i<height;i++)
  {
    for(int j=0;j<width;j++)
    {
        if(j==0) cout<<"#";
        if(i==y && j==x) cout <<"O";
        else if(i== eggY && j==eggX) cout<<"0";
        else
        {
            bool print = false;
            for(int k=0;k< ntail;k++){
                
                if(tailX[k]==j && tailY[k]==i){
                  cout<<"o";
                  print =true;
                }
            }
            if(!print) 
               cout<<" ";
        }
        if(j==width-1) cout<<"#";
    }
    cout<<endl;
  }

  for(int i=0;i<width+2;i++)  cout<<"#";
  cout<<endl; 
  cout<<"Score="<<score<<endl;
  
}
void Input()
{
   if (_kbhit())
	{
		switch (_getch())
        {
        case 'a':
           dir=LEFT;
           break;
        case 'd':
           dir=RIGHT;
           break;
        case 'w':
           dir=UP;
           break;
        case 's':
           dir=DOWN;
           break;
        case 'x':
           GameOver = true;
           break;
    }
 }
}
void Logic(){
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]= x;
    tailY[0]= y;
    for(int i=1;i<ntail;i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
  switch (dir){
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
  }
  //if(x > width || x < 0 || y > height || y < 0) 
   //   GameOver = true;
 
  if(x>=width) x=0;
  else if(x<0) x=width-1;

  if(y>=height) y=0;
  else if(y<0) y=height-1;

  for(int i=0;i<ntail;i++){
    if(tailX[i]==x && tailY[i]==y)
       GameOver = true;
  }
  if( x==eggX && y==eggY ){
    score+=1;
    eggX = rand() % width;
    eggY = rand() % height;
    ntail++;
  }
}
int main(){
    Setup();
    while(!GameOver){
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}
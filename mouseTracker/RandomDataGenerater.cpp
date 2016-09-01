#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <vector>
#include <fstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int limit =25000; 
int xBoundary=50;
int yBoundary=50;


bool isInBound(int x, int y){
	if(x < 0  || x > xBoundary) return false;
	if(y < 0  || y > yBoundary) return false;
	return true;
	
}


int main(int argc, char** argv) {
	srand (time(NULL));
	ofstream output ("randomData.txt");
//	output<<limit<<endl;
	int pathCounter = 0;
	int peopleCounter = 0;
	while(peopleCounter <limit){
		int startX=rand()%xBoundary+1;
		int startY= rand()%yBoundary+1;
		pathCounter = 0;
		vector<int> XCoordinates;
		vector<int> YCoordinates;
		XCoordinates.push_back(startX);
		YCoordinates.push_back(startY);
		int x=startX;
		int y=startY;
		while(true){
			
			bool canContinue = (rand()%15 ==1 && pathCounter >4) || pathCounter>20 ? false : true;
			if(!canContinue){
				peopleCounter ++;
				break;
			}
	
			int deltaX =rand()%15+5;
			int deltaY = rand()%15+5;
			
			int xDirection = rand()%2;
			int yDirection = rand()%2;
			
			if(xDirection){
				x = x+deltaX;
				if(!isInBound(x,y)){
				x-=2*deltaX;
				}
			}else {
					x = x-deltaX;
				if(!isInBound(x,y)){
				x+=2*deltaX;
				}
			}
			if(yDirection){
				y = y+deltaY;
				if(!isInBound(x,y)){
				y-=2*deltaY;
				}
			}else {
					y = y-deltaY;
				if(!isInBound(x,y)){
				y+=2*deltaY;
				}
			}  
			XCoordinates.push_back(x);
			YCoordinates.push_back(y);
			pathCounter++;	
		}	
		int size = XCoordinates.size();
		for(int i= 0 ; i  < size ; i++){
			if(i==size-1) output<<XCoordinates[i]<<" " <<YCoordinates[i];
			else output<<XCoordinates[i]<<" " <<YCoordinates[i]<<" ";
			
		}
		output<<endl;
		//output<<-1<<endl;
		
		
		
	}
	
	
	return 0;
}

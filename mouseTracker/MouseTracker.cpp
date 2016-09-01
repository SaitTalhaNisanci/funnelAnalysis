#include<bits/stdc++.h>

/*
This program implements an algorithm to find common paths from a data of video recorder from a web page.
This program assumes that at most 
An example of how to run the program :
MouseTracker.exe inputData.txt 20
where MouseTracker.exe is the name of the executable 
inoutData,txt is the data that should give the input for the program.
20 is the size of the grid on which the result is going to be drawn.
*/
using namespace std;
struct user;
int const maxSize =50;// the screen is assumed to be divided into 10 000 pieces
int base = 53; // base for enumarating paths with hash
long long base2 = 402653189; // base for hashing paths.
long long base3= 786433; // base for reverseHashing
long long mod = 1610612741;
int amount_of_people;
map<long long,long long> reverseHash; 
int amounts[15];//amount[i] stores how many elements used of length i.
int upLimit = 15; //upLimit for each length of path.
map<long long,long long> mp; // first parameter: hash value, second parameter: how many times the hash was found
int gridSize=0; // gives the size of the grid. Matrix griDsize*gridSize
struct user{
	vector<long long> paths;
}users[800000];

//This compare method sorts the array based on the second elements of pairs.
//pair<int,int> p1 where
//the first parameter =the hash value
//the second parameter= the amount 

//In order to sort the paths in descending order of the length when their amount is the same, comment out the code.
bool cmp(pair<long long,long long> p1,pair<long long,long long> p2){
	if(p1.second>p2.second) return true;
	if(p1.second==p2.second){
		/*
		long long currentHash =p1.first; 
		long long value= reverseHash[currentHash];
		int person = value/base3/base3%base3;
		int left = value/base3%base3;
		int right = value%base3;
		int l1 = right-left+1;
		long long currentHash2 =p2.first; 
		long long value2= reverseHash[currentHash];
		int person2 = value2/base3/base3%base3;
		int left2 = value2/base3%base3;
		int right2 = value2%base3;
		int l2 = right2-left2+1;
		if(l1 > l2) return true;
		*/	
	}
	return false;
}

//gets the x of the point from which the line starts.
int getX1(long long hashValue,int base){
	return hashValue/base/base/base%(base);
}
//gets the y of the point from which the line starts.
int getY1(long long hashValue,int base){
	return hashValue/base/base%(base);
}
//gets the x of the point to which the line goes
int getX2(long long hashValue,int base){
	return hashValue/base%(base);
}
//gets the y of the point to which the line goes.
int getY2(long long hashValue,int base){
	return hashValue%(base);
}

//The input file should be given as the second argument and the gridSize should be given as the third argument while executing the program.
 
int main(int argc, char** argv) {
	
	
	if(argc>2){
		istringstream ss(argv[2]);
		ss>>gridSize;
	}
	//checks whether the gridSize is valid. if not fixes it. 
	if(gridSize<2) gridSize=2;
	if(gridSize > maxSize) gridSize=maxSize;
	double divider = (double)maxSize/gridSize;//divider is used to convert the points to the given gridSize.
	
	FILE *in = fopen(argv[1],"r");
	FILE *out = fopen("output2.txt","w");
	fscanf(in,"%d",&amount_of_people); 	
	int previousX,previousY;
	//This for loop uses hashing to number the paths. Two paths are considered to be different if their length differs or their starting and ending points are different.
	for(int i = 0 ; i < amount_of_people;i++){
		int counter =0;
		while(true){
			int x,y;
			fscanf(in,"%d",&x);
			if(x==-1) break;
			fscanf(in,"%d",&y);	
			x/=divider;
			y/=divider;
			if(counter) users[i].paths.push_back(previousX*base*base*base+previousY*base*base+x*base+y);
			previousX=x;
			previousY=y;
			counter++;
  		}
	}
	for(int i = 0 ; i <  amount_of_people ; i++){	
		int currentSize = users[i].paths.size();
			for(int start = 0 ; start < currentSize;start++ ){
				long long currentHash = 0 ;
				for(int finish = start; finish < currentSize && finish<start+6 ;finish++ ){
					currentHash*=base2;
					currentHash%=mod;
					currentHash+=1LL*users[i].paths[finish];
					currentHash%=mod;	
					mp[currentHash]++;
				if(reverseHash.find(currentHash) == reverseHash.end())
				reverseHash[currentHash] = base3*base3*i+base3*start+finish;
				}	
			}
	}
	vector<pair<long long, long long> > mapcopy(mp.begin(), mp.end()); //copies the elements of the map to a vector called mapcopy to be able to sort them.
	sort(mapcopy.begin() , mapcopy.end(),cmp);//sorts the array.
	int counter2 = 0;
	 printf("[");
	for(int i = 0 ; i <  mapcopy.size(); i++){ 
		long long currentHash =mapcopy[i].first; 	
		long long value= reverseHash[currentHash];long long person = value/base3/base3%base3;
		long long left = value/base3%base3; long long right = value%base3;
		if(right-left<0) continue;
		amounts[right-left]++;
		if(amounts[right-left]>upLimit) continue;
		if(mapcopy[i].second<3) continue;
		counter2++;
		if(counter2>1)	printf(",[%d,",mapcopy[i].second);
		else printf("[%d,",mapcopy[i].second);
		int counter3= 0;
		for(int j = left ;  j<=right ; j++){
			counter3++;
			int hash = users[person].paths[j] ;
			int x1 = getX1(hash,base);int y1 = getY1(hash,base);
			int x2 = getX2(hash,base);int y2 = getY2(hash,base);
			if(left==right)printf("%d,%d,%d,%d",x1,y1,x2,y2);
			else if(j==left)printf("%d,%d,%d,%d,",x1,y1,x2,y2);
			else if(j==right) printf("%d,%d",x2,y2);
			else printf("%d,%d,",x2,y2);
		}
		printf(",%d]",counter3);
		
		
	}

	 printf("]");

	
	return 0;
}

#include<bits/stdc++.h>


using namespace std;
struct user;
#define ss second.second
#define sf second.first


int deviceFilter = 1; // show only type of 1
int userFilter = 1;
int sourceFilter = 1;
int base1 = 101;// base for enumarating paths with hash
long long base2 = 402653189; // base for hashing paths.
long long base3= 786433; // base for hashing to get which person and what interval.
long long mod = 1610612741;
int totalMoneyForSources[3];

struct user{
	int deviceType; // 0 mobile ,  1  laptop-pc , 2 tablet
	int source; //0 google, 1 social media, 2 others
	int userType; //0 new , 1 old
	int spentMoney;
	vector<long long> paths; //the hash value of going from a page to another page
}users[500000];
map<long long,pair<long long,long long> > mp; // first arg -> hash value , second arg ->amount 
map<int,string> convertions;
map<long long,long long> reverseHash;

bool cmp(pair<long long,pair<long long,long long> > p1,pair<long long,pair<long long,long long> > p2){	

	if(p1.ss>p2.ss) return true;	
	else if(p1.ss<p2.ss) return false; 
	else {	
		if(p1.sf > p2.sf) return true;
		else if(p1.sf<p2.sf) return false;  
		else {
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
				else return false;
		}
	}	
			


}

int getCurrentPageID(int hash,int base){
	return hash/base%base;
}
int getPreviousPageID(int hash,int base){
	return hash%base;
}


int main(int argc, char** argv) {
	convertions[0] = "Home";
	convertions[1] = "Product";
	convertions[2] = "Categories";
	convertions[3] = "Information";
	convertions[4] = "Profile";
	convertions[5] = "Settings";
	convertions[6] = "Contact";
	convertions[7] = "LogIn";
	convertions[8] = "SignUp";
	convertions[9] = "Cart";
	
	
	FILE *in = fopen("funnelRandomData.txt","r");
	FILE *out = fopen("funnelAlgorithmOutput.txt","w");
	int amount_of_people;
	fscanf(in,"%d",&amount_of_people);
	
	for(int i = 0 ; i < amount_of_people;i++){
		int counter = 0;
		int previousPageID;
		while(true){
			int currentPageID;
			fscanf(in,"%d",&currentPageID);
			if(currentPageID==-1){
				int money;
				int userType,deviceType,source;
				
				 fscanf(in,"%d%d%d%d",&money,&userType,&deviceType,&source);
				 users[i].spentMoney=money;
				 users[i].userType=userType;
				 users[i].deviceType=deviceType;
				 users[i].source=source;
				 break;
			}
			if(counter){
				users[i].paths.push_back(1LL*currentPageID*base1+previousPageID);
			}else {
				//from A-A is used to be able to hash the path of length 0.
				users[i].paths.push_back(1LL*currentPageID*base1+currentPageID);
			}
			previousPageID=currentPageID;
			counter++;
		}
	}
	
		for(int i = 0 ; i <  amount_of_people ; i++){	
			if(users[i].deviceType !=deviceFilter ||  users[i].userType != userFilter || users[i].source !=sourceFilter) continue;
			int currentSize = users[i].paths.size();
			long long currentHash = 0 ;
	
		for(int start = 0 ; start < currentSize;start++ ){
			
			
				currentHash*=base2;
				currentHash%=mod;
				currentHash+=1LL*users[i].paths[start];
				currentHash%=mod;
				
				if(start!=currentSize-1) continue;	
				
				mp[currentHash].first++;
				mp[currentHash].second+=users[i].spentMoney;
			if(reverseHash.find(currentHash) == reverseHash.end())
			// since we take the whole interval for a person we emit the base*0 in the below equation. the interval is (0,size-1)
			reverseHash[currentHash] = base3*base3*i+start;
			
		}
	}

	/*
	for(int i = 0 ; i <  amount_of_people ; i++){	
	int currentSize = users[i].paths.size();
		for(int start = 0 ; start < currentSize;start++ ){
			long long currentHash = 0 ;
			for(int finish = start; finish < currentSize  ;finish++ ){
				currentHash*=base2;
				currentHash%=mod;
				currentHash+=1LL*users[i].paths[finish];
				currentHash%=mod;
				if(finish!=currentSize-1) continue;	
				cout<<i<<endl;
				mp[currentHash]++;
			if(reverseHash.find(currentHash) == reverseHash.end())
			reverseHash[currentHash] = base3*base3*i+base3*start+finish;
			}	
		}
	}
	*/
	vector<pair<long long, pair<long long,long long> > > mapcopy(mp.begin(), mp.end()); //copies the elements of the map to a vector called mapcopy to be able to sort them.
	sort(mapcopy.begin() , mapcopy.end(),cmp);//sorts the array.

	for(int i = 0 ; i <  mapcopy.size(); i++){ 
	
		long long currentHash =mapcopy[i].first; 	
		long long value= reverseHash[currentHash];long long person = value/base3/base3%base3;
		long long left = value/base3%base3; long long right = value%base3;
		if(right-left<0) continue;
		if(mapcopy[i].second.first<1) continue;
		fprintf(out,"money: %d ",mapcopy[i].second.second);
		fprintf(out,"amount: %d path: ",mapcopy[i].second.first);	
		for(int j = left ;  j<=right ; j++){
		
			int hash = users[person].paths[j] ;
			int currentPageID = getCurrentPageID(hash,base1);
			int previousPageID = getPreviousPageID(hash,base1);

			if(currentPageID==previousPageID) fprintf(out,"%s ",convertions[currentPageID].c_str());
			else fprintf(out,"%s-%s ",convertions[previousPageID].c_str(),convertions[currentPageID].c_str());
		}
		fprintf(out,"\n");
		
		
	}	
	
	
	
	
	return 0;
}

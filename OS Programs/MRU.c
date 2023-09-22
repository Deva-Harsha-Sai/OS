//MRU
#include<stdio.h>
int main(){
	int n = 4,i,j,hit=0,pagefault=0;
	int PL[10]={1,2,3,4,5,6,7,4,2,1};
	int FR[4]={-1,-1,-1,-1};
	for(i=0;i<10;i++){
		for(j=0;j<n;j++){
			if(FR[j]==-1){
				break;
			}
			else if(FR[j]==PL[i]){
				hit++;
				break;
			}
		}
		if(FR[j]==-1){
			pagefault++;
			FR[j]=PL[i];
			continue;
		}
		else if(j==n){
			pagefault++;
			int loc;
			for(loc=0;loc<n;loc++){
				if(FR[loc]==PL[i-1]){
					FR[loc]=PL[i];
					break;
				}
			}
		}
	}
	printf("%d",hit);
}

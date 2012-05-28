#include <stdio.h>
#include <math.h>

using namespace std;

unsigned long long pascal_triangle[2300][2300];	
long long int K;
const unsigned long long INF = (unsigned long long) 10000000000LL;
int count = 0;
#define MAX 2100

unsigned long long max(unsigned long long x,unsigned long long y){
	return (x>y)?x:y;
}

unsigned long long min(unsigned long long x,unsigned long long y){
	return (x<y)?x:y;
}

/** calcula las primeras MAX filas del triangulo de pascal */

void pascal(int limit){
	while(count < limit){
		pascal_triangle[count][0] = 1;
		pascal_triangle[count][count] = 1; 
		for(int i = 1; i < count; i++){ // Seteo un elemento INF en caso de que haya overflow
			pascal_triangle[count][i] =  min(INF, pascal_triangle[count-1][i-1] + pascal_triangle[count-1][i]);
		}
		count++;
	}	
}

int getLimit(){
	int left=1, right = MAX, med;
	while(right-left>1){
		med = (right+left)/2;
		if((med*(med-1)*(med-2))/6 <= K){
			left = med;
		} else {
			right = med;
		}
	}
	return med;
}


int main(){
	
	#ifdef MISTDIN
        freopen("entrada.in","r",stdin);
    #endif

	while(scanf("%lld",&K)&&K!=-1){
		unsigned long long cantMenoresOIgualesK = 0;
		
		if(K < 6) { // Casos triviales que rompen el approach
			printf("%lld\n", (2*(K-2))+1);
			continue;
		} 
		unsigned long long tmp;

		/** cantidad de elementos menores o iguales a K en las diagonales de comb(n,1) y comb(n,n-1) **/
		tmp = (unsigned long long) max((2 * (K-2)) + 1, 0);
		cantMenoresOIgualesK += tmp;
		
		/** cantidad de elementos menores o iguales a K en las diagonales de comb(n,2) y comb(n,n-2) **/
		tmp = (unsigned long long) max((( 1 + (unsigned long long) (sqrt((long double) (1 + 8 * K))) )/2), 0); // (1 + sqrt(1 + 8K))/2
		tmp = 2*(tmp-4)+1;
		cantMenoresOIgualesK += tmp; 
		
		if(K > 19){ // A partir de K=20 hay elementos en las diagonales de los comb(n,m) con m>=3
			
			int limit = getLimit();		
			/** calculo las primeras MAX filas del triangulo de pascal **/
			pascal(limit+10);
			/** 
			* Recorro las diagonales de comb(n,m) para m >= 3
			**/
			int menores = 0; 
			for(int k = 3; k < MAX/2; k++){
				menores += pascal_triangle[2*k][k] <= K;
				/** 
				 * Si el primer elemento de la diagonal del comb(n,m) es mayor que K entonces a partir de ahi no
				 * hay mas elementos menores o iguales a K en las demas diagonales
				**/
				if (pascal_triangle[2*k][k] > K) break; 
				
				for(int i = 2*k+1; i < MAX; i++){
					menores += 2 * (pascal_triangle[i][k] <= K);
					if (pascal_triangle[i][k] > K) break;
				}
			}
			cantMenoresOIgualesK += menores;
		}
		printf("%llu\n", cantMenoresOIgualesK);	
	}
	return 0;
}

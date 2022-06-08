#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

char* itoa(int val,char* buf,size_t radix){
    assert(buf != 0);
    char* p = buf;
    if(val < 0){
        *p++ = '-';
        val = -1 * val;
    }

    int a = 0;
    do{
        a = val % radix;
        val /= radix;
        if(a > 9){
            *p++ = (char)(a-9+'a');
        }else{
            *p++ = (char)(a + '0');
        }
    }while(val != 0);

    *p = '\0';
    //reverse
    size_t len = strlen(buf);
    int left = 0;
    if(*buf == '-' || *buf == '+'){
        left++;
    }
    int right = len - 1;
    while(left < right){
        swap(buf[left++],buf[right--]);
    }
    return buf;
}

int detSym(char c) {
	if (c == '+')
		return 1;
	if (c == '-')
		return 2;
	if (c == '^')
		return 3;
	if (c == '/')
		return 4;
	if (c == '*')
		return 5;
	if (c == '%')
		return 6;
	if (c == '>')
		return 7;
	if (c == '<')
		return 8;
}

int calculator(char Num1[], char Num2[], int sym) {
	int N1 = 0;
	int N2 = 0;
	N1 = atoi(Num1);
	N2 = atoi(Num2);
	if (sym == 1)
		return(N1 + N2);
	if (sym == 2)
		return(N1 - N2);
	if (sym == 3)
	{	
		int answer = N1;
		for (int i = 1; i <= N2; i++){
			answer = answer * N1;
		}
		return answer;
	}
	if (sym == 4)
		return(N1 / N2);
	if (sym == 5)
		return(N1 * N2);
	if (sym == 6)
		return(N1 % N2);
	if (sym == 7)
		return(N1 >> N2);
	if (sym == 8)
		return(N1 << N2);

}

void main() {
	void* context = zmq_ctx_new();
	void* requester = zmq_socket(context, ZMQ_REP);
	int rc = zmq_bind(requester, "tcp://*:5555");
	assert(rc == 0);

	char Buffer[5] = { 0 };

	zmq_recv(requester, &Buffer, 5, 0);
	int tmp = 0;
	if (atoi(Buffer) != 12345)
		tmp = 1;
	if (tmp == 0) {
		printf("CONNECT\n");
		zmq_send(requester, "CONNECT", 7, 0);
		for (;; zmq_sleep(0.5)) {
			int tmp1 = 0;
			char tmp2 = NULL;
			char NumINT1[100] = { NULL };
			char NumINT2[100] = { NULL };
			char MASS[100] = { NULL };
			zmq_recv(requester, &MASS, 100, 0);
			int num = 0;
			for (int i = 0, j = 0; i < (100 - j) && MASS[i] != '\0'; i++) {
				if (ispunct(MASS[i])) {
					tmp1 = 1;
					tmp2 = MASS[i];
					j++;
					if (isdigit(MASS[i + 1])) {
						tmp1 = 2;
						j = 0;
					}
				}
				if (isdigit(MASS[i]) && tmp1 == 0)
					NumINT1[i] = MASS[i];
				if (isdigit(MASS[i]) && tmp1 == 2) {
					NumINT2[j] = MASS[i];
					j++;
				}

			}
			
			int result = calculator(NumINT1, NumINT2, detSym(tmp2));
			char Buf2[20] = { NULL };
			itoa(result, Buf2, 20);
			zmq_send(requester, Buf2, 20, 0);
		}


	}
}

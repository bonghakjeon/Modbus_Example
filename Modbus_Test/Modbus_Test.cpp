#include <stdio.h>
// #include <string.h> memset 함수 사용하기 위해

void test_send(char * buf);
int recv(char * buf, int size, char * buf2);
void test_recv(char * buf, int size, char * buf2);

int main(void)
{
	char obuf[8];
    char ibuf[8];

	test_send(obuf);

	int i;
	// int j;

	for (i = 0; i < sizeof(obuf); i++)
	{
		printf("obuf의 %d번째 데이터 : %d\n", i+1, obuf[i]);
	}
	printf("\n");

	test_recv(ibuf, sizeof(ibuf), obuf);
	
	return 0;
}

void test_send(char * buf)
/* 데이터를 전송하는 함수 test_send의 정의 */
{
	// make modbus packet (데이터 패킷)
	buf[0] = 0x1;              // slave ID
	buf[1] = 0x3;              // data 읽기 명령(func code)
	buf[2] = 0; buf[3] = 0;    // 0번지 부터
	buf[4] = 0; buf[5] = 10;   // 10개의 값을 읽음.
	buf[6] = 64;               /* 체크썸 2bytes CRC high에서 C의 아스키코드값 앞자리(6)와 
							      h의 아스키코드값 뒷자리(4)를 의미함. */     
	buf[7] = 68;               /* 체크썸 2bytes CRC low에서 C의 아스키코드값 앞자리(6)와
							      l의 아스키코드값 뒷자리(8)을 의미함. */

	// buf[];      1. 둘다 나중에 (1, 2)
	// tcp_send(buf, buf_size);  둘다 나중에(1, 2)
}

int recv(char * buf, int size, char * buf2)
/* 데이터를 수신하는 함수 recv의 정의
   성공 시 수신한 바이트 수 반환 */
{
	buf[size] = { 0, };  // buf 배열 모두 0으로 초기화 
	// 또는 memset(buf, 0, sizeof(buf)); 이렇게 해도 됨
	buf[0] = buf2[0];
	buf[1] = buf2[1];
	buf[2] = buf2[2];
	buf[3] = buf2[3];
	buf[4] = buf2[4];
	buf[5] = buf2[5];
	buf[6] = buf2[6];
	buf[7] = buf2[7];

	return sizeof(buf);
}

void test_recv(char * buf, int size, char * buf2)
{

	int ret = recv(buf, sizeof(buf), buf2);
	// int i;

	// decoding
	// for (int i = 0; i < ret; i++)
	
    printf("ibuf의 1번째 데이터 : %d\n", buf[0]);
	printf("ibuf의 2번째 데이터 : %d\n", buf[1]);
	printf("ibuf의 3번째 데이터 : %d\n", buf[2]);
	printf("ibuf의 4번째 데이터 : %d\n", buf[3]);
	printf("ibuf의 5번째 데이터 : %d\n", buf[4]);
	printf("ibuf의 6번째 데이터 : %d\n", buf[5]);
	printf("ibuf의 7번째 데이터 : %d\n", buf[6]);
	printf("ibuf의 8번째 데이터 : %d\n", buf[7]);
}
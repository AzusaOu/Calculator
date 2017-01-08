#include <stdio.h>
#include <math.h>

#define LEN 16

/* If the facility cannot work with "pow()", this may help.
int intPow(int a, int x)
{
    int i;
    for(i=0; i<x-1; i++)
        a *= a;
    return a;
}
*/

int str2num(char s[], int len)
{
  int i;
  int result = 0;
  for(i=0; i<len; i++)
  {
    result += s[i] * (int)pow(10, len-i-1);
  }
  return result;
}

void serial_num2str(int num, int len)
{
	int i, tmp;
	char asc2[10];
	for(i=0; i<10; i++)
		asc2[i] = i+48;
	for(i=0; i<len; i++)
	{
		tmp = num / pow(10, len-i-1);

		// >>> This should be changed according to your needing.
		printf("%c", asc2[tmp]);
		// <<< In STM32, it should act as putting a character on the LCD and serial terminal.

		num -= tmp * pow(10, len-i-1);
	}
}

int calit(char equation[], int len)
{
	int result = 0;
	int sum[len];
	int i, count = 0, minus = 0, iSum = 0;
	char tmp[len];

    // >>> When it comes to the real equipments, be sure the vars (numbers only) are 1..9 and delete this block.
	for(i=0; i<len; i++)
	{
		if(equation[i] >= 48 && equation[i] <= 57)
			equation[i] -= 48;
	}
	// <<<


    putchar("\n");
	for(i=0; i<len; i++)
        sum[i] = 0;

	for(i=0; i<len; i++)
	{
		if(equation[i] <= 9 && equation[i] >= 0)
		{
			tmp[count] = equation[i];
			++count;
		}
		else
		{
		    if(i == len-1)
                count--;
			sum[iSum] = str2num(tmp, count);
			++iSum;
			count = 0;
		}
	}


	int countx = 0;
	for(i=0; i<len; i++)
	{
		if(equation[i] > 9)
		{
			++countx;
			switch(equation[i])
			{
				case '-':
					sum[countx] = 0 - sum[countx];
					break;
				case 'X':
					sum[countx] *= sum[countx-1];
					sum[countx-1] = 0;
					break;
				case '/':
					sum[countx] = sum[countx-1] / sum[countx];
					sum[countx-1] = 0;
					break;
				default:
					break;
			}
		}
	}


	for(i=0; i<len; i++)
	{
	    printf("%d ", sum[i]);
		result += sum[i];
	}
	return result;
}

int duoshaowei(int num)
{
    int count = 0;
    while(num != 0)
    {
        num /= 10;
        ++count;
    }
    return count;
}

int main()
{
	char getStr[LEN+1];
	int i, equLen = 0;
	for(i=0; i<LEN+1; ++i)
        getStr[i] = '@';

    // >>> Use the correct way to get characters of equation and transform them into string.>>> 
	scanf("%s", getStr);
	// <<< Mostly, we get it with 9X9 keyboard.

	while(getStr[equLen] != '@')
    {
        ++equLen;
    }
    equLen += 1;
	getStr[equLen-1] = '+';
	int a = calit(getStr, equLen);
	// >>> Test script. Delete it any time.
	printf("= %d\n\n", a);
	// <<<
	serial_num2str(a, duoshaowei(a));
	return 0;
}

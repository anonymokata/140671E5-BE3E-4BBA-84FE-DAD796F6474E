//
// Created by xiuqi on 1/25/17.
//

#include "roman.h"
#include "string.h"
#include "stdlib.h"

/* ERROR MESSAGES */

static char error_numa_wrong_input[100]="ERROR: first number input illegal!";
static char error_numb_wrong_input[100]="ERROR: second number input illegal!";
static char error_result_overflow[100]="ERROR: result is out of roman range!";

/* main function*/

char* addRomanNumbers(char* numA,char* numB,int isMinus){

    size_t lenA = strnlen(numA,14);
    size_t lenB = strnlen(numB,14);
    if(lenA > 13)return error_numa_wrong_input;
    if(lenB > 13)return error_numb_wrong_input;

    int a = convertRomanToInteger(numA);
    int b = convertRomanToInteger(numB);
    if(a < 1) return error_numa_wrong_input;
    if(b < 1) return error_numb_wrong_input;
    int result = isMinus?b - a:a + b;
    if(result < 1 || result > 3999)return error_result_overflow;

    return convertIntegerToRoman(result);
}

/* Convert Roman to integer */
/* Scan the Roman number from start to end, 
when the digits don't decend or too much continuous character
then return -1 as fail*/
int convertRomanToInteger(char* num){
#define _M 1000
#define _D 500
#define _C 100
#define _L 50
#define _X 10
#define _V 5
#define _I 1
    int result  = 0;
    int i;
    int last = _M;
    int continous_count = 0;
    int prev_is_down = 0;
    int prev_min = _M;
    int prev_sec = _M;
    for(i = 0;i < strlen(num);i++)
    {
        switch (num[i])
        {
            case 'M':
                result = (last >= _M ? result + _M:result + _M - (last << 1));
                if(last == _M){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
                else continous_count = 1;
                if(last < _M){
                    if(prev_is_down || last != _C)return -1;
                    prev_is_down = 1;
		    if(prev_sec <= _M - last)return -1;
		    else prev_min = _M - last;
                }
                else {
		    prev_is_down = 0;
		    if(prev_min < _M)return -1;
		}
                last = _M;
                break;
            case 'D':
                result = (last >= _D ? result + _D:result + _D - (last << 1));
                if(last == _D){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
                if(last < _D){
                    if(prev_is_down || last != _C)return -1;
                    prev_is_down = 1;
		    if(prev_sec <= _D - last) return -1;
		    else prev_min = _D - last;
                }
                else {
		    prev_is_down = 0;
		    if(prev_min < _D)return -1;
		    prev_sec = prev_min;
		    prev_min = _D;
		}
		//if(prev_min < _D)return -1;
                last = _D;
                break;
            case 'C':
                result = (last >= _C ? result + _C:result + _C - (last << 1));
                if(last == _C){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
                if(last < _C){
                    if(prev_is_down || last != _X)return -1;
                    prev_is_down = 1;
		    if(prev_sec <= _C - last) return -1;
		    else prev_min = _C - last;
                }
                else {
		    prev_is_down = 0;
		    if(prev_min < _C)return -1;
		    prev_sec = prev_min;
		    prev_min = _C;
		}
		//if(prev_min < _C)return -1;
                last = _C;
                break;
            case 'L':
                result = (last >= _L ? result + _L:result + _L - (last << 1));
                if(last == _L){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
                if(last < _L){
                    if(prev_is_down || last != _X)return -1;
                    prev_is_down = 1;
		    if(prev_sec <= _L - last) return -1;
		    else prev_min = _L - last;
                }
                else {
		    prev_is_down = 0;
		    if(prev_min < _L)return -1;
		    prev_sec = prev_min;
		    prev_min = _L;
		}
		//if(prev_min < _L)return -1;
                last = _L;
                break;
            case 'X':
                result = (last >= _X ? result + _X:result + _X - (last << 1));
                if(last == _X){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
                if(last < _X){
                    if(prev_is_down || last != _I)return -1;
                    prev_is_down = 1;
		    if(prev_sec <= _X - last) return -1;
		    else prev_min = _X - last;
                }
                else {
		    prev_is_down = 0;
		    if(prev_min < _X)return -1;
		    prev_sec = prev_min;
		    prev_min = _X;
		}
		//if(prev_min < _X)return -1;
                last = _X;
                break;
            case 'V':
                result = (last >= _V ? result + _V:result + _V - (last << 1));
                if(last == _V){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
                if(last < _V){
                    if(prev_is_down)return -1;
                    prev_is_down = 1;
		    if(prev_sec <= _V - last) return -1;
		    else prev_min = _V - last;
                }
                else {
		    prev_is_down = 0;
		    if(prev_min < _V)return -1;
		    prev_sec = prev_min;
		    prev_min = _V;
		}
		//if(prev_min < _V)return -1;
                last = _V;
                break;
            case 'I':
                result = (last >= _I ? result + _I:result + _I - (last << 1));
                if(last == _I){
                    if(continous_count == 2)return -1;
                    continous_count++;
                }
		else{
		    prev_min = _I;
		}
                last = _I;
                break;
            default:
                return -1;
        }

    }
    return result;


}

/* Convert integer to Roman */

char* convertIntegerToRoman(int num){
    char *chM[] = {"","M","MM","MMM"};
    char *chC[] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
    char *chX[] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
    char *chI[] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
    int step[] = {0,1,2,3,2,1,2,3,4,2};
    char *p = (char *)malloc(20);
    memset(p,0,20);
    int i = 0;
    int mod = 0;

    mod = num/1000;
    int j = 0;
    for(j=0;j<step[mod];j++)
    {
        *(p+i)= *(chM[mod]+j);
        i++;
    }

    mod = num/100%10;
    for(j=0;j<step[mod];j++)
    {
        *(p+i)= *(chC[mod]+j);
        i++;
    }

    mod = num/10%10;
    for(j=0;j<step[mod];j++)
    {
        *(p+i)= *(chX[mod]+j);
        i++;
    }

    mod = num%10;
    for(j=0;j<step[mod];j++)
    {
        *(p+i)= *(chI[mod]+j);
        i++;
    }
    return p;
}

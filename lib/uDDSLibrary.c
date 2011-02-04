#include <string.h>

/* reverse:  reverse string s in place */
void strreverse(char* begin, char* end) {
	char aux;

	while(end>begin)
		aux=*end, *end--=*begin, *begin++=aux;
}
	
void itoa(int value, char* str, int base) {
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	char* wstr=str;

	int sign;

	// Validate base
	if (base<2 || base>35){ *wstr='\0'; return; }
	// Take care of sign
	if ((sign=value) < 0) value = -value;
	// Conversion. Number is reversed.
	do *wstr++ = num[value%base]; while(value/=base);
	if(sign<0) *wstr++='-';
	*wstr='\0';
	// Reverse string

	strreverse(str,wstr-1);
}

//ltoa implementation **************
#define INT_DIGITOS 63
static char buf[INT_DIGITOS + 2];
/* Buffer para INT_DIGITS dígitos, signo - y fin de string '\0' */

char * ltoa(long int i, unsigned int base) {
   char *p = buf + INT_DIGITOS + 1;                   /* apunta a posición de unidades */
   int dig, signo=0;
   if (i<0) {
      signo=1;i = -i;
   }
   if(base<=0 || base>36) base=10;          /*evita división por cero */
   do {
       dig=(i%base);
       if (dig <=9) *--p = '0' + dig; 
         else *--p= '7'+ dig ; 
         i /= base;
   }
   while (i != 0);
   if(signo) *--p = '-';
   return p;
}
//End ltoa implementation **************


char* substring(const char* cadena, int inicio, int chars){
    char* sub;
    int total = (inicio + chars - 2);
    int lenCad = strlen(cadena) - 1;
    if (total > lenCad){
        sub = (char *)malloc(lenCad * sizeof(char));
        sprintf(sub, "%.*s", lenCad, cadena + (inicio - 1) );
    }
    else{
        sub = (char *)malloc(total * sizeof(char));
        sprintf(sub, "%.*s", chars , cadena + (inicio - 1));
    }
     return sub;
}

//dtoa implementation **************
char * dtoa (double value, int ndigits, char *buf)
{
//printf("El numero double es: %f\n", value);
  char *p = buf;
  sprintf (buf, "%-#.*g", ndigits, value);
  /* It seems they expect us to return .XXXX instead of 0.XXXX  */
  if (*p == '-')
    p++;
  if (*p == '0' && p[1] == '.')
    memmove (p, p + 1, strlen (p + 1) + 1);
  /* They want Xe-YY, not X.e-YY, and XXXX instead of XXXX.  */
  p = strchr (buf, 'e');
  if (!p)
    {
      p = buf + strlen (buf);
      /* They don't want trailing zeroes.  */
      while (p[-1] == '0' && p > buf + 2)
        *--p = '\0';
    }
  if (p > buf && p[-1] == '.')
    memmove (p - 1, p, strlen (p) + 1);
  //printf("El bufer es: %s\n\n",buf);
  return buf;
}
//End dtoa implementation **************

//ftoa implementation **************
char *ftoa(float f, int ndigits){
   char * buffer;
   buffer=malloc(30);
   //printf("El numero float es: %f\n", f);
   return(dtoa((double)f,ndigits,buffer));
}
//end ftoa implementation **************
//atod (strtod) implementation from dietlibc
double atod(const char* s, char** endptr) {
    register const char*  p     = s;
    register long double  value = 0.L;
    int                   sign  = +1;
    long double           factor;
    unsigned int          expo;

    while ( *p == ' ' || *p == '\t' || *p == '\n' || *p == '\v' || *p == '\f' || *p == '\r' ) //mike 04022011 isspace(*p)
        p++;

    switch (*p) {
    case '-': sign = -1;
    case '+': p++;
    default : break;
    }

    while ( (unsigned int)(*p - '0') < 10u )
        value = value*10 + (*p++ - '0');

    if ( *p == '.' ) {
        factor = 1.;

        p++;
        while ( (unsigned int)(*p - '0') < 10u ) {
            factor *= 0.1;
            value  += (*p++ - '0') * factor;
        }
    }

    if ( (*p | 32) == 'e' ) {
        expo   = 0;
        factor = 10.L;

        switch (*++p) {                 // ja hier weiß ich nicht, was mindestens nach einem 'E' folgenden MUSS.
        case '-': factor = 0.1;
        case '+': p++;
                  break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                  break;
        default : value = 0.L;
                  p     = s;
                  goto done;
        }

        while ( (unsigned int)(*p - '0') < 10u )
            expo = 10 * expo + (*p++ - '0');

        while ( 1 ) {
            if ( expo & 1 )
                value *= factor;
            if ( (expo >>= 1) == 0 )
                break;
            factor *= factor;
        }
    }

done:
    if ( endptr != NULL )
        *endptr = (char*)p;

    return value * sign;
}


//end atod implementation   ******************************** modificado 161209 ***************************************************************************
void showDataTopic(uDDS_MsgPackage xxxPackMsg){
   //printf("xxxPackMsg.uDDS_MsgHeader.MsgType = %d \n",xxxPackMsg.uDDS_MsgHeader.MsgType);
   //printf("xxxPackMsg.uDDS_MsgHeader.TopicId = %s \n",xxxPackMsg.uDDS_MsgHeader.TopicId);
   printf("xxxPackMsg.String_Data            = %s\n",xxxPackMsg.String_Data);
   printf("xxxPackMsg.Int_Data               = %d\n",xxxPackMsg.Int_Data);
   printf("xxxPackMsg.Float_Data             = %f\n",xxxPackMsg.Float_Data);
   printf("xxxPackMsg.Double_Data            = %3.15f\n",xxxPackMsg.Double_Data);
   printf("xxxPackMsg.LongInt_Data           = %ld\n",xxxPackMsg.LongInt_Data);
}



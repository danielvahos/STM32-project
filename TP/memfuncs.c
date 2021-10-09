//#include <string.h>
/*
void *memset( void *dest, int ch, size_t count ){
    int *destint= (int *) dest;
    int *destfin= (int *) (dest + count)
    for(dest; ; i=i+4){
        *(destint+i)= ch;
    }
    for(int i= 0; i<count; i++){
        *(destint+i)= ch;
    }

}

*/
#include <stddef.h>

void * memset (void *dest, int val, size_t len)
{
  unsigned char *ptr = dest;
  while (len-- > 0)
    //*ptr=val
    //ptr++
    *ptr++ = val;
  return dest;
}

void * memcpy (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}

void * memmove (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  if (d < s)
    while (len--)
      *d++ = *s++;
  else
    {
      const char *lasts = s + (len-1);
      char *lastd = d + (len-1);
      while (len--)
        *lastd-- = *lasts--;
    }
  return dest;
}

int memcmp (const void *str1, const void *str2, size_t count)
{
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;

  while (count-- > 0)
    {
      if (*s1++ != *s2++)
	  return s1[-1] < s2[-1] ? -1 : 1;
    }
  return 0;
}
/*
void* memcpy( void *dest, const void *src, size_t count );
    for(*i= *src; dest; )
}
*/
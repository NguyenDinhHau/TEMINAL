#include<stdio.h>
#include "MKL46Z4.h"
#include "queue.h"

static queue_str_t g_queue;

void Queue_Init(void)
{ 
    g_queue.read = 0;
    g_queue.write = 0;
    g_queue.count = 0;
}

bool Queue_IsFull(void)
{
  bool check = false;
  
  if(QUEUE_SIZE == g_queue.count)
  {
    check = true;
  }
  
    return check;
}

bool Queue_IsEmpty(void)
{
  bool check = false;
  
  if(0 == g_queue.count)
  {
    check = true;
  }
  
    return check;
}
/* allocate for autbuff mapping outbuff with g_queue*/
void Queue_PushData(uint8_t ** outBuff)
{
    if (!Queue_IsFull())
    {
        *outBuff = g_queue.a[g_queue.write % QUEUE_SIZE].data;
    }
    else
    {
      *outBuff = NULL;
    }
}
/*increate write and count when we add data from g_queue*/
void Queue_Push_NextWrite(void)
{
    if (!Queue_IsFull())/* Queue is not full */
    {
        g_queue.write++;
        g_queue.count++;
    }
}
/* allocate for outbuff mapping outbuff with g_queue*/
void Queue_PopData(uint8_t ** outBuff)
{
    if (!Queue_IsEmpty())
    {
        *outBuff = g_queue.a[g_queue.read % QUEUE_SIZE].data;
    }
    else
    {
        *outBuff = NULL;
    }
}
/*increate increate and reduce count when we remove data from g_queue*/
void Queue_Pop_NextRead(void)
{
    if (!Queue_IsEmpty())
    {
        g_queue.read++;
        g_queue.count--;
    }
}
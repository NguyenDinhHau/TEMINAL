#include "MKL46Z4.h"
#include "QUEUE.h"
#include "UART.h"


static queue_str_t queue;
static int i = -1;
void QueueInit()
{
  queue.rear = 0;
  queue.front = 0;
  queue.count = 0;
}

bool isFull(void)
{
    return QUEUE_SIZE == queue.count;
}

bool isEmpty(void)
{
    return 0 == queue.count;
}
/* allocate for autbuff mapping outbuff with queue*/
void Pushdata(char data)
{
    if (!isFull())
    {
      if('\n' != data)
        {
        queue.queue_data[(queue.rear)%QUEUE_SIZE].data[++i] = data;
        }
      else
      {
         queue.count++;
          queue.rear++;
          i = -1;
      } 
    }
}

/* allocate for outbuff mapping outbuff with queue*/
data_str_t * PopData()
{
  data_str_t *data;
  
    if (!isEmpty())
    {
        data = &queue.queue_data[queue.front];
        queue.front = (queue.front++) % QUEUE_SIZE;
        queue.count--;
    }
    
    return data;
}
/*increate increate and reduce count when we remove data from queue*/

#include "MKL46Z4.h"
#include "queue.h"

static queue_str_t queue;

void QueueInit(void)
{ 
    queue.read = 0;
    queue.write = 0;
    queue.count = 0;
}

bool Queue_isFull(void)
{
    return QUEUE_SIZE == queue.count;
}

bool Queue_isEmpty(void)
{
    return 0 == queue.count;
}
/* allocate for autbuff mapping outbuff with queue*/
void Pushdata(uint8_t ** outBuff)
{

    if (!Queue_isFull())
    {
        *outBuff = queue.a[queue.write % QUEUE_SIZE].data;
    }
}
/*increate write and count when we add data from queue*/
void queue_push(void)
{
    if (!Queue_isFull())/* Queue is not full */
    {
        queue.write++;
        queue.count++;
    }
}
/* allocate for outbuff mapping outbuff with queue*/
void PopData(uint8_t ** outBuff)
{
    if (!Queue_isEmpty())
    {
        *outBuff = queue.a[queue.read % QUEUE_SIZE].data;
    }
}
/*increate increate and reduce count when we remove data from queue*/
void queue_pop(void)
{
    if (!Queue_isEmpty())
    {
        queue.read++;
        queue.count--;
    }
}
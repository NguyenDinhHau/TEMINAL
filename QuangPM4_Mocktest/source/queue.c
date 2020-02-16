#include "MKL46Z4.h"
#include "queue.h"
#include <stdio.h>
static queue_t queue;
/*******************************************************************************
 * Code
 ******************************************************************************/

void queue_init(void)
{
    queue.read = 0;
    queue.write = 0;
    queue.size = 0;
}

bool queue_check_Empty(void)
{
    bool retVal = false;
    if (0 == queue.size)
    {
        retVal = true;
    }
    return retVal;
}
bool queue_check_Full(void)
{
    bool retVal = false;
    if (MAX_QUEUE_SIZE == queue.size)
    {
        retVal = true;
    }
    return retVal;
}
void queue_Pushdata(char ** data_push)
{
    uint8_t Push_index = queue.write % MAX_QUEUE_SIZE;
    if (queue_check_Full() == false)
    {
        *data_push = queue.index[Push_index].data;// *data_push = (uint8_t*)&queue.index[Push_index].data[0]
        /* using Queue Circular */
    }
    else
    {
        *data_push =NULL;
    }
}
void queue_push(void)
{
    if (queue_check_Full() == false) /* push until queue full */
    {
        queue.write++;
        queue.size++; /* when push, element in queue is increase */
    }
}
void queue_POP_Data(char ** data_pop)
{
    uint8_t Pop_index = queue.read % MAX_QUEUE_SIZE;
    if (queue_check_Empty() == false)
    {
        *data_pop = queue.index[Pop_index].data;
        /* using Queue Circular */
    }
}
void queue_pop(void)
{
    if (queue_check_Empty() == false)/* pop until queue empty */
    {
        queue.read++;
        queue.size--;/* when pop, element in queue is reduce */
    }
}
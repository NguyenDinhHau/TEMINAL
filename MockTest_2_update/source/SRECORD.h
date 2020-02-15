#ifndef _SRECORD_H_
#define _SRECORD_H_

bool Check_Srecord(uint8_t *data);


typedef struct
{
  uint32_t address;
  uint8_t addLengh;
  uint8_t data[40];
}add_data_str;

#endif  /*_SRECORD_H_*/
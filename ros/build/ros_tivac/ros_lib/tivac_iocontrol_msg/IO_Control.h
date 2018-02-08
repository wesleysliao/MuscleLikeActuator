#ifndef _ROS_tivac_iocontrol_msg_IO_Control_h
#define _ROS_tivac_iocontrol_msg_IO_Control_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace tivac_iocontrol_msg
{

  class IO_Control : public ros::Msg
  {
    public:
      typedef uint8_t _port_type;
      _port_type port;
      typedef int8_t _mask_type;
      _mask_type mask;
      typedef int8_t _value_type;
      _value_type value;

    IO_Control():
      port(0),
      mask(0),
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->port >> (8 * 0)) & 0xFF;
      offset += sizeof(this->port);
      union {
        int8_t real;
        uint8_t base;
      } u_mask;
      u_mask.real = this->mask;
      *(outbuffer + offset + 0) = (u_mask.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mask);
      union {
        int8_t real;
        uint8_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->port =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->port);
      union {
        int8_t real;
        uint8_t base;
      } u_mask;
      u_mask.base = 0;
      u_mask.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mask = u_mask.real;
      offset += sizeof(this->mask);
      union {
        int8_t real;
        uint8_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return "tivac_iocontrol_msg/IO_Control"; };
    const char * getMD5(){ return "dc750dd0a815484a3bf3d6f436ecdc55"; };

  };

}
#endif
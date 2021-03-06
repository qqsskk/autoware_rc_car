#ifndef _ROS_jsk_gui_msgs_SlackMessage_h
#define _ROS_jsk_gui_msgs_SlackMessage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"

namespace jsk_gui_msgs
{

  class SlackMessage : public ros::Msg
  {
    public:
      const char* channel;
      const char* text;
      sensor_msgs::Image image;

    SlackMessage():
      channel(""),
      text(""),
      image()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_channel = strlen(this->channel);
      memcpy(outbuffer + offset, &length_channel, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->channel, length_channel);
      offset += length_channel;
      uint32_t length_text = strlen(this->text);
      memcpy(outbuffer + offset, &length_text, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->text, length_text);
      offset += length_text;
      offset += this->image.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_channel;
      memcpy(&length_channel, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_channel; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_channel-1]=0;
      this->channel = (char *)(inbuffer + offset-1);
      offset += length_channel;
      uint32_t length_text;
      memcpy(&length_text, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_text; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_text-1]=0;
      this->text = (char *)(inbuffer + offset-1);
      offset += length_text;
      offset += this->image.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "jsk_gui_msgs/SlackMessage"; };
    const char * getMD5(){ return "b68991d3b722980bd0f3eeeeee52635b"; };

  };

}
#endif
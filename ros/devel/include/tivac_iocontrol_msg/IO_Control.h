// Generated by gencpp from file tivac_iocontrol_msg/IO_Control.msg
// DO NOT EDIT!


#ifndef TIVAC_IOCONTROL_MSG_MESSAGE_IO_CONTROL_H
#define TIVAC_IOCONTROL_MSG_MESSAGE_IO_CONTROL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace tivac_iocontrol_msg
{
template <class ContainerAllocator>
struct IO_Control_
{
  typedef IO_Control_<ContainerAllocator> Type;

  IO_Control_()
    : port(0)
    , mask(0)
    , value(0)  {
    }
  IO_Control_(const ContainerAllocator& _alloc)
    : port(0)
    , mask(0)
    , value(0)  {
  (void)_alloc;
    }



   typedef uint8_t _port_type;
  _port_type port;

   typedef int8_t _mask_type;
  _mask_type mask;

   typedef int8_t _value_type;
  _value_type value;




  typedef boost::shared_ptr< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> const> ConstPtr;

}; // struct IO_Control_

typedef ::tivac_iocontrol_msg::IO_Control_<std::allocator<void> > IO_Control;

typedef boost::shared_ptr< ::tivac_iocontrol_msg::IO_Control > IO_ControlPtr;
typedef boost::shared_ptr< ::tivac_iocontrol_msg::IO_Control const> IO_ControlConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace tivac_iocontrol_msg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'tivac_iocontrol_msg': ['/home/wesley/Sources/MuscleLikeActuator/ros/src/tivac_iocontrol_msg/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dc750dd0a815484a3bf3d6f436ecdc55";
  }

  static const char* value(const ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdc750dd0a815484aULL;
  static const uint64_t static_value2 = 0x3bf3d6f436ecdc55ULL;
};

template<class ContainerAllocator>
struct DataType< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "tivac_iocontrol_msg/IO_Control";
  }

  static const char* value(const ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 port\n\
int8 mask\n\
int8 value\n\
";
  }

  static const char* value(const ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.port);
      stream.next(m.mask);
      stream.next(m.value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IO_Control_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::tivac_iocontrol_msg::IO_Control_<ContainerAllocator>& v)
  {
    s << indent << "port: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.port);
    s << indent << "mask: ";
    Printer<int8_t>::stream(s, indent + "  ", v.mask);
    s << indent << "value: ";
    Printer<int8_t>::stream(s, indent + "  ", v.value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TIVAC_IOCONTROL_MSG_MESSAGE_IO_CONTROL_H
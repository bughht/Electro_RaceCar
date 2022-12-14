// Generated by gencpp from file raceworld/status.msg
// DO NOT EDIT!


#ifndef RACEWORLD_MESSAGE_STATUS_H
#define RACEWORLD_MESSAGE_STATUS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace raceworld
{
template <class ContainerAllocator>
struct status_
{
  typedef status_<ContainerAllocator> Type;

  status_()
    : leader()
    , follower1()
    , follower2()
    , follower3()
    , follower4()
    , formation(0)  {
    }
  status_(const ContainerAllocator& _alloc)
    : leader(_alloc)
    , follower1(_alloc)
    , follower2(_alloc)
    , follower3(_alloc)
    , follower4(_alloc)
    , formation(0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _leader_type;
  _leader_type leader;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _follower1_type;
  _follower1_type follower1;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _follower2_type;
  _follower2_type follower2;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _follower3_type;
  _follower3_type follower3;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _follower4_type;
  _follower4_type follower4;

   typedef uint8_t _formation_type;
  _formation_type formation;





  typedef boost::shared_ptr< ::raceworld::status_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::raceworld::status_<ContainerAllocator> const> ConstPtr;

}; // struct status_

typedef ::raceworld::status_<std::allocator<void> > status;

typedef boost::shared_ptr< ::raceworld::status > statusPtr;
typedef boost::shared_ptr< ::raceworld::status const> statusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::raceworld::status_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::raceworld::status_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::raceworld::status_<ContainerAllocator1> & lhs, const ::raceworld::status_<ContainerAllocator2> & rhs)
{
  return lhs.leader == rhs.leader &&
    lhs.follower1 == rhs.follower1 &&
    lhs.follower2 == rhs.follower2 &&
    lhs.follower3 == rhs.follower3 &&
    lhs.follower4 == rhs.follower4 &&
    lhs.formation == rhs.formation;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::raceworld::status_<ContainerAllocator1> & lhs, const ::raceworld::status_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace raceworld

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::raceworld::status_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::raceworld::status_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::raceworld::status_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::raceworld::status_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raceworld::status_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::raceworld::status_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::raceworld::status_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7f786ce8ae9e22085ec0c660926ddd4c";
  }

  static const char* value(const ::raceworld::status_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7f786ce8ae9e2208ULL;
  static const uint64_t static_value2 = 0x5ec0c660926ddd4cULL;
};

template<class ContainerAllocator>
struct DataType< ::raceworld::status_<ContainerAllocator> >
{
  static const char* value()
  {
    return "raceworld/status";
  }

  static const char* value(const ::raceworld::status_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::raceworld::status_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string leader\n"
"string follower1\n"
"string follower2\n"
"string follower3\n"
"string follower4\n"
"uint8 formation\n"
;
  }

  static const char* value(const ::raceworld::status_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::raceworld::status_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.leader);
      stream.next(m.follower1);
      stream.next(m.follower2);
      stream.next(m.follower3);
      stream.next(m.follower4);
      stream.next(m.formation);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct status_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::raceworld::status_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::raceworld::status_<ContainerAllocator>& v)
  {
    s << indent << "leader: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.leader);
    s << indent << "follower1: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.follower1);
    s << indent << "follower2: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.follower2);
    s << indent << "follower3: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.follower3);
    s << indent << "follower4: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.follower4);
    s << indent << "formation: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.formation);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RACEWORLD_MESSAGE_STATUS_H

// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "seg_path.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* mp_seg_path_data_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_seg_path_data_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* mp_seg_path_data_Seg_Type_descriptor_ = NULL;
const ::google::protobuf::Descriptor* mp_seg_path_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_seg_path_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_seg_5fpath_2eproto() {
  protobuf_AddDesc_seg_5fpath_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "seg_path.proto");
  GOOGLE_CHECK(file != NULL);
  mp_seg_path_data_descriptor_ = file->message_type(0);
  static const int mp_seg_path_data_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, x1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, y1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, th1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, x2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, y2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, th2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, p_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, complete_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, speed_),
  };
  mp_seg_path_data_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_seg_path_data_descriptor_,
      mp_seg_path_data::default_instance_,
      mp_seg_path_data_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path_data, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_seg_path_data));
  mp_seg_path_data_Seg_Type_descriptor_ = mp_seg_path_data_descriptor_->enum_type(0);
  mp_seg_path_descriptor_ = file->message_type(1);
  static const int mp_seg_path_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path, seg_path_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path, data_),
  };
  mp_seg_path_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_seg_path_descriptor_,
      mp_seg_path::default_instance_,
      mp_seg_path_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_seg_path, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_seg_path));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_seg_5fpath_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_seg_path_data_descriptor_, &mp_seg_path_data::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_seg_path_descriptor_, &mp_seg_path::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_seg_5fpath_2eproto() {
  delete mp_seg_path_data::default_instance_;
  delete mp_seg_path_data_reflection_;
  delete mp_seg_path::default_instance_;
  delete mp_seg_path_reflection_;
}

void protobuf_AddDesc_seg_5fpath_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016seg_path.proto\022\003KPS\"\343\001\n\020mp_seg_path_da"
    "ta\022\n\n\002x1\030\001 \002(\002\022\n\n\002y1\030\002 \002(\002\022\013\n\003th1\030\003 \002(\002\022"
    "\n\n\002x2\030\004 \002(\002\022\n\n\002y2\030\005 \002(\002\022\013\n\003th2\030\006 \002(\002\022.\n\006"
    "p_type\030\007 \002(\0162\036.KPS.mp_seg_path_data.Seg_"
    "Type\022\020\n\010complete\030\010 \002(\002\022\r\n\005speed\030\t \002(\002\"4\n"
    "\010Seg_Type\022\014\n\010PATH_SEG\020\000\022\014\n\010PATH_ROT\020\001\022\014\n"
    "\010PATH_ARC\020\002\"I\n\013mp_seg_path\022\025\n\rseg_path_n"
    "ame\030\001 \002(\t\022#\n\004data\030\002 \003(\0132\025.KPS.mp_seg_pat"
    "h_data", 326);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "seg_path.proto", &protobuf_RegisterTypes);
  mp_seg_path_data::default_instance_ = new mp_seg_path_data();
  mp_seg_path::default_instance_ = new mp_seg_path();
  mp_seg_path_data::default_instance_->InitAsDefaultInstance();
  mp_seg_path::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_seg_5fpath_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_seg_5fpath_2eproto {
  StaticDescriptorInitializer_seg_5fpath_2eproto() {
    protobuf_AddDesc_seg_5fpath_2eproto();
  }
} static_descriptor_initializer_seg_5fpath_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* mp_seg_path_data_Seg_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_seg_path_data_Seg_Type_descriptor_;
}
bool mp_seg_path_data_Seg_Type_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const mp_seg_path_data_Seg_Type mp_seg_path_data::PATH_SEG;
const mp_seg_path_data_Seg_Type mp_seg_path_data::PATH_ROT;
const mp_seg_path_data_Seg_Type mp_seg_path_data::PATH_ARC;
const mp_seg_path_data_Seg_Type mp_seg_path_data::Seg_Type_MIN;
const mp_seg_path_data_Seg_Type mp_seg_path_data::Seg_Type_MAX;
const int mp_seg_path_data::Seg_Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int mp_seg_path_data::kX1FieldNumber;
const int mp_seg_path_data::kY1FieldNumber;
const int mp_seg_path_data::kTh1FieldNumber;
const int mp_seg_path_data::kX2FieldNumber;
const int mp_seg_path_data::kY2FieldNumber;
const int mp_seg_path_data::kTh2FieldNumber;
const int mp_seg_path_data::kPTypeFieldNumber;
const int mp_seg_path_data::kCompleteFieldNumber;
const int mp_seg_path_data::kSpeedFieldNumber;
#endif  // !_MSC_VER

mp_seg_path_data::mp_seg_path_data()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_seg_path_data::InitAsDefaultInstance() {
}

mp_seg_path_data::mp_seg_path_data(const mp_seg_path_data& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_seg_path_data::SharedCtor() {
  _cached_size_ = 0;
  x1_ = 0;
  y1_ = 0;
  th1_ = 0;
  x2_ = 0;
  y2_ = 0;
  th2_ = 0;
  p_type_ = 0;
  complete_ = 0;
  speed_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_seg_path_data::~mp_seg_path_data() {
  SharedDtor();
}

void mp_seg_path_data::SharedDtor() {
  if (this != default_instance_) {
  }
}

void mp_seg_path_data::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_seg_path_data::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_seg_path_data_descriptor_;
}

const mp_seg_path_data& mp_seg_path_data::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_seg_5fpath_2eproto();  return *default_instance_;
}

mp_seg_path_data* mp_seg_path_data::default_instance_ = NULL;

mp_seg_path_data* mp_seg_path_data::New() const {
  return new mp_seg_path_data;
}

void mp_seg_path_data::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    x1_ = 0;
    y1_ = 0;
    th1_ = 0;
    x2_ = 0;
    y2_ = 0;
    th2_ = 0;
    p_type_ = 0;
    complete_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    speed_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_seg_path_data::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required float x1 = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &x1_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_y1;
        break;
      }
      
      // required float y1 = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_y1:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &y1_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(29)) goto parse_th1;
        break;
      }
      
      // required float th1 = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_th1:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &th1_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(37)) goto parse_x2;
        break;
      }
      
      // required float x2 = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_x2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &x2_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(45)) goto parse_y2;
        break;
      }
      
      // required float y2 = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_y2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &y2_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(53)) goto parse_th2;
        break;
      }
      
      // required float th2 = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_th2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &th2_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_p_type;
        break;
      }
      
      // required .KPS.mp_seg_path_data.Seg_Type p_type = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_p_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::KPS::mp_seg_path_data_Seg_Type_IsValid(value)) {
            set_p_type(static_cast< ::KPS::mp_seg_path_data_Seg_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(7, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(69)) goto parse_complete;
        break;
      }
      
      // required float complete = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_complete:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &complete_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(77)) goto parse_speed;
        break;
      }
      
      // required float speed = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_speed:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &speed_)));
          _set_bit(8);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void mp_seg_path_data::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required float x1 = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->x1(), output);
  }
  
  // required float y1 = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->y1(), output);
  }
  
  // required float th1 = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->th1(), output);
  }
  
  // required float x2 = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->x2(), output);
  }
  
  // required float y2 = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->y2(), output);
  }
  
  // required float th2 = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(6, this->th2(), output);
  }
  
  // required .KPS.mp_seg_path_data.Seg_Type p_type = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      7, this->p_type(), output);
  }
  
  // required float complete = 8;
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(8, this->complete(), output);
  }
  
  // required float speed = 9;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(9, this->speed(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_seg_path_data::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required float x1 = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(1, this->x1(), target);
  }
  
  // required float y1 = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->y1(), target);
  }
  
  // required float th1 = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->th1(), target);
  }
  
  // required float x2 = 4;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->x2(), target);
  }
  
  // required float y2 = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->y2(), target);
  }
  
  // required float th2 = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(6, this->th2(), target);
  }
  
  // required .KPS.mp_seg_path_data.Seg_Type p_type = 7;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      7, this->p_type(), target);
  }
  
  // required float complete = 8;
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(8, this->complete(), target);
  }
  
  // required float speed = 9;
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(9, this->speed(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_seg_path_data::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required float x1 = 1;
    if (has_x1()) {
      total_size += 1 + 4;
    }
    
    // required float y1 = 2;
    if (has_y1()) {
      total_size += 1 + 4;
    }
    
    // required float th1 = 3;
    if (has_th1()) {
      total_size += 1 + 4;
    }
    
    // required float x2 = 4;
    if (has_x2()) {
      total_size += 1 + 4;
    }
    
    // required float y2 = 5;
    if (has_y2()) {
      total_size += 1 + 4;
    }
    
    // required float th2 = 6;
    if (has_th2()) {
      total_size += 1 + 4;
    }
    
    // required .KPS.mp_seg_path_data.Seg_Type p_type = 7;
    if (has_p_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->p_type());
    }
    
    // required float complete = 8;
    if (has_complete()) {
      total_size += 1 + 4;
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required float speed = 9;
    if (has_speed()) {
      total_size += 1 + 4;
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void mp_seg_path_data::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_seg_path_data* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_seg_path_data*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_seg_path_data::MergeFrom(const mp_seg_path_data& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_x1(from.x1());
    }
    if (from._has_bit(1)) {
      set_y1(from.y1());
    }
    if (from._has_bit(2)) {
      set_th1(from.th1());
    }
    if (from._has_bit(3)) {
      set_x2(from.x2());
    }
    if (from._has_bit(4)) {
      set_y2(from.y2());
    }
    if (from._has_bit(5)) {
      set_th2(from.th2());
    }
    if (from._has_bit(6)) {
      set_p_type(from.p_type());
    }
    if (from._has_bit(7)) {
      set_complete(from.complete());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_speed(from.speed());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_seg_path_data::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_seg_path_data::CopyFrom(const mp_seg_path_data& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_seg_path_data::IsInitialized() const {
  if ((_has_bits_[0] & 0x000001ff) != 0x000001ff) return false;
  
  return true;
}

void mp_seg_path_data::Swap(mp_seg_path_data* other) {
  if (other != this) {
    std::swap(x1_, other->x1_);
    std::swap(y1_, other->y1_);
    std::swap(th1_, other->th1_);
    std::swap(x2_, other->x2_);
    std::swap(y2_, other->y2_);
    std::swap(th2_, other->th2_);
    std::swap(p_type_, other->p_type_);
    std::swap(complete_, other->complete_);
    std::swap(speed_, other->speed_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_seg_path_data::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_seg_path_data_descriptor_;
  metadata.reflection = mp_seg_path_data_reflection_;
  return metadata;
}


// ===================================================================

const ::std::string mp_seg_path::_default_seg_path_name_;
#ifndef _MSC_VER
const int mp_seg_path::kSegPathNameFieldNumber;
const int mp_seg_path::kDataFieldNumber;
#endif  // !_MSC_VER

mp_seg_path::mp_seg_path()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_seg_path::InitAsDefaultInstance() {
}

mp_seg_path::mp_seg_path(const mp_seg_path& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_seg_path::SharedCtor() {
  _cached_size_ = 0;
  seg_path_name_ = const_cast< ::std::string*>(&_default_seg_path_name_);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_seg_path::~mp_seg_path() {
  SharedDtor();
}

void mp_seg_path::SharedDtor() {
  if (seg_path_name_ != &_default_seg_path_name_) {
    delete seg_path_name_;
  }
  if (this != default_instance_) {
  }
}

void mp_seg_path::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_seg_path::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_seg_path_descriptor_;
}

const mp_seg_path& mp_seg_path::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_seg_5fpath_2eproto();  return *default_instance_;
}

mp_seg_path* mp_seg_path::default_instance_ = NULL;

mp_seg_path* mp_seg_path::New() const {
  return new mp_seg_path;
}

void mp_seg_path::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (seg_path_name_ != &_default_seg_path_name_) {
        seg_path_name_->clear();
      }
    }
  }
  data_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_seg_path::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string seg_path_name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_seg_path_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->seg_path_name().data(), this->seg_path_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_data;
        break;
      }
      
      // repeated .KPS.mp_seg_path_data data = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_data;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void mp_seg_path::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string seg_path_name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->seg_path_name().data(), this->seg_path_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->seg_path_name(), output);
  }
  
  // repeated .KPS.mp_seg_path_data data = 2;
  for (int i = 0; i < this->data_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->data(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_seg_path::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string seg_path_name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->seg_path_name().data(), this->seg_path_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->seg_path_name(), target);
  }
  
  // repeated .KPS.mp_seg_path_data data = 2;
  for (int i = 0; i < this->data_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->data(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_seg_path::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string seg_path_name = 1;
    if (has_seg_path_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->seg_path_name());
    }
    
  }
  // repeated .KPS.mp_seg_path_data data = 2;
  total_size += 1 * this->data_size();
  for (int i = 0; i < this->data_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->data(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void mp_seg_path::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_seg_path* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_seg_path*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_seg_path::MergeFrom(const mp_seg_path& from) {
  GOOGLE_CHECK_NE(&from, this);
  data_.MergeFrom(from.data_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_seg_path_name(from.seg_path_name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_seg_path::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_seg_path::CopyFrom(const mp_seg_path& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_seg_path::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  for (int i = 0; i < data_size(); i++) {
    if (!this->data(i).IsInitialized()) return false;
  }
  return true;
}

void mp_seg_path::Swap(mp_seg_path* other) {
  if (other != this) {
    std::swap(seg_path_name_, other->seg_path_name_);
    data_.Swap(&other->data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_seg_path::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_seg_path_descriptor_;
  metadata.reflection = mp_seg_path_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

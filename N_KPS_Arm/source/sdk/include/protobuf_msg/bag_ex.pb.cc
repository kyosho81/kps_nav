// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "bag_ex.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* mp_bag_ex_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_bag_ex_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_bag_5fex_2eproto() {
  protobuf_AddDesc_bag_5fex_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "bag_ex.proto");
  GOOGLE_CHECK(file != NULL);
  mp_bag_ex_descriptor_ = file->message_type(0);
  static const int mp_bag_ex_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, proto_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, robot_shape_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, laser_para_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, laser_ex_data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, laser_ref_data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, odom_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, amcl_pos_),
  };
  mp_bag_ex_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_bag_ex_descriptor_,
      mp_bag_ex::default_instance_,
      mp_bag_ex_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_bag_ex, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_bag_ex));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_bag_5fex_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_bag_ex_descriptor_, &mp_bag_ex::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_bag_5fex_2eproto() {
  delete mp_bag_ex::default_instance_;
  delete mp_bag_ex_reflection_;
}

void protobuf_AddDesc_bag_5fex_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::KPS::protobuf_AddDesc_base_2eproto();
  ::KPS::protobuf_AddDesc_laser_5fex_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014bag_ex.proto\022\003KPS\032\nbase.proto\032\016laser_e"
    "x.proto\"\202\002\n\tmp_bag_ex\022\022\n\nproto_type\030\001 \001("
    "\t\022\023\n\013robot_shape\030\002 \002(\t\022)\n\nlaser_para\030\003 \002"
    "(\0132\025.KPS.mp_laser_ex_para\022,\n\rlaser_ex_da"
    "ta\030\004 \002(\0132\025.KPS.mp_laser_ex_data\022.\n\016laser"
    "_ref_data\030\005 \002(\0132\026.KPS.mp_laser_ref_data\022"
    "\037\n\004odom\030\006 \002(\0132\021.KPS.mp_odom_data\022\"\n\010amcl"
    "_pos\030\007 \002(\0132\020.KPS.mp_pos_data", 308);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "bag_ex.proto", &protobuf_RegisterTypes);
  mp_bag_ex::default_instance_ = new mp_bag_ex();
  mp_bag_ex::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_bag_5fex_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_bag_5fex_2eproto {
  StaticDescriptorInitializer_bag_5fex_2eproto() {
    protobuf_AddDesc_bag_5fex_2eproto();
  }
} static_descriptor_initializer_bag_5fex_2eproto_;


// ===================================================================

const ::std::string mp_bag_ex::_default_proto_type_;
const ::std::string mp_bag_ex::_default_robot_shape_;
#ifndef _MSC_VER
const int mp_bag_ex::kProtoTypeFieldNumber;
const int mp_bag_ex::kRobotShapeFieldNumber;
const int mp_bag_ex::kLaserParaFieldNumber;
const int mp_bag_ex::kLaserExDataFieldNumber;
const int mp_bag_ex::kLaserRefDataFieldNumber;
const int mp_bag_ex::kOdomFieldNumber;
const int mp_bag_ex::kAmclPosFieldNumber;
#endif  // !_MSC_VER

mp_bag_ex::mp_bag_ex()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_bag_ex::InitAsDefaultInstance() {
  laser_para_ = const_cast< ::KPS::mp_laser_ex_para*>(&::KPS::mp_laser_ex_para::default_instance());
  laser_ex_data_ = const_cast< ::KPS::mp_laser_ex_data*>(&::KPS::mp_laser_ex_data::default_instance());
  laser_ref_data_ = const_cast< ::KPS::mp_laser_ref_data*>(&::KPS::mp_laser_ref_data::default_instance());
  odom_ = const_cast< ::KPS::mp_odom_data*>(&::KPS::mp_odom_data::default_instance());
  amcl_pos_ = const_cast< ::KPS::mp_pos_data*>(&::KPS::mp_pos_data::default_instance());
}

mp_bag_ex::mp_bag_ex(const mp_bag_ex& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_bag_ex::SharedCtor() {
  _cached_size_ = 0;
  proto_type_ = const_cast< ::std::string*>(&_default_proto_type_);
  robot_shape_ = const_cast< ::std::string*>(&_default_robot_shape_);
  laser_para_ = NULL;
  laser_ex_data_ = NULL;
  laser_ref_data_ = NULL;
  odom_ = NULL;
  amcl_pos_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_bag_ex::~mp_bag_ex() {
  SharedDtor();
}

void mp_bag_ex::SharedDtor() {
  if (proto_type_ != &_default_proto_type_) {
    delete proto_type_;
  }
  if (robot_shape_ != &_default_robot_shape_) {
    delete robot_shape_;
  }
  if (this != default_instance_) {
    delete laser_para_;
    delete laser_ex_data_;
    delete laser_ref_data_;
    delete odom_;
    delete amcl_pos_;
  }
}

void mp_bag_ex::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_bag_ex::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_bag_ex_descriptor_;
}

const mp_bag_ex& mp_bag_ex::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_bag_5fex_2eproto();  return *default_instance_;
}

mp_bag_ex* mp_bag_ex::default_instance_ = NULL;

mp_bag_ex* mp_bag_ex::New() const {
  return new mp_bag_ex;
}

void mp_bag_ex::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (proto_type_ != &_default_proto_type_) {
        proto_type_->clear();
      }
    }
    if (_has_bit(1)) {
      if (robot_shape_ != &_default_robot_shape_) {
        robot_shape_->clear();
      }
    }
    if (_has_bit(2)) {
      if (laser_para_ != NULL) laser_para_->::KPS::mp_laser_ex_para::Clear();
    }
    if (_has_bit(3)) {
      if (laser_ex_data_ != NULL) laser_ex_data_->::KPS::mp_laser_ex_data::Clear();
    }
    if (_has_bit(4)) {
      if (laser_ref_data_ != NULL) laser_ref_data_->::KPS::mp_laser_ref_data::Clear();
    }
    if (_has_bit(5)) {
      if (odom_ != NULL) odom_->::KPS::mp_odom_data::Clear();
    }
    if (_has_bit(6)) {
      if (amcl_pos_ != NULL) amcl_pos_->::KPS::mp_pos_data::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_bag_ex::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string proto_type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_proto_type()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->proto_type().data(), this->proto_type().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_robot_shape;
        break;
      }
      
      // required string robot_shape = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_robot_shape:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_robot_shape()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->robot_shape().data(), this->robot_shape().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_laser_para;
        break;
      }
      
      // required .KPS.mp_laser_ex_para laser_para = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_laser_para:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_laser_para()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_laser_ex_data;
        break;
      }
      
      // required .KPS.mp_laser_ex_data laser_ex_data = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_laser_ex_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_laser_ex_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_laser_ref_data;
        break;
      }
      
      // required .KPS.mp_laser_ref_data laser_ref_data = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_laser_ref_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_laser_ref_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_odom;
        break;
      }
      
      // required .KPS.mp_odom_data odom = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_odom:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_odom()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_amcl_pos;
        break;
      }
      
      // required .KPS.mp_pos_data amcl_pos = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_amcl_pos:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_amcl_pos()));
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

void mp_bag_ex::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string proto_type = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->proto_type().data(), this->proto_type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->proto_type(), output);
  }
  
  // required string robot_shape = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->robot_shape().data(), this->robot_shape().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->robot_shape(), output);
  }
  
  // required .KPS.mp_laser_ex_para laser_para = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->laser_para(), output);
  }
  
  // required .KPS.mp_laser_ex_data laser_ex_data = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->laser_ex_data(), output);
  }
  
  // required .KPS.mp_laser_ref_data laser_ref_data = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->laser_ref_data(), output);
  }
  
  // required .KPS.mp_odom_data odom = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->odom(), output);
  }
  
  // required .KPS.mp_pos_data amcl_pos = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      7, this->amcl_pos(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_bag_ex::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string proto_type = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->proto_type().data(), this->proto_type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->proto_type(), target);
  }
  
  // required string robot_shape = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->robot_shape().data(), this->robot_shape().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->robot_shape(), target);
  }
  
  // required .KPS.mp_laser_ex_para laser_para = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->laser_para(), target);
  }
  
  // required .KPS.mp_laser_ex_data laser_ex_data = 4;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->laser_ex_data(), target);
  }
  
  // required .KPS.mp_laser_ref_data laser_ref_data = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->laser_ref_data(), target);
  }
  
  // required .KPS.mp_odom_data odom = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->odom(), target);
  }
  
  // required .KPS.mp_pos_data amcl_pos = 7;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        7, this->amcl_pos(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_bag_ex::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string proto_type = 1;
    if (has_proto_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->proto_type());
    }
    
    // required string robot_shape = 2;
    if (has_robot_shape()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->robot_shape());
    }
    
    // required .KPS.mp_laser_ex_para laser_para = 3;
    if (has_laser_para()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->laser_para());
    }
    
    // required .KPS.mp_laser_ex_data laser_ex_data = 4;
    if (has_laser_ex_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->laser_ex_data());
    }
    
    // required .KPS.mp_laser_ref_data laser_ref_data = 5;
    if (has_laser_ref_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->laser_ref_data());
    }
    
    // required .KPS.mp_odom_data odom = 6;
    if (has_odom()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->odom());
    }
    
    // required .KPS.mp_pos_data amcl_pos = 7;
    if (has_amcl_pos()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->amcl_pos());
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

void mp_bag_ex::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_bag_ex* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_bag_ex*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_bag_ex::MergeFrom(const mp_bag_ex& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_proto_type(from.proto_type());
    }
    if (from._has_bit(1)) {
      set_robot_shape(from.robot_shape());
    }
    if (from._has_bit(2)) {
      mutable_laser_para()->::KPS::mp_laser_ex_para::MergeFrom(from.laser_para());
    }
    if (from._has_bit(3)) {
      mutable_laser_ex_data()->::KPS::mp_laser_ex_data::MergeFrom(from.laser_ex_data());
    }
    if (from._has_bit(4)) {
      mutable_laser_ref_data()->::KPS::mp_laser_ref_data::MergeFrom(from.laser_ref_data());
    }
    if (from._has_bit(5)) {
      mutable_odom()->::KPS::mp_odom_data::MergeFrom(from.odom());
    }
    if (from._has_bit(6)) {
      mutable_amcl_pos()->::KPS::mp_pos_data::MergeFrom(from.amcl_pos());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_bag_ex::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_bag_ex::CopyFrom(const mp_bag_ex& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_bag_ex::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000007e) != 0x0000007e) return false;
  
  if (has_laser_para()) {
    if (!this->laser_para().IsInitialized()) return false;
  }
  if (has_laser_ex_data()) {
    if (!this->laser_ex_data().IsInitialized()) return false;
  }
  if (has_laser_ref_data()) {
    if (!this->laser_ref_data().IsInitialized()) return false;
  }
  if (has_odom()) {
    if (!this->odom().IsInitialized()) return false;
  }
  if (has_amcl_pos()) {
    if (!this->amcl_pos().IsInitialized()) return false;
  }
  return true;
}

void mp_bag_ex::Swap(mp_bag_ex* other) {
  if (other != this) {
    std::swap(proto_type_, other->proto_type_);
    std::swap(robot_shape_, other->robot_shape_);
    std::swap(laser_para_, other->laser_para_);
    std::swap(laser_ex_data_, other->laser_ex_data_);
    std::swap(laser_ref_data_, other->laser_ref_data_);
    std::swap(odom_, other->odom_);
    std::swap(amcl_pos_, other->amcl_pos_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_bag_ex::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_bag_ex_descriptor_;
  metadata.reflection = mp_bag_ex_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

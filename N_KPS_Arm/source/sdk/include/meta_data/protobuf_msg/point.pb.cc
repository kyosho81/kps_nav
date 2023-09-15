// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "point.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* s_point_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  s_point_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_point_2eproto() {
  protobuf_AddDesc_point_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "point.proto");
  GOOGLE_CHECK(file != NULL);
  s_point_descriptor_ = file->message_type(0);
  static const int s_point_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_point, x_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_point, y_),
  };
  s_point_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      s_point_descriptor_,
      s_point::default_instance_,
      s_point_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_point, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_point, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(s_point));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_point_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    s_point_descriptor_, &s_point::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_point_2eproto() {
  delete s_point::default_instance_;
  delete s_point_reflection_;
}

void protobuf_AddDesc_point_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013point.proto\022\003KPS\"\037\n\007s_point\022\t\n\001x\030\001 \002(\002"
    "\022\t\n\001y\030\002 \002(\002", 51);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "point.proto", &protobuf_RegisterTypes);
  s_point::default_instance_ = new s_point();
  s_point::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_point_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_point_2eproto {
  StaticDescriptorInitializer_point_2eproto() {
    protobuf_AddDesc_point_2eproto();
  }
} static_descriptor_initializer_point_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int s_point::kXFieldNumber;
const int s_point::kYFieldNumber;
#endif  // !_MSC_VER

s_point::s_point()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void s_point::InitAsDefaultInstance() {
}

s_point::s_point(const s_point& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void s_point::SharedCtor() {
  _cached_size_ = 0;
  x_ = 0;
  y_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

s_point::~s_point() {
  SharedDtor();
}

void s_point::SharedDtor() {
  if (this != default_instance_) {
  }
}

void s_point::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* s_point::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return s_point_descriptor_;
}

const s_point& s_point::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_point_2eproto();  return *default_instance_;
}

s_point* s_point::default_instance_ = NULL;

s_point* s_point::New() const {
  return new s_point;
}

void s_point::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    x_ = 0;
    y_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool s_point::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required float x = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &x_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_y;
        break;
      }
      
      // required float y = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &y_)));
          _set_bit(1);
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

void s_point::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required float x = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->x(), output);
  }
  
  // required float y = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->y(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* s_point::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required float x = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(1, this->x(), target);
  }
  
  // required float y = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->y(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int s_point::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required float x = 1;
    if (has_x()) {
      total_size += 1 + 4;
    }
    
    // required float y = 2;
    if (has_y()) {
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

void s_point::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const s_point* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const s_point*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void s_point::MergeFrom(const s_point& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_x(from.x());
    }
    if (from._has_bit(1)) {
      set_y(from.y());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void s_point::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void s_point::CopyFrom(const s_point& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool s_point::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void s_point::Swap(s_point* other) {
  if (other != this) {
    std::swap(x_, other->x_);
    std::swap(y_, other->y_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata s_point::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = s_point_descriptor_;
  metadata.reflection = s_point_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

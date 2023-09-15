// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "dev_status.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* mp_dev_status_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_dev_status_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_dev_5fstatus_2eproto() {
  protobuf_AddDesc_dev_5fstatus_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "dev_status.proto");
  GOOGLE_CHECK(file != NULL);
  mp_dev_status_descriptor_ = file->message_type(0);
  static const int mp_dev_status_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, dev_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, status_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, err_code_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, cycle_ms_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, run_ms_),
  };
  mp_dev_status_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_dev_status_descriptor_,
      mp_dev_status::default_instance_,
      mp_dev_status_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_dev_status, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_dev_status));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_dev_5fstatus_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_dev_status_descriptor_, &mp_dev_status::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_dev_5fstatus_2eproto() {
  delete mp_dev_status::default_instance_;
  delete mp_dev_status_reflection_;
}

void protobuf_AddDesc_dev_5fstatus_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020dev_status.proto\022\003KPS\"q\n\rmp_dev_status"
    "\022\014\n\004name\030\001 \002(\t\022\016\n\006dev_id\030\002 \002(\005\022\016\n\006status"
    "\030\003 \002(\005\022\020\n\010err_code\030\004 \002(\005\022\020\n\010cycle_ms\030\005 \002"
    "(\005\022\016\n\006run_ms\030\006 \002(\005", 138);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "dev_status.proto", &protobuf_RegisterTypes);
  mp_dev_status::default_instance_ = new mp_dev_status();
  mp_dev_status::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_dev_5fstatus_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_dev_5fstatus_2eproto {
  StaticDescriptorInitializer_dev_5fstatus_2eproto() {
    protobuf_AddDesc_dev_5fstatus_2eproto();
  }
} static_descriptor_initializer_dev_5fstatus_2eproto_;


// ===================================================================

const ::std::string mp_dev_status::_default_name_;
#ifndef _MSC_VER
const int mp_dev_status::kNameFieldNumber;
const int mp_dev_status::kDevIdFieldNumber;
const int mp_dev_status::kStatusFieldNumber;
const int mp_dev_status::kErrCodeFieldNumber;
const int mp_dev_status::kCycleMsFieldNumber;
const int mp_dev_status::kRunMsFieldNumber;
#endif  // !_MSC_VER

mp_dev_status::mp_dev_status()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_dev_status::InitAsDefaultInstance() {
}

mp_dev_status::mp_dev_status(const mp_dev_status& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_dev_status::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&_default_name_);
  dev_id_ = 0;
  status_ = 0;
  err_code_ = 0;
  cycle_ms_ = 0;
  run_ms_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_dev_status::~mp_dev_status() {
  SharedDtor();
}

void mp_dev_status::SharedDtor() {
  if (name_ != &_default_name_) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void mp_dev_status::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_dev_status::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_dev_status_descriptor_;
}

const mp_dev_status& mp_dev_status::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dev_5fstatus_2eproto();  return *default_instance_;
}

mp_dev_status* mp_dev_status::default_instance_ = NULL;

mp_dev_status* mp_dev_status::New() const {
  return new mp_dev_status;
}

void mp_dev_status::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (name_ != &_default_name_) {
        name_->clear();
      }
    }
    dev_id_ = 0;
    status_ = 0;
    err_code_ = 0;
    cycle_ms_ = 0;
    run_ms_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_dev_status::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_dev_id;
        break;
      }
      
      // required int32 dev_id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_dev_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &dev_id_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_status;
        break;
      }
      
      // required int32 status = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_status:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &status_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_err_code;
        break;
      }
      
      // required int32 err_code = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_err_code:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &err_code_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_cycle_ms;
        break;
      }
      
      // required int32 cycle_ms = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cycle_ms:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &cycle_ms_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_run_ms;
        break;
      }
      
      // required int32 run_ms = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_run_ms:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &run_ms_)));
          _set_bit(5);
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

void mp_dev_status::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }
  
  // required int32 dev_id = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->dev_id(), output);
  }
  
  // required int32 status = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->status(), output);
  }
  
  // required int32 err_code = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->err_code(), output);
  }
  
  // required int32 cycle_ms = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->cycle_ms(), output);
  }
  
  // required int32 run_ms = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->run_ms(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_dev_status::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }
  
  // required int32 dev_id = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->dev_id(), target);
  }
  
  // required int32 status = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->status(), target);
  }
  
  // required int32 err_code = 4;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->err_code(), target);
  }
  
  // required int32 cycle_ms = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->cycle_ms(), target);
  }
  
  // required int32 run_ms = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->run_ms(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_dev_status::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // required int32 dev_id = 2;
    if (has_dev_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->dev_id());
    }
    
    // required int32 status = 3;
    if (has_status()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->status());
    }
    
    // required int32 err_code = 4;
    if (has_err_code()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->err_code());
    }
    
    // required int32 cycle_ms = 5;
    if (has_cycle_ms()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->cycle_ms());
    }
    
    // required int32 run_ms = 6;
    if (has_run_ms()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->run_ms());
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

void mp_dev_status::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_dev_status* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_dev_status*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_dev_status::MergeFrom(const mp_dev_status& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_name(from.name());
    }
    if (from._has_bit(1)) {
      set_dev_id(from.dev_id());
    }
    if (from._has_bit(2)) {
      set_status(from.status());
    }
    if (from._has_bit(3)) {
      set_err_code(from.err_code());
    }
    if (from._has_bit(4)) {
      set_cycle_ms(from.cycle_ms());
    }
    if (from._has_bit(5)) {
      set_run_ms(from.run_ms());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_dev_status::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_dev_status::CopyFrom(const mp_dev_status& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_dev_status::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003f) != 0x0000003f) return false;
  
  return true;
}

void mp_dev_status::Swap(mp_dev_status* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(dev_id_, other->dev_id_);
    std::swap(status_, other->status_);
    std::swap(err_code_, other->err_code_);
    std::swap(cycle_ms_, other->cycle_ms_);
    std::swap(run_ms_, other->run_ms_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_dev_status::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_dev_status_descriptor_;
  metadata.reflection = mp_dev_status_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)
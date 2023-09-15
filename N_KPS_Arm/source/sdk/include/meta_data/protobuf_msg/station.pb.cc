// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "station.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* s_station_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  s_station_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_station_2eproto() {
  protobuf_AddDesc_station_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "station.proto");
  GOOGLE_CHECK(file != NULL);
  s_station_descriptor_ = file->message_type(0);
  static const int s_station_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_station, base_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_station, enable_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_station, sch_date_),
  };
  s_station_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      s_station_descriptor_,
      s_station::default_instance_,
      s_station_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_station, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_station, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(s_station));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_station_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    s_station_descriptor_, &s_station::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_station_2eproto() {
  delete s_station::default_instance_;
  delete s_station_reflection_;
}

void protobuf_AddDesc_station_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::KPS::protobuf_AddDesc_base_2eproto();
  ::KPS::protobuf_AddDesc_cargo_2eproto();
  ::KPS::protobuf_AddDesc_pallet_2eproto();
  ::KPS::protobuf_AddDesc_cargo_5ftype_2eproto();
  ::KPS::protobuf_AddDesc_pallet_5ftype_2eproto();
  ::KPS::protobuf_AddDesc_lab_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rstation.proto\022\003KPS\032\nbase.proto\032\013cargo."
    "proto\032\014pallet.proto\032\020cargo_type.proto\032\021p"
    "allet_type.proto\032\tlab.proto\"N\n\ts_station"
    "\022\037\n\004base\030\001 \002(\0132\021.KPS.mp_item_base\022\016\n\006ena"
    "ble\030\002 \002(\010\022\020\n\010sch_date\030\003 \002(\t", 187);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "station.proto", &protobuf_RegisterTypes);
  s_station::default_instance_ = new s_station();
  s_station::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_station_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_station_2eproto {
  StaticDescriptorInitializer_station_2eproto() {
    protobuf_AddDesc_station_2eproto();
  }
} static_descriptor_initializer_station_2eproto_;


// ===================================================================

const ::std::string s_station::_default_sch_date_;
#ifndef _MSC_VER
const int s_station::kBaseFieldNumber;
const int s_station::kEnableFieldNumber;
const int s_station::kSchDateFieldNumber;
#endif  // !_MSC_VER

s_station::s_station()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void s_station::InitAsDefaultInstance() {
  base_ = const_cast< ::KPS::mp_item_base*>(&::KPS::mp_item_base::default_instance());
}

s_station::s_station(const s_station& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void s_station::SharedCtor() {
  _cached_size_ = 0;
  base_ = NULL;
  enable_ = false;
  sch_date_ = const_cast< ::std::string*>(&_default_sch_date_);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

s_station::~s_station() {
  SharedDtor();
}

void s_station::SharedDtor() {
  if (sch_date_ != &_default_sch_date_) {
    delete sch_date_;
  }
  if (this != default_instance_) {
    delete base_;
  }
}

void s_station::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* s_station::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return s_station_descriptor_;
}

const s_station& s_station::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_station_2eproto();  return *default_instance_;
}

s_station* s_station::default_instance_ = NULL;

s_station* s_station::New() const {
  return new s_station;
}

void s_station::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (base_ != NULL) base_->::KPS::mp_item_base::Clear();
    }
    enable_ = false;
    if (_has_bit(2)) {
      if (sch_date_ != &_default_sch_date_) {
        sch_date_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool s_station::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .KPS.mp_item_base base = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_base()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_enable;
        break;
      }
      
      // required bool enable = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_enable:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &enable_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_sch_date;
        break;
      }
      
      // required string sch_date = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_sch_date:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sch_date()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->sch_date().data(), this->sch_date().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
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

void s_station::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .KPS.mp_item_base base = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->base(), output);
  }
  
  // required bool enable = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->enable(), output);
  }
  
  // required string sch_date = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->sch_date().data(), this->sch_date().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->sch_date(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* s_station::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .KPS.mp_item_base base = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->base(), target);
  }
  
  // required bool enable = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->enable(), target);
  }
  
  // required string sch_date = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->sch_date().data(), this->sch_date().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->sch_date(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int s_station::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .KPS.mp_item_base base = 1;
    if (has_base()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->base());
    }
    
    // required bool enable = 2;
    if (has_enable()) {
      total_size += 1 + 1;
    }
    
    // required string sch_date = 3;
    if (has_sch_date()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->sch_date());
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

void s_station::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const s_station* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const s_station*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void s_station::MergeFrom(const s_station& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_base()->::KPS::mp_item_base::MergeFrom(from.base());
    }
    if (from._has_bit(1)) {
      set_enable(from.enable());
    }
    if (from._has_bit(2)) {
      set_sch_date(from.sch_date());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void s_station::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void s_station::CopyFrom(const s_station& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool s_station::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  if (has_base()) {
    if (!this->base().IsInitialized()) return false;
  }
  return true;
}

void s_station::Swap(s_station* other) {
  if (other != this) {
    std::swap(base_, other->base_);
    std::swap(enable_, other->enable_);
    std::swap(sch_date_, other->sch_date_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata s_station::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = s_station_descriptor_;
  metadata.reflection = s_station_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)
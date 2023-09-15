// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "dio.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* mp_sdi_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_sdi_reflection_ = NULL;
const ::google::protobuf::Descriptor* mp_sdo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_sdo_reflection_ = NULL;
const ::google::protobuf::Descriptor* mp_sfai_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_sfai_reflection_ = NULL;
const ::google::protobuf::Descriptor* mp_sfao_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_sfao_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_dio_2eproto() {
  protobuf_AddDesc_dio_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "dio.proto");
  GOOGLE_CHECK(file != NULL);
  mp_sdi_descriptor_ = file->message_type(0);
  static const int mp_sdi_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdi, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdi, di_),
  };
  mp_sdi_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_sdi_descriptor_,
      mp_sdi::default_instance_,
      mp_sdi_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdi, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdi, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_sdi));
  mp_sdo_descriptor_ = file->message_type(1);
  static const int mp_sdo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdo, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdo, doo_),
  };
  mp_sdo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_sdo_descriptor_,
      mp_sdo::default_instance_,
      mp_sdo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sdo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_sdo));
  mp_sfai_descriptor_ = file->message_type(2);
  static const int mp_sfai_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfai, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfai, fai_),
  };
  mp_sfai_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_sfai_descriptor_,
      mp_sfai::default_instance_,
      mp_sfai_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfai, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfai, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_sfai));
  mp_sfao_descriptor_ = file->message_type(3);
  static const int mp_sfao_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfao, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfao, fao_),
  };
  mp_sfao_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_sfao_descriptor_,
      mp_sfao::default_instance_,
      mp_sfao_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfao, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_sfao, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_sfao));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_dio_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_sdi_descriptor_, &mp_sdi::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_sdo_descriptor_, &mp_sdo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_sfai_descriptor_, &mp_sfai::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_sfao_descriptor_, &mp_sfao::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_dio_2eproto() {
  delete mp_sdi::default_instance_;
  delete mp_sdi_reflection_;
  delete mp_sdo::default_instance_;
  delete mp_sdo_reflection_;
  delete mp_sfai::default_instance_;
  delete mp_sfai_reflection_;
  delete mp_sfao::default_instance_;
  delete mp_sfao_reflection_;
}

void protobuf_AddDesc_dio_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\tdio.proto\022\003KPS\" \n\006mp_sdi\022\n\n\002id\030\001 \003(\r\022\n"
    "\n\002di\030\002 \003(\005\"!\n\006mp_sdo\022\n\n\002id\030\001 \003(\r\022\013\n\003doo\030"
    "\002 \003(\005\"\"\n\007mp_sfai\022\n\n\002id\030\001 \003(\r\022\013\n\003fai\030\002 \003("
    "\002\"\"\n\007mp_sfao\022\n\n\002id\030\001 \003(\r\022\013\n\003fao\030\002 \003(\002", 157);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "dio.proto", &protobuf_RegisterTypes);
  mp_sdi::default_instance_ = new mp_sdi();
  mp_sdo::default_instance_ = new mp_sdo();
  mp_sfai::default_instance_ = new mp_sfai();
  mp_sfao::default_instance_ = new mp_sfao();
  mp_sdi::default_instance_->InitAsDefaultInstance();
  mp_sdo::default_instance_->InitAsDefaultInstance();
  mp_sfai::default_instance_->InitAsDefaultInstance();
  mp_sfao::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_dio_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_dio_2eproto {
  StaticDescriptorInitializer_dio_2eproto() {
    protobuf_AddDesc_dio_2eproto();
  }
} static_descriptor_initializer_dio_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int mp_sdi::kIdFieldNumber;
const int mp_sdi::kDiFieldNumber;
#endif  // !_MSC_VER

mp_sdi::mp_sdi()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_sdi::InitAsDefaultInstance() {
}

mp_sdi::mp_sdi(const mp_sdi& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_sdi::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_sdi::~mp_sdi() {
  SharedDtor();
}

void mp_sdi::SharedDtor() {
  if (this != default_instance_) {
  }
}

void mp_sdi::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_sdi::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_sdi_descriptor_;
}

const mp_sdi& mp_sdi::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dio_2eproto();  return *default_instance_;
}

mp_sdi* mp_sdi::default_instance_ = NULL;

mp_sdi* mp_sdi::New() const {
  return new mp_sdi;
}

void mp_sdi::Clear() {
  id_.Clear();
  di_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_sdi::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_id())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_id())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_id;
        if (input->ExpectTag(16)) goto parse_di;
        break;
      }
      
      // repeated int32 di = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_di:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 16, input, this->mutable_di())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_di())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_di;
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

void mp_sdi::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->id(i), output);
  }
  
  // repeated int32 di = 2;
  for (int i = 0; i < this->di_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      2, this->di(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_sdi::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->id(i), target);
  }
  
  // repeated int32 di = 2;
  for (int i = 0; i < this->di_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(2, this->di(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_sdi::ByteSize() const {
  int total_size = 0;
  
  // repeated uint32 id = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->id(i));
    }
    total_size += 1 * this->id_size() + data_size;
  }
  
  // repeated int32 di = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->di_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->di(i));
    }
    total_size += 1 * this->di_size() + data_size;
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

void mp_sdi::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_sdi* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_sdi*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_sdi::MergeFrom(const mp_sdi& from) {
  GOOGLE_CHECK_NE(&from, this);
  id_.MergeFrom(from.id_);
  di_.MergeFrom(from.di_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_sdi::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_sdi::CopyFrom(const mp_sdi& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_sdi::IsInitialized() const {
  
  return true;
}

void mp_sdi::Swap(mp_sdi* other) {
  if (other != this) {
    id_.Swap(&other->id_);
    di_.Swap(&other->di_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_sdi::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_sdi_descriptor_;
  metadata.reflection = mp_sdi_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int mp_sdo::kIdFieldNumber;
const int mp_sdo::kDooFieldNumber;
#endif  // !_MSC_VER

mp_sdo::mp_sdo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_sdo::InitAsDefaultInstance() {
}

mp_sdo::mp_sdo(const mp_sdo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_sdo::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_sdo::~mp_sdo() {
  SharedDtor();
}

void mp_sdo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void mp_sdo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_sdo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_sdo_descriptor_;
}

const mp_sdo& mp_sdo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dio_2eproto();  return *default_instance_;
}

mp_sdo* mp_sdo::default_instance_ = NULL;

mp_sdo* mp_sdo::New() const {
  return new mp_sdo;
}

void mp_sdo::Clear() {
  id_.Clear();
  doo_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_sdo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_id())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_id())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_id;
        if (input->ExpectTag(16)) goto parse_doo;
        break;
      }
      
      // repeated int32 doo = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_doo:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 16, input, this->mutable_doo())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_doo())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_doo;
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

void mp_sdo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->id(i), output);
  }
  
  // repeated int32 doo = 2;
  for (int i = 0; i < this->doo_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      2, this->doo(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_sdo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->id(i), target);
  }
  
  // repeated int32 doo = 2;
  for (int i = 0; i < this->doo_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(2, this->doo(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_sdo::ByteSize() const {
  int total_size = 0;
  
  // repeated uint32 id = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->id(i));
    }
    total_size += 1 * this->id_size() + data_size;
  }
  
  // repeated int32 doo = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->doo_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->doo(i));
    }
    total_size += 1 * this->doo_size() + data_size;
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

void mp_sdo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_sdo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_sdo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_sdo::MergeFrom(const mp_sdo& from) {
  GOOGLE_CHECK_NE(&from, this);
  id_.MergeFrom(from.id_);
  doo_.MergeFrom(from.doo_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_sdo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_sdo::CopyFrom(const mp_sdo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_sdo::IsInitialized() const {
  
  return true;
}

void mp_sdo::Swap(mp_sdo* other) {
  if (other != this) {
    id_.Swap(&other->id_);
    doo_.Swap(&other->doo_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_sdo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_sdo_descriptor_;
  metadata.reflection = mp_sdo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int mp_sfai::kIdFieldNumber;
const int mp_sfai::kFaiFieldNumber;
#endif  // !_MSC_VER

mp_sfai::mp_sfai()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_sfai::InitAsDefaultInstance() {
}

mp_sfai::mp_sfai(const mp_sfai& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_sfai::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_sfai::~mp_sfai() {
  SharedDtor();
}

void mp_sfai::SharedDtor() {
  if (this != default_instance_) {
  }
}

void mp_sfai::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_sfai::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_sfai_descriptor_;
}

const mp_sfai& mp_sfai::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dio_2eproto();  return *default_instance_;
}

mp_sfai* mp_sfai::default_instance_ = NULL;

mp_sfai* mp_sfai::New() const {
  return new mp_sfai;
}

void mp_sfai::Clear() {
  id_.Clear();
  fai_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_sfai::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_id())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_id())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_id;
        if (input->ExpectTag(21)) goto parse_fai;
        break;
      }
      
      // repeated float fai = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_fai:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 1, 21, input, this->mutable_fai())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, this->mutable_fai())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_fai;
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

void mp_sfai::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->id(i), output);
  }
  
  // repeated float fai = 2;
  for (int i = 0; i < this->fai_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(
      2, this->fai(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_sfai::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->id(i), target);
  }
  
  // repeated float fai = 2;
  for (int i = 0; i < this->fai_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteFloatToArray(2, this->fai(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_sfai::ByteSize() const {
  int total_size = 0;
  
  // repeated uint32 id = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->id(i));
    }
    total_size += 1 * this->id_size() + data_size;
  }
  
  // repeated float fai = 2;
  {
    int data_size = 0;
    data_size = 4 * this->fai_size();
    total_size += 1 * this->fai_size() + data_size;
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

void mp_sfai::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_sfai* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_sfai*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_sfai::MergeFrom(const mp_sfai& from) {
  GOOGLE_CHECK_NE(&from, this);
  id_.MergeFrom(from.id_);
  fai_.MergeFrom(from.fai_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_sfai::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_sfai::CopyFrom(const mp_sfai& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_sfai::IsInitialized() const {
  
  return true;
}

void mp_sfai::Swap(mp_sfai* other) {
  if (other != this) {
    id_.Swap(&other->id_);
    fai_.Swap(&other->fai_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_sfai::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_sfai_descriptor_;
  metadata.reflection = mp_sfai_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int mp_sfao::kIdFieldNumber;
const int mp_sfao::kFaoFieldNumber;
#endif  // !_MSC_VER

mp_sfao::mp_sfao()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_sfao::InitAsDefaultInstance() {
}

mp_sfao::mp_sfao(const mp_sfao& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_sfao::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_sfao::~mp_sfao() {
  SharedDtor();
}

void mp_sfao::SharedDtor() {
  if (this != default_instance_) {
  }
}

void mp_sfao::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_sfao::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_sfao_descriptor_;
}

const mp_sfao& mp_sfao::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dio_2eproto();  return *default_instance_;
}

mp_sfao* mp_sfao::default_instance_ = NULL;

mp_sfao* mp_sfao::New() const {
  return new mp_sfao;
}

void mp_sfao::Clear() {
  id_.Clear();
  fao_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_sfao::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_id())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_id())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_id;
        if (input->ExpectTag(21)) goto parse_fao;
        break;
      }
      
      // repeated float fao = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_fao:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 1, 21, input, this->mutable_fao())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, this->mutable_fao())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_fao;
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

void mp_sfao::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->id(i), output);
  }
  
  // repeated float fao = 2;
  for (int i = 0; i < this->fao_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(
      2, this->fao(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_sfao::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 id = 1;
  for (int i = 0; i < this->id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->id(i), target);
  }
  
  // repeated float fao = 2;
  for (int i = 0; i < this->fao_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteFloatToArray(2, this->fao(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_sfao::ByteSize() const {
  int total_size = 0;
  
  // repeated uint32 id = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->id(i));
    }
    total_size += 1 * this->id_size() + data_size;
  }
  
  // repeated float fao = 2;
  {
    int data_size = 0;
    data_size = 4 * this->fao_size();
    total_size += 1 * this->fao_size() + data_size;
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

void mp_sfao::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_sfao* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_sfao*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_sfao::MergeFrom(const mp_sfao& from) {
  GOOGLE_CHECK_NE(&from, this);
  id_.MergeFrom(from.id_);
  fao_.MergeFrom(from.fao_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_sfao::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_sfao::CopyFrom(const mp_sfao& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_sfao::IsInitialized() const {
  
  return true;
}

void mp_sfao::Swap(mp_sfao* other) {
  if (other != this) {
    id_.Swap(&other->id_);
    fao_.Swap(&other->fao_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_sfao::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_sfao_descriptor_;
  metadata.reflection = mp_sfao_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "conf_ref_pos.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* mp_conf_ref_pos_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_conf_ref_pos_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_conf_5fref_5fpos_2eproto() {
  protobuf_AddDesc_conf_5fref_5fpos_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "conf_ref_pos.proto");
  GOOGLE_CHECK(file != NULL);
  mp_conf_ref_pos_descriptor_ = file->message_type(0);
  static const int mp_conf_ref_pos_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_conf_ref_pos, b_conf_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_conf_ref_pos, confidence_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_conf_ref_pos, ref_pos_),
  };
  mp_conf_ref_pos_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_conf_ref_pos_descriptor_,
      mp_conf_ref_pos::default_instance_,
      mp_conf_ref_pos_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_conf_ref_pos, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_conf_ref_pos, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_conf_ref_pos));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_conf_5fref_5fpos_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_conf_ref_pos_descriptor_, &mp_conf_ref_pos::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_conf_5fref_5fpos_2eproto() {
  delete mp_conf_ref_pos::default_instance_;
  delete mp_conf_ref_pos_reflection_;
}

void protobuf_AddDesc_conf_5fref_5fpos_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::KPS::protobuf_AddDesc_base_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022conf_ref_pos.proto\022\003KPS\032\nbase.proto\"X\n"
    "\017mp_conf_ref_pos\022\016\n\006b_conf\030\001 \002(\010\022\022\n\nconf"
    "idence\030\002 \002(\002\022!\n\007ref_pos\030\003 \002(\0132\020.KPS.mp_p"
    "os_data", 127);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "conf_ref_pos.proto", &protobuf_RegisterTypes);
  mp_conf_ref_pos::default_instance_ = new mp_conf_ref_pos();
  mp_conf_ref_pos::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_conf_5fref_5fpos_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_conf_5fref_5fpos_2eproto {
  StaticDescriptorInitializer_conf_5fref_5fpos_2eproto() {
    protobuf_AddDesc_conf_5fref_5fpos_2eproto();
  }
} static_descriptor_initializer_conf_5fref_5fpos_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int mp_conf_ref_pos::kBConfFieldNumber;
const int mp_conf_ref_pos::kConfidenceFieldNumber;
const int mp_conf_ref_pos::kRefPosFieldNumber;
#endif  // !_MSC_VER

mp_conf_ref_pos::mp_conf_ref_pos()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_conf_ref_pos::InitAsDefaultInstance() {
  ref_pos_ = const_cast< ::KPS::mp_pos_data*>(&::KPS::mp_pos_data::default_instance());
}

mp_conf_ref_pos::mp_conf_ref_pos(const mp_conf_ref_pos& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_conf_ref_pos::SharedCtor() {
  _cached_size_ = 0;
  b_conf_ = false;
  confidence_ = 0;
  ref_pos_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_conf_ref_pos::~mp_conf_ref_pos() {
  SharedDtor();
}

void mp_conf_ref_pos::SharedDtor() {
  if (this != default_instance_) {
    delete ref_pos_;
  }
}

void mp_conf_ref_pos::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_conf_ref_pos::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_conf_ref_pos_descriptor_;
}

const mp_conf_ref_pos& mp_conf_ref_pos::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_conf_5fref_5fpos_2eproto();  return *default_instance_;
}

mp_conf_ref_pos* mp_conf_ref_pos::default_instance_ = NULL;

mp_conf_ref_pos* mp_conf_ref_pos::New() const {
  return new mp_conf_ref_pos;
}

void mp_conf_ref_pos::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    b_conf_ = false;
    confidence_ = 0;
    if (_has_bit(2)) {
      if (ref_pos_ != NULL) ref_pos_->::KPS::mp_pos_data::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_conf_ref_pos::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bool b_conf = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &b_conf_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_confidence;
        break;
      }
      
      // required float confidence = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_confidence:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &confidence_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_ref_pos;
        break;
      }
      
      // required .KPS.mp_pos_data ref_pos = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_ref_pos:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_ref_pos()));
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

void mp_conf_ref_pos::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required bool b_conf = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->b_conf(), output);
  }
  
  // required float confidence = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->confidence(), output);
  }
  
  // required .KPS.mp_pos_data ref_pos = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->ref_pos(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_conf_ref_pos::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required bool b_conf = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->b_conf(), target);
  }
  
  // required float confidence = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->confidence(), target);
  }
  
  // required .KPS.mp_pos_data ref_pos = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->ref_pos(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_conf_ref_pos::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bool b_conf = 1;
    if (has_b_conf()) {
      total_size += 1 + 1;
    }
    
    // required float confidence = 2;
    if (has_confidence()) {
      total_size += 1 + 4;
    }
    
    // required .KPS.mp_pos_data ref_pos = 3;
    if (has_ref_pos()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->ref_pos());
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

void mp_conf_ref_pos::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_conf_ref_pos* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_conf_ref_pos*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_conf_ref_pos::MergeFrom(const mp_conf_ref_pos& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_b_conf(from.b_conf());
    }
    if (from._has_bit(1)) {
      set_confidence(from.confidence());
    }
    if (from._has_bit(2)) {
      mutable_ref_pos()->::KPS::mp_pos_data::MergeFrom(from.ref_pos());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_conf_ref_pos::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_conf_ref_pos::CopyFrom(const mp_conf_ref_pos& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_conf_ref_pos::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  if (has_ref_pos()) {
    if (!this->ref_pos().IsInitialized()) return false;
  }
  return true;
}

void mp_conf_ref_pos::Swap(mp_conf_ref_pos* other) {
  if (other != this) {
    std::swap(b_conf_, other->b_conf_);
    std::swap(confidence_, other->confidence_);
    std::swap(ref_pos_, other->ref_pos_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_conf_ref_pos::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_conf_ref_pos_descriptor_;
  metadata.reflection = mp_conf_ref_pos_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "cargo_type.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* mp_cargo_type_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  mp_cargo_type_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_cargo_5ftype_2eproto() {
  protobuf_AddDesc_cargo_5ftype_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "cargo_type.proto");
  GOOGLE_CHECK(file != NULL);
  mp_cargo_type_descriptor_ = file->message_type(0);
  static const int mp_cargo_type_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, base_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, cargo_type_nm__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, cargo_shape_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, pallet_type_uuid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, operation_list_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, ms_produce_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, ms_consume_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, weight_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, volume_),
  };
  mp_cargo_type_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      mp_cargo_type_descriptor_,
      mp_cargo_type::default_instance_,
      mp_cargo_type_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(mp_cargo_type, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(mp_cargo_type));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_cargo_5ftype_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    mp_cargo_type_descriptor_, &mp_cargo_type::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_cargo_5ftype_2eproto() {
  delete mp_cargo_type::default_instance_;
  delete mp_cargo_type_reflection_;
}

void protobuf_AddDesc_cargo_5ftype_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::KPS::protobuf_AddDesc_base_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020cargo_type.proto\022\003KPS\032\nbase.proto\"\341\001\n\r"
    "mp_cargo_type\022\037\n\004base\030\001 \002(\0132\021.KPS.mp_ite"
    "m_base\022\026\n\016cargo_type_nm_\030\002 \002(\t\022\023\n\013cargo_"
    "shape\030\003 \002(\r\022\030\n\020pallet_type_uuid\030\004 \002(\t\022\026\n"
    "\016operation_list\030\005 \002(\t\022\027\n\017ms_produce_time"
    "\030\006 \001(\r\022\027\n\017ms_consume_time\030\007 \001(\r\022\016\n\006weigh"
    "t\030\010 \001(\t\022\016\n\006volume\030\t \001(\t", 263);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "cargo_type.proto", &protobuf_RegisterTypes);
  mp_cargo_type::default_instance_ = new mp_cargo_type();
  mp_cargo_type::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_cargo_5ftype_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_cargo_5ftype_2eproto {
  StaticDescriptorInitializer_cargo_5ftype_2eproto() {
    protobuf_AddDesc_cargo_5ftype_2eproto();
  }
} static_descriptor_initializer_cargo_5ftype_2eproto_;


// ===================================================================

const ::std::string mp_cargo_type::_default_cargo_type_nm__;
const ::std::string mp_cargo_type::_default_pallet_type_uuid_;
const ::std::string mp_cargo_type::_default_operation_list_;
const ::std::string mp_cargo_type::_default_weight_;
const ::std::string mp_cargo_type::_default_volume_;
#ifndef _MSC_VER
const int mp_cargo_type::kBaseFieldNumber;
const int mp_cargo_type::kCargoTypeNmFieldNumber;
const int mp_cargo_type::kCargoShapeFieldNumber;
const int mp_cargo_type::kPalletTypeUuidFieldNumber;
const int mp_cargo_type::kOperationListFieldNumber;
const int mp_cargo_type::kMsProduceTimeFieldNumber;
const int mp_cargo_type::kMsConsumeTimeFieldNumber;
const int mp_cargo_type::kWeightFieldNumber;
const int mp_cargo_type::kVolumeFieldNumber;
#endif  // !_MSC_VER

mp_cargo_type::mp_cargo_type()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void mp_cargo_type::InitAsDefaultInstance() {
  base_ = const_cast< ::KPS::mp_item_base*>(&::KPS::mp_item_base::default_instance());
}

mp_cargo_type::mp_cargo_type(const mp_cargo_type& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void mp_cargo_type::SharedCtor() {
  _cached_size_ = 0;
  base_ = NULL;
  cargo_type_nm__ = const_cast< ::std::string*>(&_default_cargo_type_nm__);
  cargo_shape_ = 0u;
  pallet_type_uuid_ = const_cast< ::std::string*>(&_default_pallet_type_uuid_);
  operation_list_ = const_cast< ::std::string*>(&_default_operation_list_);
  ms_produce_time_ = 0u;
  ms_consume_time_ = 0u;
  weight_ = const_cast< ::std::string*>(&_default_weight_);
  volume_ = const_cast< ::std::string*>(&_default_volume_);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

mp_cargo_type::~mp_cargo_type() {
  SharedDtor();
}

void mp_cargo_type::SharedDtor() {
  if (cargo_type_nm__ != &_default_cargo_type_nm__) {
    delete cargo_type_nm__;
  }
  if (pallet_type_uuid_ != &_default_pallet_type_uuid_) {
    delete pallet_type_uuid_;
  }
  if (operation_list_ != &_default_operation_list_) {
    delete operation_list_;
  }
  if (weight_ != &_default_weight_) {
    delete weight_;
  }
  if (volume_ != &_default_volume_) {
    delete volume_;
  }
  if (this != default_instance_) {
    delete base_;
  }
}

void mp_cargo_type::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* mp_cargo_type::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return mp_cargo_type_descriptor_;
}

const mp_cargo_type& mp_cargo_type::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_cargo_5ftype_2eproto();  return *default_instance_;
}

mp_cargo_type* mp_cargo_type::default_instance_ = NULL;

mp_cargo_type* mp_cargo_type::New() const {
  return new mp_cargo_type;
}

void mp_cargo_type::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (base_ != NULL) base_->::KPS::mp_item_base::Clear();
    }
    if (_has_bit(1)) {
      if (cargo_type_nm__ != &_default_cargo_type_nm__) {
        cargo_type_nm__->clear();
      }
    }
    cargo_shape_ = 0u;
    if (_has_bit(3)) {
      if (pallet_type_uuid_ != &_default_pallet_type_uuid_) {
        pallet_type_uuid_->clear();
      }
    }
    if (_has_bit(4)) {
      if (operation_list_ != &_default_operation_list_) {
        operation_list_->clear();
      }
    }
    ms_produce_time_ = 0u;
    ms_consume_time_ = 0u;
    if (_has_bit(7)) {
      if (weight_ != &_default_weight_) {
        weight_->clear();
      }
    }
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (_has_bit(8)) {
      if (volume_ != &_default_volume_) {
        volume_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool mp_cargo_type::MergePartialFromCodedStream(
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
        if (input->ExpectTag(18)) goto parse_cargo_type_nm_;
        break;
      }
      
      // required string cargo_type_nm_ = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_cargo_type_nm_:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_cargo_type_nm_()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->cargo_type_nm_().data(), this->cargo_type_nm_().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_cargo_shape;
        break;
      }
      
      // required uint32 cargo_shape = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cargo_shape:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cargo_shape_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_pallet_type_uuid;
        break;
      }
      
      // required string pallet_type_uuid = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_pallet_type_uuid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_pallet_type_uuid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->pallet_type_uuid().data(), this->pallet_type_uuid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_operation_list;
        break;
      }
      
      // required string operation_list = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_operation_list:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_operation_list()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->operation_list().data(), this->operation_list().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_ms_produce_time;
        break;
      }
      
      // optional uint32 ms_produce_time = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_ms_produce_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ms_produce_time_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_ms_consume_time;
        break;
      }
      
      // optional uint32 ms_consume_time = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_ms_consume_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ms_consume_time_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_weight;
        break;
      }
      
      // optional string weight = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_weight:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_weight()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->weight().data(), this->weight().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_volume;
        break;
      }
      
      // optional string volume = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_volume:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_volume()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->volume().data(), this->volume().length(),
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

void mp_cargo_type::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .KPS.mp_item_base base = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->base(), output);
  }
  
  // required string cargo_type_nm_ = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->cargo_type_nm_().data(), this->cargo_type_nm_().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->cargo_type_nm_(), output);
  }
  
  // required uint32 cargo_shape = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->cargo_shape(), output);
  }
  
  // required string pallet_type_uuid = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->pallet_type_uuid().data(), this->pallet_type_uuid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->pallet_type_uuid(), output);
  }
  
  // required string operation_list = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->operation_list().data(), this->operation_list().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->operation_list(), output);
  }
  
  // optional uint32 ms_produce_time = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->ms_produce_time(), output);
  }
  
  // optional uint32 ms_consume_time = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->ms_consume_time(), output);
  }
  
  // optional string weight = 8;
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->weight().data(), this->weight().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      8, this->weight(), output);
  }
  
  // optional string volume = 9;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->volume().data(), this->volume().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      9, this->volume(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* mp_cargo_type::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .KPS.mp_item_base base = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->base(), target);
  }
  
  // required string cargo_type_nm_ = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->cargo_type_nm_().data(), this->cargo_type_nm_().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->cargo_type_nm_(), target);
  }
  
  // required uint32 cargo_shape = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->cargo_shape(), target);
  }
  
  // required string pallet_type_uuid = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->pallet_type_uuid().data(), this->pallet_type_uuid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->pallet_type_uuid(), target);
  }
  
  // required string operation_list = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->operation_list().data(), this->operation_list().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->operation_list(), target);
  }
  
  // optional uint32 ms_produce_time = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->ms_produce_time(), target);
  }
  
  // optional uint32 ms_consume_time = 7;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->ms_consume_time(), target);
  }
  
  // optional string weight = 8;
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->weight().data(), this->weight().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        8, this->weight(), target);
  }
  
  // optional string volume = 9;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->volume().data(), this->volume().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->volume(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int mp_cargo_type::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .KPS.mp_item_base base = 1;
    if (has_base()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->base());
    }
    
    // required string cargo_type_nm_ = 2;
    if (has_cargo_type_nm_()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->cargo_type_nm_());
    }
    
    // required uint32 cargo_shape = 3;
    if (has_cargo_shape()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cargo_shape());
    }
    
    // required string pallet_type_uuid = 4;
    if (has_pallet_type_uuid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->pallet_type_uuid());
    }
    
    // required string operation_list = 5;
    if (has_operation_list()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->operation_list());
    }
    
    // optional uint32 ms_produce_time = 6;
    if (has_ms_produce_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ms_produce_time());
    }
    
    // optional uint32 ms_consume_time = 7;
    if (has_ms_consume_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ms_consume_time());
    }
    
    // optional string weight = 8;
    if (has_weight()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->weight());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional string volume = 9;
    if (has_volume()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->volume());
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

void mp_cargo_type::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const mp_cargo_type* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const mp_cargo_type*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void mp_cargo_type::MergeFrom(const mp_cargo_type& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_base()->::KPS::mp_item_base::MergeFrom(from.base());
    }
    if (from._has_bit(1)) {
      set_cargo_type_nm_(from.cargo_type_nm_());
    }
    if (from._has_bit(2)) {
      set_cargo_shape(from.cargo_shape());
    }
    if (from._has_bit(3)) {
      set_pallet_type_uuid(from.pallet_type_uuid());
    }
    if (from._has_bit(4)) {
      set_operation_list(from.operation_list());
    }
    if (from._has_bit(5)) {
      set_ms_produce_time(from.ms_produce_time());
    }
    if (from._has_bit(6)) {
      set_ms_consume_time(from.ms_consume_time());
    }
    if (from._has_bit(7)) {
      set_weight(from.weight());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_volume(from.volume());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void mp_cargo_type::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void mp_cargo_type::CopyFrom(const mp_cargo_type& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool mp_cargo_type::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  
  if (has_base()) {
    if (!this->base().IsInitialized()) return false;
  }
  return true;
}

void mp_cargo_type::Swap(mp_cargo_type* other) {
  if (other != this) {
    std::swap(base_, other->base_);
    std::swap(cargo_type_nm__, other->cargo_type_nm__);
    std::swap(cargo_shape_, other->cargo_shape_);
    std::swap(pallet_type_uuid_, other->pallet_type_uuid_);
    std::swap(operation_list_, other->operation_list_);
    std::swap(ms_produce_time_, other->ms_produce_time_);
    std::swap(ms_consume_time_, other->ms_consume_time_);
    std::swap(weight_, other->weight_);
    std::swap(volume_, other->volume_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata mp_cargo_type::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = mp_cargo_type_descriptor_;
  metadata.reflection = mp_cargo_type_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

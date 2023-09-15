// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "view_data.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace KPS {

namespace {

const ::google::protobuf::Descriptor* s_view_data_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  s_view_data_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* s_view_data_Shape_Type_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* s_view_data_Insert_Type_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_view_5fdata_2eproto() {
  protobuf_AddDesc_view_5fdata_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "view_data.proto");
  GOOGLE_CHECK(file != NULL);
  s_view_data_descriptor_ = file->message_type(0);
  static const int s_view_data_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, insert_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, pos_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, point_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, shape_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, lab_),
  };
  s_view_data_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      s_view_data_descriptor_,
      s_view_data::default_instance_,
      s_view_data_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(s_view_data, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(s_view_data));
  s_view_data_Shape_Type_descriptor_ = s_view_data_descriptor_->enum_type(0);
  s_view_data_Insert_Type_descriptor_ = s_view_data_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_view_5fdata_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    s_view_data_descriptor_, &s_view_data::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_view_5fdata_2eproto() {
  delete s_view_data::default_instance_;
  delete s_view_data_reflection_;
}

void protobuf_AddDesc_view_5fdata_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::KPS::protobuf_AddDesc_point_2eproto();
  ::KPS::protobuf_AddDesc_pos_2eproto();
  ::KPS::protobuf_AddDesc_lab_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017view_data.proto\022\003KPS\032\013point.proto\032\tpos"
    ".proto\032\tlab.proto\"\261\002\n\013s_view_data\022\014\n\004nam"
    "e\030\001 \002(\t\0221\n\013insert_type\030\002 \002(\0162\034.KPS.s_vie"
    "w_data.Insert_Type\022\027\n\003pos\030\003 \003(\0132\n.KPS.s_"
    "pos\022\033\n\005point\030\004 \003(\0132\014.KPS.s_point\022/\n\nshap"
    "e_type\030\005 \001(\0162\033.KPS.s_view_data.Shape_Typ"
    "e\022\030\n\003lab\030\006 \001(\0132\013.KPS.mp_lab\"=\n\nShape_Typ"
    "e\022\n\n\006CIRCLE\020\000\022\014\n\010TRIANGLE\020\001\022\n\n\006SQUARE\020\002\022"
    "\t\n\005ARROW\020\003\"!\n\013Insert_Type\022\007\n\003NEW\020\000\022\t\n\005ME"
    "RGE\020\001", 365);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "view_data.proto", &protobuf_RegisterTypes);
  s_view_data::default_instance_ = new s_view_data();
  s_view_data::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_view_5fdata_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_view_5fdata_2eproto {
  StaticDescriptorInitializer_view_5fdata_2eproto() {
    protobuf_AddDesc_view_5fdata_2eproto();
  }
} static_descriptor_initializer_view_5fdata_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* s_view_data_Shape_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return s_view_data_Shape_Type_descriptor_;
}
bool s_view_data_Shape_Type_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const s_view_data_Shape_Type s_view_data::CIRCLE;
const s_view_data_Shape_Type s_view_data::TRIANGLE;
const s_view_data_Shape_Type s_view_data::SQUARE;
const s_view_data_Shape_Type s_view_data::ARROW;
const s_view_data_Shape_Type s_view_data::Shape_Type_MIN;
const s_view_data_Shape_Type s_view_data::Shape_Type_MAX;
const int s_view_data::Shape_Type_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* s_view_data_Insert_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return s_view_data_Insert_Type_descriptor_;
}
bool s_view_data_Insert_Type_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const s_view_data_Insert_Type s_view_data::NEW;
const s_view_data_Insert_Type s_view_data::MERGE;
const s_view_data_Insert_Type s_view_data::Insert_Type_MIN;
const s_view_data_Insert_Type s_view_data::Insert_Type_MAX;
const int s_view_data::Insert_Type_ARRAYSIZE;
#endif  // _MSC_VER
const ::std::string s_view_data::_default_name_;
#ifndef _MSC_VER
const int s_view_data::kNameFieldNumber;
const int s_view_data::kInsertTypeFieldNumber;
const int s_view_data::kPosFieldNumber;
const int s_view_data::kPointFieldNumber;
const int s_view_data::kShapeTypeFieldNumber;
const int s_view_data::kLabFieldNumber;
#endif  // !_MSC_VER

s_view_data::s_view_data()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void s_view_data::InitAsDefaultInstance() {
  lab_ = const_cast< ::KPS::mp_lab*>(&::KPS::mp_lab::default_instance());
}

s_view_data::s_view_data(const s_view_data& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void s_view_data::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&_default_name_);
  insert_type_ = 0;
  shape_type_ = 0;
  lab_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

s_view_data::~s_view_data() {
  SharedDtor();
}

void s_view_data::SharedDtor() {
  if (name_ != &_default_name_) {
    delete name_;
  }
  if (this != default_instance_) {
    delete lab_;
  }
}

void s_view_data::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* s_view_data::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return s_view_data_descriptor_;
}

const s_view_data& s_view_data::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_view_5fdata_2eproto();  return *default_instance_;
}

s_view_data* s_view_data::default_instance_ = NULL;

s_view_data* s_view_data::New() const {
  return new s_view_data;
}

void s_view_data::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (name_ != &_default_name_) {
        name_->clear();
      }
    }
    insert_type_ = 0;
    shape_type_ = 0;
    if (_has_bit(5)) {
      if (lab_ != NULL) lab_->::KPS::mp_lab::Clear();
    }
  }
  pos_.Clear();
  point_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool s_view_data::MergePartialFromCodedStream(
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
        if (input->ExpectTag(16)) goto parse_insert_type;
        break;
      }
      
      // required .KPS.s_view_data.Insert_Type insert_type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_insert_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::KPS::s_view_data_Insert_Type_IsValid(value)) {
            set_insert_type(static_cast< ::KPS::s_view_data_Insert_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_pos;
        break;
      }
      
      // repeated .KPS.s_pos pos = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_pos:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_pos()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_pos;
        if (input->ExpectTag(34)) goto parse_point;
        break;
      }
      
      // repeated .KPS.s_point point = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_point:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_point()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_point;
        if (input->ExpectTag(40)) goto parse_shape_type;
        break;
      }
      
      // optional .KPS.s_view_data.Shape_Type shape_type = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_shape_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::KPS::s_view_data_Shape_Type_IsValid(value)) {
            set_shape_type(static_cast< ::KPS::s_view_data_Shape_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(5, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_lab;
        break;
      }
      
      // optional .KPS.mp_lab lab = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_lab:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_lab()));
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

void s_view_data::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }
  
  // required .KPS.s_view_data.Insert_Type insert_type = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->insert_type(), output);
  }
  
  // repeated .KPS.s_pos pos = 3;
  for (int i = 0; i < this->pos_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->pos(i), output);
  }
  
  // repeated .KPS.s_point point = 4;
  for (int i = 0; i < this->point_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->point(i), output);
  }
  
  // optional .KPS.s_view_data.Shape_Type shape_type = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      5, this->shape_type(), output);
  }
  
  // optional .KPS.mp_lab lab = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->lab(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* s_view_data::SerializeWithCachedSizesToArray(
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
  
  // required .KPS.s_view_data.Insert_Type insert_type = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->insert_type(), target);
  }
  
  // repeated .KPS.s_pos pos = 3;
  for (int i = 0; i < this->pos_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->pos(i), target);
  }
  
  // repeated .KPS.s_point point = 4;
  for (int i = 0; i < this->point_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->point(i), target);
  }
  
  // optional .KPS.s_view_data.Shape_Type shape_type = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      5, this->shape_type(), target);
  }
  
  // optional .KPS.mp_lab lab = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->lab(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int s_view_data::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // required .KPS.s_view_data.Insert_Type insert_type = 2;
    if (has_insert_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->insert_type());
    }
    
    // optional .KPS.s_view_data.Shape_Type shape_type = 5;
    if (has_shape_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->shape_type());
    }
    
    // optional .KPS.mp_lab lab = 6;
    if (has_lab()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->lab());
    }
    
  }
  // repeated .KPS.s_pos pos = 3;
  total_size += 1 * this->pos_size();
  for (int i = 0; i < this->pos_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->pos(i));
  }
  
  // repeated .KPS.s_point point = 4;
  total_size += 1 * this->point_size();
  for (int i = 0; i < this->point_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->point(i));
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

void s_view_data::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const s_view_data* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const s_view_data*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void s_view_data::MergeFrom(const s_view_data& from) {
  GOOGLE_CHECK_NE(&from, this);
  pos_.MergeFrom(from.pos_);
  point_.MergeFrom(from.point_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_name(from.name());
    }
    if (from._has_bit(1)) {
      set_insert_type(from.insert_type());
    }
    if (from._has_bit(4)) {
      set_shape_type(from.shape_type());
    }
    if (from._has_bit(5)) {
      mutable_lab()->::KPS::mp_lab::MergeFrom(from.lab());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void s_view_data::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void s_view_data::CopyFrom(const s_view_data& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool s_view_data::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  for (int i = 0; i < pos_size(); i++) {
    if (!this->pos(i).IsInitialized()) return false;
  }
  for (int i = 0; i < point_size(); i++) {
    if (!this->point(i).IsInitialized()) return false;
  }
  if (has_lab()) {
    if (!this->lab().IsInitialized()) return false;
  }
  return true;
}

void s_view_data::Swap(s_view_data* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(insert_type_, other->insert_type_);
    pos_.Swap(&other->pos_);
    point_.Swap(&other->point_);
    std::swap(shape_type_, other->shape_type_);
    std::swap(lab_, other->lab_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata s_view_data::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = s_view_data_descriptor_;
  metadata.reflection = s_view_data_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

// @@protoc_insertion_point(global_scope)

// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GLaserScan.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* GBeam_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GBeam_reflection_ = NULL;
const ::google::protobuf::Descriptor* GEcho_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GEcho_reflection_ = NULL;
const ::google::protobuf::Descriptor* GLaserScan_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GLaserScan_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_GLaserScan_2eproto() {
  protobuf_AddDesc_GLaserScan_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "GLaserScan.proto");
  GOOGLE_CHECK(file != NULL);
  GBeam_descriptor_ = file->message_type(0);
  static const int GBeam_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GBeam, angle_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GBeam, dist_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GBeam, validity_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GBeam, rssi_),
  };
  GBeam_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GBeam_descriptor_,
      GBeam::default_instance_,
      GBeam_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GBeam, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GBeam, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GBeam));
  GEcho_descriptor_ = file->message_type(1);
  static const int GEcho_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GEcho, beams_),
  };
  GEcho_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GEcho_descriptor_,
      GEcho::default_instance_,
      GEcho_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GEcho, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GEcho, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GEcho));
  GLaserScan_descriptor_ = file->message_type(2);
  static const int GLaserScan_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, beams_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, time_stamp_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, echos_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, message_counter_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, scan_counter_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, powerup_duration_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, transmission_duration_),
  };
  GLaserScan_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GLaserScan_descriptor_,
      GLaserScan::default_instance_,
      GLaserScan_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GLaserScan, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GLaserScan));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_GLaserScan_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GBeam_descriptor_, &GBeam::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GEcho_descriptor_, &GEcho::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GLaserScan_descriptor_, &GLaserScan::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_GLaserScan_2eproto() {
  delete GBeam::default_instance_;
  delete GBeam_reflection_;
  delete GEcho::default_instance_;
  delete GEcho_reflection_;
  delete GLaserScan::default_instance_;
  delete GLaserScan_reflection_;
}

void protobuf_AddDesc_GLaserScan_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020GLaserScan.proto\"D\n\005GBeam\022\r\n\005angle\030\001 \001"
    "(\001\022\014\n\004dist\030\002 \001(\001\022\020\n\010validity\030\003 \001(\010\022\014\n\004RS"
    "SI\030\004 \001(\001\"\036\n\005GEcho\022\025\n\005beams\030\001 \003(\0132\006.GBeam"
    "\"\266\001\n\nGLaserScan\022\025\n\005beams\030\001 \003(\0132\006.GBeam\022\022"
    "\n\ntime_stamp\030\002 \001(\001\022\025\n\005echos\030\003 \003(\0132\006.GEch"
    "o\022\027\n\017message_counter\030\004 \001(\005\022\024\n\014scan_count"
    "er\030\005 \001(\005\022\030\n\020powerup_duration\030\006 \001(\001\022\035\n\025tr"
    "ansmission_duration\030\007 \001(\001", 305);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "GLaserScan.proto", &protobuf_RegisterTypes);
  GBeam::default_instance_ = new GBeam();
  GEcho::default_instance_ = new GEcho();
  GLaserScan::default_instance_ = new GLaserScan();
  GBeam::default_instance_->InitAsDefaultInstance();
  GEcho::default_instance_->InitAsDefaultInstance();
  GLaserScan::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GLaserScan_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GLaserScan_2eproto {
  StaticDescriptorInitializer_GLaserScan_2eproto() {
    protobuf_AddDesc_GLaserScan_2eproto();
  }
} static_descriptor_initializer_GLaserScan_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int GBeam::kAngleFieldNumber;
const int GBeam::kDistFieldNumber;
const int GBeam::kValidityFieldNumber;
const int GBeam::kRSSIFieldNumber;
#endif  // !_MSC_VER

GBeam::GBeam()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GBeam::InitAsDefaultInstance() {
}

GBeam::GBeam(const GBeam& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GBeam::SharedCtor() {
  _cached_size_ = 0;
  angle_ = 0;
  dist_ = 0;
  validity_ = false;
  rssi_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GBeam::~GBeam() {
  SharedDtor();
}

void GBeam::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GBeam::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GBeam::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GBeam_descriptor_;
}

const GBeam& GBeam::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GLaserScan_2eproto();  return *default_instance_;
}

GBeam* GBeam::default_instance_ = NULL;

GBeam* GBeam::New() const {
  return new GBeam;
}

void GBeam::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    angle_ = 0;
    dist_ = 0;
    validity_ = false;
    rssi_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GBeam::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double angle = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &angle_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_dist;
        break;
      }
      
      // optional double dist = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_dist:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &dist_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_validity;
        break;
      }
      
      // optional bool validity = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_validity:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &validity_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(33)) goto parse_RSSI;
        break;
      }
      
      // optional double RSSI = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_RSSI:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &rssi_)));
          _set_bit(3);
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

void GBeam::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional double angle = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->angle(), output);
  }
  
  // optional double dist = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->dist(), output);
  }
  
  // optional bool validity = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->validity(), output);
  }
  
  // optional double RSSI = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->rssi(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GBeam::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional double angle = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->angle(), target);
  }
  
  // optional double dist = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->dist(), target);
  }
  
  // optional bool validity = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->validity(), target);
  }
  
  // optional double RSSI = 4;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->rssi(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GBeam::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional double angle = 1;
    if (has_angle()) {
      total_size += 1 + 8;
    }
    
    // optional double dist = 2;
    if (has_dist()) {
      total_size += 1 + 8;
    }
    
    // optional bool validity = 3;
    if (has_validity()) {
      total_size += 1 + 1;
    }
    
    // optional double RSSI = 4;
    if (has_rssi()) {
      total_size += 1 + 8;
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

void GBeam::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GBeam* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GBeam*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GBeam::MergeFrom(const GBeam& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_angle(from.angle());
    }
    if (from._has_bit(1)) {
      set_dist(from.dist());
    }
    if (from._has_bit(2)) {
      set_validity(from.validity());
    }
    if (from._has_bit(3)) {
      set_rssi(from.rssi());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GBeam::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GBeam::CopyFrom(const GBeam& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GBeam::IsInitialized() const {
  
  return true;
}

void GBeam::Swap(GBeam* other) {
  if (other != this) {
    std::swap(angle_, other->angle_);
    std::swap(dist_, other->dist_);
    std::swap(validity_, other->validity_);
    std::swap(rssi_, other->rssi_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GBeam::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GBeam_descriptor_;
  metadata.reflection = GBeam_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GEcho::kBeamsFieldNumber;
#endif  // !_MSC_VER

GEcho::GEcho()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GEcho::InitAsDefaultInstance() {
}

GEcho::GEcho(const GEcho& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GEcho::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GEcho::~GEcho() {
  SharedDtor();
}

void GEcho::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GEcho::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GEcho::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GEcho_descriptor_;
}

const GEcho& GEcho::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GLaserScan_2eproto();  return *default_instance_;
}

GEcho* GEcho::default_instance_ = NULL;

GEcho* GEcho::New() const {
  return new GEcho;
}

void GEcho::Clear() {
  beams_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GEcho::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .GBeam beams = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_beams:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_beams()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_beams;
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

void GEcho::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .GBeam beams = 1;
  for (int i = 0; i < this->beams_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->beams(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GEcho::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .GBeam beams = 1;
  for (int i = 0; i < this->beams_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->beams(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GEcho::ByteSize() const {
  int total_size = 0;
  
  // repeated .GBeam beams = 1;
  total_size += 1 * this->beams_size();
  for (int i = 0; i < this->beams_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->beams(i));
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

void GEcho::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GEcho* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GEcho*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GEcho::MergeFrom(const GEcho& from) {
  GOOGLE_CHECK_NE(&from, this);
  beams_.MergeFrom(from.beams_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GEcho::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GEcho::CopyFrom(const GEcho& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GEcho::IsInitialized() const {
  
  return true;
}

void GEcho::Swap(GEcho* other) {
  if (other != this) {
    beams_.Swap(&other->beams_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GEcho::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GEcho_descriptor_;
  metadata.reflection = GEcho_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int GLaserScan::kBeamsFieldNumber;
const int GLaserScan::kTimeStampFieldNumber;
const int GLaserScan::kEchosFieldNumber;
const int GLaserScan::kMessageCounterFieldNumber;
const int GLaserScan::kScanCounterFieldNumber;
const int GLaserScan::kPowerupDurationFieldNumber;
const int GLaserScan::kTransmissionDurationFieldNumber;
#endif  // !_MSC_VER

GLaserScan::GLaserScan()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GLaserScan::InitAsDefaultInstance() {
}

GLaserScan::GLaserScan(const GLaserScan& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GLaserScan::SharedCtor() {
  _cached_size_ = 0;
  time_stamp_ = 0;
  message_counter_ = 0;
  scan_counter_ = 0;
  powerup_duration_ = 0;
  transmission_duration_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GLaserScan::~GLaserScan() {
  SharedDtor();
}

void GLaserScan::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GLaserScan::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GLaserScan::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GLaserScan_descriptor_;
}

const GLaserScan& GLaserScan::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GLaserScan_2eproto();  return *default_instance_;
}

GLaserScan* GLaserScan::default_instance_ = NULL;

GLaserScan* GLaserScan::New() const {
  return new GLaserScan;
}

void GLaserScan::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    time_stamp_ = 0;
    message_counter_ = 0;
    scan_counter_ = 0;
    powerup_duration_ = 0;
    transmission_duration_ = 0;
  }
  beams_.Clear();
  echos_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GLaserScan::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .GBeam beams = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_beams:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_beams()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_beams;
        if (input->ExpectTag(17)) goto parse_time_stamp;
        break;
      }
      
      // optional double time_stamp = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_time_stamp:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &time_stamp_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_echos;
        break;
      }
      
      // repeated .GEcho echos = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_echos:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_echos()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_echos;
        if (input->ExpectTag(32)) goto parse_message_counter;
        break;
      }
      
      // optional int32 message_counter = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_message_counter:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &message_counter_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_scan_counter;
        break;
      }
      
      // optional int32 scan_counter = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_scan_counter:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &scan_counter_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(49)) goto parse_powerup_duration;
        break;
      }
      
      // optional double powerup_duration = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_powerup_duration:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &powerup_duration_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(57)) goto parse_transmission_duration;
        break;
      }
      
      // optional double transmission_duration = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_transmission_duration:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &transmission_duration_)));
          _set_bit(6);
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

void GLaserScan::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .GBeam beams = 1;
  for (int i = 0; i < this->beams_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->beams(i), output);
  }
  
  // optional double time_stamp = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->time_stamp(), output);
  }
  
  // repeated .GEcho echos = 3;
  for (int i = 0; i < this->echos_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->echos(i), output);
  }
  
  // optional int32 message_counter = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->message_counter(), output);
  }
  
  // optional int32 scan_counter = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->scan_counter(), output);
  }
  
  // optional double powerup_duration = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->powerup_duration(), output);
  }
  
  // optional double transmission_duration = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->transmission_duration(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GLaserScan::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .GBeam beams = 1;
  for (int i = 0; i < this->beams_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->beams(i), target);
  }
  
  // optional double time_stamp = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->time_stamp(), target);
  }
  
  // repeated .GEcho echos = 3;
  for (int i = 0; i < this->echos_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->echos(i), target);
  }
  
  // optional int32 message_counter = 4;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->message_counter(), target);
  }
  
  // optional int32 scan_counter = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->scan_counter(), target);
  }
  
  // optional double powerup_duration = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->powerup_duration(), target);
  }
  
  // optional double transmission_duration = 7;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->transmission_duration(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GLaserScan::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // optional double time_stamp = 2;
    if (has_time_stamp()) {
      total_size += 1 + 8;
    }
    
    // optional int32 message_counter = 4;
    if (has_message_counter()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->message_counter());
    }
    
    // optional int32 scan_counter = 5;
    if (has_scan_counter()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->scan_counter());
    }
    
    // optional double powerup_duration = 6;
    if (has_powerup_duration()) {
      total_size += 1 + 8;
    }
    
    // optional double transmission_duration = 7;
    if (has_transmission_duration()) {
      total_size += 1 + 8;
    }
    
  }
  // repeated .GBeam beams = 1;
  total_size += 1 * this->beams_size();
  for (int i = 0; i < this->beams_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->beams(i));
  }
  
  // repeated .GEcho echos = 3;
  total_size += 1 * this->echos_size();
  for (int i = 0; i < this->echos_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->echos(i));
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

void GLaserScan::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GLaserScan* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GLaserScan*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GLaserScan::MergeFrom(const GLaserScan& from) {
  GOOGLE_CHECK_NE(&from, this);
  beams_.MergeFrom(from.beams_);
  echos_.MergeFrom(from.echos_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from._has_bit(1)) {
      set_time_stamp(from.time_stamp());
    }
    if (from._has_bit(3)) {
      set_message_counter(from.message_counter());
    }
    if (from._has_bit(4)) {
      set_scan_counter(from.scan_counter());
    }
    if (from._has_bit(5)) {
      set_powerup_duration(from.powerup_duration());
    }
    if (from._has_bit(6)) {
      set_transmission_duration(from.transmission_duration());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GLaserScan::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GLaserScan::CopyFrom(const GLaserScan& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GLaserScan::IsInitialized() const {
  
  return true;
}

void GLaserScan::Swap(GLaserScan* other) {
  if (other != this) {
    beams_.Swap(&other->beams_);
    std::swap(time_stamp_, other->time_stamp_);
    echos_.Swap(&other->echos_);
    std::swap(message_counter_, other->message_counter_);
    std::swap(scan_counter_, other->scan_counter_);
    std::swap(powerup_duration_, other->powerup_duration_);
    std::swap(transmission_duration_, other->transmission_duration_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GLaserScan::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GLaserScan_descriptor_;
  metadata.reflection = GLaserScan_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
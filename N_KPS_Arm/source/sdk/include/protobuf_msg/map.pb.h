// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: map.proto

#ifndef PROTOBUF_map_2eproto__INCLUDED
#define PROTOBUF_map_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace KPS {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_map_2eproto();
void protobuf_AssignDesc_map_2eproto();
void protobuf_ShutdownFile_map_2eproto();

class mp_map_data;
class mp_map;

// ===================================================================

class mp_map_data : public ::google::protobuf::Message {
 public:
  mp_map_data();
  virtual ~mp_map_data();
  
  mp_map_data(const mp_map_data& from);
  
  inline mp_map_data& operator=(const mp_map_data& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const mp_map_data& default_instance();
  
  void Swap(mp_map_data* other);
  
  // implements Message ----------------------------------------------
  
  mp_map_data* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_map_data& from);
  void MergeFrom(const mp_map_data& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 gx = 1;
  inline bool has_gx() const;
  inline void clear_gx();
  static const int kGxFieldNumber = 1;
  inline ::google::protobuf::uint32 gx() const;
  inline void set_gx(::google::protobuf::uint32 value);
  
  // required uint32 gy = 2;
  inline bool has_gy() const;
  inline void clear_gy();
  static const int kGyFieldNumber = 2;
  inline ::google::protobuf::uint32 gy() const;
  inline void set_gy(::google::protobuf::uint32 value);
  
  // required uint32 value = 3;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 3;
  inline ::google::protobuf::uint32 value() const;
  inline void set_value(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:KPS.mp_map_data)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 gx_;
  ::google::protobuf::uint32 gy_;
  ::google::protobuf::uint32 value_;
  friend void  protobuf_AddDesc_map_2eproto();
  friend void protobuf_AssignDesc_map_2eproto();
  friend void protobuf_ShutdownFile_map_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static mp_map_data* default_instance_;
};
// -------------------------------------------------------------------

class mp_map : public ::google::protobuf::Message {
 public:
  mp_map();
  virtual ~mp_map();
  
  mp_map(const mp_map& from);
  
  inline mp_map& operator=(const mp_map& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const mp_map& default_instance();
  
  void Swap(mp_map* other);
  
  // implements Message ----------------------------------------------
  
  mp_map* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_map& from);
  void MergeFrom(const mp_map& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string map_name = 1;
  inline bool has_map_name() const;
  inline void clear_map_name();
  static const int kMapNameFieldNumber = 1;
  inline const ::std::string& map_name() const;
  inline void set_map_name(const ::std::string& value);
  inline void set_map_name(const char* value);
  inline void set_map_name(const char* value, size_t size);
  inline ::std::string* mutable_map_name();
  
  // required uint32 origin_gx = 2;
  inline bool has_origin_gx() const;
  inline void clear_origin_gx();
  static const int kOriginGxFieldNumber = 2;
  inline ::google::protobuf::uint32 origin_gx() const;
  inline void set_origin_gx(::google::protobuf::uint32 value);
  
  // required uint32 origin_gy = 3;
  inline bool has_origin_gy() const;
  inline void clear_origin_gy();
  static const int kOriginGyFieldNumber = 3;
  inline ::google::protobuf::uint32 origin_gy() const;
  inline void set_origin_gy(::google::protobuf::uint32 value);
  
  // required float origin_wx = 4;
  inline bool has_origin_wx() const;
  inline void clear_origin_wx();
  static const int kOriginWxFieldNumber = 4;
  inline float origin_wx() const;
  inline void set_origin_wx(float value);
  
  // required float origin_wy = 5;
  inline bool has_origin_wy() const;
  inline void clear_origin_wy();
  static const int kOriginWyFieldNumber = 5;
  inline float origin_wy() const;
  inline void set_origin_wy(float value);
  
  // required float resolution = 6;
  inline bool has_resolution() const;
  inline void clear_resolution();
  static const int kResolutionFieldNumber = 6;
  inline float resolution() const;
  inline void set_resolution(float value);
  
  // repeated .KPS.mp_map_data data = 7;
  inline int data_size() const;
  inline void clear_data();
  static const int kDataFieldNumber = 7;
  inline const ::KPS::mp_map_data& data(int index) const;
  inline ::KPS::mp_map_data* mutable_data(int index);
  inline ::KPS::mp_map_data* add_data();
  inline const ::google::protobuf::RepeatedPtrField< ::KPS::mp_map_data >&
      data() const;
  inline ::google::protobuf::RepeatedPtrField< ::KPS::mp_map_data >*
      mutable_data();
  
  // @@protoc_insertion_point(class_scope:KPS.mp_map)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* map_name_;
  static const ::std::string _default_map_name_;
  ::google::protobuf::uint32 origin_gx_;
  ::google::protobuf::uint32 origin_gy_;
  float origin_wx_;
  float origin_wy_;
  float resolution_;
  ::google::protobuf::RepeatedPtrField< ::KPS::mp_map_data > data_;
  friend void  protobuf_AddDesc_map_2eproto();
  friend void protobuf_AssignDesc_map_2eproto();
  friend void protobuf_ShutdownFile_map_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static mp_map* default_instance_;
};
// ===================================================================


// ===================================================================

// mp_map_data

// required uint32 gx = 1;
inline bool mp_map_data::has_gx() const {
  return _has_bit(0);
}
inline void mp_map_data::clear_gx() {
  gx_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 mp_map_data::gx() const {
  return gx_;
}
inline void mp_map_data::set_gx(::google::protobuf::uint32 value) {
  _set_bit(0);
  gx_ = value;
}

// required uint32 gy = 2;
inline bool mp_map_data::has_gy() const {
  return _has_bit(1);
}
inline void mp_map_data::clear_gy() {
  gy_ = 0u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 mp_map_data::gy() const {
  return gy_;
}
inline void mp_map_data::set_gy(::google::protobuf::uint32 value) {
  _set_bit(1);
  gy_ = value;
}

// required uint32 value = 3;
inline bool mp_map_data::has_value() const {
  return _has_bit(2);
}
inline void mp_map_data::clear_value() {
  value_ = 0u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 mp_map_data::value() const {
  return value_;
}
inline void mp_map_data::set_value(::google::protobuf::uint32 value) {
  _set_bit(2);
  value_ = value;
}

// -------------------------------------------------------------------

// mp_map

// required string map_name = 1;
inline bool mp_map::has_map_name() const {
  return _has_bit(0);
}
inline void mp_map::clear_map_name() {
  if (map_name_ != &_default_map_name_) {
    map_name_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& mp_map::map_name() const {
  return *map_name_;
}
inline void mp_map::set_map_name(const ::std::string& value) {
  _set_bit(0);
  if (map_name_ == &_default_map_name_) {
    map_name_ = new ::std::string;
  }
  map_name_->assign(value);
}
inline void mp_map::set_map_name(const char* value) {
  _set_bit(0);
  if (map_name_ == &_default_map_name_) {
    map_name_ = new ::std::string;
  }
  map_name_->assign(value);
}
inline void mp_map::set_map_name(const char* value, size_t size) {
  _set_bit(0);
  if (map_name_ == &_default_map_name_) {
    map_name_ = new ::std::string;
  }
  map_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_map::mutable_map_name() {
  _set_bit(0);
  if (map_name_ == &_default_map_name_) {
    map_name_ = new ::std::string;
  }
  return map_name_;
}

// required uint32 origin_gx = 2;
inline bool mp_map::has_origin_gx() const {
  return _has_bit(1);
}
inline void mp_map::clear_origin_gx() {
  origin_gx_ = 0u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 mp_map::origin_gx() const {
  return origin_gx_;
}
inline void mp_map::set_origin_gx(::google::protobuf::uint32 value) {
  _set_bit(1);
  origin_gx_ = value;
}

// required uint32 origin_gy = 3;
inline bool mp_map::has_origin_gy() const {
  return _has_bit(2);
}
inline void mp_map::clear_origin_gy() {
  origin_gy_ = 0u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 mp_map::origin_gy() const {
  return origin_gy_;
}
inline void mp_map::set_origin_gy(::google::protobuf::uint32 value) {
  _set_bit(2);
  origin_gy_ = value;
}

// required float origin_wx = 4;
inline bool mp_map::has_origin_wx() const {
  return _has_bit(3);
}
inline void mp_map::clear_origin_wx() {
  origin_wx_ = 0;
  _clear_bit(3);
}
inline float mp_map::origin_wx() const {
  return origin_wx_;
}
inline void mp_map::set_origin_wx(float value) {
  _set_bit(3);
  origin_wx_ = value;
}

// required float origin_wy = 5;
inline bool mp_map::has_origin_wy() const {
  return _has_bit(4);
}
inline void mp_map::clear_origin_wy() {
  origin_wy_ = 0;
  _clear_bit(4);
}
inline float mp_map::origin_wy() const {
  return origin_wy_;
}
inline void mp_map::set_origin_wy(float value) {
  _set_bit(4);
  origin_wy_ = value;
}

// required float resolution = 6;
inline bool mp_map::has_resolution() const {
  return _has_bit(5);
}
inline void mp_map::clear_resolution() {
  resolution_ = 0;
  _clear_bit(5);
}
inline float mp_map::resolution() const {
  return resolution_;
}
inline void mp_map::set_resolution(float value) {
  _set_bit(5);
  resolution_ = value;
}

// repeated .KPS.mp_map_data data = 7;
inline int mp_map::data_size() const {
  return data_.size();
}
inline void mp_map::clear_data() {
  data_.Clear();
}
inline const ::KPS::mp_map_data& mp_map::data(int index) const {
  return data_.Get(index);
}
inline ::KPS::mp_map_data* mp_map::mutable_data(int index) {
  return data_.Mutable(index);
}
inline ::KPS::mp_map_data* mp_map::add_data() {
  return data_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::KPS::mp_map_data >&
mp_map::data() const {
  return data_;
}
inline ::google::protobuf::RepeatedPtrField< ::KPS::mp_map_data >*
mp_map::mutable_data() {
  return &data_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace KPS

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_map_2eproto__INCLUDED

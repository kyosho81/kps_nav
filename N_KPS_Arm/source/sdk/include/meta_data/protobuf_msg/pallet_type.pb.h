// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pallet_type.proto

#ifndef PROTOBUF_pallet_5ftype_2eproto__INCLUDED
#define PROTOBUF_pallet_5ftype_2eproto__INCLUDED

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
#include "base.pb.h"
// @@protoc_insertion_point(includes)

namespace KPS {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_pallet_5ftype_2eproto();
void protobuf_AssignDesc_pallet_5ftype_2eproto();
void protobuf_ShutdownFile_pallet_5ftype_2eproto();

class mp_pallet_type;

// ===================================================================

class mp_pallet_type : public ::google::protobuf::Message {
 public:
  mp_pallet_type();
  virtual ~mp_pallet_type();
  
  mp_pallet_type(const mp_pallet_type& from);
  
  inline mp_pallet_type& operator=(const mp_pallet_type& from) {
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
  static const mp_pallet_type& default_instance();
  
  void Swap(mp_pallet_type* other);
  
  // implements Message ----------------------------------------------
  
  mp_pallet_type* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_pallet_type& from);
  void MergeFrom(const mp_pallet_type& from);
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
  
  // required .KPS.mp_item_base base = 1;
  inline bool has_base() const;
  inline void clear_base();
  static const int kBaseFieldNumber = 1;
  inline const ::KPS::mp_item_base& base() const;
  inline ::KPS::mp_item_base* mutable_base();
  
  // required string pallet_type_nm_ = 2;
  inline bool has_pallet_type_nm_() const;
  inline void clear_pallet_type_nm_();
  static const int kPalletTypeNmFieldNumber = 2;
  inline const ::std::string& pallet_type_nm_() const;
  inline void set_pallet_type_nm_(const ::std::string& value);
  inline void set_pallet_type_nm_(const char* value);
  inline void set_pallet_type_nm_(const char* value, size_t size);
  inline ::std::string* mutable_pallet_type_nm_();
  
  // optional uint32 pallet_category = 3;
  inline bool has_pallet_category() const;
  inline void clear_pallet_category();
  static const int kPalletCategoryFieldNumber = 3;
  inline ::google::protobuf::uint32 pallet_category() const;
  inline void set_pallet_category(::google::protobuf::uint32 value);
  
  // optional string weight = 4;
  inline bool has_weight() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 4;
  inline const ::std::string& weight() const;
  inline void set_weight(const ::std::string& value);
  inline void set_weight(const char* value);
  inline void set_weight(const char* value, size_t size);
  inline ::std::string* mutable_weight();
  
  // optional string volume = 5;
  inline bool has_volume() const;
  inline void clear_volume();
  static const int kVolumeFieldNumber = 5;
  inline const ::std::string& volume() const;
  inline void set_volume(const ::std::string& value);
  inline void set_volume(const char* value);
  inline void set_volume(const char* value, size_t size);
  inline ::std::string* mutable_volume();
  
  // optional string load_weight = 6;
  inline bool has_load_weight() const;
  inline void clear_load_weight();
  static const int kLoadWeightFieldNumber = 6;
  inline const ::std::string& load_weight() const;
  inline void set_load_weight(const ::std::string& value);
  inline void set_load_weight(const char* value);
  inline void set_load_weight(const char* value, size_t size);
  inline ::std::string* mutable_load_weight();
  
  // optional string load_volume = 7;
  inline bool has_load_volume() const;
  inline void clear_load_volume();
  static const int kLoadVolumeFieldNumber = 7;
  inline const ::std::string& load_volume() const;
  inline void set_load_volume(const ::std::string& value);
  inline void set_load_volume(const char* value);
  inline void set_load_volume(const char* value, size_t size);
  inline ::std::string* mutable_load_volume();
  
  // optional float length = 8;
  inline bool has_length() const;
  inline void clear_length();
  static const int kLengthFieldNumber = 8;
  inline float length() const;
  inline void set_length(float value);
  
  // optional float width = 9;
  inline bool has_width() const;
  inline void clear_width();
  static const int kWidthFieldNumber = 9;
  inline float width() const;
  inline void set_width(float value);
  
  // optional float height = 10;
  inline bool has_height() const;
  inline void clear_height();
  static const int kHeightFieldNumber = 10;
  inline float height() const;
  inline void set_height(float value);
  
  // @@protoc_insertion_point(class_scope:KPS.mp_pallet_type)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::KPS::mp_item_base* base_;
  ::std::string* pallet_type_nm__;
  static const ::std::string _default_pallet_type_nm__;
  ::google::protobuf::uint32 pallet_category_;
  ::std::string* weight_;
  static const ::std::string _default_weight_;
  ::std::string* volume_;
  static const ::std::string _default_volume_;
  ::std::string* load_weight_;
  static const ::std::string _default_load_weight_;
  ::std::string* load_volume_;
  static const ::std::string _default_load_volume_;
  float length_;
  float width_;
  float height_;
  friend void  protobuf_AddDesc_pallet_5ftype_2eproto();
  friend void protobuf_AssignDesc_pallet_5ftype_2eproto();
  friend void protobuf_ShutdownFile_pallet_5ftype_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(10 + 31) / 32];
  
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
  static mp_pallet_type* default_instance_;
};
// ===================================================================


// ===================================================================

// mp_pallet_type

// required .KPS.mp_item_base base = 1;
inline bool mp_pallet_type::has_base() const {
  return _has_bit(0);
}
inline void mp_pallet_type::clear_base() {
  if (base_ != NULL) base_->::KPS::mp_item_base::Clear();
  _clear_bit(0);
}
inline const ::KPS::mp_item_base& mp_pallet_type::base() const {
  return base_ != NULL ? *base_ : *default_instance_->base_;
}
inline ::KPS::mp_item_base* mp_pallet_type::mutable_base() {
  _set_bit(0);
  if (base_ == NULL) base_ = new ::KPS::mp_item_base;
  return base_;
}

// required string pallet_type_nm_ = 2;
inline bool mp_pallet_type::has_pallet_type_nm_() const {
  return _has_bit(1);
}
inline void mp_pallet_type::clear_pallet_type_nm_() {
  if (pallet_type_nm__ != &_default_pallet_type_nm__) {
    pallet_type_nm__->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& mp_pallet_type::pallet_type_nm_() const {
  return *pallet_type_nm__;
}
inline void mp_pallet_type::set_pallet_type_nm_(const ::std::string& value) {
  _set_bit(1);
  if (pallet_type_nm__ == &_default_pallet_type_nm__) {
    pallet_type_nm__ = new ::std::string;
  }
  pallet_type_nm__->assign(value);
}
inline void mp_pallet_type::set_pallet_type_nm_(const char* value) {
  _set_bit(1);
  if (pallet_type_nm__ == &_default_pallet_type_nm__) {
    pallet_type_nm__ = new ::std::string;
  }
  pallet_type_nm__->assign(value);
}
inline void mp_pallet_type::set_pallet_type_nm_(const char* value, size_t size) {
  _set_bit(1);
  if (pallet_type_nm__ == &_default_pallet_type_nm__) {
    pallet_type_nm__ = new ::std::string;
  }
  pallet_type_nm__->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_type::mutable_pallet_type_nm_() {
  _set_bit(1);
  if (pallet_type_nm__ == &_default_pallet_type_nm__) {
    pallet_type_nm__ = new ::std::string;
  }
  return pallet_type_nm__;
}

// optional uint32 pallet_category = 3;
inline bool mp_pallet_type::has_pallet_category() const {
  return _has_bit(2);
}
inline void mp_pallet_type::clear_pallet_category() {
  pallet_category_ = 0u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 mp_pallet_type::pallet_category() const {
  return pallet_category_;
}
inline void mp_pallet_type::set_pallet_category(::google::protobuf::uint32 value) {
  _set_bit(2);
  pallet_category_ = value;
}

// optional string weight = 4;
inline bool mp_pallet_type::has_weight() const {
  return _has_bit(3);
}
inline void mp_pallet_type::clear_weight() {
  if (weight_ != &_default_weight_) {
    weight_->clear();
  }
  _clear_bit(3);
}
inline const ::std::string& mp_pallet_type::weight() const {
  return *weight_;
}
inline void mp_pallet_type::set_weight(const ::std::string& value) {
  _set_bit(3);
  if (weight_ == &_default_weight_) {
    weight_ = new ::std::string;
  }
  weight_->assign(value);
}
inline void mp_pallet_type::set_weight(const char* value) {
  _set_bit(3);
  if (weight_ == &_default_weight_) {
    weight_ = new ::std::string;
  }
  weight_->assign(value);
}
inline void mp_pallet_type::set_weight(const char* value, size_t size) {
  _set_bit(3);
  if (weight_ == &_default_weight_) {
    weight_ = new ::std::string;
  }
  weight_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_type::mutable_weight() {
  _set_bit(3);
  if (weight_ == &_default_weight_) {
    weight_ = new ::std::string;
  }
  return weight_;
}

// optional string volume = 5;
inline bool mp_pallet_type::has_volume() const {
  return _has_bit(4);
}
inline void mp_pallet_type::clear_volume() {
  if (volume_ != &_default_volume_) {
    volume_->clear();
  }
  _clear_bit(4);
}
inline const ::std::string& mp_pallet_type::volume() const {
  return *volume_;
}
inline void mp_pallet_type::set_volume(const ::std::string& value) {
  _set_bit(4);
  if (volume_ == &_default_volume_) {
    volume_ = new ::std::string;
  }
  volume_->assign(value);
}
inline void mp_pallet_type::set_volume(const char* value) {
  _set_bit(4);
  if (volume_ == &_default_volume_) {
    volume_ = new ::std::string;
  }
  volume_->assign(value);
}
inline void mp_pallet_type::set_volume(const char* value, size_t size) {
  _set_bit(4);
  if (volume_ == &_default_volume_) {
    volume_ = new ::std::string;
  }
  volume_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_type::mutable_volume() {
  _set_bit(4);
  if (volume_ == &_default_volume_) {
    volume_ = new ::std::string;
  }
  return volume_;
}

// optional string load_weight = 6;
inline bool mp_pallet_type::has_load_weight() const {
  return _has_bit(5);
}
inline void mp_pallet_type::clear_load_weight() {
  if (load_weight_ != &_default_load_weight_) {
    load_weight_->clear();
  }
  _clear_bit(5);
}
inline const ::std::string& mp_pallet_type::load_weight() const {
  return *load_weight_;
}
inline void mp_pallet_type::set_load_weight(const ::std::string& value) {
  _set_bit(5);
  if (load_weight_ == &_default_load_weight_) {
    load_weight_ = new ::std::string;
  }
  load_weight_->assign(value);
}
inline void mp_pallet_type::set_load_weight(const char* value) {
  _set_bit(5);
  if (load_weight_ == &_default_load_weight_) {
    load_weight_ = new ::std::string;
  }
  load_weight_->assign(value);
}
inline void mp_pallet_type::set_load_weight(const char* value, size_t size) {
  _set_bit(5);
  if (load_weight_ == &_default_load_weight_) {
    load_weight_ = new ::std::string;
  }
  load_weight_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_type::mutable_load_weight() {
  _set_bit(5);
  if (load_weight_ == &_default_load_weight_) {
    load_weight_ = new ::std::string;
  }
  return load_weight_;
}

// optional string load_volume = 7;
inline bool mp_pallet_type::has_load_volume() const {
  return _has_bit(6);
}
inline void mp_pallet_type::clear_load_volume() {
  if (load_volume_ != &_default_load_volume_) {
    load_volume_->clear();
  }
  _clear_bit(6);
}
inline const ::std::string& mp_pallet_type::load_volume() const {
  return *load_volume_;
}
inline void mp_pallet_type::set_load_volume(const ::std::string& value) {
  _set_bit(6);
  if (load_volume_ == &_default_load_volume_) {
    load_volume_ = new ::std::string;
  }
  load_volume_->assign(value);
}
inline void mp_pallet_type::set_load_volume(const char* value) {
  _set_bit(6);
  if (load_volume_ == &_default_load_volume_) {
    load_volume_ = new ::std::string;
  }
  load_volume_->assign(value);
}
inline void mp_pallet_type::set_load_volume(const char* value, size_t size) {
  _set_bit(6);
  if (load_volume_ == &_default_load_volume_) {
    load_volume_ = new ::std::string;
  }
  load_volume_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_pallet_type::mutable_load_volume() {
  _set_bit(6);
  if (load_volume_ == &_default_load_volume_) {
    load_volume_ = new ::std::string;
  }
  return load_volume_;
}

// optional float length = 8;
inline bool mp_pallet_type::has_length() const {
  return _has_bit(7);
}
inline void mp_pallet_type::clear_length() {
  length_ = 0;
  _clear_bit(7);
}
inline float mp_pallet_type::length() const {
  return length_;
}
inline void mp_pallet_type::set_length(float value) {
  _set_bit(7);
  length_ = value;
}

// optional float width = 9;
inline bool mp_pallet_type::has_width() const {
  return _has_bit(8);
}
inline void mp_pallet_type::clear_width() {
  width_ = 0;
  _clear_bit(8);
}
inline float mp_pallet_type::width() const {
  return width_;
}
inline void mp_pallet_type::set_width(float value) {
  _set_bit(8);
  width_ = value;
}

// optional float height = 10;
inline bool mp_pallet_type::has_height() const {
  return _has_bit(9);
}
inline void mp_pallet_type::clear_height() {
  height_ = 0;
  _clear_bit(9);
}
inline float mp_pallet_type::height() const {
  return height_;
}
inline void mp_pallet_type::set_height(float value) {
  _set_bit(9);
  height_ = value;
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

#endif  // PROTOBUF_pallet_5ftype_2eproto__INCLUDED

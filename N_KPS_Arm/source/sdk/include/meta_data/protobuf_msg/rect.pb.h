// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rect.proto

#ifndef PROTOBUF_rect_2eproto__INCLUDED
#define PROTOBUF_rect_2eproto__INCLUDED

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
void  protobuf_AddDesc_rect_2eproto();
void protobuf_AssignDesc_rect_2eproto();
void protobuf_ShutdownFile_rect_2eproto();

class mp_rect_region;

// ===================================================================

class mp_rect_region : public ::google::protobuf::Message {
 public:
  mp_rect_region();
  virtual ~mp_rect_region();
  
  mp_rect_region(const mp_rect_region& from);
  
  inline mp_rect_region& operator=(const mp_rect_region& from) {
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
  static const mp_rect_region& default_instance();
  
  void Swap(mp_rect_region* other);
  
  // implements Message ----------------------------------------------
  
  mp_rect_region* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_rect_region& from);
  void MergeFrom(const mp_rect_region& from);
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
  
  // required uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);
  
  // required string rect_name = 2;
  inline bool has_rect_name() const;
  inline void clear_rect_name();
  static const int kRectNameFieldNumber = 2;
  inline const ::std::string& rect_name() const;
  inline void set_rect_name(const ::std::string& value);
  inline void set_rect_name(const char* value);
  inline void set_rect_name(const char* value, size_t size);
  inline ::std::string* mutable_rect_name();
  
  // required .KPS.mp_pos_data pos = 3;
  inline bool has_pos() const;
  inline void clear_pos();
  static const int kPosFieldNumber = 3;
  inline const ::KPS::mp_pos_data& pos() const;
  inline ::KPS::mp_pos_data* mutable_pos();
  
  // required float rect_length = 4;
  inline bool has_rect_length() const;
  inline void clear_rect_length();
  static const int kRectLengthFieldNumber = 4;
  inline float rect_length() const;
  inline void set_rect_length(float value);
  
  // required float rect_width = 5;
  inline bool has_rect_width() const;
  inline void clear_rect_width();
  static const int kRectWidthFieldNumber = 5;
  inline float rect_width() const;
  inline void set_rect_width(float value);
  
  // optional float rect_height = 6;
  inline bool has_rect_height() const;
  inline void clear_rect_height();
  static const int kRectHeightFieldNumber = 6;
  inline float rect_height() const;
  inline void set_rect_height(float value);
  
  // optional string pallet_type = 7;
  inline bool has_pallet_type() const;
  inline void clear_pallet_type();
  static const int kPalletTypeFieldNumber = 7;
  inline const ::std::string& pallet_type() const;
  inline void set_pallet_type(const ::std::string& value);
  inline void set_pallet_type(const char* value);
  inline void set_pallet_type(const char* value, size_t size);
  inline ::std::string* mutable_pallet_type();
  
  // required float pallet_length = 8;
  inline bool has_pallet_length() const;
  inline void clear_pallet_length();
  static const int kPalletLengthFieldNumber = 8;
  inline float pallet_length() const;
  inline void set_pallet_length(float value);
  
  // required float pallet_width = 9;
  inline bool has_pallet_width() const;
  inline void clear_pallet_width();
  static const int kPalletWidthFieldNumber = 9;
  inline float pallet_width() const;
  inline void set_pallet_width(float value);
  
  // optional float pallet_height = 10;
  inline bool has_pallet_height() const;
  inline void clear_pallet_height();
  static const int kPalletHeightFieldNumber = 10;
  inline float pallet_height() const;
  inline void set_pallet_height(float value);
  
  // required float row_spacing = 11;
  inline bool has_row_spacing() const;
  inline void clear_row_spacing();
  static const int kRowSpacingFieldNumber = 11;
  inline float row_spacing() const;
  inline void set_row_spacing(float value);
  
  // required float col_spacing = 12;
  inline bool has_col_spacing() const;
  inline void clear_col_spacing();
  static const int kColSpacingFieldNumber = 12;
  inline float col_spacing() const;
  inline void set_col_spacing(float value);
  
  // repeated .KPS.mp_pos_data pallet_pos = 13;
  inline int pallet_pos_size() const;
  inline void clear_pallet_pos();
  static const int kPalletPosFieldNumber = 13;
  inline const ::KPS::mp_pos_data& pallet_pos(int index) const;
  inline ::KPS::mp_pos_data* mutable_pallet_pos(int index);
  inline ::KPS::mp_pos_data* add_pallet_pos();
  inline const ::google::protobuf::RepeatedPtrField< ::KPS::mp_pos_data >&
      pallet_pos() const;
  inline ::google::protobuf::RepeatedPtrField< ::KPS::mp_pos_data >*
      mutable_pallet_pos();
  
  // optional string para = 14;
  inline bool has_para() const;
  inline void clear_para();
  static const int kParaFieldNumber = 14;
  inline const ::std::string& para() const;
  inline void set_para(const ::std::string& value);
  inline void set_para(const char* value);
  inline void set_para(const char* value, size_t size);
  inline ::std::string* mutable_para();
  
  // @@protoc_insertion_point(class_scope:KPS.mp_rect_region)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 id_;
  ::std::string* rect_name_;
  static const ::std::string _default_rect_name_;
  ::KPS::mp_pos_data* pos_;
  float rect_length_;
  float rect_width_;
  float rect_height_;
  ::std::string* pallet_type_;
  static const ::std::string _default_pallet_type_;
  float pallet_length_;
  float pallet_width_;
  float pallet_height_;
  float row_spacing_;
  float col_spacing_;
  ::google::protobuf::RepeatedPtrField< ::KPS::mp_pos_data > pallet_pos_;
  ::std::string* para_;
  static const ::std::string _default_para_;
  friend void  protobuf_AddDesc_rect_2eproto();
  friend void protobuf_AssignDesc_rect_2eproto();
  friend void protobuf_ShutdownFile_rect_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(14 + 31) / 32];
  
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
  static mp_rect_region* default_instance_;
};
// ===================================================================


// ===================================================================

// mp_rect_region

// required uint32 id = 1;
inline bool mp_rect_region::has_id() const {
  return _has_bit(0);
}
inline void mp_rect_region::clear_id() {
  id_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 mp_rect_region::id() const {
  return id_;
}
inline void mp_rect_region::set_id(::google::protobuf::uint32 value) {
  _set_bit(0);
  id_ = value;
}

// required string rect_name = 2;
inline bool mp_rect_region::has_rect_name() const {
  return _has_bit(1);
}
inline void mp_rect_region::clear_rect_name() {
  if (rect_name_ != &_default_rect_name_) {
    rect_name_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& mp_rect_region::rect_name() const {
  return *rect_name_;
}
inline void mp_rect_region::set_rect_name(const ::std::string& value) {
  _set_bit(1);
  if (rect_name_ == &_default_rect_name_) {
    rect_name_ = new ::std::string;
  }
  rect_name_->assign(value);
}
inline void mp_rect_region::set_rect_name(const char* value) {
  _set_bit(1);
  if (rect_name_ == &_default_rect_name_) {
    rect_name_ = new ::std::string;
  }
  rect_name_->assign(value);
}
inline void mp_rect_region::set_rect_name(const char* value, size_t size) {
  _set_bit(1);
  if (rect_name_ == &_default_rect_name_) {
    rect_name_ = new ::std::string;
  }
  rect_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_rect_region::mutable_rect_name() {
  _set_bit(1);
  if (rect_name_ == &_default_rect_name_) {
    rect_name_ = new ::std::string;
  }
  return rect_name_;
}

// required .KPS.mp_pos_data pos = 3;
inline bool mp_rect_region::has_pos() const {
  return _has_bit(2);
}
inline void mp_rect_region::clear_pos() {
  if (pos_ != NULL) pos_->::KPS::mp_pos_data::Clear();
  _clear_bit(2);
}
inline const ::KPS::mp_pos_data& mp_rect_region::pos() const {
  return pos_ != NULL ? *pos_ : *default_instance_->pos_;
}
inline ::KPS::mp_pos_data* mp_rect_region::mutable_pos() {
  _set_bit(2);
  if (pos_ == NULL) pos_ = new ::KPS::mp_pos_data;
  return pos_;
}

// required float rect_length = 4;
inline bool mp_rect_region::has_rect_length() const {
  return _has_bit(3);
}
inline void mp_rect_region::clear_rect_length() {
  rect_length_ = 0;
  _clear_bit(3);
}
inline float mp_rect_region::rect_length() const {
  return rect_length_;
}
inline void mp_rect_region::set_rect_length(float value) {
  _set_bit(3);
  rect_length_ = value;
}

// required float rect_width = 5;
inline bool mp_rect_region::has_rect_width() const {
  return _has_bit(4);
}
inline void mp_rect_region::clear_rect_width() {
  rect_width_ = 0;
  _clear_bit(4);
}
inline float mp_rect_region::rect_width() const {
  return rect_width_;
}
inline void mp_rect_region::set_rect_width(float value) {
  _set_bit(4);
  rect_width_ = value;
}

// optional float rect_height = 6;
inline bool mp_rect_region::has_rect_height() const {
  return _has_bit(5);
}
inline void mp_rect_region::clear_rect_height() {
  rect_height_ = 0;
  _clear_bit(5);
}
inline float mp_rect_region::rect_height() const {
  return rect_height_;
}
inline void mp_rect_region::set_rect_height(float value) {
  _set_bit(5);
  rect_height_ = value;
}

// optional string pallet_type = 7;
inline bool mp_rect_region::has_pallet_type() const {
  return _has_bit(6);
}
inline void mp_rect_region::clear_pallet_type() {
  if (pallet_type_ != &_default_pallet_type_) {
    pallet_type_->clear();
  }
  _clear_bit(6);
}
inline const ::std::string& mp_rect_region::pallet_type() const {
  return *pallet_type_;
}
inline void mp_rect_region::set_pallet_type(const ::std::string& value) {
  _set_bit(6);
  if (pallet_type_ == &_default_pallet_type_) {
    pallet_type_ = new ::std::string;
  }
  pallet_type_->assign(value);
}
inline void mp_rect_region::set_pallet_type(const char* value) {
  _set_bit(6);
  if (pallet_type_ == &_default_pallet_type_) {
    pallet_type_ = new ::std::string;
  }
  pallet_type_->assign(value);
}
inline void mp_rect_region::set_pallet_type(const char* value, size_t size) {
  _set_bit(6);
  if (pallet_type_ == &_default_pallet_type_) {
    pallet_type_ = new ::std::string;
  }
  pallet_type_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_rect_region::mutable_pallet_type() {
  _set_bit(6);
  if (pallet_type_ == &_default_pallet_type_) {
    pallet_type_ = new ::std::string;
  }
  return pallet_type_;
}

// required float pallet_length = 8;
inline bool mp_rect_region::has_pallet_length() const {
  return _has_bit(7);
}
inline void mp_rect_region::clear_pallet_length() {
  pallet_length_ = 0;
  _clear_bit(7);
}
inline float mp_rect_region::pallet_length() const {
  return pallet_length_;
}
inline void mp_rect_region::set_pallet_length(float value) {
  _set_bit(7);
  pallet_length_ = value;
}

// required float pallet_width = 9;
inline bool mp_rect_region::has_pallet_width() const {
  return _has_bit(8);
}
inline void mp_rect_region::clear_pallet_width() {
  pallet_width_ = 0;
  _clear_bit(8);
}
inline float mp_rect_region::pallet_width() const {
  return pallet_width_;
}
inline void mp_rect_region::set_pallet_width(float value) {
  _set_bit(8);
  pallet_width_ = value;
}

// optional float pallet_height = 10;
inline bool mp_rect_region::has_pallet_height() const {
  return _has_bit(9);
}
inline void mp_rect_region::clear_pallet_height() {
  pallet_height_ = 0;
  _clear_bit(9);
}
inline float mp_rect_region::pallet_height() const {
  return pallet_height_;
}
inline void mp_rect_region::set_pallet_height(float value) {
  _set_bit(9);
  pallet_height_ = value;
}

// required float row_spacing = 11;
inline bool mp_rect_region::has_row_spacing() const {
  return _has_bit(10);
}
inline void mp_rect_region::clear_row_spacing() {
  row_spacing_ = 0;
  _clear_bit(10);
}
inline float mp_rect_region::row_spacing() const {
  return row_spacing_;
}
inline void mp_rect_region::set_row_spacing(float value) {
  _set_bit(10);
  row_spacing_ = value;
}

// required float col_spacing = 12;
inline bool mp_rect_region::has_col_spacing() const {
  return _has_bit(11);
}
inline void mp_rect_region::clear_col_spacing() {
  col_spacing_ = 0;
  _clear_bit(11);
}
inline float mp_rect_region::col_spacing() const {
  return col_spacing_;
}
inline void mp_rect_region::set_col_spacing(float value) {
  _set_bit(11);
  col_spacing_ = value;
}

// repeated .KPS.mp_pos_data pallet_pos = 13;
inline int mp_rect_region::pallet_pos_size() const {
  return pallet_pos_.size();
}
inline void mp_rect_region::clear_pallet_pos() {
  pallet_pos_.Clear();
}
inline const ::KPS::mp_pos_data& mp_rect_region::pallet_pos(int index) const {
  return pallet_pos_.Get(index);
}
inline ::KPS::mp_pos_data* mp_rect_region::mutable_pallet_pos(int index) {
  return pallet_pos_.Mutable(index);
}
inline ::KPS::mp_pos_data* mp_rect_region::add_pallet_pos() {
  return pallet_pos_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::KPS::mp_pos_data >&
mp_rect_region::pallet_pos() const {
  return pallet_pos_;
}
inline ::google::protobuf::RepeatedPtrField< ::KPS::mp_pos_data >*
mp_rect_region::mutable_pallet_pos() {
  return &pallet_pos_;
}

// optional string para = 14;
inline bool mp_rect_region::has_para() const {
  return _has_bit(13);
}
inline void mp_rect_region::clear_para() {
  if (para_ != &_default_para_) {
    para_->clear();
  }
  _clear_bit(13);
}
inline const ::std::string& mp_rect_region::para() const {
  return *para_;
}
inline void mp_rect_region::set_para(const ::std::string& value) {
  _set_bit(13);
  if (para_ == &_default_para_) {
    para_ = new ::std::string;
  }
  para_->assign(value);
}
inline void mp_rect_region::set_para(const char* value) {
  _set_bit(13);
  if (para_ == &_default_para_) {
    para_ = new ::std::string;
  }
  para_->assign(value);
}
inline void mp_rect_region::set_para(const char* value, size_t size) {
  _set_bit(13);
  if (para_ == &_default_para_) {
    para_ = new ::std::string;
  }
  para_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_rect_region::mutable_para() {
  _set_bit(13);
  if (para_ == &_default_para_) {
    para_ = new ::std::string;
  }
  return para_;
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

#endif  // PROTOBUF_rect_2eproto__INCLUDED

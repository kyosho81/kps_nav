// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: lab.proto

#ifndef PROTOBUF_lab_2eproto__INCLUDED
#define PROTOBUF_lab_2eproto__INCLUDED

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
void  protobuf_AddDesc_lab_2eproto();
void protobuf_AssignDesc_lab_2eproto();
void protobuf_ShutdownFile_lab_2eproto();

class mp_lab;

// ===================================================================

class mp_lab : public ::google::protobuf::Message {
 public:
  mp_lab();
  virtual ~mp_lab();
  
  mp_lab(const mp_lab& from);
  
  inline mp_lab& operator=(const mp_lab& from) {
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
  static const mp_lab& default_instance();
  
  void Swap(mp_lab* other);
  
  // implements Message ----------------------------------------------
  
  mp_lab* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const mp_lab& from);
  void MergeFrom(const mp_lab& from);
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
  
  // required float x = 2;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 2;
  inline float x() const;
  inline void set_x(float value);
  
  // required float y = 3;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 3;
  inline float y() const;
  inline void set_y(float value);
  
  // required string lab = 4;
  inline bool has_lab() const;
  inline void clear_lab();
  static const int kLabFieldNumber = 4;
  inline const ::std::string& lab() const;
  inline void set_lab(const ::std::string& value);
  inline void set_lab(const char* value);
  inline void set_lab(const char* value, size_t size);
  inline ::std::string* mutable_lab();
  
  // required uint32 show = 5;
  inline bool has_show() const;
  inline void clear_show();
  static const int kShowFieldNumber = 5;
  inline ::google::protobuf::uint32 show() const;
  inline void set_show(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:KPS.mp_lab)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 id_;
  float x_;
  float y_;
  ::std::string* lab_;
  static const ::std::string _default_lab_;
  ::google::protobuf::uint32 show_;
  friend void  protobuf_AddDesc_lab_2eproto();
  friend void protobuf_AssignDesc_lab_2eproto();
  friend void protobuf_ShutdownFile_lab_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
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
  static mp_lab* default_instance_;
};
// ===================================================================


// ===================================================================

// mp_lab

// required uint32 id = 1;
inline bool mp_lab::has_id() const {
  return _has_bit(0);
}
inline void mp_lab::clear_id() {
  id_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 mp_lab::id() const {
  return id_;
}
inline void mp_lab::set_id(::google::protobuf::uint32 value) {
  _set_bit(0);
  id_ = value;
}

// required float x = 2;
inline bool mp_lab::has_x() const {
  return _has_bit(1);
}
inline void mp_lab::clear_x() {
  x_ = 0;
  _clear_bit(1);
}
inline float mp_lab::x() const {
  return x_;
}
inline void mp_lab::set_x(float value) {
  _set_bit(1);
  x_ = value;
}

// required float y = 3;
inline bool mp_lab::has_y() const {
  return _has_bit(2);
}
inline void mp_lab::clear_y() {
  y_ = 0;
  _clear_bit(2);
}
inline float mp_lab::y() const {
  return y_;
}
inline void mp_lab::set_y(float value) {
  _set_bit(2);
  y_ = value;
}

// required string lab = 4;
inline bool mp_lab::has_lab() const {
  return _has_bit(3);
}
inline void mp_lab::clear_lab() {
  if (lab_ != &_default_lab_) {
    lab_->clear();
  }
  _clear_bit(3);
}
inline const ::std::string& mp_lab::lab() const {
  return *lab_;
}
inline void mp_lab::set_lab(const ::std::string& value) {
  _set_bit(3);
  if (lab_ == &_default_lab_) {
    lab_ = new ::std::string;
  }
  lab_->assign(value);
}
inline void mp_lab::set_lab(const char* value) {
  _set_bit(3);
  if (lab_ == &_default_lab_) {
    lab_ = new ::std::string;
  }
  lab_->assign(value);
}
inline void mp_lab::set_lab(const char* value, size_t size) {
  _set_bit(3);
  if (lab_ == &_default_lab_) {
    lab_ = new ::std::string;
  }
  lab_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* mp_lab::mutable_lab() {
  _set_bit(3);
  if (lab_ == &_default_lab_) {
    lab_ = new ::std::string;
  }
  return lab_;
}

// required uint32 show = 5;
inline bool mp_lab::has_show() const {
  return _has_bit(4);
}
inline void mp_lab::clear_show() {
  show_ = 0u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 mp_lab::show() const {
  return show_;
}
inline void mp_lab::set_show(::google::protobuf::uint32 value) {
  _set_bit(4);
  show_ = value;
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

#endif  // PROTOBUF_lab_2eproto__INCLUDED

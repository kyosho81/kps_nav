// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: action.proto

#ifndef PROTOBUF_action_2eproto__INCLUDED
#define PROTOBUF_action_2eproto__INCLUDED

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
#include "lab.pb.h"
// @@protoc_insertion_point(includes)

namespace KPS {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_action_2eproto();
void protobuf_AssignDesc_action_2eproto();
void protobuf_ShutdownFile_action_2eproto();

class s_action;

// ===================================================================

class s_action : public ::google::protobuf::Message {
 public:
  s_action();
  virtual ~s_action();
  
  s_action(const s_action& from);
  
  inline s_action& operator=(const s_action& from) {
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
  static const s_action& default_instance();
  
  void Swap(s_action* other);
  
  // implements Message ----------------------------------------------
  
  s_action* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const s_action& from);
  void MergeFrom(const s_action& from);
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
  
  // required string action_type_nm = 2;
  inline bool has_action_type_nm() const;
  inline void clear_action_type_nm();
  static const int kActionTypeNmFieldNumber = 2;
  inline const ::std::string& action_type_nm() const;
  inline void set_action_type_nm(const ::std::string& value);
  inline void set_action_type_nm(const char* value);
  inline void set_action_type_nm(const char* value, size_t size);
  inline ::std::string* mutable_action_type_nm();
  
  // repeated string action_name_para = 3;
  inline int action_name_para_size() const;
  inline void clear_action_name_para();
  static const int kActionNameParaFieldNumber = 3;
  inline const ::std::string& action_name_para(int index) const;
  inline ::std::string* mutable_action_name_para(int index);
  inline void set_action_name_para(int index, const ::std::string& value);
  inline void set_action_name_para(int index, const char* value);
  inline void set_action_name_para(int index, const char* value, size_t size);
  inline ::std::string* add_action_name_para();
  inline void add_action_name_para(const ::std::string& value);
  inline void add_action_name_para(const char* value);
  inline void add_action_name_para(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& action_name_para() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_action_name_para();
  
  // @@protoc_insertion_point(class_scope:KPS.s_action)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::KPS::mp_item_base* base_;
  ::std::string* action_type_nm_;
  static const ::std::string _default_action_type_nm_;
  ::google::protobuf::RepeatedPtrField< ::std::string> action_name_para_;
  friend void  protobuf_AddDesc_action_2eproto();
  friend void protobuf_AssignDesc_action_2eproto();
  friend void protobuf_ShutdownFile_action_2eproto();
  
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
  static s_action* default_instance_;
};
// ===================================================================


// ===================================================================

// s_action

// required .KPS.mp_item_base base = 1;
inline bool s_action::has_base() const {
  return _has_bit(0);
}
inline void s_action::clear_base() {
  if (base_ != NULL) base_->::KPS::mp_item_base::Clear();
  _clear_bit(0);
}
inline const ::KPS::mp_item_base& s_action::base() const {
  return base_ != NULL ? *base_ : *default_instance_->base_;
}
inline ::KPS::mp_item_base* s_action::mutable_base() {
  _set_bit(0);
  if (base_ == NULL) base_ = new ::KPS::mp_item_base;
  return base_;
}

// required string action_type_nm = 2;
inline bool s_action::has_action_type_nm() const {
  return _has_bit(1);
}
inline void s_action::clear_action_type_nm() {
  if (action_type_nm_ != &_default_action_type_nm_) {
    action_type_nm_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& s_action::action_type_nm() const {
  return *action_type_nm_;
}
inline void s_action::set_action_type_nm(const ::std::string& value) {
  _set_bit(1);
  if (action_type_nm_ == &_default_action_type_nm_) {
    action_type_nm_ = new ::std::string;
  }
  action_type_nm_->assign(value);
}
inline void s_action::set_action_type_nm(const char* value) {
  _set_bit(1);
  if (action_type_nm_ == &_default_action_type_nm_) {
    action_type_nm_ = new ::std::string;
  }
  action_type_nm_->assign(value);
}
inline void s_action::set_action_type_nm(const char* value, size_t size) {
  _set_bit(1);
  if (action_type_nm_ == &_default_action_type_nm_) {
    action_type_nm_ = new ::std::string;
  }
  action_type_nm_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* s_action::mutable_action_type_nm() {
  _set_bit(1);
  if (action_type_nm_ == &_default_action_type_nm_) {
    action_type_nm_ = new ::std::string;
  }
  return action_type_nm_;
}

// repeated string action_name_para = 3;
inline int s_action::action_name_para_size() const {
  return action_name_para_.size();
}
inline void s_action::clear_action_name_para() {
  action_name_para_.Clear();
}
inline const ::std::string& s_action::action_name_para(int index) const {
  return action_name_para_.Get(index);
}
inline ::std::string* s_action::mutable_action_name_para(int index) {
  return action_name_para_.Mutable(index);
}
inline void s_action::set_action_name_para(int index, const ::std::string& value) {
  action_name_para_.Mutable(index)->assign(value);
}
inline void s_action::set_action_name_para(int index, const char* value) {
  action_name_para_.Mutable(index)->assign(value);
}
inline void s_action::set_action_name_para(int index, const char* value, size_t size) {
  action_name_para_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* s_action::add_action_name_para() {
  return action_name_para_.Add();
}
inline void s_action::add_action_name_para(const ::std::string& value) {
  action_name_para_.Add()->assign(value);
}
inline void s_action::add_action_name_para(const char* value) {
  action_name_para_.Add()->assign(value);
}
inline void s_action::add_action_name_para(const char* value, size_t size) {
  action_name_para_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
s_action::action_name_para() const {
  return action_name_para_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
s_action::mutable_action_name_para() {
  return &action_name_para_;
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

#endif  // PROTOBUF_action_2eproto__INCLUDED
